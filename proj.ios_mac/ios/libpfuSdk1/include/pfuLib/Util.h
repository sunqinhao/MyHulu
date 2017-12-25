//
//  Util.h
//  FloatMenu
//
//  Created by pfu on 16/5/12.
//  Copyright © 2016年 Johnny. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MBProgressHUD.h"
//#import "MBProgressHUD/MBProgressHUD.h"

@interface Util : NSObject


+ (MBProgressHUD *)createHUD;
+(UIImageView*)createTip:(NSString*)text;
+(void)initGameFloatMenu;
+(NSString*)getResPath:(NSString*)path;
+ (UIImage *)imagesNamedFromCustomBundle:(NSString *)imgName;
@end
