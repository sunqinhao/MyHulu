#include "NET_Message.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"

//NET_ClientMessage
bool NET_ClientMessage::excuteScriptWrite(IO_OutputDataStream* stream)
{
	js_proxy_t * p = jsb_get_native_proxy(this);
	if (!p) return false;

	JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
//	js_proxy_t *proxy = js_get_or_create_proxy<IO_OutputDataStream>(cx, stream);
    js_proxy_t *proxy;
    
    {
        js_type_class_t *typeProxy = js_get_type_from_native<IO_OutputDataStream>(stream);
        if(!typeProxy)
        {
            CCLOGINFO("Coule not fing the IO_OutputDataStream type of native object");
        }
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        JS::RootedObject proto(cx,const_cast<JSObject*>(typeProxy->proto.ref()));
        JS::RootedObject parent(cx,const_cast<JSObject*>(typeProxy->parentProto.ref()));
        JS::RootedObject js_obj(cx,JS_NewObject(cx, typeProxy->jsclass, proto, parent));
        proxy = jsb_new_proxy(stream, js_obj);
    }
    
    jsval jsObj = OBJECT_TO_JSVAL(proxy->obj);

	jsval retval;
    //lisj mod
//	JSBool ret = ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj),  "writeMsg",1,&jsObj,&retval);
	return false;
}


bool NET_ClientMessage::Write(IO_OutputDataStream* stream)
{
	if (bScript)
	{
		return excuteScriptWrite(stream);
	}
	return false;
}

//NET_ServerMessage

NET_ServerMessage::NET_ServerMessage()
:msgsize(0)
,buffer(NULL)
{

}
NET_ServerMessage::~NET_ServerMessage()
{
	CC_SAFE_DELETE(buffer);
}

int NET_ServerMessage::getMsgStatus()
{
	return status;
}

bool NET_ServerMessage::initStream(IO_InputDataStream* stream)
{
	msgsize = stream->ReadInt() - 1;
	status = stream->ReadByte();
	if (status == 0)
	{
		return true;
	}
	if (msgsize > 0)
	{
		buffer = new char[msgsize];
		stream->ReadFull(buffer,msgsize);

		if (!input.Open(buffer,msgsize))
		{
			return false;
		}

		serverStream.Open(&input);
	}
	return true;
}

int NET_ServerMessage::ReadByte()
{
	return serverStream.ReadByte();
}
int NET_ServerMessage::ReadShort()
{
	return serverStream.ReadShort();
}
int NET_ServerMessage::ReadInt()
{
	return serverStream.ReadInt();
}
float NET_ServerMessage::ReadFloat()
{
	return serverStream.ReadFloat();
}
int64 NET_ServerMessage::ReadInt64()
{
	return serverStream.ReadInt64();
}
std::string NET_ServerMessage::ReadString()
{
	return serverStream.ReadString();
}


