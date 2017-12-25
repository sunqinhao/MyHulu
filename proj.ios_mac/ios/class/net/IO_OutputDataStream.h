#ifndef __IO_OUTPUTDATASTREAM_H__
#define __IO_OUTPUTDATASTREAM_H__

#include "IO_OutputStream.h"
#include "IO_Exception.h"

class IO_OutputDataStream : public IO_OutputStream
{
public:
	IO_OutputDataStream();
	virtual ~IO_OutputDataStream();

public:
	bool Open(IO_OutputStream* stream);
	void Close();

public:
	virtual int Write(int ch);
	virtual int Write(const void* buffer, int size);

public:
	virtual int GetOutputSize();

public:
	void WriteByte(char data) throw (IO_Exception);
	void WriteShort(short data) throw (IO_Exception);
	void WriteInt(int data) throw (IO_Exception);
	void WriteInt64(int64 data) throw (IO_Exception);
	void WriteString(string& text, int encode = IO_ENCODE_UTF8) throw(IO_Exception);
	void WriteFull(const void* buffer, int size) throw (IO_Exception);
	void WriteFloat(float data) throw (IO_Exception)
	{
		char* p = (char*)(&data);
		WriteFull(p, 4);
	}
private:
	IO_OutputStream* stream;
};

#endif /*__IO_OUTPUTDATASTREAM_H__*/
