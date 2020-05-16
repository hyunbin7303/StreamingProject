


#include "../inc/server.h"
int main(int argc, char** argv)
{
	int argValue = 0;
	argValue = Util::commandLineParser(argc, argv);
	//TODO: checking argument settings.
	UDP_Server::Server server{};
	int check = server.ServerStart();
	if(check == SERVICE_DONE)
	{
		std::cout <<"Service Done. " << std::endl;
	}
	return 0;
}
