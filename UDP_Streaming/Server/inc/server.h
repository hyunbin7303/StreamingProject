

#ifndef _SERVER_H_
#define _SERVER_H_
#include "../../Common/inc/common.h"




namespace UDP_Server
{
    class Server
    {
    public:
        Server(const std::string & addr, int port);
        ~Server(); // Destructor
        int getSocket() const;
        int getPort() const;
        std::string getAddress() const;
        int LinuxUDPServerStart();
        int ServerStart(int argc, char** argv);
        int packetReceive(char * info, size_t size);
        int timed_recv(char * msg, size_t, int maxWaitMS); // what is this?

        int getServerIp(char* ip);
        void generateResult(char * str);
    private:
        int _socket;
        int _port;
        std::string _address;
        struct addrinfo * _addrinfo;

    };

    class UDP_runtimeError 
    {

    };

};



int FirstDataParse(char* DataInfoBuffer);
int isNumberCheck(char* str);
#endif
