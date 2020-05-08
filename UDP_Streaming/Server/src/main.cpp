


// #include "../inc/Common.h"
// #include "../inc/iSpeedClient.h"
// #include "../inc/iSpeedServer.h"
#include "../inc/server.hpp"

using namespace std;

int main(int argc, char** argv)
{
	int serviceNum = 0;
	int argValue = 0;
    
	
	// Calling Linux based method.
     argValue = commandLineParser(argc, argv);
	// if (argValue == SERVER_ARG)
	// {
	// 	printf("LINUX SERVER RUN. \n");
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
	// else if (argValue == CLIENT_ARG)
	// {
	// 	printf("LINUX CLIENT RUN. \n");
	// 	ClientStart(argc, argv);
	// }
	// else {
	// 	printf("[ERROR] Linux based not detectable. \n");
	// }
	// printf("SERVER SERVICE IS DONE. EXIT THIS PROGRAM.\n");
	cout <<"TESTING MAIN FUNCTION" << endl;

	return 0;
}
