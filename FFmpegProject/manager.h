#ifndef _MANAGER_H_
#define _MANAGER_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern "C"
{
#include <libavformat/avformat.h>
#include <libavutil/dict.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>


}
#define INBUF_SIZE 4096

#pragma warning(disable : 4996)


namespace FFmpeg
{
	class Manager
	{
	public:
		int testing();

		int testing2(const char* fileName);

		int LoadVideoStream();
		void pgm_save(unsigned char* buf, int wrap, int xsize, int ysize, const char* filename);
		void decoding(AVCodecContext* dec_ctx, AVFrame* frame, AVPacket* pkt, const char* fileName);
		int readFrame(AVPacket* packet);
		uint8_t streamsCount();
		
		
		void testDecoding(const char* fileName);


	};

}

#endif // !_MANAGER_H_
