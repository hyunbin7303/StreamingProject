#ifndef _MANAGER_H_
#define _MANAGER_H_


#include <stdio.h>

extern "C"
{
#include <libavformat/avformat.h>
#include <libavutil/dict.h>
}
#pragma warning(disable : 4996)
class Manager
{
public:
	int testing();

	int testing2(const char* fileName);



};

#endif // !_MANAGER_H_
