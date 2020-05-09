#ifndef _myHostInfo
#define _myHostInfo
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string>

using namespace std;    
enum hostType {NAME, ADDRESS};
const int HOST_NAME_LENGTH = 64;

class myHostInfo
{

private:
	char searchHostDB;     // search the host database flag
	struct hostent *hostPtr;    // Entry within the host address database

public:
    myHostInfo();
    myHostInfo(string& hostName, hostType type);
    ~myHostInfo()
    {
        endhostent();
    }



    // Retrieves the next host entry in the database
    char getNextHost();

    // Opens the host entry database
    void openHostDb()
    {
        endhostent();
        searchHostDB = 1;
        sethostent(1);
    }

    // Retrieves the hosts IP address
    char* getHostIPAddress() 
    {
        // struct in_addr is third member of sockaddr_in structure
        struct in_addr *addr_ptr;
		// the first address in the list of host addresses
        addr_ptr = (struct in_addr *)*hostPtr->h_addr_list;
		// changed the address format to the Internet address in standard dot notation
        return inet_ntoa(*addr_ptr);
    }    
    
    // Retrieves the hosts name
    char* getHostName()
    {
        return hostPtr->h_name;
    }


};

#endif