#ifndef __MSG_HEADER_H__
#define __MSG_HEADER_H__

#include "IO_Base.h"
class IO_InputDataStream;
class IO_OutputDataStream;

class MSG_Header
{
public:
	MSG_Header();
	~MSG_Header();

public:
	virtual bool Read(IO_InputDataStream* stream);
	virtual bool Write(IO_OutputDataStream* stream);

public:
	void ResetSettings();

public:
	void SetCompress();
	void ClearCompress();
	bool IsCompress();

public:
	void SetDataSize(int size);
	int GetDataSize();

public:
	void SetMessageCount(int count);
	void SetMessageSize(int size);

protected:
	int flags;

	byte svr_head[5];
	int svr_app_id;
	int svr_dig_id;
	int svr_seq_id;
	int svr_net_delay;

	int messageCount;
	int messageSize;
};

#endif /*__MSG_HEADER_H__*/
