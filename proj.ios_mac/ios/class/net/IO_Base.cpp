#include "IO_Base.h"


bool IO_Base::Compress(void* dest, int* destSize, const void* src, int srcSize, int level)
{
	if(compress2((Bytef*)dest, (uLongf*)destSize, (Bytef*)src, srcSize, level) == Z_OK)
	{
		return true;
	}

	return false;
}

bool IO_Base::Decompress(void* dest, uLongf* destSize, const void* src, int srcSize)
{
    //printf("uncompress == %d",uncompress((Bytef*)dest, (uLongf*)destSize, (Bytef*)src, srcSize));
	if(uncompress((Bytef*)dest, (uLongf*)destSize, (Bytef*)src, srcSize) == Z_OK)
	{
		return true;
	}

	return false;
}

int IO_Base::GetMaxCompressSize(int srcSize)
{
	int destSize = (int)(srcSize * 1.001 + 12 + 0.5);

	return destSize;
}

bool IO_Base::IsCanInflate(const void* src, int srcSize, int level)
{
	int destSize = GetMaxCompressSize(srcSize);
	char* dest = new char[destSize];

	if(dest == NULL)
	{
		return false;
	}

	if(!Compress(dest, &destSize, src, srcSize, level))
	{
		delete [] dest;
		return false;
	}

	delete [] dest;

	if(destSize >= srcSize)
	{
		return false;
	}

	return true;
}

int IO_Base::SplitString(const string& input,const string& delimiter, strary& output)
{
	if(input.size() == 0)
	{
		return 0;
	}

	if(delimiter.size() == 0)
	{
		output.push_back(input);

		return 1;
	}

	int startIndex = 0;
	int findIndex = 0;
	int count = 0;

	while(true)
	{
		findIndex = input.find(delimiter, startIndex);
		if(findIndex == -1)
		{
			if(startIndex != input.size())
			{
				output.push_back(input.substr(startIndex, input.size() - startIndex));
				++count;
			}

			break;
		}

		int length = findIndex - startIndex;
		if(length > 0)
		{
			output.push_back(input.substr(startIndex, length));
		}

		startIndex = findIndex + 1;

		++count;
	}

	return count;
}

int IO_Base::SplitString2(const string& input, const string& delimiter, strary& output)
{
	if(input.size() == 0)
	{
		return 0;
	}

	if(delimiter.size() == 0)
	{
		output.push_back(input);

		return 1;
	}

	int startIndex = 0;
	int findIndex = 0;
	int count = 0;

	while(true)
	{
		findIndex = -1;

		for(uint i = 0; i < delimiter.length(); ++i)
		{
			int fi = input.find(delimiter[i], startIndex);

			if(fi != -1)
			{
				if(findIndex == -1)
				{
					findIndex = fi;
				}
				else if(fi < findIndex)
				{
					findIndex = fi;
				}
			}
		}

		if(findIndex == -1)
		{
			if(startIndex != input.size())
			{
				output.push_back(input.substr(startIndex, input.size() - startIndex));
				++count;
			}

			break;
		}

		int length = findIndex - startIndex;
		if(length > 0)
		{
			output.push_back(input.substr(startIndex, length));
		}

		startIndex = findIndex + 1;

		++count;
	}

	return count;
}

