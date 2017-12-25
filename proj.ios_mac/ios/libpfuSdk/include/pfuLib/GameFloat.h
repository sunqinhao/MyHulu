//
//  GameFloat.h
//  testframework
//
//  Created by pfu on 16/6/16.
//  Copyright © 2016年 pfu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
//#import "Menu/FloatView.h"
#import "ViewControllerDelegate.h"
#import "FloatMenuDelegate.h"
//#import "ViewController.h"
@interface GameFloat : NSObject<ViewControllerDelegate>
//@property(nonatomic,retain,strong) UIWindow* _boardWindow;
@property(nonatomic,retain) UIView* _boardView;
//+ (GameFloat *)getInstanceFloatView:(UIViewController*)rootview;
@property (strong, nonatomic) UIWindow *window;
//@property (strong, nonatomic) ViewController * viewController;

@property(nonatomic,retain) id<FloatMenuDelegate> delegate;
@property (strong,nonatomic)  UIWindow* floatWindow;
//@property (strong,nonatomic)   FloatView * floatView;

+(void)initFloatView:(UIViewController*)rootview;
+ (GameFloat *)getInstanceFloatView;
- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration;
- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation;
-(void)PresentLoginView;
@end
