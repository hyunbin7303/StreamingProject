


#include "../inc/server.h"
int main(int argc, char** argv)
{
	std::cout<<"START " << std::endl;
	UDP_Server::Server server{};
	int check = server.ServerStart();
	if(check == SERVICE_DONE)
	{
		std::cout <<"Service Done. " << std::endl;
	}
	return 0;
}
