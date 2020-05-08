
#include "../inc/Common.h"



int portValue = 0;
char* Address = "";
int BlockSize = 0;
int numBlocks = 0;

int commandLineParser(int argc, char** argv)
{
	int returnValue = 0;
	if (argc == SERVER_ARG)
	{
		if (strcmp(argv[1], "-p") == 0)
		{
			char* ServerPortStr = argv[2];
			if (isNumberCheck(ServerPortStr) == 0) {
				printf("PORT VALUE ERROR \n");
				return INVALID_CMD_ARG;
			}
			EachValue.portNum = atoi(ServerPortStr);
			returnValue = SERVER_ARG;
		}
		else
		{
			returnValue = SERVER_ARG;
		}
	}
	else if (argc == CLIENT_ARG) // Meaning Client side.
	{
		int i = 0;
		// Validation Function
		for (i =0; i < CLIENT_ARG; i++)
		{

			if ((strcmp(argv[i],"-UDP") == 0) || (strcmp(argv[i], "-udp") == 0))
			{
				EachValue.Protocol = UDP;
			}
			if (strcmp(argv[i],"-a") ==0)
			{
				Address = argv[i + 1];
				printf("Address Value %s \n", Address);
				ipAdd = Address; // assign to global var
				EachValue.IpAddr = Address;
			}
			if (strcmp(argv[i],"-p") == 0)
			{
				char* portStr = argv[i + 1];
				if (isNumberCheck(portStr) == 0) {
					printf("PORT VALUE ERROR \n");
					return INVALID_CMD_ARG;
				}
				portValue = atoi(portStr);
				EachValue.portNum = portValue;
				printf("Port Value : %d \n", portValue);
			}
			if (strcmp(argv[i],"-s") == 0)
			{
				char* BlockSizeStr = argv[i + 1];
				BlockSize = atoi(BlockSizeStr);
				EachValue.BlockSize = BlockSize;
				printf("Block Size Value : %u \n", BlockSize);
			}
			if (strcmp(argv[i],"-n") == 0)
			{
				char* numBlocksStr = argv[i + 1];
				numBlocks = atoi(numBlocksStr);
				EachValue.numBlock = numBlocks;
				printf("The number of Blocks: %u \n", numBlocks);
			}
		}
		if (i == 10) // meaning 10 arguments were read
		{
			returnValue = i;
		}
	}
	else
	{
		printf("Argument else.. ");
		returnValue = ERROR;
	}

	return returnValue;
}

int isNumberCheck(char* str)
{
	int isDigit = 0;
	int i = 0;
	while (i < strlen(str))
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			isDigit = 1;
		}
		else
		{
			isDigit = 0;

		}
		i++;
	}
	return isDigit;
}

