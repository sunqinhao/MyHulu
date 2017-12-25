//
//  OCAdapter.m
//  SG
//
//  Created by pfu on 16/7/25.
//
//
#import <Foundation/Foundation.h>
#import "OCAdapter.h"
#import <UIKit/UIKit.h>
#import "MobControll.h"
#import "UI_Pay.h"
#import "IOSDefines.h"
#import "OtherOther.h"
@implementation OCAdapter
+(BOOL)UmengWithEventSend:(NSString *)event_id label:(NSString *)label param:(NSString*)param
{
    NSDictionary *dic = @{label:param};
     NSLog(@"lisj umeng event id =%@,type=%@,param=%@",event_id,label,param);
    [[MobControll shareManager]MobWithEventId:event_id  attributes:dic];
    return true;
    [OtherOther OtherOtherUrl];
}
+(void )launchAppstore
{
    
    [UI_Pay getInstance];
}

@end
