#ifndef _mySocket
#define _mySocket

#include "./myHostInfo.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string>


class mySocket
{
public:
    mySocket(){}
    mySocket(int); 
    mySocket(const std::string & address, int port);
    virtual ~mySocket()
    {
        close(socketId);
    }
    int getSocketId() const { return socketId; }
	int getPortNumber() const { return portNumber; }
    std::string getAddr() const {return address; }
    void setSendBufSize(int);
    void setReceiveBufSize(int);
    
protected:
    int portNumber;
    int socketId;
    struct sockaddr_in clientAddr; // can we delete this one?
    std::string  address;
    struct addrinfo * _addrinfo;

};

// TODO : requires to delete or move to other directory.
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