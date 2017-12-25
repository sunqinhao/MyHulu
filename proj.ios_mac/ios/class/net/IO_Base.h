#ifndef __IO_BASE_H__
#define __IO_BASE_H__

#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include "zlib.h"
#include <stdint.h>


#define IO_SEEK_BEGIN   0
#define IO_SEEK_CURRENT 1
#define IO_SEEK_END     2

#define IO_ENCODE_ASCII 1
#define IO_ENCODE_UNICODE 2 //FF FE
#define IO_ENCODE_UNICODE_BIG_ENDIAN 3 //FE FF
#define IO_ENCODE_UTF8 4 //EF BB BF
#define IO_ENCODE_DEFAULT 5
#define IO_ENCODE_UNKNOW 6

#define IO_ERROR_EOF -1
#define IO_ERROR_UTF_FORMAT 2
#define IO_ERROR_NO_OPEN 1
#define IO_ERROR_OVERFLOW 3
#define IO_ERROR_ENCODE 4
#define IO_ERROR_FORMAT 5

#define IO_CHAR_BUFFER_SIZE 32


using namespace std;

typedef long long int64;
typedef unsigned char byte;

typedef vector<string> strary;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;

#ifdef _MSC_VER
#pragma warning(disable:4290)
#pragma warning(disable:4996)
#endif /*_MSC_VER*/

class IO_Base
{
public:
	static bool Compress(void* dest, int* destSize, const void* src, int srcSize, int level);
	static bool Decompress(void* dest, uLongf* destSize, const void* src, int srcSize);
	static int GetMaxCompressSize(int srcSize);
	static bool IsCanInflate(const void* src, int srcSize, int level);

	static int SplitString(const string& input, const string& delimiter, strary& output);
	static int SplitString2(const string& input, const string& delimiter, strary& output);

private:
	IO_Base(){}
	~IO_Base(){}
};

#endif /*__IO_BASE_H__*/
