


#include "../inc/Common.h"
#include "../inc/iSpeedClient.h"
#include "../inc/iSpeedServer.h"

int main(int argc, char** argv)
{
	int serviceNum = SERVICE_RESTART;
	int argValue = 0;
	//generateResult("SOMETHING.\n");
	// Define whether OS is Linux or Window
#ifdef _WIN32 // WINDOW
	argValue = commandLineParser(argc, argv);
	if (argValue == SERVER_ARG)
	{
		// Call Start Server method.
		printf("WINDOW SERVER RUN START\n");
		while (1)
		{
			serviceNum = ServerStart(argc, argv);
			if (serviceNum == SERVICE_DONE)
			{
				continue;
			}
			else if (serviceNum == SERVICE_ERROR)
			{
				printf("SERVICE ERROR HAPPEN. \n");
				break;
			}
			else
			{
				printf("SOMETHING HAPPEN. Check return value of ServerStart method.\n");
				break;
			}
		}

	}
	else if (argValue == CLIENT_ARG)
	{
		ClientStart(argc, argv);
	}
	else if (argValue == FAIL_WINDOW)
	{
		printf("Error: -TCP or -UDP wasn't entered\n");
	}
#else // Linux Based.
    // Calling Linux based method.
    argValue = commandLineParser(argc, argv);
	if (argValue == SERVER_ARG)
	{
		printf("LINUX SERVER RUN. \n");
		while (1)
		{
			serviceNum = ServerStart(argc,argv);
			if (serviceNum == SERVICE_DONE)
			{

#ifdef _WIN32
                continue;
#else
                break;
#endif
			}
			else if(serviceNum == SERVICE_ERROR)
			{
                printf("SERVICE ERROR HAPPEN. \n");
                break;
			}
			else{
                printf("SOMETHING HAPPEN. \n");
                break;
			}
		}
	}
	else if (argValue == CLIENT_ARG)
	{
		printf("LINUX CLIENT RUN. \n");
		ClientStart(argc, argv);
	}
	else {
		printf("[ERROR] Linux based not detectable. \n");
	}


#endif // _WIN32

	printf("SERVER SERVICE IS DONE. EXIT THIS PROGRAM.\n");
	system("Pause");

	return 0;
}
