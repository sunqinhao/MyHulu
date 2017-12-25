#include "NET_IMessageHandler.h"
#include "NET_MessageQueue.h"

NET_IMessageHandler::NET_IMessageHandler()
{

}

NET_IMessageHandler::~NET_IMessageHandler()
{

}

int NET_IMessageHandler::QueryPacketSize(IO_InputBuffer* data)
{
	if(data == NULL)
	{
		return MSG_HEADER_SIZE;
	}

	int needRead = MSG_HEADER_SIZE - data->GetInputSize();

	if(needRead > 0)
	{
		//return needRead + MSG_HEADER_SIZE;
		//return needRead;
		return MSG_HEADER_SIZE;
	}

	IO_InputDataStream dataStream;
	if(!dataStream.Open(data))
	{
		return -1;
	}

	int packetSize = dataStream.ReadInt();
	if(packetSize < 0 || packetSize > MSG_MAX_PACKET_SIZE)
	{
		return -1;
	}

	return packetSize + MSG_HEADER_SIZE;
}

IO_OutputBuffer* NET_IMessageHandler::Package(NET_MessageQueue* queue)
{
	if(queue == NULL)
	{
		return NULL;
	}

	IO_OutputBuffer* dataBuffer = NULL;

	IO_OutputBuffer msgBuffer;
	if(!msgBuffer.Open(1024, 1024))
	{
		return NULL;
	}
	IO_OutputDataStream msgStream;
	if(!msgStream.Open(&msgBuffer))
	{
		return NULL;
	}
	int msgCount = queue->GetCount();
	NET_Message* msg = NULL;
	try
	{
		for(int i = 0; i < msgCount; ++i)
		{
			msg = queue->Pop();
			if(msg == NULL)
			{
				return NULL;
			}
			//int msgBegin = 4;
			msgStream.WriteInt(msg->getMsgID());
			int msgBegin = msgBuffer.GetPosition();
			msgStream.WriteInt(0);
			if(!msg->Write(&msgStream))
			{
				delete msg;
				return NULL;
			}
			int msgEnd = msgBuffer.GetPosition();

			msgBuffer.Seek(msgBegin, IO_SEEK_BEGIN);
			msgStream.WriteInt(msgEnd - msgBegin - 4);
			msgBuffer.Seek(msgEnd, IO_SEEK_BEGIN);

			delete msg;
			msg = NULL;
		}
		dataBuffer = new IO_OutputBuffer();
		if(!dataBuffer->Open(msgBuffer.GetMaxSize(), 1024))
		{
			delete msg;
			return NULL;
		}

		IO_OutputDataStream dataStream;
		if(!dataStream.Open(dataBuffer))
		{
			delete msg;
			return NULL;
		}

		header.ClearCompress();
		header.SetMessageCount(msgCount);
		header.SetMessageSize(msgBuffer.GetOutputSize());

		if(!header.Write(&dataStream))
		{
			return NULL;
		}

		dataStream.WriteFull(msgBuffer.GetBase(), msgBuffer.GetOutputSize());
	}
	catch (...)
	{
		if(msg != NULL)
		{
			delete msg;
		}

		if(dataBuffer != NULL)
		{
			delete dataBuffer;
			dataBuffer = NULL;
		}
		return NULL;
	}
	return dataBuffer;
}

NET_MessageQueue* NET_IMessageHandler::Unpackage(IO_InputBuffer* data)
{
	if(data == NULL)
	{
		return NULL;
	}

	IO_InputBuffer input;
	if(!input.Open(data->GetBase(), data->GetInputSize()))
	{
		return NULL;
	}

	IO_InputDataStream dataStream;
	if(!dataStream.Open(&input))
	{
		return NULL;
	}

	dataStream.ReadInt();

	if(!header.Read(&dataStream))
	{
		return NULL;
	}

	IO_OutputBuffer output;
	if(header.IsCompress())
	{
		if(!output.Open(header.GetDataSize(), -1))
		{
			return NULL;
		}

        
		int inputSize = input.GetInputSize() - input.GetPosition();
		if(!Decompress(output, input, inputSize))
		{
			return NULL;
		}
		if(!input.Open(output.GetBase(), output.GetMaxSize()))
		{
			return NULL;
		}
		if(!dataStream.Open(&input))
		{
			return NULL;
		}
	}
	NET_MessageQueue* messageQueue = MakeMessage(&dataStream);
	if(messageQueue == NULL)
	{
		return NULL;
	}

	return messageQueue;
}

bool NET_IMessageHandler::Decompress(IO_OutputBuffer& output, IO_InputBuffer& input, int inputSize)
{
	uLongf outputSize = output.GetMaxSize();
	if(!IO_Base::Decompress(output.GetBase(), &outputSize, input.GetBuffer(), inputSize))
	{
		return false;
	}

	if(outputSize != output.GetMaxSize())
	{
		return false;
	}

	return true;
}

NET_MessageQueue* NET_IMessageHandler::MakeMessage(IO_InputDataStream* stream)
{
	if(stream == NULL)
	{
		return NULL;
	}

	NET_MessageQueue* queue	= new NET_MessageQueue();
	if(queue == NULL)
	{
		return NULL;
	}

	NET_ServerMessage* msg = NULL;
	try
	{
		int msgCount = stream->ReadShort() & 0xffff;
		CCLOG("read msgCount %d",msgCount);
		for(int i = 0; i < msgCount; ++i)
		{
			int msgID = stream->ReadInt();
			//int msgSize = stream->ReadInt();

			CCLOG("read msgID %d",msgID);

			msg = new NET_ServerMessage();
			msg->setMsgID(msgID);
			if (msg->initStream(stream) == false)
			{
				throw IO_Exception(IO_ERROR_EOF);
			}
			
			//switch(msgID)
			//{
			//	
			//default:
			//	stream->Skip(msgSize);
			//	break;
			//}

			if(msg != NULL)
			{
				queue->Push(msg);
			}
		}
	}
	catch(...)
	{
		delete msg;
		delete queue;
		return NULL;
	}

	return queue;
}
