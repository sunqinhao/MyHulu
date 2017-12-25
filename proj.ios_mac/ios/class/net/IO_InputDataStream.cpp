#include "IO_InputDataStream.h"
#include "IO_CharDecoder.h"

IO_InputDataStream::IO_InputDataStream()
{
	stream = NULL;
}

IO_InputDataStream::~IO_InputDataStream()
{
	Close();
}

bool IO_InputDataStream::Open(IO_InputStream* stream)
{
	if(stream == NULL)
	{
		return false;
	}

	this->stream = stream;

	return true;
}

void IO_InputDataStream::Close()
{
	stream = NULL;
}

int IO_InputDataStream::Read()
{
	if(stream == NULL)
	{
		return -1;
	}

	return stream->Read();
}

int IO_InputDataStream::Read(void* buffer, int size)
{
	if(stream == NULL)
	{
		return -1;
	}

	return stream->Read(buffer, size);
}

int IO_InputDataStream::Seek(int offset, int origin)
{
	if(stream == NULL)
	{
		return -1;
	}

	return stream->Seek(offset, origin);
}

int IO_InputDataStream::GetPosition()
{
	if(stream == NULL)
	{
		return -1;
	}

	return stream->GetPosition();
}

int IO_InputDataStream::GetInputSize()
{
	if(stream == NULL)
	{
		return -1;
	}

	return stream->GetInputSize();
}

char IO_InputDataStream::ReadByte() throw (IO_Exception)
{
	int ch = Read();
	if(ch == -1)
	{
		throw IO_Exception(IO_ERROR_EOF);
	}

	return (char)ch;
}

short IO_InputDataStream::ReadShort() throw (IO_Exception)
{
	int ch1 = Read();
	int ch2 = Read();

	if(ch1 == -1 || ch2 == -1)
	{
		throw IO_Exception(IO_ERROR_EOF);
	}

	return (short)((ch1 << 8) | ch2);
}

int IO_InputDataStream::ReadInt() throw (IO_Exception)
{
	int ch1 = Read();
	int ch2 = Read();
	int ch3 = Read();
	int ch4 = Read();

	if(ch1 == -1 || ch2 == -1 || ch3 == -1 || ch4 == -1)
	{
		throw IO_Exception(IO_ERROR_EOF);
	}

	return ((ch1 << 24) | (ch2 << 16) | (ch3 << 8) | ch4);
}

int64 IO_InputDataStream::ReadInt64() throw (IO_Exception)
{
	return ((int64)(ReadInt()) << 32) + (ReadInt() & 0xffffffffL);
}

string IO_InputDataStream::ReadString(int encode/* = IO_ENCODE_UTF8*/) throw (IO_Exception)
{
	string text;

	/*if(encode == IO_ENCODE_ASCII)
	{
		if(!IO_CharDecoder::ReadASCII(this, text))
		{
			throw IO_Exception(IO_ERROR_ENCODE);
		}

		return text;
	}
	else if(encode == IO_ENCODE_UNICODE)
	{
		if(!IO_CharDecoder::ReadUNICODE(this, text))
		{
			throw IO_Exception(IO_ERROR_ENCODE);
		}

		return text;
	}
	else if(encode == IO_ENCODE_UNICODE_BIG_ENDIAN)
	{
		if(!IO_CharDecoder::ReadBigEndianUNICODE(this, text))
		{
			throw IO_Exception(IO_ERROR_ENCODE);
		}

		return text;
	}
	else */
		if(encode == IO_ENCODE_UTF8)
	{
		if(!IO_CharDecoder::ReadUTF8(this, text))
		{
			throw IO_Exception(IO_ERROR_ENCODE);
		}
		return text;
	}

	throw IO_Exception(IO_ERROR_ENCODE);

	return string();
}

void IO_InputDataStream::ReadFull(void* buffer, int size) throw (IO_Exception)
{
	if(Read(buffer, size) != size)
	{
		throw IO_Exception(IO_ERROR_EOF);
	}
}
