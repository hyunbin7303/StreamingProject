
#include "../inc/server.hpp"

// #include "../inc/iSpeedServer.h"
int FirstTime = 0;	// Checking whether it is the first time execution.

int ServerStart(int argc, char** argv)
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
	printf("Server's Port      : [%d]\n", EachValue.portNum);
	printf("Server's IP Address : [%s]\n", serverIp);


	if ((listen_socket = socket(AF_INET, socket_type, 0)) <0) {
		printf("ERROR, failed getting server socket\n");
		return 2;
	}	/* endif */
	int a = 1;
	setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR,
		   (const void *)&a, sizeof(int));


	memset(&local,0,sizeof(local));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_port = htons(EachValue.portNum);	// in network byte order

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
	if (FirstTime == 0)
	{

        client_len = sizeof(from);
		if ((client_socket = accept(listen_socket, (struct sockaddr *)&from, &client_len)) < 0)	{
			printf("[LINUX ERROR] Accept Fail. \n");
			close(listen_socket);
			exit(4);
		}
		printf("[LINUX] Accept Works.\n");

		// Posix read() api does not return a NULL terminated string which was stuffing garbage characters in the buffer.
		int receivedNum = read(client_socket, BlockSizeValueStr,sizeof(BlockSizeValueStr));
		printf("Rceveid Num : %d \n", receivedNum);
		if (receivedNum < 0)
		{
			printf("ERROR reading from Socket.\n");
		}
		//close(client_socket);
		//exit(0);
		// getting the first data input from client side and store it.
		if (FirstDataParse(BlockSizeValueStr) == -1)
		{
			printf("[ERROR] First Data Information Format Fail.\n");
			return 4;
		}
		FirstTime = 1;// Meaning that got the first connection whether it is UDP or TCP.
	}

	int iWsaStartup;
	int iWsaCleanup;
	int AllMissingBlock;// The number of the missing blocks.
	clock_t t;			// Used for timechecking.

	// IF TCP Connection.
	if (EachValue.Protocol == TCP)
	{

		char* DynamicArr = (char *)malloc(EachValue.BlockSize * sizeof(char)+1);
		if(DynamicArr == NULL)
		{
			printf("Dyniamic Memory allocation Fail\n");
			return -1;
		}
		// Time counting start
		char * FirstValue = "";		// The first parameter of the network protocol in the Buffer.
		int i = 0;
		double time_taken = 0.0;
		t = clock();// start time
		unsigned int TotalBytes = 0;
		char* secondValue = "" ;
		while (i < EachValue.numBlock)
		{
#ifdef _WIN32
			int checkReceived = recv(message_socket, DynamicArr, EachValue.BlockSize, 0);
#else
			int checkReceived = read(client_socket, DynamicArr, EachValue.BlockSize);
#endif
			if (checkReceived <= 0) // If received value is minus value, it means error.
			{
				if (checkReceived == -1)
				{
					printf("Exiting loop\n");
					return -9;
				}
				else if (checkReceived == 0) // messages stop sending // reconfigure tcp
				{
					printf("Received value is 0. Please check Receiving method. \n");
#ifdef _WIN32
					//closesocket(message_socket);
					//printf("Waiting for new connection\n");
					//message_socket = accept(listen_socket,(struct sockaddr*)&from, &fromlen);
#else
					//close(client_socket);
					//printf("Waiting for new connection\n");
					//client_socket = accept(listen_socket,(struct sockaddr*)&from, &fromlen);
					//int checkReceived = read(client_socket, Buffer, EachValue.BlockSize);
#endif
				}
			}
			TotalBytes += checkReceived;			// Getting the Total Bytes number.
			FirstValue = strtok(DynamicArr, "|");	// Getting the index number of the received message.
			curVal = atoi(FirstValue);				// Convert to integer.
			//printf("Current Received Packet Num : [%d], Previous Num : [%d]\n", curVal, preVal);
			if (curVal < preVal)
			{
				printf("UNORDERED VALUE DETECTED. \n");
				CountUnordered++;				// Counting Unordered.
			}
			preVal = curVal;
			// Comparison the block size value
			i++;
		}
		t = clock() - t;
		time_taken = ((double)t) / (CLOCKS_PER_SEC / 1000); // in milliseconds
		AllMissingBlock = EachValue.numBlock - i;	// Calculating the all missing blocks.

		//printf("RECEIVED TOTAL BYTES . [%d] \n", TotalBytes);
		//double SpeedCal = (double)TotalBytes / time_taken;  // Speed Calculation Value  (Bytes / Seconds)
		double SpeedCal = ((double)TotalBytes/(1024))  /  1024; // convert to megabytes
		SpeedCal = SpeedCal/time_taken; // megabytes per second
		SpeedCal = (SpeedCal*8); // megbits per second
		printf("Size: <<%d>> Sent: <<%d>> Time: <<%.5f>> Speed: <<%f> Missing: <<%d>> Disordered: <<%d>>\n", EachValue.BlockSize,EachValue.numBlock, time_taken, SpeedCal, AllMissingBlock, CountUnordered);
		
		if (DynamicArr == NULL)
		{
			printf("DYNAMIC ARRAY IS ALREADY NULL.\n");
		}
		else
			free(DynamicArr);
#ifdef _WIN32 // WINDOWS 
		printf("Closing windows sokcet\n");
		closesocket(listen_socket);
#else // LINUX
	//	close(listen_socket);
		int enableReuse = 1; 
		printf("Closing linux sokcet\n");
		if(setsockopt(listen_socket,SOL_SOCKET,SO_REUSEADDR,&enableReuse,sizeof(int))<0)
		{
			printf("ERROR setsockpot failed\n");
		}

#endif
	} // TCP If statement closing.
	

	else if (EachValue.Protocol == UDP)
	{

		char* Buffer = (char *)malloc(EachValue.BlockSize * sizeof(char)+1);
		if(Buffer == NULL)
		{
			printf("Dyniamic Memory allocation Fail\n");
			return -1;
		}
		// Closing TCP Socket for the first connection.
#ifdef _WIN32
		iWsaCleanup = WSACleanup();
		if (iWsaCleanup == SOCKET_ERROR)
			printf("CLEANUP ERROR :%d \n", WSAGetLastError());
		printf("CLEAN UP DONE WINDOWS\n");
		closesocket(listen_socket);
#else
		printf("CLEAN UP DONE LINUX\n");
		close(listen_socket);
#endif
		// -------------UDP SETTING UP START -------------------------
#ifdef _WIN32
		SOCKET UDPsocket;						// UDP Socket Init.
		WSADATA WinSockData;					// Window Socket data Initialization.
		iWsaStartup = WSAStartup(MAKEWORD(2, 2), &WinSockData);
		if (iWsaStartup != 0)
		{
			printf("UDP WSA StartUP RUN FAILED.\n");
			return -1;
		}
#else
		int UDPsocket;
#endif
		struct sockaddr_in UDPClient;			// Socket Client address struct
		struct sockaddr_in UDPServer;

		//char Buffer[SIZEBUF] = "";
		//int iBufferLen = (int)(strlen(Buffer));  // The Total length of the Buffer.
		int iReceiveFrom;
		int iUDPClientLen = sizeof(UDPClient);
		int iCloseSocket;

		memset(&UDPServer, 0, sizeof(UDPServer));
		memset(&UDPClient, 0, sizeof(UDPClient));
		UDPServer.sin_family = AF_INET;
		UDPServer.sin_addr.s_addr = INADDR_ANY;
		UDPServer.sin_port = htons(EachValue.portNum);
#ifdef _WIN32
		UDPsocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
#else 
		UDPsocket = socket(AF_INET, SOCK_DGRAM, 0);
		int optval = 1;
		// make socket reusable
		setsockopt(UDPsocket, SOL_SOCKET, SO_REUSEADDR,
		   (const void *)&optval, sizeof(int));
#endif	
		if (UDPsocket <0)
		{

#ifdef _WIN32
			printf("UDP INVALID SOCKET - %d\n", WSAGetLastError());
			iCloseSocket = closesocket(UDPsocket);
			return -1;
#else
			printf("UDP LINUX INVALID SOCKET \n"); 
			close(UDPsocket);
			return -1;
#endif
		}


		if (bind(UDPsocket, (const struct sockaddr*)&UDPServer, sizeof(UDPServer)) < 0 )
		{
#ifdef _WIN32
			printf("SOCKET BUILDING ERROR - %d \n", WSAGetLastError());
			closesocket(UDPsocket);
			return -1;
#else
			printf("UPD SOCKET BINDING ERROR\n");
			close(UDPsocket);
			return -1;
#endif
		}

		printf("UDP Receiving...\n");
		int i = 0;
		int MissingBlock = 0;
		double time_taken = 0.0;
		t = clock();// start time
		int iTimeout = 5000;
		// Used for time out.
		int iRet = setsockopt(UDPsocket,SOL_SOCKET,SO_RCVTIMEO,(const char *)&iTimeout,sizeof(iTimeout));
		unsigned int TotalBytes = 0;
		while (i < EachValue.numBlock)
		{
#ifdef _WIN32
			// Receiving information
			iReceiveFrom = recvfrom(UDPsocket, Buffer,EachValue.BlockSize+1,0, (SOCKADDR*)&UDPClient, &iUDPClientLen);
			if (WSAGetLastError() == WSAETIMEDOUT)// time out checking.
			{
				printf("Connection Time out.\n");
				break;
			}
#else
			iReceiveFrom = recvfrom(UDPsocket, Buffer, EachValue.BlockSize+1,0,(struct sockaddr *)&UDPClient, &iUDPClientLen); // Might have to do sizeof(Buffer) - 2
#endif
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
		t = clock() - t;
		time_taken = ((double)t) / (CLOCKS_PER_SEC / 1000); // in milliseconds
		AllMissingBlock = EachValue.numBlock - i;
		double SpeedCal = ((double)TotalBytes/(1024))  /  1024; // convert to megabytes
		SpeedCal = SpeedCal/time_taken; // megabytes per second
		SpeedCal = (SpeedCal*8); // megbits per second
		printf("Size: <<%d>> Sent: <<%d>> Time: <<%.5f>> Speed: <<%f> Missing: <<%d>> Disordered: <<%d>>\n", EachValue.BlockSize,EachValue.numBlock, time_taken, SpeedCal, AllMissingBlock, CountUnordered);
		
		// Freeing memory allocation.
		if (Buffer == NULL)
			printf("DYNAMIC ARRAY IS ALREADY NULL.\n");
		else
			free(Buffer);
#ifdef  _WIN32
		closesocket(UDPsocket);	// UDP Socket closing.
#else 
		close(UDPsocket);
#endif 
	}

#ifdef _WIN32
	iWsaCleanup = WSACleanup();
	if (iWsaCleanup == SOCKET_ERROR)
	{
		printf("CLEANUP ERROR :%d \n", WSAGetLastError());
	}
#endif
	printf("CLEAN UP DONE\n");
	return SERVICE_DONE;
}


/*
METHOD		: generateResult
PARAMETER	: str - the string inforatmion that wants to store in to text file.
RETURN		: return success or not .
DESCRIPTION : This method is used for generating file to get result value.
*/
int generateResult(char* str)
{
	FILE * file;
	file = fopen("Result.txt", "a");
	if (file == NULL)
	{
		printf("Please check whether file exists and you have write privilege.\n");
		exit(EXIT_FAILURE);
	}
	fprintf(file, "%s", str);
	fclose(file);
	return 0;
}

#ifdef _WIN32
int handle_communications(/*SOCKET message_socket*/)
{
	return 0;
}	

#else
int LinuxTCPServerStart()
{
	char buffer[BUFSIZ];
	int server_socket = 0;
	int client_socket;
	int client_len;
	struct sockaddr_in client_addr, server_addr;
	int len;
	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("[LINUX ERROR] Server Socket Error Detection.\n");
		exit(1);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(EachValue.portNum);

	if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("[LINUX ERROR] BINDING FAIL. \n");
		close(server_socket);
		exit(2);
	}
	if (listen(server_socket, 5) < 0)
	{
		printf("[LINUX ERROR] Listen FAIL. \n");
		close(server_socket);
		exit(3);
	}
	printf("LINUX SERVER TCP LISTEN SUCCESS.\n");

	while (1)
	{
		client_len = sizeof(client_addr);
		if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len)) < 0)
		{
			printf("[LINUX ERROR] Accept Fail. \n");
			close(server_socket);
			exit(4);
		}
		if (fork() == 0) {

			read(client_socket, buffer, BUFSIZ);
			write(client_socket, buffer, len);
			close(client_socket);
			exit(0);


		}
		else {

			close(client_socket);
		}
	}
	close(client_socket);
	return 1;
}


#endif


// getting the ip address of the server  credit: IAD Resources, getip.c

/*
	METHOD	   : getServerIP
	PARAMETER  : ip - ip address string.
	RETURN	   : Error return if it's wrong.
	DESCRIPTION: get the ip address value.
*/

int getServerIp(char* ip)
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

#ifdef LITTLEENDIAN
	sprintf(ip, "%d.%d.%d.%d", (addr & 0xFF), ((addr >> 8) & 0xFF), ((addr >> 16) & 0xFF), ((addr >> 24) & 0xFF));
#else
	sprintf(ip, "%d.%d.%d.%d", ((addr >> 24) & 0xFF), ((addr >> 16) & 0xFF), ((addr >> 8) & 0xFF), (addr & 0xFF));
#endif

	return 1;
}




/*
	METHOD	   :
	PARAMETER  :
	RETURN	   :
	DESCRIPTION:
*/

int FirstDataParse(char* DataInfoBuffer)
{
	// Data Format will be : PROTOCOL|ADDRESS|PORT|BLOCK SIZE|NUM BLOCK
	// Parsing Start.
	char * parseStr;
	parseStr = strtok(DataInfoBuffer, "|");
	int i = 0;
	while (parseStr != NULL)
	{
		if (i == 0)
		{
			if (strcmp(parseStr, "10") == 0)
			{
				EachValue.Protocol = TCP;
			}
			else if (strcmp(parseStr, "20") == 0)
			{
				EachValue.Protocol = UDP;
			}
		}
		else if (i == 1)
		{
			printf("Arg[2]: %s\n", parseStr);
			EachValue.BlockSize = atoi(parseStr);
		}
		else if (i == 2)
		{
			printf("Arg[3]: %s\n", parseStr);
			EachValue.numBlock = atoi(parseStr);
		}
		parseStr = strtok(NULL, "|");
		i++;
	}
	return 1;
}
