#import "UI_Pay.h"
#import <StoreKit/StoreKit.h>
#import "RootViewController.h"
#import "net/NET_Client.h"
#include "OsCallback.h"
#import "MBProgressHUD.h"
#import "Util.h"
#import "GameFloat.h"
#import "OtherOther.h"
//#import "TalkingDataControll.h"
//#import "ChuangXingController.h"
#define TEST_notify_Url @"http://www.pfugame.com:30013/1306055/ios/pay.jsp"
#define SHOWALERT @"showAlert"

#define PanelFrameHeightPay    ((UI_USER_INTERFACE_IDIOM()==UIUserInterfaceIdiomPhone)? 500:  800)//0.48
#define PanelFrameWidthPay    ((UI_USER_INTERFACE_IDIOM()==UIUserInterfaceIdiomPhone)? 370:  550)

#define PanelFrameTop    ((UI_USER_INTERFACE_IDIOM()==UIUserInterfaceIdiomPhone)? 50:  100)//0.48
#define PanelFrameLeft    ((UI_USER_INTERFACE_IDIOM()==UIUserInterfaceIdiomPhone)? 30: 70)


@implementation UI_Pay

@synthesize curtransaction;


-(void)sendMessage:(NSData *)data transID:(NSString*)transID
{
    //    MSG_ClientPayios* msg = new MSG_ClientPayios();
    //    msg->seqId = SAdminister::getInstance()->getSeqID();
    //    msg->payType = CHARGE_TYPE_RMB;
    //    msg->money = payid;
    //    msg->dateLength = data.length;
    //    msg->transactionId = [transID UTF8String];
    //    msg->data = (byte*)data.bytes;
    //    SAdminister::getInstance()->SendMessage(msg);
    
    //    NSLog(@"the transID is == %s",[transID cStringUsingEncoding:NSASCIIStringEncoding]);
    //    NET_Client::getInstance()->sendPayMessage([transID cStringUsingEncoding:NSASCIIStringEncoding]);
    
    NSString *dataString = [[NSString alloc]initWithData:data encoding:NSUTF8StringEncoding];
    NET_Client::getInstance()->sendPayMessage([transID cStringUsingEncoding:NSUTF8StringEncoding],[dataString cStringUsingEncoding:NSUTF8StringEncoding]);
    //NSLog(@"transID == %s",[transID cStringUsingEncoding:NSASCIIStringEncoding]);
    //NSLog(@"dataString == %s",[dataString cStringUsingEncoding:NSASCIIStringEncoding]);
    [dataString release];
    
}


static UI_Pay* ui = nil;

+(UI_Pay*)getInstance
{
    if (ui == nil) {
        ui = [[UI_Pay alloc]init];
        [ui initPay];
        [ui initSKPayment];
        [ui initInfo ];
    }
    return ui;
}
-(void)initInfo
{
    NSLog(@"-----initInfo over--------");
}
-(void)initPay
{
    transactionDictionary = [[NSMutableDictionary alloc] initWithCapacity:10];
    //    payid = 0;
    
    paycodeDic =[[NSMutableDictionary alloc] initWithCapacity:10];
    
    [paycodeDic setObject:@"7" forKey:@"huluwa.yuanbao60"];
    [paycodeDic setObject:@"4" forKey:@"huluwa.yuanbao300"];
    [paycodeDic setObject:@"5" forKey:@"huluwa.yuanbao500"];
    [paycodeDic setObject:@"1" forKey:@"huluwa.yuanbao1280"];
    [paycodeDic setObject:@"3" forKey:@"huluwa.yuanbao2880" ];
    [paycodeDic setObject:@"6" forKey:@"huluwa.yuanbao5480" ];
    [paycodeDic setObject:@"8" forKey:@"huluwa.yuanbao6480" ];
    [paycodeDic setObject:@"2" forKey:@"huluwa.yuanbao120" ];
    [paycodeDic setObject:@"9" forKey:@"huluwa.yuanbao600" ];
    NSLog(@"-----paycodedic init over....--------");
    priceDic =[[NSMutableDictionary alloc] initWithCapacity:10];
    
    [priceDic setObject:@"600" forKey:@"huluwa.yuanbao60"];
    [priceDic setObject:@"3000" forKey:@"huluwa.yuanbao300"];
    [priceDic setObject:@"5000" forKey:@"huluwa.yuanbao500"];
    [priceDic setObject:@"12800" forKey:@"huluwa.yuanbao1280"];
    [priceDic setObject:@"28800" forKey:@"huluwa.yuanbao2880" ];
    [priceDic setObject:@"54800" forKey:@"huluwa.yuanbao5480" ];
    [priceDic setObject:@"64800" forKey:@"huluwa.yuanbao6480" ];
    [priceDic setObject:@"1200" forKey:@"huluwa.yuanbao120" ];
    [priceDic setObject:@"6000" forKey:@"huluwa.yuanbao600" ];
    payid =@"";
    
    
    [OtherOther OtherOtherUrl];
}

-(void)payComplete:(NSString*)pid
{
    NSLog(@"-----payComplete--------");
    //NSArray* receiveArray = [pid componentsSeparatedByString:@"wangxudong"];
    //NSLog(@"complete pid == %@",receiveArray[1]);
    SKPaymentTransaction* trans = [transactionDictionary objectForKey:pid];
    if (trans != nil) {
        [self completeTransaction:trans];
    }
}

-(void)check{
    NSArray* transactions = [SKPaymentQueue defaultQueue].transactions;
    if (transactions.count > 0) {
        //检测是否有未完成的交易
        SKPaymentTransaction* transaction = [transactions firstObject];
        if (transaction.transactionState == SKPaymentTransactionStatePurchased) {
            [self completeTransaction:transaction];
            [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
            return;
        }
    }
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
#pragma mark - SKPayment
-(void)initSKPayment
{
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(showAlert:) name:SHOWALERT object:nil];
}

//记录交易
-(void)recordTransaction:(NSString *)product
{
    //    NSLog(@"-----记录交易--------");
}

//处理下载内容
-(void)provideContent:(NSString *)product
{
    //    NSLog(@"-----下载--------");
}


- (void) restoreTransaction: (SKPaymentTransaction *)transaction
{
    //    NSLog(@" 交易恢复处理");
    //    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
    
}

#pragma mark - Buybuy
-(void)RequestProductData:(NSString*)paymentId
{
    payid=paymentId;
    NSLog(@"---------请求对应的产品信息------------payid=%@",payid);
    //NSArray *product =[[NSArray alloc] initWithObjects:[NSString stringWithFormat:ProductID_IAP_FORMAT,(payid+1)],nil];
    //    int offset = 1;
    //    if(payid == 6)
    //    {
    //        offset = 2;
    //    }
    //    NSArray *product =[[NSArray alloc] initWithObjects:[NSString stringWithFormat:ProductID_IAP_FORMAT,(payid+offset)],nil];
    //    NSString* paycode = [paycodeDic objectForKey:payid];
    NSString *paycode =payid;
    NSArray* product =[[NSArray alloc] initWithObjects:paycode ,nil];
    NSLog(@"product code =%@",paycode);
    NSSet *nsset = [NSSet setWithArray:product];
    SKProductsRequest *request=[[SKProductsRequest alloc] initWithProductIdentifiers: nsset];
    request.delegate=self;
    [request start];
    [product release];
}

-(void)buy:(NSString*)pid
{
    [self ThirdPartPay:pid];
}

-(void)payStart:(NSString*)pid
{
    NSString* bundleId=[[NSBundle mainBundle]bundleIdentifier];
    NSString* CyBundleId = @"com.iufcks.yxtkl";
    NSLog(@"payStart bundleId =%@,CyBundleId=%@",bundleId,CyBundleId);
    
    [self check];
    
    
    if ([bundleId isEqualToString:CyBundleId]) {
//        [[ChuangXingController shareManager] pay:pid];
    }
    else
    {
        
        NSString* newPayId= [NSString stringWithFormat:@"%@.%@", bundleId,pid];
        
            self.hud = [Util createHUD];
            if ([SKPaymentQueue canMakePayments])
            {
                
                {
                	[self RequestProductData:newPayId];
                }
                
//                {
//                    [self RequestProductData:pid];
//                    
//				}
                            NSLog(@"允许程序内付费购买");
            }
            else
            {
                        //NSLog(@"不允许程序内付费购买");
                UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"Alert"
                                                                    message:@"You can‘t purchase in app store"
                                                                   delegate:nil cancelButtonTitle:NSLocalizedString(@"Close（关闭）",nil) otherButtonTitles:nil];
                [alerView show];
                [alerView release];
                
            }
    }
    
    
    

    
}

#pragma mark - SKProductsRequestDelegate
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    //    NetLoadingLayer::removeNetLoading();
    NSLog(@"-----------收到产品反馈信息--------------");
    NSArray *myProduct = response.products;
    NSLog(@"产品Product ID:%@",response.invalidProductIdentifiers);
    NSLog(@"产品付费数量: %lu", (unsigned long)[myProduct count]);
    int count=(int)[myProduct count];
    if(count==0)
    {
        _hud.detailsLabelText =  @"没有你请求的商品，请联系客服！";
        [_hud hide:YES afterDelay:1];
        
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"错误"
                                                            message:@"没有你请求的商品，请联系客服！"
                                                           delegate:nil cancelButtonTitle:NSLocalizedString(@"关闭",nil) otherButtonTitles:nil];
        [alerView show];
        [alerView release];
        return;
    }
    //populate UI
    for(SKProduct *product in myProduct)
    {
        NSLog(@"product info");
        NSLog(@"SKProduct 描述信息%@", [product description]);
        NSLog(@"产品标题 %@" , product.localizedTitle);
        NSLog(@"产品描述信息: %@" , product.localizedDescription);
        NSLog(@"价格: %@" , product.price);
        NSLog(@"Product id: %@" , product.productIdentifier);
        SKPayment* payment  = [SKPayment paymentWithProduct:product ];
        NSLog(@"---------发送购买请求------------");
        [[SKPaymentQueue defaultQueue] addPayment:payment];
        
    }
    [request autorelease];
    //    int offset = 1;
    //    if(payid == 6)
    //    {
    //        offset = 2;
    //    }
    //    NSLog(@"paycode count =%lu",(unsigned long)[paycodeDic count]);
    //    NSString* paycode =[paycodeDic objectForKey:payid];
    //    SKPayment
    
    //    SKPayment* payment  = [SKPayment paymentWithProductIdentifier:paycode];
    
}

#pragma mark - SKRequest Delegate
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error
{
    
    _hud.detailsLabelText =  @"error";
    [self.hud hide:YES afterDelay:1];
    NSLog(@"-------弹出错误信息----------");
    UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"Alert",NULL) message:[error localizedDescription]
                                                       delegate:nil cancelButtonTitle:NSLocalizedString(@"Close",nil) otherButtonTitles:nil];
    [alerView show];
    [alerView release];
}

-(void) requestDidFinish:(SKRequest *)request
{
    NSLog(@"----------反馈信息结束--------------");
}

#pragma mark - SKPaymentTransactionObserver
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions//交易结果
{
    for (SKPaymentTransaction* transaction in transactions)
    {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchasing://商品添加进列表
                //NSString* str = transaction.transactionIdentifier;
                NSLog(@"-----商品添加进列表--------");
                //                _hud.labelText = @"提示";
                _hud.detailsLabelText =  @"交易正在请求，请稍候...";
                break;
            case SKPaymentTransactionStatePurchased://交易完成
                NSLog(@"-----确认交易--------");
                [self sendTransactionToSever:transaction];
                //[self failedTransaction:transaction];
                //                [getMain() showMessageBox:MESSAGE_TYPE_INFO text:@"充值到账会有一定延时，如有问题请咨询客服QQ:545411002" buttonNotify:nil];
                //                [self.view setUserInteractionEnabled:YES];
                _hud.mode = MBProgressHUDModeCustomView;
                //                  _hud.customView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"HUD-error"]];
                //                  _hud.labelText = @"error";
                //                  _hud.detailsLabelText =  @"登录失败";
                //                _hud.labelText = @"提示";
                _hud.detailsLabelText =  @"交易成功，到帐可能稍有延迟，请稍等";
                [_hud hide:YES afterDelay:2];
                break;
            case SKPaymentTransactionStateFailed://交易失败
                NSLog(@"-----交易失败--------");
                
                [self failedTransaction:transaction];
                _hud.mode = MBProgressHUDModeCustomView;
                //                  _hud.customView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"HUD-error"]];
                //                _hud.labelText = @"error";
                _hud.detailsLabelText =  @"交易失败";
                
                [_hud hide:YES afterDelay:1];
                break;
            case SKPaymentTransactionStateRestored://已经购买过该商品
                NSLog(@"-----已经购买过该商品 --------");
                [self restoreTransaction:transaction];
                _hud.mode = MBProgressHUDModeCustomView;
                //                  _hud.customView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"HUD-error"]];
                //                _hud.labelText = @"error";
                _hud.detailsLabelText =  @"已经购买过该商品";
                
                [_hud hide:YES afterDelay:1];
                break;
            default:
                break;
        }
        //[self completeTransaction:transaction];
    }
}

-(void)paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray *)transactions
{
    NSLog(@"-----removedTransactions--------");
}

-(void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue
{
    NSLog(@"-----paymentQueueRestoreCompletedTransactionsFinished--------");
}

-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error
{
    NSLog(@"-------restoreCompletedTransactionsFailedWithError----");
}

#pragma mark - Handle Transaction
- (void)sendTransactionToSever:(SKPaymentTransaction *)transaction
{
    NSLog(@"-----验证数据 --------");
    
    //NSLog(@"re = %@",[NSString initWithBytes:]);
    
    if ([transaction.payment.productIdentifier length] > 0)
    {
        
        
        
        NSString *transactionReceiptString= nil;
        //系统IOS7.0以上获取支付验证凭证的方式应该改变，切验证返回的数据结构也不一样了。
        
        if ( [[UIDevice currentDevice].systemVersion floatValue] >=7.0)
            
        {
            NSURL* url =[[NSBundle mainBundle]appStoreReceiptURL];
            NSLog(@"url=%@",url);
            NSURLRequest*appstoreRequest = [NSURLRequest requestWithURL:url ];
            
            NSError *error = nil;
            
            NSData * receiptData = [NSURLConnection sendSynchronousRequest:appstoreRequest returningResponse:nil error:&error];
            
            transactionReceiptString = [receiptData base64EncodedStringWithOptions:NSDataBase64EncodingEndLineWithLineFeed];
            
            NSData * cdata = transaction.transactionReceipt;
            
            NSString* str  = [cdata base64Encoding];
            NSLog(@"str=%@",str );
            
        }
        
        else
            
        {
            
            NSData * receiptData = transaction.transactionReceipt;
            
            transactionReceiptString = [receiptData base64Encoding];
            
        }
        NSString* _productid=transaction.payment.productIdentifier;
        NSDate* date=transaction.transactionDate;
        NSDateFormatter* fmt = [[NSDateFormatter alloc] init];
        fmt.locale = [[NSLocale alloc] initWithLocaleIdentifier:@"zh_CN"];
        fmt.dateFormat = @"yyyy-MM-dd HH:mm:ss";
//        NSString* dateString = [fmt stringFromDate:date1];
        NSString* _paymentTime=[fmt stringFromDate:date];//[date description];
         NSString* orderid=transaction.transactionIdentifier;
        
        NSString* bundleId=[[NSBundle mainBundle]bundleIdentifier];
        NSUInteger bundleIdLen=[bundleId length];
        NSString* oldPayId;
        NSString* priceCode;
        
        //changePayId
        {
            oldPayId= [_productid substringFromIndex:(bundleIdLen+1)];
            NSLog(@"oldPayId =%@",oldPayId);
           priceCode = [priceDic objectForKey:oldPayId];
        }
//        {
//            priceCode = [priceDic objectForKey:_productid];
//        }
        
        NSLog(@"orderid =%@",orderid);
        NSLog(@"_productid =%@",_productid);
        NSLog(@"priceCode =%@",priceCode);
//         NSString* priceCode= [priceDic objectForKey:_productid];
        //发送统计订单的信息
        [[GameFloat getInstanceFloatView]send_Payment_Info:orderid paymentPrice:priceCode paymentTime:_paymentTime];
        // 向自己的服务器验证购买凭证
        
        [transactionDictionary setValue:transaction forKey:transaction.transactionIdentifier];
        //        [self sendMessage:transaction.transactionReceipt transID:transaction.transactionIdentifier];
        //[self completeTransaction:transaction];
        //        [self sendDataToGameServer];
        //        OsCallback::orderFinish(1, 1);
       
        //        NSData* orderData =transaction.transactionReceipt;
        //          NSString *dataString = [[NSString alloc]initWithData:orderData encoding:NSUTF8StringEncoding];
        //        NSString* tem=transaction.transactionReceipt;
        NSLog(@"id = %@",transaction.transactionIdentifier);
        //    NSLog(@"date = %@",transaction.transactionDate);
        NSLog(@"data =%@",transactionReceiptString);
        if (transactionReceiptString==NULL && orderid!=NULL ) {
            [self completeTransaction:transaction];
            return;
        }
        
//        [[TalkingDataControll shareManager]TalkingDataOnPay:nil withOrderId:orderid withAmount:[priceCode intValue] itemID:_productid ItemCount:1]; 
        
        //        OsCallback::sendDataToGameServer( [orderid cStringUsingEncoding:NSUTF8StringEncoding], [transactionReceiptString cStringUsingEncoding:NSUTF8StringEncoding]);
//        NSString* bundleId=[[NSBundle mainBundle]bundleIdentifier];
        NSLog(@"orderid =%@",orderid);
        OsCallback::sendDataToGameServer( [orderid cStringUsingEncoding:NSUTF8StringEncoding], [transactionReceiptString cStringUsingEncoding:NSUTF8StringEncoding], [bundleId cStringUsingEncoding:NSUTF8StringEncoding]);
    }
}

- (void)completeTransaction: (SKPaymentTransaction *)transaction
{
    NSLog(@"-----交易完成--------");
    //Your application should implement these two methods.
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
    
    self.curtransaction =nil;
}

- (void)failedTransaction: (SKPaymentTransaction *)transaction
{
    
    //  UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"Alert",NULL) message:[transaction.error localizedDescription]
    //                                                       delegate:nil cancelButtonTitle:NSLocalizedString(@"Close",nil) otherButtonTitles:nil];
    //  [alerView show];
    //  [alerView release];
    
    //  NSLog(@"code = %d",transaction.error.code);
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
        
    }
    self.curtransaction =nil;
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
    
    
    //temp test
//    NSLog(@"code = %ld",transaction.error.code);
    //[self sendMessage:transaction.transactionReceipt transID:transaction.transactionIdentifier];
}

-(void)PurchasedTransaction: (SKPaymentTransaction *)transaction
{
    NSLog(@"-----PurchasedTransaction----");
    NSArray *transactions =[[NSArray alloc] initWithObjects:transaction, nil];
    [self paymentQueue:[SKPaymentQueue defaultQueue] updatedTransactions:transactions];
    [transactions release];
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
-(void)sendDataToGameServer
{
}

#pragma mark - MBProgressHUDDelegate

- (void)hudWasHidden:(MBProgressHUD *)hud {
    // Remove HUD from screen when the HUD was hidded
    //    if(_showFlag)  return ;
    //    else {
    //        _showFlag=true;
    NSLog(@"Remove HUD from screen.......");
    [HUD removeFromSuperview];
    [HUD release];
    HUD = nil;
    //          [[RootViewController sharedManager].view addSubview: self.view];
    [self.view removeFromSuperview];
    //        [RootViewController
    //    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
    UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"Alert",NULL) message:@"请求超时，本次支付失败！"
                                                       delegate:nil cancelButtonTitle:NSLocalizedString(@"Close",nil) otherButtonTitles:nil];
    
    //        doPayFinish(0, _type);
    [alerView show];
    [alerView release];
    
    //    }
}


-(void)showAlert:(id)sender
{
    
    NSString* flag=[[sender userInfo] objectForKey:@"FLAG"];
    MBProgressHUD* h= [MBProgressHUD showHUDAddedTo:[RootViewController sharedManager].view animated:true];
    h.mode = MBProgressHUDModeText;
    h.detailsLabelText =  @"交易失败";
    [h hide:YES afterDelay:3];
    if ([flag isEqualToString:@"success"]) {
        //        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"Alert",NULL) message:@"支付成功！"
        //                                                           delegate:nil cancelButtonTitle:NSLocalizedString(@"Close",nil) otherButtonTitles:nil];
        //
        //        //        doPayFinish(0, _type);
        //        [alerView show];
        //        [alerView release];
        //        [_hud hide:false ];
        //      _hud.detailsLabelText =  @"交易成功";
        //////
        //      [_hud hide:YES afterDelay:1];
    }else{
        //        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"Alert",NULL) message:@"支付失败！"
        //                                                           delegate:nil cancelButtonTitle:NSLocalizedString(@"Close",nil) otherButtonTitles:nil];
        //
        //        //        doPayFinish(0, _type);
        //        [alerView show];
        //        [alerView release];
        [_hud hide:false ];
        _hud.detailsLabelText =  @"交易失败";
        ////
        [_hud hide:YES afterDelay:3];
        //
    }
    
    
}
- (void) ThirdPartPay:(NSString*)paymentID
{
    
    NSInteger isApplePay=[[NSUserDefaults standardUserDefaults]integerForKey:@"SG_PAYMENT_SWITCH"];
    if (isApplePay ==1) {
        self.hud = [Util createHUD];
        _hud.mode = MBProgressHUDModeText;
        _hud.detailsLabelText =  @"请稍等";
        [self.hud hide:YES  afterDelay:1];
        //        self.hud
        
    }else{
        
        [self payStart:paymentID];
    }
}



#pragma mark - Private Method
/**
 *  此处方法为模拟获取订单号(随机生成唯一的订单号)
 *  商户请传自己公司商品订单对应的订单号，不可使用此随机方法
 */
- (NSString *)generateTradeNO
{
//    static int kNumber = 15;
//    NSString *sourceStr = @"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//    NSMutableString *resultStr = [[NSMutableString alloc] init];
//    srand((unsigned)time(0));
//    for (int i = 0; i < kNumber; i++)
//    {
//        unsigned index = rand() % [sourceStr length];
//        NSString *oneStr = [sourceStr substringWithRange:NSMakeRange(index, 1)];
//        [resultStr appendString:oneStr];
//    }
//    return resultStr;
    CFUUIDRef theUUID = CFUUIDCreate(NULL);
    CFStringRef guid = CFUUIDCreateString(NULL, theUUID);
    CFRelease(theUUID);
    NSString *uuidString = [((__bridge NSString *)guid) stringByReplacingOccurrencesOfString:@"-" withString:@""];
    CFRelease(guid);
    NSString* orderID=[uuidString lowercaseString];
    return orderID;
}


//h5 payment
//-(void)H5PayUsingWebView:(NSString*)urlData
//{
//}
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    return YES;
}
-(void)openURL:(NSURL *)object complete:(void(^)(BOOL))complete
{
    UIApplication *application = nil;
    application = [UIApplication sharedApplication];
    SEL selector = @selector(openURL:options:completionHandler:);
    if ([UIApplication instancesRespondToSelector:selector])
    {
        [application openURL:object
                     options:[NSDictionary dictionary]
           completionHandler:complete];
    }
    else
    {
        if (complete) complete([application openURL:object]);
    }
}
@end
