#include "MSG_Header.h"
#include "IO_InputDataStream.h"
#include "IO_OutputDataStream.h"

#define MSG_FLAG_COMPRESS 0x80000000
#define MSG_MASK_DATA_SIZE 0x00ffffff

MSG_Header::MSG_Header()
{
	ResetSettings();
}

MSG_Header::~MSG_Header()
{
	
}

void MSG_Header::ResetSettings()
{
	flags = 0;

	svr_head[0] = 0;
	svr_head[1] = 1;
	svr_head[2] = 1;
	svr_head[3] = 1;
	svr_head[4] = 0;

	svr_app_id = 1;
	svr_dig_id = 1;
	svr_seq_id = 1;
	svr_net_delay = 100;

	messageCount = 0;
	messageSize = 0;
}

void MSG_Header::SetCompress()
{
	flags |= MSG_FLAG_COMPRESS;
}

void MSG_Header::ClearCompress()
{
	flags &= ~MSG_FLAG_COMPRESS;
}

bool MSG_Header::IsCompress()
{
	if(flags & MSG_FLAG_COMPRESS)
	{
		return true;
	}

	return false;
}

void MSG_Header::SetDataSize(int size)
{
	flags &= ~MSG_MASK_DATA_SIZE;
	flags |= (MSG_MASK_DATA_SIZE & size);
}

int MSG_Header::GetDataSize()
{
	return flags & MSG_MASK_DATA_SIZE;
}

void MSG_Header::SetMessageCount(int count)
{
	messageCount = count;
}

void MSG_Header::SetMessageSize(int size)
{
	messageSize = size;
}

bool MSG_Header::Read(IO_InputDataStream* stream)
{
	if(stream == NULL)
	{
		return false;
	}

	flags = stream->ReadInt();

	stream->ReadFull(svr_head, 5);
	svr_app_id = stream->ReadInt();
	svr_dig_id = stream->ReadInt();
	svr_seq_id = stream->ReadInt();
	svr_net_delay = stream->ReadInt();
	CCLOG("Read %d %d %d %d %d %d %d %d %d %d",flags,svr_head[0],svr_head[1],svr_head[2],svr_head[3],svr_head[4],svr_app_id,svr_dig_id,svr_seq_id,svr_net_delay);
	return true;
}

bool MSG_Header::Write(IO_OutputDataStream* stream)
{
	if(stream == NULL)
	{
		return false;
	}
	
	stream->WriteFull(svr_head, 5);
	stream->WriteInt(svr_app_id);
	stream->WriteInt(svr_dig_id);
	stream->WriteInt(svr_seq_id);
	stream->WriteInt(svr_net_delay);

	stream->WriteInt(messageSize + 4 + 2);
	stream->WriteInt(flags);
	stream->WriteShort(messageCount);
	CCLOG("messageCount %d",messageCount);
	CCLOG("messageSize %d",messageSize);
	CCLOG("Write %d %d %d %d %d %d %d %d %d %d",flags,svr_head[0],svr_head[1],svr_head[2],svr_head[3],svr_head[4],svr_app_id,svr_dig_id,svr_seq_id,svr_net_delay);
	return true;
}
