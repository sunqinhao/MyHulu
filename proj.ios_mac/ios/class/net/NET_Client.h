#ifndef __NET_CLIENT_H__
#define __NET_CLIENT_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <winsock2.h>
#include <windows.h>
#include <io.h>
#include <conio.h>
#include <direct.h>
#include "pthread.h"
#endif 

#include "ODSocket.h"
#include "NET_MessageQueue.h"
#include "NET_IMessageHandler.h"


#define	MAX_SOCKETMSG_BUFF	1024 * 128 //ª∫¥Ê


#define NET_STATUS_SUCCESS		0
#define NET_STATUS_MSG			1
#define NET_STATUS_CLOSE		2
#define NET_STATUS_ERROR		3
#define NET_STATUS_RECONNECT		4
typedef struct _CLIENT {
	void* netC; 
	string ip; 
	unsigned short port;
} CLIENT;

class NET_Client :public cocos2d::Ref
{
public:
	NET_Client();
	virtual ~NET_Client();

	static NET_Client* getInstance();
public:
	 /**
     *  @brief Errors in websocket
     */
	enum ErrorCode
	{ 
		NET_ERROR_FAIL,
		NET_ERROR_TIMEOUT,
		NET_ERROR_NOCONNECT,
		NET_ERROR_READ,
		NET_ERROR_WRITE,
		NET_ERROR_UNKNOW,
	};

	class ThreadMessage
	{
	public:
		ThreadMessage() : what(0),state(0), obj(NULL){}
		unsigned int what; // message type
		int state;
		NET_MessageQueue* obj;
	};

	class NET_INotify
	{
	public:
		virtual bool OnConnect(NET_Client* handler){ return false; }
		virtual bool OnMessage(NET_Client* handler,NET_ServerMessage* message){ return false; }
		virtual bool OnNetError(NET_Client* handler, int status){ return false; }
		virtual void OnMessageEnd(){};
		virtual void onSdkLogin(){};
		virtual void onSdkLoginFailed(){};
		virtual void onInnerSwitcher(){};
		virtual void onSendHeart(){};
		virtual void onSendPayMessage(const char *productId,const char* str){};
		virtual void onCheckCdk(const char *cdk){};
		virtual void onUpdateView(const char *func){};
	};

	typedef list<NET_INotify*> NET_NotifyList;
public:
	bool initConnect(const string& address, short port, int second);
	void ConnectAgain(const string& address, short port);
	bool Reconnect();
	void CloseConnect(bool isClose = false);
    bool isConnect();
	void setConnect(bool isc);
	bool initPthread();

	bool Connect();
	void SetConnectWillClose();
public:
	bool sendMessage(NET_Message* message);
	bool sendMessageEndExitThread(NET_Message* message);
public:
    
	bool Register(NET_INotify* notify);
	bool Unregister(NET_INotify* notify);
	bool clearRegister();

	bool sdkRegister(NET_INotify* notify);
	bool sdkLFRegister(NET_INotify* notify);
	bool innerSwitcherRegister(NET_INotify* notify);
	bool sendHeartRegister(NET_INotify* notify);
	bool sendPayMessageRegister(NET_INotify* notify);
	bool checkCdkRegister(NET_INotify* notify);
	bool updateViewRegister(NET_INotify* notify);
	//ccl add this
	void sdkLogin();
	void sdkLoginFailed();
	void innerSwitcher();
	void sendHeart();
	void sendPayMessage(const char *productId,const char* str);
	void checkCdk(const char *cdk);
	void updateView(const char *func);
	NET_INotify* sdkLoginNotify;
	NET_INotify* sdkLoginFailedNotify;
	NET_INotify* innerSwitcherNotify;
	NET_INotify* sendHeartNotify;
	NET_INotify* sendPayMessageNotify;
	NET_INotify* checkCdkNotify;
	NET_INotify* updateViewNotify;
	bool GetConnectAgain(){return isConnectAgain;};
	ODSocket* GetSocket(){return &mODSocket;};
	NET_IMessageHandler* GetMsgHandler(){return &msgHandler;};
public:
	virtual void OnRecv(char* block, int size);
	void connectSuccess();
	void sendError(ErrorCode code);
	int		m_nRecvBufLen;	         
	char		m_szRecvBuf[MAX_SOCKETMSG_BUFF + 1];	/*Ω” ’ª∫¥Ê«¯*/ 
	bool thread_end;
protected:
	
protected:
	void HandleConnect();
	void HandleRecv(NET_MessageQueue* queue);
	void HandleError(int status);
	bool HandleExitMsg(NET_MessageQueue* queue); 

	std::list<ThreadMessage*> queueList;
	void addMessage(ThreadMessage* mq);
public:
	virtual void update(float dt);
	
public:
	NET_IMessageHandler msgHandler;
	NET_NotifyList notifyList;

    bool isConnectAgain;
	bool connected;
	bool connectWillClose;
	ODSocket mODSocket;
	string address;
	unsigned short port;

	
	pthread_mutex_t  m_mutex;
	pthread_t m_tThreadID;
	map<int,int> eixtMsg;
protected:
	static NET_Client* s_netclient;
};

#endif /*__NET_CLIENT_H__*/
