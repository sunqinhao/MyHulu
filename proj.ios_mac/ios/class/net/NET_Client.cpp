#include "NET_Client.h"
#include "cocos2d.h"
USING_NS_CC;

NET_Client* NET_Client::s_netclient = NULL;

NET_Client::NET_Client()
{
	connected = false;
	isConnectAgain = false;

	memset(m_szRecvBuf,0,MAX_SOCKETMSG_BUFF+1);
	m_nRecvBufLen = 0;
	pthread_mutex_init(&m_mutex, NULL);
	sdkLoginNotify=NULL;
	sdkLoginFailedNotify=NULL;
	innerSwitcherNotify = NULL;
	sendHeartNotify = NULL;
	sendPayMessageNotify = NULL;
	checkCdkNotify = NULL;
	updateViewNotify = NULL;
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
}

NET_Client::~NET_Client()
{
	CloseConnect();
    pthread_mutex_destroy(&m_mutex);
	CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
}

NET_Client* NET_Client::getInstance()
{
	if (s_netclient == NULL)
	{
		s_netclient = new NET_Client();
	}
	return s_netclient;
}

static void* thread_funcation(void* arg)
{
	NET_Client* nclient = (NET_Client*)arg;

	//CLIENT client = *(CLIENT*)arg;
	//NET_Client* nclient  = (NET_Client*)client.netC;
	//string  ip = client.ip;
	//short port = port;

	ODSocket* socket = nclient->GetSocket();	
	nclient->Connect();
	short port = nclient->port;
	CCLOG("(%d)start thread_funcation ..................................................................................",port);
	while (nclient->isConnect())
	{
		CCLOG("(%d)while ------------------",port);
		if(nclient->port!=port)
		{
			break;
		}
		IO_InputBuffer data;
		if(!data.Open(nclient->m_szRecvBuf, nclient->m_nRecvBufLen))
		{
			CCLOG("............CCL...................sendError0................................1...................");
			while (nclient->isConnect())
			nclient->sendError(NET_Client::NET_ERROR_FAIL);
			break;
		}

		int packetSize = nclient->GetMsgHandler()->QueryPacketSize(&data);
		//CCLOG("(%d)packetSize %d",port,packetSize);
		if(packetSize < 0)
		{
			CCLOG("............CCL...................sendError0................................2...................");
			nclient->sendError(NET_Client::NET_ERROR_FAIL);
			break;
		}

		int unread = packetSize - data.GetInputSize();
		//CCLOG("(%d)Recv begin %d",port,unread);
		if(unread > 0)
		{
			
			char* buffer = nclient->m_szRecvBuf + nclient->m_nRecvBufLen;
			int nLen = socket->Recv(buffer,unread,0);//MAX_SOCKETMSG_BUFF recv(pODSocket->m_sock,pODSocket->m_szRecvBuf,pODSocket->m_nRecvBufLen,0);
			int nErr = socket->GetError();
			//CCLOG("(%d)Recv end nLen = %d,nErr = %d",port,nLen,nErr);
			if(nLen == 0)
			{
				nclient->sendError(NET_Client::NET_ERROR_NOCONNECT);
			}
			else if(nLen < 0)
			{
				switch(nErr)
				{
				case ETIMEDOUT:
					nclient->sendError(NET_Client::NET_ERROR_TIMEOUT);
					break;
				//case EWOULDBLOCK:
					//	break;
				case ECONNABORTED:
					nclient->sendError(NET_Client::NET_ERROR_NOCONNECT);
					break;
				default:
					if(nclient->isConnect())
					{
						CCLOG("............CCL...................sendError0................................3...................");
						nclient->sendError(NET_Client::NET_ERROR_FAIL);
					}					
					break;
				}
			}
			else
			{
				nclient->m_nRecvBufLen += nLen;
				//CCLOG("m_nRecvBufLen %d",nclient->m_nRecvBufLen);
			}
		}
		else
		{
			if(nclient->port!=port)
			{
				break;
			}
			CCLOG("(%d)OnRecv ------------------start",port);
			nclient->OnRecv(nclient->m_szRecvBuf,packetSize);
			//CCLOG("(%d)OnRecv ------------------start2",port);
			memset(nclient->m_szRecvBuf,0,MAX_SOCKETMSG_BUFF+1);
			//CCLOG("(%d)OnRecv ------------------start3",port);
			nclient->m_nRecvBufLen = 0;
			//CCLOG("(%d)OnRecv ------------------end",port);
		}	
	}
    CCLOG("(%d)end thread_funcation------------------",port);
	//nclient->thread_end=true;
	pthread_exit(0);
	
	return 0;
}

bool NET_Client::initPthread()
{
	// 发送线程
	int errCode = 0;
	do{
		pthread_attr_t attr;
		errCode = pthread_attr_init(&attr);
		CC_BREAK_IF(errCode!=0);
		errCode = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		if (errCode!=0) {
			pthread_attr_destroy(&attr);
			break;
		}

		//CLIENT client;
		//client.netC = this;
		//client.ip = this->address;
		//client.port = this->port;

		errCode = pthread_create(&m_tThreadID, &attr, thread_funcation, (void*)(this));
	}while (0);
	thread_end=false;
	return errCode == 0;
}


bool NET_Client::initConnect(const string& address, short port, int second)
{
	CCLOG("connect %s %d",address.c_str(),port);
	if(!isConnect())
	{
		//CCLOG("start connect");
		mODSocket.Init();
		if (mODSocket.Create(AF_INET,SOCK_STREAM,0) == false)
		{
			sendError(NET_ERROR_NOCONNECT);
			CloseConnect(true);
			return false;
		}
		this->address = address;
		this->port = port;
		initPthread();
	}
	else
	{
		//CCLOG("initConnect .............................close connect");
		ConnectAgain(address,port);
		//setConnect(false);
		CloseConnect();
		ThreadMessage* msg = new ThreadMessage();
		msg->what = NET_STATUS_RECONNECT;
		addMessage(msg);
	}
	return true;
}

bool NET_Client::Connect()
{
	if(mODSocket.Connect(address.c_str(),port))
	{
		connectSuccess();
		return true;
	}
	sendError(NET_ERROR_NOCONNECT);
	return false;
}

void NET_Client::ConnectAgain(const string& address, short port)
{
	this->address = address;
	this->port = port;

	//MSG_ClientVIPLoginGetInfo *pMsg3 = new MSG_ClientVIPLoginGetInfo();
	//pMsg3->seqId = SAdminister::getInstance()->getSeqID();
	//sendMessage(pMsg3);
	isConnectAgain = true;
}

//bool IsBig_Endian()
////如果字节序为big-endian，返回true;
////反之为   little-endian，返回false
//{
//	unsigned short test = 0x1122;
//	if(*( (unsigned char*) &test ) == 0x11)//将i的地址传给数组指针p，实际上p指向的地址是i在内存中存储的第一个字节，大端就是0x12，小端就是0x78  
//		return true;
//	else
//		return false;
//}//IsBig_Endian()

//
//uint EndianConvertLToB(uint InputNum) {  
//	uchar *p = (uchar*)&InputNum;  
//	return(((uint)*p<<24)+((uint)*(p+1)<<16)+  
//		((uint)*(p+2)<<8)+(uint)*(p+3));  
//}  
//
////同样的原理适用于大端转小端，但是大端转小端时移位有差别，函数如下：
//
//uint EndianConvertBToL(uint InputNum) {  
//	uchar *p = (uchar*)&InputNum;  
//	return(((uint)*p)+((uint)*(p+1)<<8)+  
//		((uint)*(p+2)<<16)+(uint)*(p+3)<<24);  
//}  


bool NET_Client::Reconnect()
{
	isConnectAgain = false;
	CloseConnect();
	mODSocket.Init();
	if (mODSocket.Create(AF_INET,SOCK_STREAM,0) == false)
	{
		CloseConnect(true);
		return false;
	}
	initPthread();
	return true;
}

bool NET_Client::isConnect()
{
    return connected;
}

void NET_Client::setConnect(bool isc)
{	
	connected = isc;
}


void NET_Client::CloseConnect(bool isClose)
{
	if (connected || isClose)
	{		
		connected = false;
		mODSocket.Close();
		mODSocket.Clean();
		//CCLOG("pthread_join............");
		//pthread_join(m_tThreadID, NULL);
	}
	
	memset(m_szRecvBuf,0,MAX_SOCKETMSG_BUFF+1);
	m_nRecvBufLen = 0;
}


bool NET_Client::sendMessageEndExitThread(NET_Message* message)
{
	if (connected)
	{		
		NET_MessageQueue msgQueue;
		msgQueue.Push(message);
		CCLOG("sendMessage %d",message->getMsgID());
		eixtMsg[message->getMsgID()] = 1;
		CCLOG("sendMessageEndExitThread--------------1");
		IO_OutputBuffer* data = msgHandler.Package(&msgQueue);
		if(data == NULL)
		{
			CCLOG("sendMessageEndExitThread data == NULL");
			return false;
		}
		CCLOG("size=%d",data->GetOutputSize());
		//CCLOG("%d,%d,%d,%d",((char*)data->GetBase())[0],((char*)data->GetBase())[1],((char*)data->GetBase())[2],((char*)data->GetBase())[3]);
		int ret = mODSocket.Send((char*)data->GetBase(), data->GetOutputSize());
		if(ret < 0)
		{
			CCLOG("send error");
			HandleError(NET_ERROR_WRITE);
			delete data;
			return false;
		}
		delete data;
		return true;
	}
	return false;
}

bool NET_Client::sendMessage(NET_Message* message)
{
	if (connected)
	{		
		NET_MessageQueue msgQueue;
		msgQueue.Push(message);
		CCLOG("sendMessage %d",message->getMsgID());
		IO_OutputBuffer* data = msgHandler.Package(&msgQueue);
		if(data == NULL)
		{
			CCLOG("sendMessage-----------------------data == NULL----");
			return false;
		}
		CCLOG("size=%d",data->GetOutputSize());
		//CCLOG("%d,%d,%d,%d",((char*)data->GetBase())[0],((char*)data->GetBase())[1],((char*)data->GetBase())[2],((char*)data->GetBase())[3]);
		int ret = mODSocket.Send((char*)data->GetBase(), data->GetOutputSize());
		if(ret < 0)
		{
			CCLOG("send error");
			HandleError(NET_ERROR_WRITE);
			delete data;
			return false;
		}
		delete data;
		return true;
	}
	return false;
}


bool NET_Client::sdkRegister(NET_INotify* _notify)
{
	sdkLoginNotify = _notify;
	return true;
}
bool NET_Client::sdkLFRegister(NET_INotify* _notify)
{
	sdkLoginFailedNotify = _notify;
	return true;
}
bool NET_Client::innerSwitcherRegister(NET_INotify* _notify)
{
	innerSwitcherNotify = _notify;
	return true;
}

bool NET_Client::sendHeartRegister(NET_INotify* _notify)
{
	sendHeartNotify = _notify;
	return true;
}

bool NET_Client::sendPayMessageRegister(NET_INotify* _notify)
{
	sendPayMessageNotify = _notify;
	return true;
}

bool NET_Client::checkCdkRegister(NET_INotify* _notify)
{
	checkCdkNotify = _notify;
	return true;
}

bool NET_Client::updateViewRegister(NET_INotify* _notify)
{
	updateViewNotify = _notify;
	return true;
}

bool NET_Client::Register(NET_INotify* notify)
{
	if(notify == NULL)
	{
		return false;
	}

	NET_NotifyList::iterator it;
	for(it = notifyList.begin(); it != notifyList.end(); it++)
	{
		if(*it == notify)
		{
			
			//notifyList.remove(*it);
			//return false;
			notifyList.erase(it);
			break;
		}
	}

	notifyList.push_front(notify);
	return true;
}

bool NET_Client::Unregister(NET_INotify* notify)
{
	NET_NotifyList::iterator it;

	for(it = notifyList.begin(); it != notifyList.end(); it++)
	{
		if(*it == notify)
		{
			notifyList.erase(it);
			return true;
		}
	}

	return false;
}

bool NET_Client::clearRegister()
{
	notifyList.clear();
	return true;
}

void NET_Client::sdkLogin()
{
	if(sdkLoginNotify)
	{
		sdkLoginNotify->onSdkLogin();
	}
}

void NET_Client::sdkLoginFailed()
{
	if(sdkLoginFailedNotify)
	{
		sdkLoginFailedNotify->onSdkLoginFailed();
	}
}

void NET_Client::innerSwitcher()
{
	if (innerSwitcherNotify)
	{
		innerSwitcherNotify->onInnerSwitcher();
	}
}

void NET_Client::sendHeart()
{
	if (sendHeartNotify)
	{
		sendHeartNotify->onSendHeart();
	}
}

void NET_Client::sendPayMessage(const char *productId,const char* str)
{
	if (sendPayMessageNotify)
	{
		sendPayMessageNotify->onSendPayMessage(productId,str);
	}
}

void NET_Client::checkCdk(const char *cdk)
{
	if (checkCdkNotify)
	{
		checkCdkNotify->onCheckCdk(cdk);
	}
}

void NET_Client::updateView(const char *func)
{
	if (updateViewNotify)
	{
		updateViewNotify->onUpdateView(func);
	}
}

void NET_Client::OnRecv(char* block, int size)
{
	IO_InputBuffer data;
	if(!data.Open(block, size))
	{
		HandleError(NET_ERROR_READ);
		return;
	}

	NET_MessageQueue* queue = msgHandler.Unpackage(&data);
	if(queue == NULL)
	{
		HandleError(NET_ERROR_READ);
		return;
	}
	if(HandleExitMsg(queue))
	{
		CloseConnect();
	}
	ThreadMessage* msg = new ThreadMessage();
	msg->what = NET_STATUS_MSG;
	msg->obj = queue;
	addMessage(msg);
}

void NET_Client::connectSuccess()
{
	connected = true;
	ThreadMessage* msg = new ThreadMessage();
	msg->what = NET_STATUS_SUCCESS;
	addMessage(msg);
}

void NET_Client::sendError(ErrorCode code)
{
	ThreadMessage* msg = new ThreadMessage();
	msg->what = NET_STATUS_ERROR;
	msg->state = code;
	addMessage(msg);

	if (code != NET_ERROR_READ)
	{
		CloseConnect(false);
		//setConnect(false);
		CCLOG("sendError %d",code);
		CCLOG("closeConnect %s %d error = %d",address.c_str(),port,code);
	}
	HandleError(NET_ERROR_FAIL);
}

void NET_Client::HandleConnect()
{
	NET_NotifyList::iterator it = notifyList.begin();
	for(; it != notifyList.end(); ++it)
	{
		if((*it)->OnConnect(this))
		{
			break;
		}
	}
}


bool NET_Client::HandleExitMsg(NET_MessageQueue* queue) 
{
	NET_MessageList::iterator it;
	it = queue->getMessageList()->begin();
	while(it != queue->getMessageList()->end())
	{
		NET_ServerMessage* msg = (NET_ServerMessage*)(*it);
		if(msg != NULL)
		{
			int msgid = msg->getMsgID();
			if(eixtMsg[msgid]==1)
			{
				eixtMsg.clear();
				return true;
			}
		}
		it++;
	}
	return false;
}

void NET_Client::HandleRecv(NET_MessageQueue* queue)
{
	while(queue->GetCount() != 0)
	{
		NET_ServerMessage* msg = (NET_ServerMessage*)queue->Pop();
		if(msg != NULL)
		{
			int msgid = msg->getMsgID();
			CCLOG("message status: %d", msg->getMsgStatus());

			NET_NotifyList::iterator it = notifyList.begin();
			for(; it != notifyList.end(); it++)
			{
				if((*it)->OnMessage(this, msg))
				{
					CCLOG("message end :%d",msgid);
					delete msg;
					return;
				}
			}
			CCLOG("message no notify :%d",msgid);
			delete msg;
		}
	}
}


void NET_Client::addMessage(ThreadMessage* mq)
{
	pthread_mutex_lock(&m_mutex);
	queueList.push_back(mq);
	pthread_mutex_unlock(&m_mutex);
}

void NET_Client::update(float dt)
{
	ThreadMessage *msg = NULL;

	// Returns quickly if no message
	pthread_mutex_lock(&m_mutex);
	if (0 == queueList.size())
	{
		pthread_mutex_unlock(&m_mutex);
		return;
	}

	// Gets message
	msg = *(queueList.begin());
	queueList.pop_front();
	pthread_mutex_unlock(&m_mutex);

	switch(msg->what)
	{
	case NET_STATUS_SUCCESS:
		HandleConnect();
		break;
	case NET_STATUS_MSG:
		HandleRecv(msg->obj);
		if(notifyList.size()>0)
		{
			(notifyList.back())->OnMessageEnd();
		}
		break;
	case NET_STATUS_CLOSE:
		CloseConnect(msg->state);
		break;
	case NET_STATUS_ERROR:
		HandleError(msg->state);
		break;
	case NET_STATUS_RECONNECT:
		//CCLOG("......................................Reconnect      %d  %d %d",GetConnectAgain(),thread_end,isConnect());
		if(GetConnectAgain())
		{
			//if ( thread_end)
			//{			
				Reconnect();
			//}
			//else
			//{
				//ThreadMessage* msg = new ThreadMessage();
				//msg->what = NET_STATUS_RECONNECT;
				//addMessage(msg);
			//}
		}
		break;
	}
}

void NET_Client::HandleError(int status)
{
	NET_NotifyList::iterator it = notifyList.begin();
	for(; it != notifyList.end(); ++it)
	{
		if((*it)->OnNetError(this, status))
		{
			break;
		}
	}
}

void NET_Client::SetConnectWillClose()
{
	connectWillClose=true;
}
