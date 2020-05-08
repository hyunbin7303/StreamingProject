

#ifndef _SERVER_H_
#define _SERVER_H_
#include "../../Common/inc/common.h"
int ServerStart(int argc, char** argv);
int generateResult(char * str);
int getServerIp(char* ip);
int FirstDataParse(char* DataInfoBuffer);
int LinuxTCPServerStart();
int LinuxUDPServerStart();
int isNumberCheck(char* str);
#endif
