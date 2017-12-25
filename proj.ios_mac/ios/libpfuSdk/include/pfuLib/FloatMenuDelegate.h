//
//  FloatMenuDelegate.h
//  gameFloatMenu
//
//  Created by pfu on 16/7/7.
//  Copyright © 2016年 pfu. All rights reserved.
//

#ifndef FloatMenuDelegate_h
#define FloatMenuDelegate_h

@protocol FloatMenuDelegate <NSObject>
@required
-(void)pfuDidLogin:(NSString*)token;

@end
#endif /* FloatMenuDelegate_h */
