//
//  OsCallback.cpp
//  CandyJs
//
//  Created by Jason on 15/10/28.
//
//

#include "OsCallback.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
//#include "scripting/js-bindings/manual/ScriptingCore.h"
//#include "ScriptingCore.h"
#include "IOSDefines.h"
#include "CommonAdapter.h"
//////////////////////////////////////////////////////////////////////////////////////////////
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//////////////////////////////////////////////////////////////////////////////////////////////
void JSFunction::callFuncWithNoParam(const string &funcName)
{
    ScriptingCore* sc = ScriptingCore::getInstance();
    JSContext* cx=sc->getGlobalContext();
    JS::RootedValue nsval(cx);
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    JS_GetProperty(cx, global, OS_DELEGATE, &nsval);
    if(nsval != JSVAL_VOID)
    {
        sc->executeFunctionWithOwner(nsval,funcName.c_str(),0,NULL);
    }
}

void JSFunction::callFuncWithOneInt(const string &funcName,int param)
{
    ScriptingCore* sc = ScriptingCore::getInstance();
    JSContext* cx=sc->getGlobalContext();
    JS::RootedValue nsval(cx);
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    JS_GetProperty(cx, global, OS_DELEGATE, &nsval);
    if(nsval != JSVAL_VOID)
    {
        jsval v[] = {
            v[0] = int32_to_jsval(cx, param)
        };
        sc->executeFunctionWithOwner(nsval, funcName.c_str(), 1, v);
    }
}

void JSFunction::callFuncWithOneString(const string &funcName,const string &param)
{
    ScriptingCore* sc = ScriptingCore::getInstance();
    JSContext* cx=sc->getGlobalContext();
    JS::RootedValue nsval(cx);
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    JS_GetProperty(cx, global, OS_DELEGATE, &nsval);
    if(nsval != JSVAL_VOID)
    {
        jsval v[] = {
            v[0] = std_string_to_jsval(cx,param)
        };
        sc->executeFunctionWithOwner(nsval, funcName.c_str(), 1, v);
    }
}
void JSFunction::callFuncWithTwoString(const string &funcName,const string &param,const string &param2)
{
    ScriptingCore* sc = ScriptingCore::getInstance();
    JSContext* cx=sc->getGlobalContext();
    JS::RootedValue nsval(cx);
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    JS_GetProperty(cx, global, OS_DELEGATE, &nsval);
    if(nsval != JSVAL_VOID)
    {
        jsval v[] = {
            v[0] = std_string_to_jsval(cx,param),
            v[1] = std_string_to_jsval(cx,param2)
        };
        sc->executeFunctionWithOwner(nsval, funcName.c_str(), 2, v);
    }
}

void JSFunction::callFuncWithTwoInt(const string &funcName,int param,int param2)
{
    ScriptingCore* sc = ScriptingCore::getInstance();
    JSContext* cx=sc->getGlobalContext();
    JS::RootedValue nsval(cx);
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    JS_GetProperty(cx, global, OS_DELEGATE, &nsval);
    if(nsval != JSVAL_VOID)
    {
        jsval v[] = {
            v[0] = int32_to_jsval(cx, param),
            v[1] = int32_to_jsval(cx, param2)
        };
        sc->executeFunctionWithOwner(nsval, funcName.c_str(), 2, v);
    }
}
void JSFunction::callFuncWithThreeString(const string &funcName,const string &param,const string &param2,const string &param3)
{
    ScriptingCore* sc = ScriptingCore::getInstance();
    JSContext* cx=sc->getGlobalContext();
    JS::RootedValue nsval(cx);
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    JS_GetProperty(cx, global, OS_DELEGATE, &nsval);
    if(nsval != JSVAL_VOID)
    {
        jsval v[] = {
            v[0] = std_string_to_jsval(cx,param),
            v[1] = std_string_to_jsval(cx,param2),
            v[2] = std_string_to_jsval(cx,param3)
        };
        sc->executeFunctionWithOwner(nsval, funcName.c_str(), 3, v);
    }
    
    
}

void JSFunction::callFunctionJSWithOneStringPara(const string &funcName,const string &param)
{
    ScriptingCore* sc = ScriptingCore::getInstance();
    JSContext* cx=sc->getGlobalContext();
    js_proxy_t* p= jsb_get_native_proxy(cx);
    jsval retval;
    jsval v[]={
        v[0]  = std_string_to_jsval( cx, param),
    };
    ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), funcName.c_str(), 1, v);

}

//add lisj
std::string JSFunction::callFuncWithRtnValue(const string &funcName)
{
    ScriptingCore* sc = ScriptingCore::getInstance();
    JSContext* cx=sc->getGlobalContext();
    JS::RootedValue nsval(cx);
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    JS_GetProperty(cx, global, OS_DELEGATE, &nsval);
    // if(nsval != JSVAL_VOID)
    // {
    jsval v[] = {
        //v[0] = std_string_to_jsval(cx,param),
        //            v[1] = std_string_to_jsval(cx,param2),
        //            v[2] = std_string_to_jsval(cx,param3)
    };
    
    
    JS::MutableHandleValue retVal(&nsval);
    JS::RootedValue retVal2(cx);
    //JS::RootedValue nsval(cx);
    //sc->executeFunctionWithOwner(nsval, funcName.c_str(), 0,  v,  &retVal2);
    sc->executeFunctionWithOwner(nsval, funcName.c_str(), 0, v, &retVal2);
    std::string arg0;
    //JSContext *cx, JS::HandleValue v, std::string* ret
    jsval_to_std_string(cx, retVal2,&arg0);
    //   sc->executeFunctionWithOwner(nsval, funcName.c_str(), 0 , v, retVal);
    //}
    //================
    
    // jsval ret;
    // ScriptingCore::getInstance()->evalString("IOS1", &ret);
    // JS::CallArgs args = JS::CallArgsFromVp(1, &retVal2);
    //// JS::CallReceiverFromArgv(JS::Value *argv)
    //  bool ok = true;
    //  std::string arg0;
    // ok &= jsval_to_std_string(cx, args.get(0), &arg0);
    
    // CCLOG("return str=%s",arg0.c_str());
    return arg0;
}
//////////////////////////////////////////////////////////////////////////////////////////////
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//////////////////////////////////////////////////////////////////////////////////////////////
///*************************以下为平台回调方法****************************///
void OsCallback::sendDataToGameServer(const char* id,const char* data,const char* bundleId)
{
    //    const char* a ="";
    string id_str =string(id);
    string data_str=string(data );
    string bundelId_str=bundleId;
    CCLOG("id_str =%s",id_str.c_str());
//   JSFunction::callFuncWithTwoString("iOSSendPaydataToGameServer",id_str,data_str);
    JSFunction::callFuncWithThreeString("iOSSendPaydataToGameServer2", id_str, data_str, bundelId_str);
//    JSFunction::callFuncWithThreeString("iOSSendPaydataToGameServer2", id_str, data_str, bundelId_str);
    //    ("iOSSendPaydataToGameServer",id_str,data_str);
}


void OsCallback::orderFinish(int result)
{
    JSFunction::callFuncWithOneInt("oderFinish",result);
}

void OsCallback::IOSLoginCallbackWithToken(const char* token)
{
    CCLOG("token OsCallback =%s",token);
     string token_str =string(token);

    int flag=getActivityOpenFlag();
    
    CCLOG("OsCallback::IOSLoginCallbackWithToken activityOpen flag=%d",flag);
    //JSFunction::callFuncWithOneString("IOSLoginCallback",token_str );
    if(flag ==1)
    {
          //正式服务器
          JSFunction::callFuncWithTwoString("IOSLoginCallback2",token_str,IOS_CHANNEL );
        CCLOG("正式服务器");
    }else{
//        //区分评审服务器
          JSFunction::callFuncWithTwoString("IOSLoginCallback2",token_str,IOS_SHENHE_CHANNEL );
        CCLOG("评审服务器");
    }
}

void OsCallback::IOSLoginCallbackWithTokenAndChannel(const char* token,const char* channel)
{
    CCLOG("token OsCallback =%s",token);
    CCLOG("channel OsCallback =%s",channel);
    string token_str =string(token);
    string channel_str =string(channel);
    
    //    int flag=getActivityOpenFlag();
    //    if(flag ==1)
    //    {
    JSFunction::callFuncWithTwoString("IOSLoginCallback2",token_str,channel_str );
    //    }else{
    //        //区分评审服务器
    //        JSFunction::callFuncWithTwoString("IOSLoginCallback2",token_str,IOS_CHANNEL );
    //    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa//
//////////////////////////////////////////////////////////////////////////////////////////////
//IOSActivityOpenSetting
void OsCallback::IOSActivityOpenSetting(int flag)
{
    CCLOG("token IOSActivityOpenSetting =%d",flag);
    JSFunction::callFuncWithOneInt("IOSActivityOpenSetting",flag);

}

std::string OsCallback::getPayInfo(const char* payid)
{
    return   JSFunction::callFuncWithRtnValue("IOSGetInfoStr");
    
}
