
#ifndef _MAIN_H_
#define _MAIN_H_

#include "../inc/server.h"
int main(int argc, char** argv)
{
	UDP_Server::Server server{};
	int check = server.ServerStart();
	if(check == SERVICE_DONE)
	{
		std::cout <<"Service Done. " << std::endl;
	}
	return 0;
}


#endif