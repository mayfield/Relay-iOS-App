//
//  Copyright (c) 2018 Open Whisper Systems. All rights reserved.
//

#import "UIFont+OWS.h"
#import <RelayServiceKit/MIMETypeUtil.h>
#import <RelayServiceKit/UIImage+OWS.h>

typedef void (^completionBlock)(void);

/**
 *
 * UIUtil contains various class methods that centralize common app UI functionality that would otherwise be hardcoded.
 *
 */

@interface UIUtil : NSObject

+ (void)applyRoundedBorderToImageView:(UIImageView *)imageView;
+ (void)removeRoundedBorderToImageView:(UIImageView *__strong *)imageView;

+ (void)setupSignalAppearence;

@end
