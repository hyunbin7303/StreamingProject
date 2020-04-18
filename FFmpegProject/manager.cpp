
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

int Manager::testing2(const char * fileName) {
	AVFormatContext* fmt_ctx = NULL;
	int ret;

	av_register_all();
	if ((ret = avformat_open_input(&fmt_ctx, fileName, NULL, NULL)))
	{
		return ret;
	}


}