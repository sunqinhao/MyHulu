#ifndef __IO_INPUTSTREAM_H__
#define __IO_INPUTSTREAM_H__

#include "IO_Base.h"
#include "cocos2d.h"

class IO_InputStream :public cocos2d::CCObject
{
public:
	IO_InputStream(){}
	virtual ~IO_InputStream(){}

public:
	virtual int Read(){return 0;};
	virtual int Read(void* buffer, int size);
	virtual int PeekRead();
	virtual int PeekRead(void* buffer, int size);

public:
	virtual int Seek(int offset, int origin){ return -1; }
	virtual int GetPosition(){ return -1; }
	virtual int GetInputSize(){ return -1; }
	virtual int Skip(int size) { return Seek(size, IO_SEEK_CURRENT); }
};

#endif /*__IO_INPUTSTREAM_H__*/

