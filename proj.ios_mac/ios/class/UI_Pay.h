#import <StoreKit/StoreKit.h>
#import "MBProgressHUD.h"
#define ProductID_IAP_FORMAT  @"gj00%d"	//$0.99
@interface UI_Pay : UIViewController<UIScrollViewDelegate,SKPaymentTransactionObserver,SKProductsRequestDelegate,MBProgressHUDDelegate,UIWebViewDelegate>
{
     MBProgressHUD *HUD;
    NSMutableDictionary* transactionDictionary;
    NSMutableDictionary* priceDic;
    NSMutableDictionary* paycodeDic;
    NSString* payid;
    //add apppay variable
    NSString* mAppId;
    NSString* mChannel;
    //webview
    UIWebView* mywebview;
}
@property (nonatomic, strong) MBProgressHUD *hud;
@property(nonatomic, retain) SKPaymentTransaction* curtransaction;

+(UI_Pay*)getInstance;

-(void)payComplete:(NSString*)pid;
-(void)initSKPayment;

-(void)buy:(NSString*)type;

//-(void)storeTransaction:(SKPaymentTransaction *)transaction;
-(void)sendTransactionToSever: (SKPaymentTransaction *)transaction;
-(void)failedTransaction: (SKPaymentTransaction *)transaction;
-(void)completeTransaction: (SKPaymentTransaction *)transaction;
//-(void)H5PayUsingWebView:(NSString*)urlData;
@end
