
#ifndef __ZIPUTIL_H
#define __ZIPUTIL_H

#include <string>


class ZipUtil{

    
public:
    
	static bool unCompress(const char * zipFileName, const std::string &password);
	static bool unCompress(const char * zipFileName);
};


#endif
