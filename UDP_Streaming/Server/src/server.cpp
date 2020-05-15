

#include "../inc/server.h"
int FirstTime = 0;	// Checking whether it is the first time execution.
using namespace UDP_Server;
using namespace Util;



Server::Server(const std::string & addr,int port)
{
	char decimal_port[16];
//	snprintf(decimal_port, sizeof(dec))
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


bool Server::bindSocketForListening() const {
	if( mySoc->socketId <0 )
	{
		std::cerr <<"[SERVER] Binding failed. Possible Reason : Socket wasn't initialized. " << std::endl;
		return false;
	}

	sockaddr_in soc_addr;
	memset(reinterpret_cast<char*>(&soc_addr), 0, sizeof(soc_addr));
	soc_addr.sin_family = AF_INET;
	soc_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	soc_addr.sin_port = htons(mySoc->getPortNumber());
	int bindCheck = bind(mySoc->socketId, reinterpret_cast<sockaddr*>(&soc_addr), sizeof(soc_addr));
	if(bindCheck < 0)
	{
		std::cerr << "[SERVER] Binding Failed. " << std::endl;
		return false;
	}
	return true;
}


int Server::ServerStart(){
	// socket setup
	// socket->socketId = 

	 mySoc->socketId = socket(AF_INET, SOCK_DGRAM, 0);
	// setsockopt(mySoc->socketId , SOL_SOCKET, SO_REUSEADDR,
	// 	   (const void *)&a, sizeof(int));
	// binding.
	bindSocketForListening();
	int iReceiveFrom= 0;
	int iTimeout = 5000;
	// Used for time out.
	int iRet = setsockopt(mySoc->socketId,SOL_SOCKET,SO_RCVTIMEO,(const char *)&iTimeout,sizeof(iTimeout));
	char buffer[1024];
	int i = 0;		
	while (i < 5)
	{
			//TODO Change this roof!
		iReceiveFrom = recvfrom(mySoc->socketId, buffer, EachValue.BlockSize+1,0,(struct sockaddr *)&UDPClient, &iUDPClientLen); // Might have to do sizeof(Buffer) - 2
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
			char* num = strtok(buffer, "|");
			printf("BYTES RECEIVED : [%d], info :%s \n", iReceiveFrom, num);
		}
		i++;
	}
	close(mySoc->socketId);
	return 0;
}
