#ifndef __IO_INPUTDATASTREAM_H__
#define __IO_INPUTDATASTREAM_H__

#include "IO_InputStream.h"
#include "IO_Exception.h"

class IO_InputDataStream : public IO_InputStream
{
public:
	IO_InputDataStream();
	virtual ~IO_InputDataStream();

public:
	bool Open(IO_InputStream* stream);
	void Close();

public:
	virtual int Read();
	virtual int Read(void* buffer, int size);

public:
	virtual int Seek(int offset, int origin);
	virtual int GetPosition();
	virtual int GetInputSize();

public:
	char ReadByte() throw (IO_Exception);
	short ReadShort() throw (IO_Exception);
	int ReadInt() throw (IO_Exception);
	int64 ReadInt64() throw (IO_Exception);
	string ReadString(int encode = IO_ENCODE_UTF8) throw (IO_Exception);
	void ReadFull(void* buffer, int size) throw (IO_Exception);
	float ReadFloat() throw (IO_Exception)
	{
		float v;
		ReadFull(&v, 4);
		return v;
	}
private:
	IO_InputStream* stream;
};

#endif /*__IO_INPUTDATASTREAM_H__*/
