#ifndef _mySocket
#define _mySocket

#include "./myHostInfo.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

class mySocket
{
public:
    mySocket(){}
    mySocket(int); 
    virtual ~mySocket()
    {
        close(socketId);
    }
    int getSocketId() { return socketId; }
	int getPortNumber() { return portNumber; }
    void setSendBufSize(int);
    void setReceiveBufSize(int);

protected:
    int portNumber;
    int socketId;
    struct sockaddr_in clientAddr;
};


class myTcpSocket : public mySocket
{
public:
	myTcpSocket() {};
	~myTcpSocket() {};
	myTcpSocket(int portId) : mySocket(portId) { };
	int sendMessage(string&);
	int recieveMessage(string&);
	void bindSocket();
	myTcpSocket* acceptClient(string&);
	void listenToClient(int numPorts = 5);
	virtual void connectToServer(string&,hostType);

};
#endif