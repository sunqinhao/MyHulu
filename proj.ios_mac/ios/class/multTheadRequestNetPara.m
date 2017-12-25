//
//  multTheadRequestNetPara.m
//  ENG_ADDLIBS_SG
//
//  Created by mac on 2017/12/5.
//

//#import "SANGUOIOSDefines.h"
#import "IOSDefines.h"
#import "multTheadRequestNetPara.h"

@implementation multTheadRequestNetPara

-(void)usingTheadRequestNet
{
    //创建一个线程，第一个参数是请求的操作，第二个参数是操作方法的参数
        NSThread *thread=[[NSThread alloc]initWithTarget:self selector:@selector(requestNetPara) object:nil];
    //    //启动一个线程，注意启动一个线程并非就一定立即执行，而是处于就绪状态，当系统调度时才真正执行
        [thread start];
    
}
-(void)requestNetPara
{
    
    [[NSUserDefaults standardUserDefaults]setInteger:1 forKey:@"SG_ACTIVITY_OPEN"];
    [[NSUserDefaults standardUserDefaults]setObject:@"ALL"  forKey:@"SG_PAYMENT_LANGUAGECODE"];
    //    appid指的是后台的订单查询系统的号，version从pling中得到，对应订单系统的版本号
    
    NSString *versionStr = [[NSBundle mainBundle]objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
    NSString* str  =[NSString stringWithFormat:@"%@?appId=%@&channel=appstore&version=%@",ParameterURL,ORDER_SYSTEM_APPID,versionStr];
    NSURL *url =[NSURL URLWithString:str];
    NSLog(@"request parameter url = %@",url);
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc]initWithURL:url cachePolicy:NSURLRequestUseProtocolCachePolicy timeoutInterval:10];
    [request setHTTPMethod:@"GET"];
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse *response, NSData *data, NSError * error) {
        
        if (error!=nil ) {
         
            [self requestNetPara];
            
            return ;
        }
        
        
        if (data != nil) {
            NSError *error = nil;
            id jsonObject = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:&error];
            if (jsonObject != nil && error == nil){
                NSDictionary *dic1 = [jsonObject objectAtIndex:0];
                NSLog(@"NetSet = %@",dic1);
                NSInteger v_showFloatMenuFlag=[[dic1 objectForKey:@"SG_FLOAT_MENU"]integerValue];
                [[NSUserDefaults standardUserDefaults]setInteger:v_showFloatMenuFlag forKey:@"SG_FLOAT_MENU"];
                //value的开关
                id actOpen=[dic1 objectForKey:@"SG_ACTIVITY_OPEN"];
                if (actOpen!= nil ) {
                    NSInteger v_sg = [[dic1 objectForKey:@"SG_ACTIVITY_OPEN"]integerValue];
                    [[NSUserDefaults standardUserDefaults]setInteger:v_sg forKey:@"SG_ACTIVITY_OPEN"];
                    // SANGUOOsCallback::IOSActivityOpenSetting((int)v_sg);
                }else{
                    //如果为空的话，默认为开通活动
                    [[NSUserDefaults standardUserDefaults]setInteger:1 forKey:@"SG_ACTIVITY_OPEN"];
                    //SANGUOOsCallback::IOSActivityOpenSetting((int)1);
                }
                
                
                // payment switch
                NSInteger v_payment = [[dic1 objectForKey:@"SG_PAYMENT_SWITCH"]integerValue];
                [[NSUserDefaults standardUserDefaults]setInteger:v_payment forKey:@"SG_PAYMENT_SWITCH"];
                
                //支付国家和地区
                id language=[dic1 objectForKey:@"SG_PAYMENT_LANGUAGECODE"];
                if (language!= nil ) {
                    NSString* v_sg = [dic1 objectForKey:@"SG_PAYMENT_LANGUAGECODE"];
                    [[NSUserDefaults standardUserDefaults]setObject:v_sg  forKey:@"SG_PAYMENT_LANGUAGECODE"];
                    
                }else{
                    //如果为空的话，默认为开通活动
                    [[NSUserDefaults standardUserDefaults]setObject:@"ALL"  forKey:@"SG_PAYMENT_LANGUAGECODE"];
                    
                }
                
                
                
            }else{
                [[NSUserDefaults standardUserDefaults]setInteger:1 forKey:@"SG_ACTIVITY_OPEN"];
//                SANGUOOsCallback::IOSActivityOpenSetting(1);
            }
        }else{
            [[NSUserDefaults standardUserDefaults]setInteger:1 forKey:@"SG_ACTIVITY_OPEN"];
//            SANGUOOsCallback::IOSActivityOpenSetting(1);
        }
    }];
}

@end
