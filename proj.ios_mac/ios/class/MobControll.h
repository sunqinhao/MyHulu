//
//  MobControll.h
//  Tank
//
//  Created by shb on 15/11/27.
//
//

#import <Foundation/Foundation.h>

@interface MobControll : NSObject

+(MobControll*)shareManager;

-(void)MobWithEventId:(NSString*)eventID Label:(NSString*)label;
-(void)MobWithEventId:(NSString *)eventID attributes:(NSDictionary *)attributes;
@end
