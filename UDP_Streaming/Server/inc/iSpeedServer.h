/*
	=============================================================
	File:	iSpeedServer.h
	Date:	Jan. 08 2018
	Description: This file will contain all the includes,
	constants, struct and function prototypes for the server side
	of this application.
	=============================================================
*/

#ifndef _ISPEEDSERVER_H_
#define _ISPEEDSERVER_H_
#include "Common.h"

int ServerStart(int argc, char** argv);
int generateResult(char * str);
int getServerIp(char* ip);
int FirstDataParse(char* DataInfoBuffer);
#ifdef _WIN32
//int handle_communications(SOCKET message_socket);
#else
int LinuxTCPServerStart();
int LinuxUDPServerStart();

#endif // _WIN32
int isNumberCheck(char* str);


#endif
