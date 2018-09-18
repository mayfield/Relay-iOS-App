//
//  FLContactsManager.swift
//  RelayMessaging
//
//  Created by Mark Descalzo on 8/14/18.
//  Copyright © 2018 Open Whisper Systems. All rights reserved.
//

import Foundation
import YapDatabase
import RelayServiceKit

@objc public class FLContactsManager: NSObject {
    
    @objc public static let shared = FLContactsManager()
    
    @objc public var allRecipients: [RelayRecipient] = []
    @objc public var activeRecipients: [RelayRecipient] = []
    
    private let readConnection: YapDatabaseConnection = { return OWSPrimaryStorage.shared().dbReadConnection }()
    private let readWriteConnection: YapDatabaseConnection = { return OWSPrimaryStorage.shared().dbReadWriteConnection }()
    private var latestRecipientsById: [AnyHashable : Any] = [:]
    private var activeRecipientsBacker: [ RelayRecipient ] = []
    private var visibleRecipientsPredicate: NSCompoundPredicate?
    
    private let avatarCache: NSCache<NSString, UIImage>
    private let recipientCache: NSCache<NSString, RelayRecipient>
    private let tagCache: NSCache<NSString, FLTag>

    // TODO: require for gravatar implementation
//    private var prefs: PropertyListPreferences?

    override init() {
        avatarCache = NSCache<NSString, UIImage>()
        recipientCache = NSCache<NSString, RelayRecipient>()
        tagCache = NSCache<NSString, FLTag>()

        super.init()

        // Prepopulate the caches?
//        DispatchQueue.global(qos: .default).async(execute: {
//            self.readConnection.asyncRead({ transaction in
//                RelayRecipient.enumerateCollectionObjects(with: transaction, using: { object, stop in
//                    if let recipient = object as? RelayRecipient {
//                        self.recipientCache.setObject(recipient, forKey: recipient.uniqueId! as NSString)
//                    }
//                })
//                FLTag.enumerateCollectionObjects(with: transaction, using: { object, stop in
//                    if let aTag = object as? FLTag {
//                        self.tagCache.setObject(aTag, forKey: aTag.uniqueId! as NSString)
//                    }
//                })
//            })
//        })

        NotificationCenter.default.addObserver(self, selector: #selector(self.processRecipientsBlob), name: NSNotification.Name(rawValue: FLCCSMUsersUpdated), object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(self.processTagsBlob), name: NSNotification.Name(rawValue: FLCCSMTagsUpdated), object: nil)


        avatarCache.delegate = self
        recipientCache.delegate = self
        tagCache.delegate = self
    }
    
    deinit {
        NotificationCenter.default.removeObserver(self)
    }
    
    @objc public func selfRecipient() -> RelayRecipient {
        let selfId = TSAccountManager.localUID()! as NSString
        var recipient:RelayRecipient? = recipientCache.object(forKey: selfId)
        
        if recipient == nil {
            recipient = RelayRecipient.fetch(uniqueId: selfId as String)
            recipientCache .setObject(recipient!, forKey: selfId)
        }
        return recipient!
    }
    
    @objc public class func recipientComparator() -> Comparator {
        return { obj1, obj2 in
            let contact1 = obj1 as? RelayRecipient
            let contact2 = obj2 as? RelayRecipient
            
            // Use lastname sorting
//            let firstNameOrdering = false // ABPersonGetSortOrdering() == kABPersonCompositeNameFormatFirstNameFirst ? YES : NO;
//
//            if firstNameOrdering {
//                return (contact1?.firstName.caseInsensitiveCompare(contact2?.firstName ?? ""))!
//            } else {
            return (contact1?.lastName!.caseInsensitiveCompare(contact2?.lastName ?? ""))!
//            }
        }    }
        
    @objc public func doAfterEnvironmentInitSetup() {
    }
    
    @objc public func updateRecipient(userId: String) {
            self.readWriteConnection.asyncReadWrite { (transaction) in
                self.updateRecipient(userId: userId, with: transaction)
            }
    }
    
    fileprivate func updateRecipient(userId: String, with transaction: YapDatabaseReadWriteTransaction) {
        
        if let updateDict:Dictionary<String, Any> = ccsmFetchRecipientDictionary(userId: userId) {
            if let recipient = recipient(fromDictionary: updateDict, transaction: transaction) {
                save(recipient: recipient, with: transaction)
            }
        }
    }
    
    fileprivate func ccsmFetchRecipientDictionary(userId: String) -> Dictionary<String, Any>? {
        
        // must not execute on main thread
        assert(!Thread.isMainThread)
        
        var result: Dictionary<String, Any>?
        
        let url = "\(CCSMEnvironment.sharedInstance().ccsmURLString!)/v1/directory/user/?id=\(userId)"
        
        let semaphore = DispatchSemaphore(value: 0)
        
        CCSMCommManager.getThing(url,
                                 success: { (payload) in
                                    
                                    if let resultsArray: Array = payload?["results"] as? Array<Dictionary<String, Any>> {
                                        result = resultsArray.last
                                    }
                                    semaphore.signal()
        }, failure: { (error) in
            Logger.debug("CCSM User lookup failed.")
            semaphore.signal()
        })
        
        let timeout = DispatchTime.now() + .seconds(3)
        if semaphore.wait(timeout: timeout) == .timedOut {
            Logger.debug("CCSM user lookup timed out.")
        }
        return result
    }
    
    @objc public func recipient(withId userId: String) -> RelayRecipient? {
        
        // Check the cache
        var recipient:RelayRecipient? = recipientCache.object(forKey: userId as NSString)
        
        // Check the db
        if recipient == nil {
            self.readWriteConnection.readWrite { (transaction) in
                recipient = self.recipient(withId: userId, transaction: transaction)
            }
        }
        
        return recipient
    }
    
    @objc public func recipient(withId userId: String, transaction: YapDatabaseReadWriteTransaction) -> RelayRecipient? {
        
        var recipient: RelayRecipient? = RelayRecipient.fetch(uniqueId: userId, transaction: transaction)
        
        if recipient == nil {
            
            let semaphore = DispatchSemaphore(value: 0)
            
            DispatchQueue.global(qos: .background).async {
                if let userDict = self.ccsmFetchRecipientDictionary(userId: userId) {
                        recipient = self.recipient(fromDictionary: userDict, transaction: transaction)
                }
                semaphore.signal()
            }
            let timeout = DispatchTime.now() + .seconds(3)
            if semaphore.wait(timeout: timeout) == .timedOut {
                Logger.debug("CCSM user lookup timed out.")
            }
        }
        
        if recipient != nil {
            recipientCache.setObject(recipient!, forKey: userId as NSString)
        }
        
        return recipient
    }

    @objc public func recipient(fromDictionary userDict: Dictionary<String, Any>) -> RelayRecipient? {
        var recipient: RelayRecipient? = nil
        self.readWriteConnection.readWrite({ transaction in
            recipient = self.recipient(fromDictionary: userDict, transaction: transaction)
        })
        return recipient
    }
    
    func recipient(fromDictionary userDict: Dictionary<String, Any>, transaction: YapDatabaseReadWriteTransaction) -> RelayRecipient? {

        guard let uuid = NSUUID.init(uuidString:(userDict["id"] as? String)!) else {
           Logger.debug("Attempt to build recipient with malformed dictionary.")
            return nil
        }
        
        guard let tagDict = userDict["tag"] as? [AnyHashable : Any] else {
            Logger.debug("Missing tagDictionary for Recipient: \(uuid.uuidString)")
            return nil
        }

        let uidString = uuid.uuidString
        
        let recipient = RelayRecipient.getOrBuildUnsavedRecipient(forRecipientId: uidString, transaction: transaction)
        
        recipient.isActive = (Int(truncating: userDict["is_active"] as? NSNumber ?? 0)) == 1 ? true : false
        if !recipient.isActive {
            Logger.info("Removing inactive user: \(uidString)")
            self.remove(recipient: recipient, with: transaction)
            return nil
        }
        
        recipient.firstName = userDict["first_name"] as? String
        recipient.lastName = userDict["last_name"] as? String
        recipient.email = userDict["email"] as? String
        recipient.phoneNumber = userDict["phone"] as? String
        recipient.gravatarHash = userDict["gravatar_hash"] as? String
        recipient.isMonitor = (Int(truncating: userDict["is_monitor"] as? NSNumber ?? 0)) == 1 ? true : false
        
        let orgDict = userDict["org"] as? [AnyHashable : Any]
        if orgDict != nil {
            recipient.orgID = orgDict!["id"] as? String
            recipient.orgSlug = orgDict!["slug"] as? String
        } else {
            Logger.debug("Missing orgDictionary for Recipient: \(self.description)")
        }
        recipient.flTag = FLTag.getOrCreateTag(with: tagDict, transaction: transaction)
        recipient.flTag?.recipientIds = Set<AnyHashable>([recipient.uniqueId]) as? NSCountedSet
        if recipient.flTag?.tagDescription?.count == 0 {
            recipient.flTag?.tagDescription = recipient.fullName()
        }
        if recipient.flTag?.orgSlug.count == 0 {
            recipient.flTag?.orgSlug = recipient.orgSlug!
        }
        if recipient.flTag == nil {
            Logger.error("Attempt to create recipient with a nil tag!  Recipient: \(recipient.uniqueId)")
            self.remove(recipient: recipient, with: transaction)
            return nil
//        } else {
//            Logger.debug("Saving updated recipient: \(recipient.uniqueId)")
//            self.save(recipient: recipient, with: transaction)
        }
        
        return recipient
    }

    
    @objc public func refreshCCSMRecipients() {
        DispatchQueue.global(qos: .background).async {
            self.recipientCache.removeAllObjects()
            self.tagCache.removeAllObjects()
            CCSMCommManager.refreshCCSMData()
            self.validateNonOrgRecipients()
        }
    }
    
    private func validateNonOrgRecipients() {
        for obj in RelayRecipient.allObjectsInCollection() {
            if let recipient = obj as? RelayRecipient {
                if recipient.orgID != TSAccountManager.selfRecipient().orgID ||
                   recipient.orgID == "public" ||
                   recipient.orgID == "forsta" {
                    self.updateRecipient(userId: recipient.uniqueId)
                }
            }
        }
    }

    
    @objc public func setImage(image: UIImage, recipientId: String) {
        if let recipient = self.recipient(withId: recipientId) {
            recipient.avatar = image
            self.avatarCache.setObject(image, forKey: recipientId as NSString)
        }
    }
    
    @objc public func image(forRecipientId uid: String) -> UIImage? {
        // TODO: implement gravatars here
        var image: UIImage? = nil
        var cacheKey: NSString? = nil
        
        // if using gravatars
        // cacheKey = "gravatar:\(uid)"
        // else
        cacheKey = "avatar:\(uid)" as NSString
        image = self.avatarCache.object(forKey: cacheKey!)
        
        if image == nil {
            image = self.recipient(withId: uid)?.avatar
            if image != nil {
                self.avatarCache.setObject(image!, forKey: cacheKey!)
            }
        }
        return image
    }
    
    @objc public func nameString(forRecipientId uid: String) -> String? {
        if let recipient:RelayRecipient = self.recipient(withId: uid) {
            if recipient.fullName().count > 0 {
                return recipient.fullName()
            } else if (recipient.flTag?.displaySlug.count)! > 0 {
                return recipient.flTag?.displaySlug
            }
        }
        return NSLocalizedString("UNKNOWN_CONTACT_NAME", comment: "Displayed if for some reason we can't determine a contacts ID *or* name");
    }
    
    // MARK: - Recipient management
    @objc public func processRecipientsBlob() {
        let recipientsBlob: NSDictionary = CCSMStorage.sharedInstance().getUsers()! as NSDictionary
        DispatchQueue.global(qos: .background).async {
            for recipientDict in recipientsBlob.allValues {
                self.readWriteConnection.asyncReadWrite({ (transaction) in
                    if let recipient: RelayRecipient = RelayRecipient.getOrCreateRecipient(withUserDictionary: recipientDict as! NSDictionary, transaction: transaction) {
                        self.save(recipient: recipient, with: transaction)
                    }
                })
            }
        }
    }

    @objc public func save(recipient: RelayRecipient) {
        self.readWriteConnection .readWrite { (transaction) in
            self.save(recipient: recipient, with: transaction)
        }
    }
    
    @objc public func save(recipient: RelayRecipient, with transaction: YapDatabaseReadWriteTransaction) {
        recipient.save(with: transaction)
        if let aTag = recipient.flTag {
            aTag.save(with: transaction)
        }
        self.recipientCache.setObject(recipient, forKey: recipient.uniqueId as NSString)
    }
    
    @objc public func remove(recipient: RelayRecipient) {
        self.readWriteConnection .readWrite { (transaction) in
            self.remove(recipient: recipient, with: transaction)
        }
    }
    
    @objc public func remove(recipient: RelayRecipient, with transaction: YapDatabaseReadWriteTransaction) {
        self.recipientCache.removeObject(forKey: recipient.uniqueId as NSString)
        if let aTag = recipient.flTag {
            aTag.remove(with: transaction)
        }
        recipient.remove(with: transaction)
    }
    
    // MARK: - Tag management
    @objc public func processTagsBlob() {
        let tagsBlob: NSDictionary = CCSMStorage.sharedInstance().getTags()! as NSDictionary
        DispatchQueue.global(qos: .background).async {
            for tagDict in tagsBlob.allValues {
                self.readWriteConnection.asyncReadWrite({ (transaction) in
                    let aTag:FLTag = FLTag.getOrCreateTag(with: tagDict as! [AnyHashable : Any], transaction: transaction)!
                    if aTag.recipientIds?.count == 0 {
                        self.remove(tag: aTag, with: transaction)
                    } else {
                        self.save(tag: aTag, with: transaction)
                    }
                })
            }
        }
    }

    @objc public func save(tag: FLTag) {
        self.readWriteConnection.readWrite { (transaction) in
            self.save(tag: tag, with: transaction)
        }
    }
    
    @objc public func save(tag: FLTag, with transaction: YapDatabaseReadWriteTransaction) {
        tag.save(with: transaction)
        self.tagCache.setObject(tag, forKey: tag.uniqueId as NSString)
    }
    
    @objc public func remove(tag: FLTag) {
        self.readWriteConnection.readWrite { (transaction) in
            self.remove(tag: tag, with: transaction)
        }
    }
    
    @objc public func remove(tag: FLTag, with transaction: YapDatabaseReadWriteTransaction) {
        self.tagCache.removeObject(forKey: tag.uniqueId as NSString)
        tag.remove(with: transaction)
    }
    

    @objc func nukeAndPave() {
        self.tagCache.removeAllObjects()
        self.recipientCache.removeAllObjects()
        RelayRecipient.removeAllObjectsInCollection()
        FLTag.removeAllObjectsInCollection()
    }
    
    // MARK: - Helpers

}



extension FLContactsManager : NSCacheDelegate {

    public func cache(_ cache: NSCache<AnyObject, AnyObject>, willEvictObject obj: Any) {
        // called when objects evicted from any of the caches
    }
}
