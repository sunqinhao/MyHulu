#ifndef __FILEUTILS_H__
#define __FILEUTILS_H__

#include "string"

using namespace std;

class FileTools 
{
public:
	static std::string readFromFile(std::string &pFileName);
	static bool writeToFile(std::string &pFileName,std::string &text);
    static void pay(std::string &rechargeId);
    static void payCompleteCallback(std::string &pid );
    static void showLoginGameWindow();
    static void MobWithEventId(std::string& evnetid,std::string& label,std::string& count);
    static int getActivityParameter();
    static void hideFloatMenu();
    static std::string  getIOSBundleID();
    static void payUsingWebView(std::string & URLData);
    static int getPaymentSwitchParameter();
    static std::string getCurVersion();
    static void RegistSuccess(std::string& account);
    static void sendUserInfo(std::string& accountInfo);
    static void onLogin(std::string& account);
    static void talkingDataPayment(std::string& orderid,int price,std::string& itemid,int itemcount,std::string& productDesc);
};

#endif
