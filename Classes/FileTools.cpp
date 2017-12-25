#include "FileTools.h"
#include "cocos2d.h"
#include "CommonAdapter.h"

using namespace cocos2d;

std::string FileTools::readFromFile(std::string &pFileName)
{
    string path = FileUtils::getInstance()->getWritablePath() + pFileName;
    CCLOG("path = %s",path.c_str());
    
    FILE* file = fopen(path.c_str(), "r");
    
    if (file) {
        char* buf;
        int len;
        fseek(file, 0, SEEK_END);
        len = ftell(file);
        rewind(file);
        CCLOG("count the file content len = %d",len);
        buf = (char*)malloc(sizeof(char) * len + 1);
        if (!buf) {
            CCLOG("malloc space is not enough.");
            return NULL;
        }

        int rLen = fread(buf, sizeof(char), len, file);
        buf[rLen] = '\0';
        CCLOG("has read Length = %d",rLen);
        CCLOG("has read content = %s",buf);
        
        string result = buf;
        fclose(file);
        free(buf);
        return result;
    }
    else
        CCLOG("open file error.");
    
    return NULL;
    
}

bool FileTools::writeToFile(std::string &pFileName,std::string &text)
{
    string path = pFileName;
    CCLOG("wanna save file path = %s",path.c_str());

    FILE* file = fopen(path.c_str(), "w");
    if (file) {  
        fputs(text.c_str(), file);  
        fclose(file);  
        return true;
    }  
    else  
    {
        CCLOG("save file error."); 
    }
    return false; 
}

void FileTools::pay(std::string & rechargeId)
{
    CCLOG("FileTools rechargeId %s",rechargeId.c_str());
     ApplePay(rechargeId.c_str() );
}
void FileTools::payCompleteCallback(std::string &pid )
{
    ApplePayCompleteCallback(pid.c_str());
}

void FileTools::showLoginGameWindow()
{
    showLoginView();
}
void FileTools::hideFloatMenu()
{
    hideFloatMenuView();
}
void FileTools::MobWithEventId(std::string& evnetid,std::string& label,std::string& count)
{
    UmengWithEvnetId(evnetid.c_str(),label.c_str(),count.c_str());
}

int FileTools::getActivityParameter()
{
    int para=getActivityOpenFlag();
    CCLOG("File::Tool ->getActivityParameter %d",para );
    return para;
}
std::string  FileTools::getIOSBundleID()
{
    return getBundleID();
}

void FileTools::payUsingWebView(std::string & URLData)
{
//    PayIapyUsingWebView(URLData);
}

int FileTools::getPaymentSwitchParameter()
{
    int para=getPaymentSwitchFlag();
    CCLOG("File::Tool ->getPaymentSwitchParameter %d",para );
    return para;
}
std::string FileTools::getCurVersion()
{
    return getVersion();
}
void FileTools::RegistSuccess(std::string & account)
{
    CCLOG("FileTools ->RegistSuccess %s",account.c_str());
    RigestUsingReyun(account);
}

void FileTools::sendUserInfo(std::string& accountInfo)
{
    setUserAccountInfo(accountInfo);
    CCLOG("FileTools ->sendUserInfo %s",accountInfo.c_str());
}

void FileTools::onLogin(std::string& account)
{
    OnGamelogin(account);
    CCLOG("FileTools ->onLogin %s",account.c_str());
}
void FileTools::talkingDataPayment(std::string& orderid,int price,std::string& itemid,int itemcount,std::string& productDesc)
{
    sendGamePaymentTalkingData(orderid, price, itemid, itemcount, productDesc);
}
