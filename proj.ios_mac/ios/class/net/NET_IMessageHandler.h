#ifndef __NET_IMESSAGEHANDLER_H__
#define __NET_IMESSAGEHANDLER_H__

#include "MSG_Header.h"
#include "IO_InputBuffer.h"
#include "IO_OutputBuffer.h"
class NET_MessageQueue;

#define MSG_HEADER_SIZE 4
#define MSG_MAX_PACKET_SIZE 1024 * 1024

class NET_IMessageHandler
{
public:
	NET_IMessageHandler();
	virtual ~NET_IMessageHandler();

public:
	virtual int QueryPacketSize(IO_InputBuffer* data);
	virtual IO_OutputBuffer* Package(NET_MessageQueue* queue);
	virtual NET_MessageQueue* Unpackage(IO_InputBuffer* data);

protected:
	bool Decompress(IO_OutputBuffer& output, IO_InputBuffer& input, int inputSize);
	NET_MessageQueue* MakeMessage(IO_InputDataStream* stream);

protected:
	MSG_Header header;
};

#endif /*__NET_IMESSAGEHANDLER_H__*/
