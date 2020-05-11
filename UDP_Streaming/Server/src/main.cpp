


#include "../inc/server.h"

using namespace std;

int main(int argc, char** argv)
{
	int serviceNum = 0;
	int argValue = 0;
    
     argValue = Util::commandLineParser(argc, argv);
	//TODO: checking argument settings.
	UDP_Server::Server server{};
	int check = server.ServerStart(argc, argv);
	if(check == SERVICE_DONE)
	{
	}
	// if (argValue == SERVER_ARG)
	// {
	// 	while (1)
	// 	{
	// 		serviceNum = ServerStart(argc,argv);
	// 		if (serviceNum == SERVICE_DONE)	{
    //             break;
	// 		}
	// 		else if(serviceNum == SERVICE_ERROR)
	// 		{
    //             printf("SERVICE ERROR HAPPEN. \n");
    //             break;
	// 		}
	// 		else{
    //             printf("SOMETHING HAPPEN. \n");
    //             break;
	// 		}
	// 	}
	// }
	return 0;
}
