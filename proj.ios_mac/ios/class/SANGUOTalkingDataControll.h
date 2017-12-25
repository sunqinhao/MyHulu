//
//  TalkingDataControll.h
//  SG
//
//  Created by pfu on 2017/5/11.
//
//

#import <Foundation/Foundation.h>
#import <SystemConfiguration/SystemConfiguration.h>
@interface TalkingDataControll : NSObject
+(TalkingDataControll*)shareManager;
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
-(void)TalkingDataWithEventId:(NSString*)eventID Label:(NSString*)label;
-(void)TalkingDataWithEventId:(NSString *)eventID attributes:(NSDictionary *)attributes;
-(void)TalkingDataOnLogin:(NSString*)account;
-(void )TalkingDataOnRegist:(NSString*)userid;
-(void)TalkingDataOnCreateRole:(NSString*)name;
-(void)TalkingDataSetAccountInfo:(NSString*)accountInfo;
- (void)TalkingDataOnPay:(NSString *)account withOrderId:(NSString *)orderId withAmount:(int)amount itemID:(NSString*)itemid ItemCount:(int )itemcount  IapId:(NSString*)iapId;

@end
