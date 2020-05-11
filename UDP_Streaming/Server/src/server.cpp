

#include "../inc/server.h"
int FirstTime = 0;	// Checking whether it is the first time execution.
using namespace UDP_Server;
using namespace Util;





Server::Server(const std::string & addr,int port)
{
	char decimal_port[16];
}

// not sure this is used in somewhere.
int Server::getServerIp(char* ip)
{
	unsigned int addr;
	struct hostent *hp;
	char* localIp = "127.0.0.1";
	char buffer[512];

	gethostname(buffer, 512);
	addr = inet_addr(buffer);

	if (addr == 0xFFFFFFFF)
	{
		hp = gethostbyname(buffer);
		if (hp == NULL)
		{
			return 0;
		}
		addr = *((unsigned int*)hp->h_addr_list[0]);
	}
	else
	{
		hp = gethostbyaddr((char*)&addr, 4, AF_INET);
		if (hp == NULL)
		{
			return 0;
		}
		addr = *((unsigned int*)hp->h_addr_list[0]);
	}
	sprintf(ip, "%d.%d.%d.%d", ((addr >> 24) & 0xFF), ((addr >> 16) & 0xFF), ((addr >> 8) & 0xFF), (addr & 0xFF));
	return 1;
}


int Server::ServerStart(int argc, char** argv)
{

	FirstTime = 0;// Meaning the first time.
	int preVal = 0;// Getting previous value.
	int curVal = 0;// Getting the current value.

	/*SET UP TCP FOR FIRST MESSAGE*/
	int socket_type = SOCK_STREAM;	// Setting up Socket stream(TCP). Used for getting for input from client.
	int fromlen = 0;

    int listen_socket = 0;
	int client_len = 0;
	int client_socket = 0;
	struct sockaddr_in local;	// Socket Address local set up
	struct sockaddr_in from;	// Socket Address value set up
	char serverIp[512];
	int errorMsg = 0;
	int CountUnordered = 0;
	int CountMissing = 0;

	getServerIp(serverIp);	// get the server side address value.
	printf("Server's IP Address : [%s]\n", serverIp);


	// if ((listen_socket = socket(AF_INET, socket_type, 0)) <0) {
	// 	printf("ERROR, failed getting server socket\n");
	// 	return 2;
	// }	
	int a = 1;
	setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR,
		   (const void *)&a, sizeof(int));


	memset(&local,0,sizeof(local));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_port = htons(socket->getPortNumber());	// in network byte order

	printf("WAITING FOR CLIENT NETWORK PROTOCOL INFORMAION.... \n");
	int bindRt = 0 ;
	if ((bindRt = bind(listen_socket, (struct sockaddr*)&local, sizeof(local))) < 0)
	{
		printf("Binding returned %d, ERROR, binding failed\n",bindRt);
		return 3;
	}

	if (listen(listen_socket, 5) < 0)
	{
		printf("[LINUX ERROR] Listen FAIL. \n");
		close(listen_socket);
		exit(3);
	}




	char BlockSizeValueStr[20] = "";
	fromlen = sizeof(from);

		//  char* Buffer = (char *)malloc(g * sizeof(char)+1);
		if(Buffer == NULL)
		{
			printf("Dyniamic Memory allocation Fail\n");
			return -1;
		}
		printf("CLEAN UP DONE LINUX\n");
		close(listen_socket);
		int UDPsocket;
		struct sockaddr_in UDPClient;			// Socket Client address struct
		struct sockaddr_in UDPServer;

		int iReceiveFrom;
		int iUDPClientLen = sizeof(UDPClient);
		int iCloseSocket;

		memset(&UDPServer, 0, sizeof(UDPServer));
		memset(&UDPClient, 0, sizeof(UDPClient));
		UDPServer.sin_family = AF_INET;
		UDPServer.sin_addr.s_addr = INADDR_ANY;
		UDPServer.sin_port = htons(socket->getPortNumber());
		// UDPsocket = socket(AF_INET, SOCK_DGRAM, 0);
		int optval = 1;
		// make socket reusable
		setsockopt(UDPsocket, SOL_SOCKET, SO_REUSEADDR,
		   (const void *)&optval, sizeof(int));
		if (UDPsocket <0)
		{

			printf("UDP LINUX INVALID SOCKET \n"); 
			close(UDPsocket);
			return -1;
		}


		if (bind(UDPsocket, (const struct sockaddr*)&UDPServer, sizeof(UDPServer)) < 0 )
		{
			printf("UPD SOCKET BINDING ERROR\n");
			close(UDPsocket);
			return -1;
		}

		printf("UDP Receiving...\n");
		int i = 0;
		int MissingBlock = 0;
		double time_taken = 0.0;
		int iTimeout = 5000;
		// Used for time out.
		int iRet = setsockopt(UDPsocket,SOL_SOCKET,SO_RCVTIMEO,(const char *)&iTimeout,sizeof(iTimeout));
		unsigned int TotalBytes = 0;
		while (i < EachValue.numBlock)
		{
			//TODO Change this roof!
			iReceiveFrom = recvfrom(UDPsocket, Buffer, EachValue.BlockSize+1,0,(struct sockaddr *)&UDPClient, &iUDPClientLen); // Might have to do sizeof(Buffer) - 2
			if (iReceiveFrom < 0)
			{
				printf("ERROR CODE : [%d]", iReceiveFrom);
				if (iReceiveFrom == SOCKET_ERROR)
				{
					printf("SOCKET ERROR OCCUR \n");
				}
			}
			else // If Receiving information is successful.
			{
				TotalBytes += iReceiveFrom; // Save the total bytes.
				char* num = strtok(Buffer, "|");
				printf("BYTES RECEIVED : [%d], info :%s \n", iReceiveFrom, num);


			//	printf("RECEIVED INFORMATION [%s]\n", Buffer);
			}
			i++;
		}
		double SpeedCal = ((double)TotalBytes/(1024))  /  1024; // convert to megabytes
		SpeedCal = SpeedCal/time_taken; // megabytes per second
		SpeedCal = (SpeedCal*8); // megbits per second
		printf("Size: <<%d>> Sent: <<%d>> Time: <<%.5f>> Speed: <<%f> Missing: <<%d>> Disordered: <<%d>>\n", EachValue.BlockSize,EachValue.numBlock, time_taken, SpeedCal, AllMissingBlock, CountUnordered);
		// Freeing memory allocation.
		if (Buffer == NULL)
			printf("DYNAMIC ARRAY IS ALREADY NULL.\n");
		else
			free(Buffer);
		close(UDPsocket);

	return SERVICE_DONE;
}

