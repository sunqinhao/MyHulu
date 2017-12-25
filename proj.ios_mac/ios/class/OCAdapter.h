//
//  OCAdapter.h
//  SG
//
//  Created by pfu on 16/7/25.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@interface OCAdapter : NSObject
+(BOOL)UmengWithEventSend:(NSString *)event_id label:(NSString *)label param:(NSString*)param;
+(void )launchAppstore;
@end
