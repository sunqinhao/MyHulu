#ifndef __NET_MESSAGEQUEUE_H__
#define __NET_MESSAGEQUEUE_H__

#include "NET_Message.h"

typedef list<NET_Message*> NET_MessageList;

class NET_MessageQueue
{
public:
	NET_MessageQueue();
	~NET_MessageQueue();

public:
	bool Push(NET_Message* message);
	NET_Message* Pop();
	NET_MessageList* getMessageList();
	void Clear();
	int GetCount();

protected:
	NET_MessageList list;
};

#endif /*__NET_MESSAGEQUEUE_H__*/
