#include "../inc/myHostInfo.h"


myHostInfo::myHostInfo(string& hostName,hostType type)
{
    searchHostDB=0;

    try
    {
        if(type==Name)
        {
            hostPtr=gethostbyname(hostName.c_str());
            if(hostPtr== NULL)
            {
                //exception handling here
            }

        
        }
        else if(type==ADDRESS)
        {
            unsigned long netAddr=inet_addr(hostName.c_str());
            if(netAddr==-1)
            {
                //exception handling here
            }

            hostPtr=gethostbyaddr((char*)&netAddr,sizeof(netAddr),AF_INET);
            if(hostPtr)
            {
                //exception handling here
            }
        }
    }
    catch(Exception e)
    {
        
    }


}
