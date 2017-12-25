#include "jsb_cocos2dx_custom.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
//#include "cocos2d_specifics.hpp"
#include "FileTools.h"
#include "ZipUtil.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && initializing.toBoolean();
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JS::RootedObject proto(cx, typeClass->proto.ref());
        JS::RootedObject parent(cx, typeClass->parentProto.ref());
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
        
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_FileTools_class;
JSObject *jsb_FileTools_prototype;

bool js_cocos2dx_custom_FileTools_readFromFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_FileTools_readFromFile : Error processing arguments");
        std::string ret = FileTools::readFromFile(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_readFromFile : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_FileTools_getCurVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = FileTools::getCurVersion();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_getCurVersion : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_FileTools_sendUserInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_FileTools_sendUserInfo : Error processing arguments");
        FileTools::sendUserInfo(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_sendUserInfo : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_FileTools_getActivityParameter(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        int ret = FileTools::getActivityParameter();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_getActivityParameter : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_FileTools_pay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_FileTools_pay : Error processing arguments");
        FileTools::pay(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_pay : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_FileTools_payUsingWebView(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_FileTools_payUsingWebView : Error processing arguments");
        FileTools::payUsingWebView(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_payUsingWebView : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_FileTools_hideFloatMenu(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        FileTools::hideFloatMenu();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_hideFloatMenu : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_FileTools_writeToFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_FileTools_writeToFile : Error processing arguments");
        bool ret = FileTools::writeToFile(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_writeToFile : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_FileTools_payCompleteCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_FileTools_payCompleteCallback : Error processing arguments");
        FileTools::payCompleteCallback(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_payCompleteCallback : wrong number of arguments");
    return false;
}

//bool js_cocos2dx_custom_FileTools_gameSdkSubmitRoleData(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if (argc == 1) {
//        std::string arg0;
//        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_FileTools_gameSdkSubmitRoleData : Error processing arguments");
//        FileTools::gameSdkSubmitRoleData(arg0);
//        args.rval().setUndefined();
//        return true;
//    }
//    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_gameSdkSubmitRoleData : wrong number of arguments");
//    return false;
//}

bool js_cocos2dx_custom_FileTools_RegistSuccess(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_FileTools_RegistSuccess : Error processing arguments");
        FileTools::RegistSuccess(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_RegistSuccess : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_FileTools_getPaymentSwitchParameter(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        int ret = FileTools::getPaymentSwitchParameter();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_getPaymentSwitchParameter : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_FileTools_MobWithEventId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_FileTools_MobWithEventId : Error processing arguments");
        FileTools::MobWithEventId(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_MobWithEventId : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_FileTools_talkingDataPayment(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 5) {
        std::string arg0;
        int arg1;
        std::string arg2;
        int arg3;
        std::string arg4;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        ok &= jsval_to_std_string(cx, args.get(4), &arg4);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_FileTools_talkingDataPayment : Error processing arguments");
        FileTools::talkingDataPayment(arg0, arg1, arg2, arg3, arg4);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_talkingDataPayment : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_FileTools_showLoginGameWindow(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        FileTools::showLoginGameWindow();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_showLoginGameWindow : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_FileTools_onLogin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_FileTools_onLogin : Error processing arguments");
        FileTools::onLogin(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_onLogin : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_FileTools_getIOSBundleID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = FileTools::getIOSBundleID();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_FileTools_getIOSBundleID : wrong number of arguments");
    return false;
}



void js_FileTools_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (FileTools)", obj);
}

void js_register_cocos2dx_custom_FileTools(JSContext *cx, JS::HandleObject global) {
    jsb_FileTools_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_FileTools_class->name = "FileTools";
    jsb_FileTools_class->addProperty = JS_PropertyStub;
    jsb_FileTools_class->delProperty = JS_DeletePropertyStub;
    jsb_FileTools_class->getProperty = JS_PropertyStub;
    jsb_FileTools_class->setProperty = JS_StrictPropertyStub;
    jsb_FileTools_class->enumerate = JS_EnumerateStub;
    jsb_FileTools_class->resolve = JS_ResolveStub;
    jsb_FileTools_class->convert = JS_ConvertStub;
    jsb_FileTools_class->finalize = js_FileTools_finalize;
    jsb_FileTools_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("readFromFile", js_cocos2dx_custom_FileTools_readFromFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurVersion", js_cocos2dx_custom_FileTools_getCurVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("sendUserInfo", js_cocos2dx_custom_FileTools_sendUserInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getActivityParameter", js_cocos2dx_custom_FileTools_getActivityParameter, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pay", js_cocos2dx_custom_FileTools_pay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("payUsingWebView", js_cocos2dx_custom_FileTools_payUsingWebView, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("hideFloatMenu", js_cocos2dx_custom_FileTools_hideFloatMenu, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("writeToFile", js_cocos2dx_custom_FileTools_writeToFile, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("payCompleteCallback", js_cocos2dx_custom_FileTools_payCompleteCallback, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        //JS_FN("gameSdkSubmitRoleData", js_cocos2dx_custom_FileTools_gameSdkSubmitRoleData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("RegistSuccess", js_cocos2dx_custom_FileTools_RegistSuccess, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPaymentSwitchParameter", js_cocos2dx_custom_FileTools_getPaymentSwitchParameter, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("MobWithEventId", js_cocos2dx_custom_FileTools_MobWithEventId, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("talkingDataPayment", js_cocos2dx_custom_FileTools_talkingDataPayment, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("showLoginGameWindow", js_cocos2dx_custom_FileTools_showLoginGameWindow, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onLogin", js_cocos2dx_custom_FileTools_onLogin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIOSBundleID", js_cocos2dx_custom_FileTools_getIOSBundleID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_FileTools_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_FileTools_class,
        dummy_constructor<FileTools>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "FileTools", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<FileTools> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_FileTools_class;
        auto persistentProtoRoot = new (std::nothrow) JS::PersistentRootedObject(cx, jsb_FileTools_prototype);
        p->proto.set(persistentProtoRoot);
//        p->proto = jsb_FileTools_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_ZipUtil_class;
JSObject *jsb_ZipUtil_prototype;

bool js_cocos2dx_custom_ZipUtil_unCompress(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            const char* arg0;
            std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { ok = true; break; }
            bool ret = ZipUtil::unCompress(arg0);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 2) {
            const char* arg0;
            std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            bool ret = ZipUtil::unCompress(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_custom_ZipUtil_unCompress : wrong number of arguments");
    return false;
}


void js_ZipUtil_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ZipUtil)", obj);
}

void js_register_cocos2dx_custom_ZipUtil(JSContext *cx, JS::HandleObject global) {
    jsb_ZipUtil_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_ZipUtil_class->name = "ZipUtil";
    jsb_ZipUtil_class->addProperty = JS_PropertyStub;
    jsb_ZipUtil_class->delProperty = JS_DeletePropertyStub;
    jsb_ZipUtil_class->getProperty = JS_PropertyStub;
    jsb_ZipUtil_class->setProperty = JS_StrictPropertyStub;
    jsb_ZipUtil_class->enumerate = JS_EnumerateStub;
    jsb_ZipUtil_class->resolve = JS_ResolveStub;
    jsb_ZipUtil_class->convert = JS_ConvertStub;
    jsb_ZipUtil_class->finalize = js_ZipUtil_finalize;
    jsb_ZipUtil_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("unCompress", js_cocos2dx_custom_ZipUtil_unCompress, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_ZipUtil_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_ZipUtil_class,
        dummy_constructor<ZipUtil>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ZipUtil", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<ZipUtil> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_ZipUtil_class;
        auto persistentProtoRoot = new (std::nothrow) JS::PersistentRootedObject(cx, jsb_ZipUtil_prototype);
        p->proto.set(persistentProtoRoot);
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "xx", &ns);

    js_register_cocos2dx_custom_FileTools(cx, ns);
    js_register_cocos2dx_custom_ZipUtil(cx, ns);
}

