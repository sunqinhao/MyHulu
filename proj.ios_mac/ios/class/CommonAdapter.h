//
//  CommonAdapter.h
//  SG
//
//  Created by pfu on 16/6/29.
//
//

#ifndef __CommonAdapter__
#define __CommonAdapter__
#include "string"

void ApplePay(const char* payid);
void ApplePayCompleteCallback(const char* pid );
void getNetVariable();
void showLoginView();
void UmengWithEvnetId(const char* pid,const char* label,const char* count);
int getActivityOpenFlag();
void hideFloatMenuView();
std::string getBundleID();
//void PayIapyUsingWebView(std::string& URLData);
int getPaymentSwitchFlag();
std::string getVersion();
void RigestUsingReyun(std::string& account);
int getGameSwitchFlag();
void setUserAccountInfo(std::string& accountInfo);
void OnGamelogin(std::string& account);;
void sendGamePaymentTalkingData(std::string& orderId,int price,std::string& productid,int itemcount,std::string& productDes);
#endif /* defined(__Candy__AllAD__) */
