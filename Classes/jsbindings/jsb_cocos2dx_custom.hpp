#ifndef __cocos2dx_custom_h__
#define __cocos2dx_custom_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_FileTools_class;
extern JSObject *jsb_FileTools_prototype;

bool js_cocos2dx_custom_FileTools_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_FileTools_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_FileTools(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_FileTools_readFromFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_FileTools_getCurVersion(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_FileTools_sendUserInfo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_FileTools_getActivityParameter(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_FileTools_pay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_FileTools_payUsingWebView(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_FileTools_hideFloatMenu(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_FileTools_writeToFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_FileTools_payCompleteCallback(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_FileTools_gameSdkSubmitRoleData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_FileTools_RegistSuccess(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_FileTools_getPaymentSwitchParameter(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_FileTools_MobWithEventId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_FileTools_talkingDataPayment(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_FileTools_showLoginGameWindow(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_FileTools_onLogin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_FileTools_getIOSBundleID(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ZipUtil_class;
extern JSObject *jsb_ZipUtil_prototype;

bool js_cocos2dx_custom_ZipUtil_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_ZipUtil_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_ZipUtil(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_ZipUtil_unCompress(JSContext *cx, uint32_t argc, jsval *vp);
#endif

