//
//  OsCallback.h
//  CandyJs
//
//  Created by Jason on 15/10/28.
//
//

#ifndef CandyJs_OsCallback_h
#define CandyJs_OsCallback_h

#include <string>
#include "jsapi.h"
#include "jsfriendapi.h"

using namespace std;
#define OS_DELEGATE "JSB_Delegate"

class JSFunction
{
public:
    static void callFuncWithNoParam(const string &funcName);
    static void callFuncWithOneInt(const string &funcName,int param);
    static void callFuncWithOneString(const string &funcName,const string &param);
    
    static void callFuncWithTwoInt(const string &funcName,int param,int param2);
    static void callFuncWithTwoString(const string &funcName,const string &param,const string &param2);
    static  void callFuncWithThreeString(const string &funcName,const string &param,const string &param2,const string &param3);
    //test
    static void callFunctionJSWithOneStringPara(const string &funcName,const string &param);
    static std::string  callFuncWithRtnValue(const string &funcName);
};



class OsCallback
{
public:

    static void orderFinish(int result);
//    static void sendDataToGameServer(const char* id,const char* data);
    static void sendDataToGameServer(const char* id,const char* data,const char* bundleId);
    static void IOSLoginCallbackWithToken(const char* token);
    static void IOSLoginCallbackWithTokenAndChannel(const char* token,const char* channel);
    static void IOSActivityOpenSetting(int flag);
    
     static std::string  getPayInfo(const char* payid);
};




#endif


