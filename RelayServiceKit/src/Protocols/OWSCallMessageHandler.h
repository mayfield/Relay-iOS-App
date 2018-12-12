//  Created by Michael Kirk on 12/4/16.
//  Copyright © 2016 Open Whisper Systems. All rights reserved.

NS_ASSUME_NONNULL_BEGIN

@class OWSSignalServiceProtosCallMessageOffer;
@class OWSSignalServiceProtosCallMessageAnswer;
@class OWSSignalServiceProtosCallMessageIceUpdate;
@class OWSSignalServiceProtosCallMessageHangup;
@class OWSSignalServiceProtosCallMessageBusy;

@protocol OWSCallMessageHandler <NSObject>

-(void)receivedOfferWithThreadId:(NSString *)threadId
                          callId:(NSString *)callId
                    originatorId:(NSString *)originatorId
                          peerId:(NSString *)peerId
              sessionDescription:(NSString *)sessionDescription;
//- (void)receivedOffer:(OWSSignalServiceProtosCallMessageOffer *)offer
//         fromCallerId:(NSString *)callerId NS_SWIFT_NAME(receivedOffer(_:from:));

-(void)receivedAnswerWithThreadId:(NSString *)threadId
                        callId:(NSString *)callId
                        peerId:(NSString *)peerId
            sessionDescription:(NSString *)sessionDescription;
//- (void)receivedAnswer:(OWSSignalServiceProtosCallMessageAnswer *)answer
//          fromCallerId:(NSString *)callerId NS_SWIFT_NAME(receivedAnswer(_:from:));

-(void)receivedIceUpdateWithThreadId:(NSString *)threadId
                  sessionDescription:(NSString *)sdp
                              sdpMid:(NSString *)sdpMid
                       sdpMLineIndex:(int32_t)sdpMLineIndex;
//- (void)receivedIceUpdate:(OWSSignalServiceProtosCallMessageIceUpdate *)iceUpdate
//             fromCallerId:(NSString *)callerId NS_SWIFT_NAME(receivedIceUpdate(_:from:));

-(void)receivedHangupWithThreadId:(NSString *)threadId callId:(NSString *)callId;
//- (void)receivedHangup:(OWSSignalServiceProtosCallMessageHangup *)hangup
//          fromCallerId:(NSString *)callerId NS_SWIFT_NAME(receivedHangup(_:from:));

- (void)receivedBusy:(OWSSignalServiceProtosCallMessageBusy *)busy
        fromCallerId:(NSString *)callerId NS_SWIFT_NAME(receivedBusy(_:from:));

@end

NS_ASSUME_NONNULL_END
