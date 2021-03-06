// Generated by the protocol buffer compiler.  DO NOT EDIT!

#import <ProtocolBuffers/ProtocolBuffers.h>

// @@protoc_insertion_point(imports)

@class OWSProvisioningProtosProvisionEnvelope;
@class OWSProvisioningProtosProvisionEnvelopeBuilder;
@class OWSProvisioningProtosProvisionMessage;
@class OWSProvisioningProtosProvisionMessageBuilder;
@class OWSProvisioningProtosProvisioningUuid;
@class OWSProvisioningProtosProvisioningUuidBuilder;
@class ObjectiveCFileOptions;
@class ObjectiveCFileOptionsBuilder;
@class PBDescriptorProto;
@class PBDescriptorProtoBuilder;
@class PBDescriptorProtoExtensionRange;
@class PBDescriptorProtoExtensionRangeBuilder;
@class PBEnumDescriptorProto;
@class PBEnumDescriptorProtoBuilder;
@class PBEnumOptions;
@class PBEnumOptionsBuilder;
@class PBEnumValueDescriptorProto;
@class PBEnumValueDescriptorProtoBuilder;
@class PBEnumValueOptions;
@class PBEnumValueOptionsBuilder;
@class PBFieldDescriptorProto;
@class PBFieldDescriptorProtoBuilder;
@class PBFieldOptions;
@class PBFieldOptionsBuilder;
@class PBFileDescriptorProto;
@class PBFileDescriptorProtoBuilder;
@class PBFileDescriptorSet;
@class PBFileDescriptorSetBuilder;
@class PBFileOptions;
@class PBFileOptionsBuilder;
@class PBMessageOptions;
@class PBMessageOptionsBuilder;
@class PBMethodDescriptorProto;
@class PBMethodDescriptorProtoBuilder;
@class PBMethodOptions;
@class PBMethodOptionsBuilder;
@class PBOneofDescriptorProto;
@class PBOneofDescriptorProtoBuilder;
@class PBServiceDescriptorProto;
@class PBServiceDescriptorProtoBuilder;
@class PBServiceOptions;
@class PBServiceOptionsBuilder;
@class PBSourceCodeInfo;
@class PBSourceCodeInfoBuilder;
@class PBSourceCodeInfoLocation;
@class PBSourceCodeInfoLocationBuilder;
@class PBUninterpretedOption;
@class PBUninterpretedOptionBuilder;
@class PBUninterpretedOptionNamePart;
@class PBUninterpretedOptionNamePartBuilder;



@interface OWSProvisioningProtosOwsprovisioningProtosRoot : NSObject {
}
+ (PBExtensionRegistry*) extensionRegistry;
+ (void) registerAllExtensions:(PBMutableExtensionRegistry*) registry;
@end

#define ProvisionEnvelope_publicKey @"publicKey"
#define ProvisionEnvelope_body @"body"
@interface OWSProvisioningProtosProvisionEnvelope : PBGeneratedMessage<GeneratedMessageProtocol> {
@private
  BOOL hasPublicKey_:1;
  BOOL hasBody_:1;
  NSData* publicKey;
  NSData* body;
}
- (BOOL) hasPublicKey;
- (BOOL) hasBody;
@property (readonly, strong) NSData* publicKey;
@property (readonly, strong) NSData* body;

+ (instancetype) defaultInstance;
- (instancetype) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (OWSProvisioningProtosProvisionEnvelopeBuilder*) builder;
+ (OWSProvisioningProtosProvisionEnvelopeBuilder*) builder;
+ (OWSProvisioningProtosProvisionEnvelopeBuilder*) builderWithPrototype:(OWSProvisioningProtosProvisionEnvelope*) prototype;
- (OWSProvisioningProtosProvisionEnvelopeBuilder*) toBuilder;

+ (OWSProvisioningProtosProvisionEnvelope*) parseFromData:(NSData*) data;
+ (OWSProvisioningProtosProvisionEnvelope*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (OWSProvisioningProtosProvisionEnvelope*) parseFromInputStream:(NSInputStream*) input;
+ (OWSProvisioningProtosProvisionEnvelope*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (OWSProvisioningProtosProvisionEnvelope*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (OWSProvisioningProtosProvisionEnvelope*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface OWSProvisioningProtosProvisionEnvelopeBuilder : PBGeneratedMessageBuilder {
@private
  OWSProvisioningProtosProvisionEnvelope* resultProvisionEnvelope;
}

- (OWSProvisioningProtosProvisionEnvelope*) defaultInstance;

- (OWSProvisioningProtosProvisionEnvelopeBuilder*) clear;
- (OWSProvisioningProtosProvisionEnvelopeBuilder*) clone;

- (OWSProvisioningProtosProvisionEnvelope*) build;
- (OWSProvisioningProtosProvisionEnvelope*) buildPartial;

- (OWSProvisioningProtosProvisionEnvelopeBuilder*) mergeFrom:(OWSProvisioningProtosProvisionEnvelope*) other;
- (OWSProvisioningProtosProvisionEnvelopeBuilder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (OWSProvisioningProtosProvisionEnvelopeBuilder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasPublicKey;
- (NSData*) publicKey;
- (OWSProvisioningProtosProvisionEnvelopeBuilder*) setPublicKey:(NSData*) value;
- (OWSProvisioningProtosProvisionEnvelopeBuilder*) clearPublicKey;

- (BOOL) hasBody;
- (NSData*) body;
- (OWSProvisioningProtosProvisionEnvelopeBuilder*) setBody:(NSData*) value;
- (OWSProvisioningProtosProvisionEnvelopeBuilder*) clearBody;
@end

#define ProvisioningUuid_uuid @"uuid"
@interface OWSProvisioningProtosProvisioningUuid : PBGeneratedMessage<GeneratedMessageProtocol> {
@private
    BOOL hasUuid_:1;
    NSString* uuid;
}
- (BOOL) hasUuid;
@property (readonly, strong) NSString* uuid;

+ (instancetype) defaultInstance;
- (instancetype) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (OWSProvisioningProtosProvisioningUuidBuilder*) builder;
+ (OWSProvisioningProtosProvisioningUuidBuilder*) builder;
+ (OWSProvisioningProtosProvisioningUuidBuilder*) builderWithPrototype:(OWSProvisioningProtosProvisioningUuid*) prototype;
- (OWSProvisioningProtosProvisioningUuidBuilder*) toBuilder;

+ (OWSProvisioningProtosProvisioningUuid*) parseFromData:(NSData*) data;
+ (OWSProvisioningProtosProvisioningUuid*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (OWSProvisioningProtosProvisioningUuid*) parseFromInputStream:(NSInputStream*) input;
+ (OWSProvisioningProtosProvisioningUuid*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (OWSProvisioningProtosProvisioningUuid*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (OWSProvisioningProtosProvisioningUuid*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface OWSProvisioningProtosProvisioningUuidBuilder : PBGeneratedMessageBuilder {
@private
    OWSProvisioningProtosProvisioningUuid* resultProvisioningUuid;
}

- (OWSProvisioningProtosProvisioningUuid*) defaultInstance;

- (OWSProvisioningProtosProvisioningUuidBuilder*) clear;
- (OWSProvisioningProtosProvisioningUuidBuilder*) clone;

- (OWSProvisioningProtosProvisioningUuid*) build;
- (OWSProvisioningProtosProvisioningUuid*) buildPartial;

- (OWSProvisioningProtosProvisioningUuidBuilder*) mergeFrom:(OWSProvisioningProtosProvisioningUuid*) other;
- (OWSProvisioningProtosProvisioningUuidBuilder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (OWSProvisioningProtosProvisioningUuidBuilder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasUuid;
- (NSString*) uuid;
- (OWSProvisioningProtosProvisioningUuidBuilder*) setUuid:(NSString*) value;
- (OWSProvisioningProtosProvisioningUuidBuilder*) clearUuid;
@end

#define ProvisionMessage_identityKeyPublic @"identityKeyPublic"
#define ProvisionMessage_identityKeyPrivate @"identityKeyPrivate"
#define ProvisionMessage_number @"number"
#define ProvisionMessage_provisioningCode @"provisioningCode"
#define ProvisionMessage_userAgent @"userAgent"
#define ProvisionMessage_profileKey @"profileKey"
#define ProvisionMessage_readReceipts @"readReceipts"
@interface OWSProvisioningProtosProvisionMessage : PBGeneratedMessage<GeneratedMessageProtocol> {
@private
  BOOL hasReadReceipts_:1;
  BOOL hasNumber_:1;
  BOOL hasProvisioningCode_:1;
  BOOL hasUserAgent_:1;
  BOOL hasIdentityKeyPublic_:1;
  BOOL hasIdentityKeyPrivate_:1;
  BOOL hasProfileKey_:1;
  BOOL readReceipts_:1;
  NSString* number;
  NSString* provisioningCode;
  NSString* userAgent;
  NSData* identityKeyPublic;
  NSData* identityKeyPrivate;
  NSData* profileKey;
}
- (BOOL) hasIdentityKeyPublic;
- (BOOL) hasIdentityKeyPrivate;
- (BOOL) hasNumber;
- (BOOL) hasProvisioningCode;
- (BOOL) hasUserAgent;
- (BOOL) hasProfileKey;
- (BOOL) hasReadReceipts;
@property (readonly, strong) NSData* identityKeyPublic;
@property (readonly, strong) NSData* identityKeyPrivate;
@property (readonly, strong) NSString* number;
@property (readonly, strong) NSString* provisioningCode;
@property (readonly, strong) NSString* userAgent;
@property (readonly, strong) NSData* profileKey;
- (BOOL) readReceipts;

+ (instancetype) defaultInstance;
- (instancetype) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (OWSProvisioningProtosProvisionMessageBuilder*) builder;
+ (OWSProvisioningProtosProvisionMessageBuilder*) builder;
+ (OWSProvisioningProtosProvisionMessageBuilder*) builderWithPrototype:(OWSProvisioningProtosProvisionMessage*) prototype;
- (OWSProvisioningProtosProvisionMessageBuilder*) toBuilder;

+ (OWSProvisioningProtosProvisionMessage*) parseFromData:(NSData*) data;
+ (OWSProvisioningProtosProvisionMessage*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (OWSProvisioningProtosProvisionMessage*) parseFromInputStream:(NSInputStream*) input;
+ (OWSProvisioningProtosProvisionMessage*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (OWSProvisioningProtosProvisionMessage*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (OWSProvisioningProtosProvisionMessage*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface OWSProvisioningProtosProvisionMessageBuilder : PBGeneratedMessageBuilder {
@private
  OWSProvisioningProtosProvisionMessage* resultProvisionMessage;
}

- (OWSProvisioningProtosProvisionMessage*) defaultInstance;

- (OWSProvisioningProtosProvisionMessageBuilder*) clear;
- (OWSProvisioningProtosProvisionMessageBuilder*) clone;

- (OWSProvisioningProtosProvisionMessage*) build;
- (OWSProvisioningProtosProvisionMessage*) buildPartial;

- (OWSProvisioningProtosProvisionMessageBuilder*) mergeFrom:(OWSProvisioningProtosProvisionMessage*) other;
- (OWSProvisioningProtosProvisionMessageBuilder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (OWSProvisioningProtosProvisionMessageBuilder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasIdentityKeyPublic;
- (NSData*) identityKeyPublic;
- (OWSProvisioningProtosProvisionMessageBuilder*) setIdentityKeyPublic:(NSData*) value;
- (OWSProvisioningProtosProvisionMessageBuilder*) clearIdentityKeyPublic;

- (BOOL) hasIdentityKeyPrivate;
- (NSData*) identityKeyPrivate;
- (OWSProvisioningProtosProvisionMessageBuilder*) setIdentityKeyPrivate:(NSData*) value;
- (OWSProvisioningProtosProvisionMessageBuilder*) clearIdentityKeyPrivate;

- (BOOL) hasNumber;
- (NSString*) number;
- (OWSProvisioningProtosProvisionMessageBuilder*) setNumber:(NSString*) value;
- (OWSProvisioningProtosProvisionMessageBuilder*) clearNumber;

- (BOOL) hasProvisioningCode;
- (NSString*) provisioningCode;
- (OWSProvisioningProtosProvisionMessageBuilder*) setProvisioningCode:(NSString*) value;
- (OWSProvisioningProtosProvisionMessageBuilder*) clearProvisioningCode;

- (BOOL) hasUserAgent;
- (NSString*) userAgent;
- (OWSProvisioningProtosProvisionMessageBuilder*) setUserAgent:(NSString*) value;
- (OWSProvisioningProtosProvisionMessageBuilder*) clearUserAgent;

- (BOOL) hasProfileKey;
- (NSData*) profileKey;
- (OWSProvisioningProtosProvisionMessageBuilder*) setProfileKey:(NSData*) value;
- (OWSProvisioningProtosProvisionMessageBuilder*) clearProfileKey;

- (BOOL) hasReadReceipts;
- (BOOL) readReceipts;
- (OWSProvisioningProtosProvisionMessageBuilder*) setReadReceipts:(BOOL) value;
- (OWSProvisioningProtosProvisionMessageBuilder*) clearReadReceipts;
@end


// @@protoc_insertion_point(global_scope)
