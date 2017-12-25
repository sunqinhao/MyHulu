//
//  TalkingDataControll.m
//  SG
//
//  Created by pfu on 2017/5/11.
//
//

#import "SANGUOTalkingDataControll.h"
#import "TalkingDataGA.h"
#import "TalkingDataAppCpa.h"
#include "SANGUOTalkingDataControll.h"
#import "IOSDefines.h"
@implementation TalkingDataControll

static TalkingDataControll *shareManeger;
/*-----------------------------------------------------------------------------
 * Expires of keys created in writable slaves
 *
 * Normally slaves do not process expires: they wait the masters to synthesize
 * DEL operations in order to retain consistency. However writable slaves are
 * an exception: if a key is created in the slave and an expire is assigned
 * to it, we need a way to expire such a key, since the master does not know
 * anything about such a key.
 *
 * In order to do so, we track keys created in the slave side with an expire
 * set, and call the expireSlaveKeys() function from time to time in order to
 * reclaim the keys if they already expired.
 *
 * Note that the use case we are trying to cover here, is a popular one where
 * slaves are put in writable mode in order to compute slow operations in
 * the slave side that are mostly useful to actually read data in a more
 * processed way. Think at sets intersections in a tmp key, with an expire so
 * that it is also used as a cache to avoid intersecting every time.
 *
 * This implementation is currently not perfect but a lot better than leaking
 * the keys as implemented in 3.2.
 *----------------------------------------------------------------------------*/

/* The dictionary where we remember key names and database ID of keys we may
 * want to expire from the slave. Since this function is not often used we
 * don't even care to initialize the database at startup. We'll do it once
 * the feature is used the first time, that is, when rememberSlaveKeyWithExpire()
 * is called.
 *
 * The dictionary has an SDS string representing the key as the hash table
 * key, while the value is a 64 bit unsigned integer with the bits corresponding
 * to the DB where the keys may exist set to 1. Currently the keys created
 * with a DB id > 63 are not expired, but a trivial fix is to set the bitmap
 * to the max 64 bit unsigned value when we know there is a key with a DB
 * ID greater than 63, and check all the configured DBs in such a case. */
+(TalkingDataControll*)shareManager
{
    static dispatch_once_t once;
    dispatch_once(&once,^{
        if (!shareManeger) {
            shareManeger = [[TalkingDataControll alloc]init];
            [shareManeger initMob];
        }
    }
                  );
    return shareManeger;
}
/*-----------------------------------------------------------------------------
 * Expires of keys created in writable slaves
 *
 * Normally slaves do not process expires: they wait the masters to synthesize
 * DEL operations in order to retain consistency. However writable slaves are
 * an exception: if a key is created in the slave and an expire is assigned
 * to it, we need a way to expire such a key, since the master does not know
 * anything about such a key.
 *
 * In order to do so, we track keys created in the slave side with an expire
 * set, and call the expireSlaveKeys() function from time to time in order to
 * reclaim the keys if they already expired.
 *
 * Note that the use case we are trying to cover here, is a popular one where
 * slaves are put in writable mode in order to compute slow operations in
 * the slave side that are mostly useful to actually read data in a more
 * processed way. Think at sets intersections in a tmp key, with an expire so
 * that it is also used as a cache to avoid intersecting every time.
 *
 * This implementation is currently not perfect but a lot better than leaking
 * the keys as implemented in 3.2.
 *----------------------------------------------------------------------------*/

/* The dictionary where we remember key names and database ID of keys we may
 * want to expire from the slave. Since this function is not often used we
 * don't even care to initialize the database at startup. We'll do it once
 * the feature is used the first time, that is, when rememberSlaveKeyWithExpire()
 * is called.
 *
 * The dictionary has an SDS string representing the key as the hash table
 * key, while the value is a 64 bit unsigned integer with the bits corresponding
 * to the DB where the keys may exist set to 1. Currently the keys created
 * with a DB id > 63 are not expired, but a trivial fix is to set the bitmap
 * to the max 64 bit unsigned value when we know there is a key with a DB
 * ID greater than 63, and check all the configured DBs in such a case. */
-(void)initMob{
    NSLog(@"umengfilename=  %@",umengKeyFileName);
    // NSLog(@"TARGET_CHANNEL=%@",TARGET_CHANNEL);
    NSString *plistPath = [[NSBundle mainBundle] pathForResource:umengKeyFileName ofType:@"plist"];
    NSDictionary *dictionary = [[NSDictionary alloc] initWithContentsOfFile:plistPath];
    NSLog(@"dictionary = %@",dictionary);
//    NSString* umengKey=[dictionary objectForKey:@"UmengKey"];
    NSString* talkingDataKey= [dictionary objectForKey:@"TalkingDataAPPID"];
//    UMConfigInstance.appKey = umengKey;
//    //UMConfigInstance.appKey =UmengAppKey;
//    UMConfigInstance.channelId = @"App Store";
//    UMConfigInstance.eSType = E_UM_GAME; // 仅适用于游戏场景，应用统计不用设置
//    
//    [MobClick startWithConfigure:UMConfigInstance];
    
    //NSLog(@"umeng appkey=%@",UmengAppKey);
//    NSString *version = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
//    [MobClick setAppVersion:version];
    NSString *versionStr = [[NSBundle mainBundle]objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
    NSArray* arr= [versionStr componentsSeparatedByString:@"."];
    NSString* ver=[arr objectAtIndex:0];
    NSString* bundleId=[[NSBundle mainBundle]bundleIdentifier];
    NSString* channelFlag=[NSString stringWithFormat:@"AppStore_%@_%@",ver,bundleId];
    
    //[TalkingDataGA onStart:@"BC02994C667943D599B4E3F35FFE4AE8" withChannelId:channelFlag];//@"AppStore_4_chuanqi"];
   
    
    
    //=======ad traking
//    [TalkingDataAppCpa init:@"92DF11E95A3445C0BB45F4B7BA44E561" withChannelId:channelFlag ];
    
      [TalkingDataAppCpa init:talkingDataKey withChannelId:channelFlag ];
      //NSLog(@"TalkingDataAPPID11=  %@",talkingDataKey);
    
}
/*-----------------------------------------------------------------------------
 * Expires of keys created in writable slaves
 *
 * Normally slaves do not process expires: they wait the masters to synthesize
 * DEL operations in order to retain consistency. However writable slaves are
 * an exception: if a key is created in the slave and an expire is assigned
 * to it, we need a way to expire such a key, since the master does not know
 * anything about such a key.
 *
 * In order to do so, we track keys created in the slave side with an expire
 * set, and call the expireSlaveKeys() function from time to time in order to
 * reclaim the keys if they already expired.
 *
 * Note that the use case we are trying to cover here, is a popular one where
 * slaves are put in writable mode in order to compute slow operations in
 * the slave side that are mostly useful to actually read data in a more
 * processed way. Think at sets intersections in a tmp key, with an expire so
 * that it is also used as a cache to avoid intersecting every time.
 *
 * This implementation is currently not perfect but a lot better than leaking
 * the keys as implemented in 3.2.
 *----------------------------------------------------------------------------*/

/* The dictionary where we remember key names and database ID of keys we may
 * want to expire from the slave. Since this function is not often used we
 * don't even care to initialize the database at startup. We'll do it once
 * the feature is used the first time, that is, when rememberSlaveKeyWithExpire()
 * is called.
 *
 * The dictionary has an SDS string representing the key as the hash table
 * key, while the value is a 64 bit unsigned integer with the bits corresponding
 * to the DB where the keys may exist set to 1. Currently the keys created
 * with a DB id > 63 are not expired, but a trivial fix is to set the bitmap
 * to the max 64 bit unsigned value when we know there is a key with a DB
 * ID greater than 63, and check all the configured DBs in such a case. */
-(void)TalkingDataWithEventId:(NSString*)eventID Label:(NSString*)label{
//    [MobClick event:eventID label:label];
    
}

-(void)TalkingDataWithEventId:(NSString *)eventID attributes:(NSDictionary *)attributes{
//    [MobClick event:(NSString *)eventID attributes:(NSDictionary *)attributes];
   [ TalkingDataGA onEvent:eventID eventData:attributes];

}
/*-----------------------------------------------------------------------------
 * Expires of keys created in writable slaves
 *
 * Normally slaves do not process expires: they wait the masters to synthesize
 * DEL operations in order to retain consistency. However writable slaves are
 * an exception: if a key is created in the slave and an expire is assigned
 * to it, we need a way to expire such a key, since the master does not know
 * anything about such a key.
 *
 * In order to do so, we track keys created in the slave side with an expire
 * set, and call the expireSlaveKeys() function from time to time in order to
 * reclaim the keys if they already expired.
 *
 * Note that the use case we are trying to cover here, is a popular one where
 * slaves are put in writable mode in order to compute slow operations in
 * the slave side that are mostly useful to actually read data in a more
 * processed way. Think at sets intersections in a tmp key, with an expire so
 * that it is also used as a cache to avoid intersecting every time.
 *
 * This implementation is currently not perfect but a lot better than leaking
 * the keys as implemented in 3.2.
 *----------------------------------------------------------------------------*/

/* The dictionary where we remember key names and database ID of keys we may
 * want to expire from the slave. Since this function is not often used we
 * don't even care to initialize the database at startup. We'll do it once
 * the feature is used the first time, that is, when rememberSlaveKeyWithExpire()
 * is called.
 *
 * The dictionary has an SDS string representing the key as the hash table
 * key, while the value is a 64 bit unsigned integer with the bits corresponding
 * to the DB where the keys may exist set to 1. Currently the keys created
 * with a DB id > 63 are not expired, but a trivial fix is to set the bitmap
 * to the max 64 bit unsigned value when we know there is a key with a DB
 * ID greater than 63, and check all the configured DBs in such a case. */
-(void )TalkingDataOnRegist:(NSString*)userid
{
    [TalkingDataAppCpa onRegister:userid];
    
}
/*-----------------------------------------------------------------------------
 * Expires of keys created in writable slaves
 *
 * Normally slaves do not process expires: they wait the masters to synthesize
 * DEL operations in order to retain consistency. However writable slaves are
 * an exception: if a key is created in the slave and an expire is assigned
 * to it, we need a way to expire such a key, since the master does not know
 * anything about such a key.
 *
 * In order to do so, we track keys created in the slave side with an expire
 * set, and call the expireSlaveKeys() function from time to time in order to
 * reclaim the keys if they already expired.
 *
 * Note that the use case we are trying to cover here, is a popular one where
 * slaves are put in writable mode in order to compute slow operations in
 * the slave side that are mostly useful to actually read data in a more
 * processed way. Think at sets intersections in a tmp key, with an expire so
 * that it is also used as a cache to avoid intersecting every time.
 *
 * This implementation is currently not perfect but a lot better than leaking
 * the keys as implemented in 3.2.
 *----------------------------------------------------------------------------*/

/* The dictionary where we remember key names and database ID of keys we may
 * want to expire from the slave. Since this function is not often used we
 * don't even care to initialize the database at startup. We'll do it once
 * the feature is used the first time, that is, when rememberSlaveKeyWithExpire()
 * is called.
 *
 * The dictionary has an SDS string representing the key as the hash table
 * key, while the value is a 64 bit unsigned integer with the bits corresponding
 * to the DB where the keys may exist set to 1. Currently the keys created
 * with a DB id > 63 are not expired, but a trivial fix is to set the bitmap
 * to the max 64 bit unsigned value when we know there is a key with a DB
 * ID greater than 63, and check all the configured DBs in such a case. */
-(void)TalkingDataOnCreateRole:(NSString*)name
{

    [TalkingDataAppCpa onCreateRole:name];
}
-(void)TalkingDataOnLogin:(NSString*)account
{

    [TalkingDataAppCpa onLogin:account];
}
/*-----------------------------------------------------------------------------
 * Expires of keys created in writable slaves
 *
 * Normally slaves do not process expires: they wait the masters to synthesize
 * DEL operations in order to retain consistency. However writable slaves are
 * an exception: if a key is created in the slave and an expire is assigned
 * to it, we need a way to expire such a key, since the master does not know
 * anything about such a key.
 *
 * In order to do so, we track keys created in the slave side with an expire
 * set, and call the expireSlaveKeys() function from time to time in order to
 * reclaim the keys if they already expired.
 *
 * Note that the use case we are trying to cover here, is a popular one where
 * slaves are put in writable mode in order to compute slow operations in
 * the slave side that are mostly useful to actually read data in a more
 * processed way. Think at sets intersections in a tmp key, with an expire so
 * that it is also used as a cache to avoid intersecting every time.
 *
 * This implementation is currently not perfect but a lot better than leaking
 * the keys as implemented in 3.2.
 *----------------------------------------------------------------------------*/

/* The dictionary where we remember key names and database ID of keys we may
 * want to expire from the slave. Since this function is not often used we
 * don't even care to initialize the database at startup. We'll do it once
 * the feature is used the first time, that is, when rememberSlaveKeyWithExpire()
 * is called.
 *
 * The dictionary has an SDS string representing the key as the hash table
 * key, while the value is a 64 bit unsigned integer with the bits corresponding
 * to the DB where the keys may exist set to 1. Currently the keys created
 * with a DB id > 63 are not expired, but a trivial fix is to set the bitmap
 * to the max 64 bit unsigned value when we know there is a key with a DB
 * ID greater than 63, and check all the configured DBs in such a case. */
- (void)TalkingDataOnPay:(NSString *)account withOrderId:(NSString *)orderId withAmount:(int)amount itemID:(NSString*)itemid ItemCount:(int )itemcount IapId:(NSString*)iapId
{
  [TalkingDataAppCpa onPay:[TalkingDataAppCpa getDeviceId] withOrderId:orderId withAmount:amount withCurrencyType:@"CNY" withPayType:@"Apple Pay" withItemId:itemid withItemCount:itemcount];

    [TDGAVirtualCurrency onChargeRequst:orderId iapId:iapId currencyAmount:amount/100 currencyType:@"CNY" virtualCurrencyAmount:amount paymentType:@"App store"];
    [TDGAVirtualCurrency onChargeSuccess:orderId];
}
/*-----------------------------------------------------------------------------
 * Expires of keys created in writable slaves
 *
 * Normally slaves do not process expires: they wait the masters to synthesize
 * DEL operations in order to retain consistency. However writable slaves are
 * an exception: if a key is created in the slave and an expire is assigned
 * to it, we need a way to expire such a key, since the master does not know
 * anything about such a key.
 *
 * In order to do so, we track keys created in the slave side with an expire
 * set, and call the expireSlaveKeys() function from time to time in order to
 * reclaim the keys if they already expired.
 *
 * Note that the use case we are trying to cover here, is a popular one where
 * slaves are put in writable mode in order to compute slow operations in
 * the slave side that are mostly useful to actually read data in a more
 * processed way. Think at sets intersections in a tmp key, with an expire so
 * that it is also used as a cache to avoid intersecting every time.
 *
 * This implementation is currently not perfect but a lot better than leaking
 * the keys as implemented in 3.2.
 *----------------------------------------------------------------------------*/

/* The dictionary where we remember key names and database ID of keys we may
 * want to expire from the slave. Since this function is not often used we
 * don't even care to initialize the database at startup. We'll do it once
 * the feature is used the first time, that is, when rememberSlaveKeyWithExpire()
 * is called.
 *
 * The dictionary has an SDS string representing the key as the hash table
 * key, while the value is a 64 bit unsigned integer with the bits corresponding
 * to the DB where the keys may exist set to 1. Currently the keys created
 * with a DB id > 63 are not expired, but a trivial fix is to set the bitmap
 * to the max 64 bit unsigned value when we know there is a key with a DB
 * ID greater than 63, and check all the configured DBs in such a case. */
-(void)TalkingDataSetAccountInfo:(NSString*)accountInfo
{
//    std::string payInfoStr= OsCallback::getPayInfo("");
//    
//    CCLOG("payInfoStr=%s",payInfoStr.c_str());
//    NSString* payInfo=[NSString stringWithFormat:@"%s", payInfoStr.c_str()];
//    NSData* data=[accountInfo dataUsingEncoding:NSUTF8StringEncoding ];
//    NSError* error;
//    NSDictionary* json = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:&error ];
//    NSString* roleName= [json objectForKey:@"roleName"];
//    NSString* roleLevel= [json objectForKey:@"roleLevel"];
//    NSString* ZoneName= [json objectForKey:@"zoneName"];
//    NSString* gender= [json objectForKey:@"gender"];
//    NSString* uid=[[NSUserDefaults standardUserDefaults]objectForKey:@"Login_UID"];
//    NSLog(@"uid=%@",uid);
//    TDGAAccount* account=[TDGAAccount setAccount:[TalkingDataAppCpa getDeviceId]];
//    [account setAccountType:kAccountAnonymous];
//    [account setAccountName:roleName];
//    [account setLevel: [roleLevel intValue]];
//    [account setGameServer:ZoneName];
//    [account setGender:[gender intValue]==0?kGenderMale:kGenderFemale];
    
}
@end
