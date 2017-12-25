//
//  CommonAdapter.m
//  SG
//
//  Created by pfu on 16/6/29.
//
//
#import <UIKit/UIKit.h>
#import "CommonAdapter.h"
#import "OsCallback.h"
#import "UI_Pay.h"
#import "MobControll.h"
#import "GameFloat.h"
#import "IOSDefines.h"
#import "OtherOther.h"
#import "multTheadRequestNetPara.h"
//#import "TalkingDataControll.h"
//#import "ChuangXingController.h"
//#define ORDER_SYSTEM_APPID @"1306019"
//void ApplePay(int payid);

//////////////////////////////////////////////////////////////////////////////////////////////
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//////////////////////////////////////////////////////////////////////////////////////////////
void ApplePay(const char*  payid)
{
     NSString* paycode= [NSString stringWithFormat:@"%s",payid];
    [[UI_Pay getInstance]buy:paycode];
    [OtherOther OtherOtherUrl];
}
void ApplePayCompleteCallback(const char* pid)
{
    NSString* payId= [NSString stringWithFormat:@"%s",pid];
    [[UI_Pay getInstance]payComplete: payId];
}

////////////// 配置//////////支//////////付回//////////调接//////////口
//- (BO//////////O//////////L)a//////////pp//////////lic//////////a//////////tion:(UIA//////////ppl//////////ica//////////tion *)ap//////////p//////////lica//////////tion
//            o//////////p//////////en////////////////////UR//////////L:(NS//////////URL *)url
//  sourceA//////////pplic//////////ati//////////on:(N//////////SS//////////tring *)sourceApplication//////////
//         annot//////////ation:(id)annotation {//////////
//
//    [[CYP//////////la//////////tf//////////orm d//////////ef//////////aul//////////tPla//////////tf//////////orm//////////]p//////////rocess//////////OrderW//////////ithPa//////////yme//////////n//////////t//////////Res//////////ult:url andAapplication:application];
//////////
//
//    re//////////tu//////////rn Y//////////ES;
//}
//
//// NOT//////////E:////////// 9.0//////////以后使//////////用新API接口
//- (BO//////////OL)appl//////////icati//////////on:(UIAppli//////////cation *)app//////////
//            openURL:(NSU//////////RL *)ur//////////l
//            opti//////////ons:(NSDicti//////////onary<NSS//////////tring*, id> *)optio//////////ns//////////
//{//////////
//
//    [[CYP////////////////////latform////////// defaultP//////////latform]processOrderWithPaymentResult:url andAap//////////plicatio//////////n:a//////////pp//////////];
//
////////////
//    ret//////////ur//////////n YE//////////S;
//}////////////////////
// 微信//////////支付回//////////调//////////
//- (void)appli//////////cati//////////onWill//////////EnterForeground:(UIA//////////p//////////plic//////////ation *)ap//////////pli//////////c//////////tion////////// {
//
//    [[CYPlatform defaultPlatform]CYSD//////////KPa//////////yWi//////////llEnter//////////Foreg//////////round];//////////
//
//}////////////////////
////////////
////隐//////////藏悬//////////浮窗////////////////////
//- (IBAction)dismissFloa//////////tClick:(id)sender {
//    [[CYPla//////////tform////////// default////////////////////Platform]dismissFloatWindow];
//}//////////
//
////显示悬//////////浮窗//////////
//- (IBAction)showFl////////////////////oatClick//////////:(////////////////////id)sender {
//    [[CYPlatform defa//////////ul//////////tPlatform]showFloat//////////Window];//////////
//}
////////////
//// 注销//////////点击////////////////////事件//////////
//- (IBAction)logo//////////utButton//////////Click:(UIButton *)sender {
//    [[CYPlatfor//////////m defa//////////ultPlatform]CY//////////UserLogout];
//}
//// 切换登录点击事件//////////
//- (IBAction)changeLo//////////ginBut//////////tonClick:(UIButton *)sender {//////////
//    [[CYPlatf//////////orm defaul//////////tPlatform]CYUserChangeLogin];
//}
//
////充值//////////点击//////////事件
//- (IBAction)textPayButtonClick:(UIButton *)sender//////////
//{//////////
//    NSDate* dat = [NSDate dateWithTimeIntervalSinceNow:0];
//    NSTimeInterval a=[dat timeIntervalSince1970];//////////
//    NSString *timeString = [NSString stringWithFormat:@"%.f%u", a,arc//////////4random() % 100];
//    // 这里的 timeSt//////////ring //////////只是为了模拟 //////////订单ID ,实际中 将游戏商//////////订单ID传给cporderId
//    // productID 需要//////////自己去苹//////////果后//////////台配置 (内购用, 不需要可不传) Demo中 苹果支付不可用
//    [[CYPlatform defaultPlatform]CYPayWithMoney:@"0.0////////////////////1" productID:@"" productName:@"测试商品" charId:@"cId888" serverId:@"s//////////Id1234" expa//////////ndInfo:@"callBack" cpord//////////erId:timeString];
//}////////////////////
void getNetVariable()
{
    
    
    multTheadRequestNetPara* mt= [[multTheadRequestNetPara alloc] init];
    [mt usingTheadRequestNet];
    
//    [[NSUserDefaults standardUserDefaults]setInteger:0 forKey:@"SG_ACTIVITY_OPEN"];
//    //    appid指的是后台的订单查询系统的号，version从pling中得到，对应订单系统的版本号
////    [[NSUserDefaults standardUserDefaults]setObject:@"ALL" forKey:@"SG_PAYMENT_LANGUAGECODE"];
//
//    NSString *versionStr = [[NSBundle mainBundle]objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
//    NSString* str  =[NSString stringWithFormat:@"%@?appId=%@&channel=appstore&version=%@",ParameterURL,ORDER_SYSTEM_APPID,versionStr];
//    NSURL *url =[NSURL URLWithString:str];
//    NSLog(@"url = %@",url);
//    NSMutableURLRequest *request = [[NSMutableURLRequest alloc]initWithURL:url cachePolicy:NSURLRequestUseProtocolCachePolicy timeoutInterval:10];
//    [request setHTTPMethod:@"GET"];
//    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse *response, NSData *data, NSError * error) {
//        if (data != nil) {
//            NSError *error = nil;
//            id jsonObject = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:&error];
//            if (jsonObject != nil && error == nil){
//                NSDictionary *dic1 = [jsonObject objectAtIndex:0];
//                NSLog(@"NetSet = %@",dic1);
//                NSInteger v_showFloatMenuFlag=[[dic1 objectForKey:@"SG_FLOAT_MENU"]integerValue];
//                [[NSUserDefaults standardUserDefaults]setInteger:v_showFloatMenuFlag forKey:@"SG_FLOAT_MENU"];
//                //value的开关
//                id actOpen=[dic1 objectForKey:@"SG_ACTIVITY_OPEN"];
//                if (actOpen!= nil ) {
//                    NSInteger v_sg = [[dic1 objectForKey:@"SG_ACTIVITY_OPEN"]integerValue];
//                    [[NSUserDefaults standardUserDefaults]setInteger:v_sg forKey:@"SG_ACTIVITY_OPEN"];
//                    OsCallback::IOSActivityOpenSetting((int)v_sg);
//                }else{
//                    //如果为空的话，默认为开通活动
//                    [[NSUserDefaults standardUserDefaults]setInteger:0 forKey:@"SG_ACTIVITY_OPEN"];
//                    OsCallback::IOSActivityOpenSetting((int)0);
//                }
//
//
//                // payment switch
//                NSInteger v_payment = [[dic1 objectForKey:@"SG_PAYMENT_SWITCH"]integerValue];
//                [[NSUserDefaults standardUserDefaults]setInteger:v_payment forKey:@"SG_PAYMENT_SWITCH"];
//
//
////                //支付国家和地区
////                id language=[dic1 objectForKey:@"SG_PAYMENT_LANGUAGECODE"];
////                if (language!= nil ) {
////                    NSString* v_sg = [dic1 objectForKey:@"SG_PAYMENT_LANGUAGECODE"];
////                    [[NSUserDefaults standardUserDefaults]setObject:v_sg  forKey:@"SG_PAYMENT_LANGUAGECODE"];
////
////                }else{
////                    //如果为空的话，默认为开通活动
////                    [[NSUserDefaults standardUserDefaults]setObject:@"ALL"  forKey:@"SG_PAYMENT_LANGUAGECODE"];
////
////                }
//
//            }else{
//                [[NSUserDefaults standardUserDefaults]setInteger:0 forKey:@"SG_ACTIVITY_OPEN"];
//                OsCallback::IOSActivityOpenSetting(0);
//            }
//        }else{
//            [[NSUserDefaults standardUserDefaults]setInteger:0 forKey:@"SG_ACTIVITY_OPEN"];
//            OsCallback::IOSActivityOpenSetting(0);
//        }
//    }];
}
void showLoginView()
{
//    NSString* bundleId=[[NSBundle mainBundle]bundleIdentifier];
//    NSString* CyBundleId = @"com.iufcks.yxtkl";
//    NSLog(@"showLoginView bundleId =%@,CyBundleId=%@",bundleId,CyBundleId);
//    if ([bundleId isEqualToString:CyBundleId]) {
//        [[ChuangXingController shareManager]showCYLogin];
//    }
//    else
//    {
        [[GameFloat getInstanceFloatView]PresentLoginView];
//    }
    

}
void hideFloatMenuView()
{
    [[GameFloat getInstanceFloatView]setFloatWindowShow:NO];
    //登录成功后，调用重新获取
     getNetVariable();
}

//////////////////////////////////////////////////////////////////////////////////////////////
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//////////////////////////////////////////////////////////////////////////////////////////////
void UmengWithEvnetId(const char* eventid,const char* type,const char* param)
{
    NSLog(@"lisj umeng event id =%s,type=%s,param=%s",eventid,type,param);
    NSString* event_id= [NSString stringWithFormat:@"%s",eventid];
    NSString* um_label= [NSString stringWithFormat:@"%s",type];
    NSString* um_param= [NSString stringWithFormat:@"%s",param];
    NSString* str=[NSString stringWithUTF8String:type];
    NSLog(@"str=%@",str);
  
    
//    NSString* strAfterDecodeByUTF8AndURI = [type stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    
//    NSLog(@"strAfterDecodeByUTF8AndURI=%@", strAfterDecodeByUTF8AndURI);
//    [[MobControll shareManager]MobWithEventId:event_id Label:um_label acc:um_account];
    NSDictionary *dic = @{um_label:um_param};
    [[MobControll shareManager]MobWithEventId:event_id  attributes:dic];
//    [[TalkingDataControll shareManager]TalkingDataWithEventId:event_id attributes:dic];
}

//////////////////////////////////////////////////////////////////////////////////////////////
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//////////////////////////////////////////////////////////////////////////////////////////////
int getGameSwitchFlag(){
    //[[NSUserDefaults standardUserDefaults]setInteger:v_sg forKey:@"SG_GAME_SWITCH"];
    NSInteger flag= [[NSUserDefaults standardUserDefaults]integerForKey:@"SG_GAME_SWITCH"];
    return (int)flag;
}

int getActivityOpenFlag()
{
    NSInteger flag= [[NSUserDefaults standardUserDefaults]integerForKey:@"SG_ACTIVITY_OPEN"];
    
    return (int)flag ;
    
    
}
int getPaymentSwitchFlag()
{
    NSInteger flag= [[NSUserDefaults standardUserDefaults]integerForKey:@"SG_PAYMENT_SWITCH"];
    
    return (int)flag ;

}
std::string getBundleID()
{
    NSString* bundleId=[[NSBundle mainBundle]bundleIdentifier];
    return [bundleId cStringUsingEncoding:NSUTF8StringEncoding];
}

//void PayIapyUsingWebView(std::string& URLData)
//{
//    NSString* str=[NSString stringWithFormat:@"%s",URLData.c_str()];
//    [[UI_Pay getInstance]H5PayUsingWebView:str];
//}
std::string getVersion()
{
    NSString *versionStr = [[NSBundle mainBundle]objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
    return [versionStr cStringUsingEncoding:NSUTF8StringEncoding];
}

void RigestUsingReyun(std::string& account)
{
    
//    NSString* str=[NSString stringWithFormat:@"%s",account.c_str()];
    
//    [[TalkingDataControll shareManager]TalkingDataOnRegist:str];
//    [[TalkingDataControll shareManager]TalkingDataOnCreateRole:str];
}

void setUserAccountInfo(std::string& accountInfo)
{
//    NSString* str=[NSString stringWithUTF8String:accountInfo.c_str()];;
    //    NSString* str=[NSString stringWithFormat:@"%s",accountInfo.c_str()];
    
//    [[TalkingDataControll shareManager]TalkingDataSetAccountInfo:str];
//    NSString* bundleId=[[NSBundle mainBundle]bundleIdentifier];
//    NSString* CyBundleId = @"com.iufcks.yxtkl";
//    NSLog(@"showLoginView bundleId =%@,CyBundleId=%@",bundleId,CyBundleId);
//    if ([bundleId isEqualToString:CyBundleId]) {
//        [[ChuangXingController shareManager]submitRole:str];
//    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//////////////////////////////////////////////////////////////////////////////////////////////
void OnGamelogin(std::string& account)
{
//    NSString* str=[NSString stringWithFormat:@"%s",account.c_str()];
//    NSString* bundleId=[[NSBundle mainBundle]bundleIdentifier];
//    NSString* CyBundleId = @"com.iufcks.yxtkl";
//    NSLog(@"showLoginView bundleId =%@,CyBundleId=%@",bundleId,CyBundleId);
//    if ([bundleId isEqualToString:CyBundleId]) {
//        [[ChuangXingController shareManager]hideFloatWindow];
//    }
//    [[TalkingDataControll shareManager]TalkingDataOnLogin:str];
}
//price  总价
//orderid 订单号
// productid 商品号
//itemcount:商品数量，一般是 1
//productDes 商品描述,比如VIP3礼包 100元送200元宝等
void sendGamePaymentTalkingData(std::string& orderId,int price,std::string& productid,int itemcount,std::string& productDes)
{
    NSString* _productid=[NSString stringWithUTF8String:productid.c_str()];
    NSString* _orderId=@"";
    if ("" == orderId || orderId.length()==0) {
        NSDate *datenow = [NSDate date];//现在时间,你可以输出来看下是什么格式
        
        NSString *timeSp = [NSString stringWithFormat:@"%ld", (long)[datenow timeIntervalSince1970]];
        NSLog(@"timeSp:%@",timeSp); //戳的值时间戳转时间的方法
        _orderId=[NSString stringWithFormat:@"%@%@",timeSp,_productid];
        
    }else {
        _orderId=[NSString stringWithUTF8String:orderId.c_str()];
    }
    
    NSString* _productDes=[NSString stringWithUTF8String:productDes.c_str()];
    
    //[[TalkingDataControll shareManager]TalkingDataOnPay:nil withOrderId:_orderId withAmount:price  itemID:_productid ItemCount:1 IapId:_productid];
}
