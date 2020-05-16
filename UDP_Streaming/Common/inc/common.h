


#ifndef _COMMON_H_
#define _COMMON_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <ctype.h>
#include <iostream>
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#define ERROR 0
#define FIRST_CONNECTION_FAIL -10
#define SIZEBUF 22000
#define LINUX_SERVER 1
#define LINUX_CLIENT 2
#define FAIL_WINDOW -1
#define FAIL_LINUX -2

#define SERVER_ARG 3
#define CLIENT_ARG 10
#define INVALID_CMD_ARG -1
#define UDP 20
#define TIMEOUT_MS 
#define SERVICE_DONE 		100
#define SERVICE_RESTART 	200
#define SERVICE_ERROR 		-100


namespace Util {
	int commandLineParser(int argc, char** argv);
	int isNumberCheck(char* str);
	void generateResult(char* str);
}





#endif
