/*
FILE			: iSpeedClient.c
PROGRAMMER		: Kevin Park, Julio Rivas
DATE			: 2019 - 1 - 21
PROG			: IAD - A01
DESCRIPTION		: this file is the client side of the c file. it has functionalities of client side applciation for TCP UDP(LINUX AND WINDOW)
*/

#include "../inc/Common.h"
#include "../inc/iSpeedClient.h"




/*
	METHOD	   : ClientStart
	PARAMETER  : argc - the number of the argument
		    argv - the argument string value from the cmd line.
	RETURN	   : return success 0, fail- return error code
	DESCRIPTION: This method is used for starting client side applcation.
*/

int ClientStart(int argc, char** argv)
{
#ifdef _WIN32
	SOCKET client_socket;
	WSADATA wsaData;	// WinSock initialization data
	 //initialize WinSock
	if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR) {
		return 1;
	}	/* endif */

#else
	int client_socket;

#endif
	int FirstTime = 0;
	int port = 0;
	int socket_type = SOCK_STREAM;
	unsigned int addr;
	struct hostent *hp;
	struct sockaddr_in server;
	int errorMsg = 0;

	char arrCommand[SIZEBUF] = "";
	memset(arrCommand, 0, EachValue.BlockSize); // memset array to 0 
	int tmpPort = 0;
	tmpPort = EachValue.portNum; // port num gotten from cmd line
	if (tmpPort <= 0)
		port = 3000;	// default
	else
		port = tmpPort; // port user chose
	/*
	 * resolve the ip address (in case it's a name rather than a number)
	 */
	addr = inet_addr(ipAdd);
	if (addr == INADDR_NONE)
	{
		hp = gethostbyname(ipAdd);
		if (hp == NULL)
		{
			return 3;
		}
		addr = *((unsigned int *)hp->h_addr_list[0]);
	}
	/*
	 * copy the resolved information into the sockaddr_in structure
	 */
	memset(&server, 0, sizeof(server));
	server.sin_addr.s_addr = addr;  // addr is ip address as an int 
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	/*
	 * create the client socket
	 */
	client_socket = socket(AF_INET, socket_type, 0);
	if (client_socket == INVALID_SOCKET) {
		printf("Error, can not get socket for client\n");
		return 4;
	}
	/*
	 * now connect this socket to the server
	 */
	printf("Connecting\n");// Connection to the server
	if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
		printf("Error, could not connect to server\n");
		return 5;
	}

	printf("\nConnected! \n"); // The block of size.
	char clientInfo[20] = "";	// Client information buffer
	sprintf(clientInfo, "|%d|%d|%d|", EachValue.Protocol, EachValue.BlockSize, EachValue.numBlock);// storing all information in the client side.
	int clientInfoLength = (int)strlen(clientInfo);// the length of the client
	clientInfo[clientInfoLength] = '\0';			// putting the null terminator in the end.
	int test = 0;
	if (FirstTime == 0)			// The first time try
	{
		printf("Sending client information to server : [%s] \n", clientInfo);
#ifdef _WIN32
		send(client_socket, clientInfo, (int)strlen(clientInfo), 0); // sending data
#else 
		test = write(client_socket, clientInfo, sizeof(clientInfo));
//		printf("The number of byes sent %d \n", test);
		printf("SENDED INFO IN THE FIRST LINE : %s \n", clientInfo);
		if (test < 0)
		{
			printf("[Client] Sending Fail \n");
			close(client_socket);
			return -1;
		}
#endif 
		FirstTime = 1; // meaning that Already did first time.
	}
	char* DynamicArr = (char *)malloc(EachValue.BlockSize * sizeof(char)+1);
	if (DynamicArr == NULL)
			return -1;
	if (EachValue.Protocol == TCP)
	{
		// Calculate the time taken by fun() 
		clock_t t = clock();
		int i = 0;
		int numBlockCounter = 0;
		int tempBufLength = 0;
		int tempStoreLength = 0;
		// Finalizing message to be sent
		int TCPByteCheck = 0;
		int TCPErrorCount = 0;
		char tempBuf[10001] = "";
		char tempStore[10001] = "";
		sprintf(tempBuf, "%05d|%09f|DATA CONTENT", i, (double)t / CLOCKS_PER_SEC);
		tempBufLength = (int)strlen(tempBuf);
		memset(tempStore, '-', EachValue.BlockSize - tempBufLength);
		while (i < EachValue.numBlock)
		{
			t = clock();
			sprintf(tempBuf, "%05d|%09f|DATA CONTENT", i, (double)t / CLOCKS_PER_SEC);
			tempBufLength = (int)strlen(tempBuf);
			strcat(tempBuf, tempStore);
			strcpy(DynamicArr, tempBuf);
			//printf("Buffer Information [%s]\n", DynamicArr);
#ifdef _WIN32
			TCPByteCheck = send(client_socket, DynamicArr, (int)strlen(DynamicArr), 0);
#else
			TCPByteCheck = write(client_socket, DynamicArr, (int)strlen(DynamicArr));
			printf("TCP BYTES CHECK : %d \n", TCPByteCheck);
			printf("TCP Sended Information : %s \n", DynamicArr);
#endif
			if (TCPByteCheck < 0)
			{
#ifdef _WIN32
				printf("SENDING FAILED. ERROR CODE [%d] \n", WSAGetLastError());
#else
				printf("SENDING FAILED LINUX. ERROR CODE %d \n", TCPByteCheck);
#endif
				TCPErrorCount++;	// Missing TCP Packets.
			}
		//	memset(tempBuf, 0, sizeof(tempBuf));
			memset(DynamicArr, 0, sizeof(DynamicArr)+1);
			i++;
		}
		printf("Passing All data is done. \n");
		//close our communications path
#ifdef _WIN32
		closesocket(client_socket);
		WSACleanup();
#else 
		close(client_socket);
#endif
	}
	else if (EachValue.Protocol == UDP)
	{
		//close our communications path
#ifdef _WIN32
		closesocket(client_socket);
		WSACleanup();
#else 
		close(client_socket);
#endif
		ClientUDP(argc, argv);
	}

	// Free memory allocation array.
	if (DynamicArr == NULL)
		printf("Insufficiant memory available. \n");
	else
		free(DynamicArr);
	printf("EVERYTHING IS DONE. Client OFF. \n");
	return 0; // end _WIN32

}


/*
	METHOD	   : ClientUDP
	PARAMETER  : argc - the number of argument
				 argv - the string value of argument
	RETURN	   : Return the error code depends on process
	DESCRIPTION: This is the client side of the UDP. it has both UDP and TCP.
*/
int ClientUDP(int argc, char** argv)
{
	clock_t t;		// Clock value for checking time.
	struct sockaddr_in UDPServer;// UDP server socket address setup
	char Buffer[SIZEBUF] = "";
#ifdef _WIN32
	WSADATA WinSockData;
	int iWsaStartup;
	int iWsaCleanup;
	SOCKET UDPClientSocket;
	iWsaStartup = WSAStartup(MAKEWORD(2, 2), &WinSockData);
	if (iWsaStartup != 0)
	{
		printf("WSA StartUP RUN FAILED.\n");
		return -1;
	}
#else
	int UDPClientSocket;
#endif
	int iBind = 0;			// Binding checking value.
	int iReceiveFrom = 0;
	int iUDPClientLen = sizeof(UDPServer);
	int iCloseSocket;
	int iSendto;

	// UDP SERVER setup.
	UDPServer.sin_family = AF_INET;
	UDPServer.sin_addr.s_addr = inet_addr(EachValue.IpAddr);
	UDPServer.sin_port = htons(EachValue.portNum);
	// Creating UDP client socket
	if ((UDPClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
#ifdef _WIN32
		printf("INVALID SOCKET - %d\n", WSAGetLastError());
		iCloseSocket = closesocket(UDPClientSocket);// closing Socket.
#else  
		printf("ERROR, Invalid socket\n");
		close(UDPClientSocket);	// Closing UDP socket.
#endif
		return -1;
	}
	int i = 0;
	int UDPByteCheck = 0;
	int UDPErrorCount = 0;
	char* DynamicArrUDP = (char *)malloc(EachValue.BlockSize * sizeof(char));	// Creating dynamic array for UDP 

	t = clock(); // start timer
	char tempBuf[20000] = "";
	sprintf(tempBuf, "%05d|%.5f|DATA CONTENT", i, (double)t / (CLOCKS_PER_SEC));
	int tempBufLength = strlen(tempBuf);	// The number of buffer for sending.

#ifdef _WIN32
	memset(Buffer, '-', ((unsigned __int64)EachValue.BlockSize)- tempBufLength); // Filling up with - value. 
	strcpy(DynamicArrUDP, Buffer);	
#else 
	memset(Buffer, '-', (EachValue.BlockSize)-tempBufLength);// Filling up with - value. 
	strcpy(DynamicArrUDP, Buffer);
#endif
	while (i < EachValue.numBlock)
	{
#ifdef _WIN32
		Sleep(1);
#else
		sleep(1);
#endif
		// copy message that was already made 
		char MsgBuffer[10001];	// Message Buffer Size.
		strcpy(MsgBuffer, DynamicArrUDP);

		// Creating network Protocol
		sprintf(tempBuf, "%05d|%.5f|DATA CONTENT", i, (double)t / (CLOCKS_PER_SEC));
		strcat(tempBuf, MsgBuffer);	// Merging all string.
#ifdef _WIN32
		iSendto = sendto(UDPClientSocket, tempBuf, EachValue.BlockSize, 0, (SOCKADDR*)&UDPServer, sizeof(UDPServer));
		printf("THE THE NUMBER OF BYTES SENT : [%d] \n", iSendto);
		if (iSendto == SOCKET_ERROR)
		{
			printf("SENDING DATA FAILED : %d \n", WSAGetLastError());
		}
#else
		// Linux Sending Information .
		tempBufLength = strlen(tempBuf)-1;
		tempBuf[tempBufLength] = '\0';	// put null terminator in the end of the buffer.
		iSendto = sendto(UDPClientSocket, tempBuf, EachValue.BlockSize, 0, (struct sockaddr*)&UDPServer, sizeof(UDPServer));
		printf("THE THE NUMBER OF BYTES SENT : [%d] \n", iSendto);
		//printf("Buffer Sending Information [%s]\n", tempBuf);
#endif
		i++;
	}
#ifdef _WIN32
	iCloseSocket = closesocket(UDPClientSocket); // closing UDP client socket
	if (iCloseSocket == SOCKET_ERROR)
	{
		printf("CLOSING SOCKET PROBLEM HAPPEN. : %d \n", WSAGetLastError());
	}
	iWsaCleanup = WSACleanup();
	if (iWsaCleanup == SOCKET_ERROR)
	{
		printf("CLEANUP ERROR :%d \n", WSAGetLastError());
	}
#else
	printf("SENT DATA\n");
	close(UDPClientSocket);
#endif //  _WIN32
	printf("CLEAN UP DONE\n");
	return 0;
}