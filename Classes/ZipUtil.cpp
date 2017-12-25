

#include "ZipUtil.h"
#include "platform/CCPlatformMacros.h"
#include "base/ccMacros.h"
#include "platform/CCFileUtils.h"

#include <stdio.h>
#include "unzip/unzip.h"

using namespace cocos2d;

#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

bool ZipUtil::unCompress(const char * zipFileName)
{
	return ZipUtil::unCompress(zipFileName,"");
}

bool ZipUtil::unCompress(const char * zipFileName, const std::string &password)
{
	if (!zipFileName) {
		CCLOG("unCompress() - invalid arguments");
		return 0;
	}
	FileUtils *utils = FileUtils::getInstance();
	std::string outFileName = utils->fullPathForFilename(zipFileName);
	// ��ѹ���ļ�  
	unzFile zipfile = unzOpen(outFileName.c_str());
	if (!zipfile)
	{
		CCLOG("can not open downloaded zip file %s", outFileName.c_str());
		return false;
	}
	// ��ȡzip�ļ���Ϣ  
	unz_global_info global_info;
	if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
	{
		CCLOG("can not read file global info of %s", outFileName.c_str());
		unzClose(zipfile);
		return false;
	}
	// ��ʱ���棬���ڴ�zip�ж�ȡ���ݣ�Ȼ�����ݸ���ѹ����ļ�  
	char readBuffer[BUFFER_SIZE];
	//��ʼ��ѹ��  
	CCLOG("start uncompressing");
	//�����Լ�ѹ����ʽ�޸��ļ��еĴ�����ʽ  
	std::string storageDir;
	int pos = outFileName.find_last_of("/");
	storageDir = outFileName.substr(0, pos);
    storageDir = utils->getWritablePath()+"guaji/";
	//    FileUtils::getInstance()->createDirectory(storageDir);  

	// ѭ����ȡѹ�������ļ�  
	// global_info.number_entryΪѹ�������ļ�����  
	uLong i;
	for (i = 0; i < global_info.number_entry; ++i)
	{
		// ��ȡѹ�����ڵ��ļ���  
		unz_file_info fileInfo;
		char fileName[MAX_FILENAME];
		if (unzGetCurrentFileInfo(zipfile,
			&fileInfo,
			fileName,
			MAX_FILENAME,
			NULL,
			0,
			NULL,
			0) != UNZ_OK)
		{
			CCLOG("can not read file info");
			unzClose(zipfile);
			return false;
		}

		//���ļ����·��  
		std::string fullPath = storageDir + "/" + fileName;

		// ���·�����ļ��л����ļ�  
		const size_t filenameLength = strlen(fileName);
		if (fileName[filenameLength - 1] == '/')
		{
			// ���ļ���һ���ļ��У���ô�ʹ�����  
			if (!FileUtils::getInstance()->createDirectory(fullPath.c_str()))
			{
				CCLOG("can not create directory %s", fullPath.c_str());
				unzClose(zipfile);
				return false;
			}
		}
		else
		{
			// ���ļ���һ���ļ�����ô����ȡ������  
			if (password.empty())
			{
				if (unzOpenCurrentFile(zipfile) != UNZ_OK)
				{
					CCLOG("can not open file %s", fileName);
					unzClose(zipfile);
					return false;
				}
			}
			else
			{
				if (unzOpenCurrentFilePassword(zipfile, password.c_str()) != UNZ_OK)
				{
					CCLOG("can not open file %s", fileName);
					unzClose(zipfile);
					return false;
				}
			}

			// ����Ŀ���ļ�  
			FILE *out = fopen(fullPath.c_str(), "wb");
			if (!out)
			{
				CCLOG("can not open destination file %s", fullPath.c_str());
				unzCloseCurrentFile(zipfile);
				unzClose(zipfile);
				return false;
			}

			// ��ѹ���ļ�����д��Ŀ���ļ�  
			int error = UNZ_OK;
			do
			{
				error = unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
				if (error < 0)
				{
					CCLOG("can not read zip file %s, error code is %d", fileName, error);
					unzCloseCurrentFile(zipfile);
					unzClose(zipfile);
					return false;
				}
				if (error > 0)
				{
					fwrite(readBuffer, error, 1, out);
				}
			} while (error > 0);

			fclose(out);
		}
		//�رյ�ǰ����ѹ�����ļ�  
		unzCloseCurrentFile(zipfile);

		// ���zip�ڻ��������ļ����򽫵�ǰ�ļ�ָ��Ϊ��һ������ѹ���ļ�  
		if ((i + 1) < global_info.number_entry)
		{
			if (unzGoToNextFile(zipfile) != UNZ_OK)
			{
				CCLOG("can not read next file");
				unzClose(zipfile);
				return false;
			}
		}
	}
	//ѹ�����  
	CCLOG("end uncompressing");

	//ѹ�����ɾ��zip�ļ���ɾ��ǰҪ�ȹر�  
	unzClose(zipfile);
    FileUtils::getInstance()->removeFile(outFileName.c_str());
//	if (remove(outFileName.c_str()) != 0)
//	{
//		CCLOG("can not remove downloaded zip file %s", outFileName.c_str());
//	}
	return true;
}
