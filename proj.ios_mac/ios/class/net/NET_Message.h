#ifndef __NET_MESSAGE_H__
#define __NET_MESSAGE_H__

#include "IO_InputDataStream.h"
#include "IO_OutputDataStream.h"
#include "IO_InputBuffer.h"
#include "cocos2d.h"

class NET_Message : public cocos2d::CCObject
{
public:
	NET_Message():bScript(false){}
	virtual ~NET_Message(){}

	virtual bool Read(IO_InputDataStream* stream){return false;};
	virtual bool Write(IO_OutputDataStream* stream){return false;};
public:

	int getMsgID(){return _id;};
	void setMsgID(int id){_id = id;};
	void setScriptMsgID(int id){_id = id;bScript = true;};
protected:
	int _id;
	bool bScript;
};

class NET_ClientMessage : public NET_Message
{
public:
	NET_ClientMessage(){}
	virtual ~NET_ClientMessage(){}

	virtual bool Write(IO_OutputDataStream* stream);
public:
	bool excuteScriptWrite(IO_OutputDataStream* stream);
}; 

class NET_ServerMessage : public NET_Message
{
public:
	NET_ServerMessage();
	virtual ~NET_ServerMessage();

	virtual bool initStream(IO_InputDataStream* stream);
public:
	int getMsgStatus();

	int ReadByte();
	int ReadShort();
	int ReadInt();
	float ReadFloat();
	int64 ReadInt64();
	std::string ReadString();
protected:
	int status;
	int msgsize;
	char *buffer;
	IO_InputBuffer input;
	IO_InputDataStream serverStream;
};

#endif /*__NET_MESSAGEBODY_H__*/
