
#include "manager.h"


int Manager::testing() {
	printf("Testing method\n");
	AVFormatContext* fmt_ctx = NULL;
	AVDictionaryEntry* entry = NULL;
	int ret;

	const char* fileName = "C:\\testing.mp4";


	av_register_all();
	if ((ret = avformat_open_input(&fmt_ctx, fileName, NULL, NULL)))
	{
		return ret;
	}

	while ((entry = av_dict_get(fmt_ctx->metadata, "", entry, AV_DICT_IGNORE_SUFFIX)))
	{
		printf("%s = %s \n", entry->key, entry->value);
	}
	avformat_close_input(&fmt_ctx);
	return 0;
}

int Manager::testing2(const char* fileName) {
	AVFormatContext* fmt_ctx = NULL;
	AVCodecContext* codec_ctx = NULL;
	AVCodec* codec = NULL;
	int ret;
	int VideoStreamindex = -1;

	av_register_all();
	if ((ret = avformat_open_input(&fmt_ctx, fileName, NULL, NULL)))
	{
		//av_log(NULL, AV_LOG_ERROR, "CANNOT OPEN INPUT FILE \n");
		printf("ERROR : CANNOT OPEN INPUT FILE \n");
		goto end;
	}
	if (ret = avformat_find_stream_info(fmt_ctx, NULL) < 0)
	{
		//av_log(NULL, AV_LOG_ERROR, "CANNOT OPEN INPUT FILE \n");
		goto end;
	}

	for (int i = 0; i < fmt_ctx->nb_streams; i++)
	{
		if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			VideoStreamindex = i;
			break;
		}
	}
	if (VideoStreamindex < 0)
	{
		//av_log(NULL, AV_LOG_ERROR, "CANNOT GET STREAM \n");
		goto end;
	}


	avformat_close_input(&fmt_ctx);



end:

	if (codec_ctx) {
		avcodec_close(codec_ctx);
	}
	if (fmt_ctx) {
		avformat_close_input(&fmt_ctx);
	}

	return 0;
}

int Manager::LoadVideoStream()
{
	// Create a muxer that will output the video as MP4.
	//Muxer* muxer = new Muxer("filtered_video.mp4");

	//// Create a MPEG2 codec that will encode the raw data.
	//VideoCodec* codec = new VideoCodec(AV_CODEC_ID_MPEG2VIDEO);

	//// Create an encoder that will encode the raw audio data using the codec specified above.
	//// Tie it to the muxer so it will be written to file.
	//VideoEncoder* encoder = new VideoEncoder(codec, muxer);

	//// Create a video filter and do some funny stuff with the video data.
	//Filter* filter = new Filter("scale=640:150,transpose=cclock,vignette", encoder);

	//// Load a container. Pick the best video stream container in the container
	//// And send it to the filter.
	//Demuxer* demuxer = new Demuxer("big_buck_bunny.mp4");
	//demuxer->DecodeBestVideoStream(filter);

	//// Prepare the output pipeline.
	//// This will decode a small amount of frames so the pipeline can configure itself.
	//demuxer->PreparePipeline();

	//// Push all the remaining frames through.
	//while (!demuxer->IsDone())
	//{
	//	demuxer->Step();
	//}

	//// Save everything to disk by closing the muxer.
	//muxer->Close();


	return 0;
}

void Manager::pgm_save(unsigned char* buf, int wrap, int xsize, int ysize, const char* filename)
{
	FILE* f;
	int i;
	f = fopen(filename, "w");
	fprintf(f, "P5\n%d %d\n", xsize, xsize, 255);
	for (i = 0; i < ysize; i++)
	{
		fwrite(buf + i * wrap, 1, xsize, f);
	}
	fclose(f);
}

void Manager::decoding(AVCodecContext* dec_ctx, AVFrame* frame, AVPacket* pkt, const char* fileName)
{
	char buf[1024];
	int ret;

	ret = avcodec_send_packet(dec_ctx, pkt);
	if (ret < 0)
	{
		fprintf(stderr, "Error sending a packet for decoding \n");
		exit(1);
	}
	while (ret >= 0)
	{
		ret = avcodec_receive_frame(dec_ctx, frame);
		if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
		{
			return;
		}
		else if (ret < 0)
		{
			fprintf(stderr, "ERROR DURING DECODING \n");
			exit(1);
		}
		printf("SAVING frame %3d\n", dec_ctx->frame_number);
		fflush(stdout);

		snprintf(buf, sizeof(buf), "%s-%d", fileName, dec_ctx->frame_number);
		pgm_save(frame->data[0], frame->linesize[0], frame->width, frame->height, buf);
	}
}

void Manager::testDecoding()
{
	const AVCodec* codec;
	AVCodecParserContext* parser;


}





