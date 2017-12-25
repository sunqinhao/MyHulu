#include "NET_MessageQueue.h"

NET_MessageQueue::NET_MessageQueue()
{
	
}

NET_MessageQueue::~NET_MessageQueue()
{
	Clear();
}

bool NET_MessageQueue::Push(NET_Message* message)
{
	if(message == NULL)
	{
		return false;
	}

	list.push_back(message);

	return true;
}

NET_Message* NET_MessageQueue::Pop()
{
	if(list.size() == 0)
	{
		return NULL;
	}

	NET_Message* message = list.front();

	list.pop_front();

	return message;
}

NET_MessageList* NET_MessageQueue::getMessageList()
{
	return &list;
}

void NET_MessageQueue::Clear()
{
	NET_MessageList::iterator it;

	it = list.begin();

	while(it != list.end())
	{
		delete (*it);

		it++;
	}
	
	list.clear();
}

int NET_MessageQueue::GetCount()
{
	return list.size();
}
