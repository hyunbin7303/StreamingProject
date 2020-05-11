
#include "mySocket.h"

#ifndef _SOC_EXCEPTION_H
#define _SOC_EXCEPTION_H


class MySocketException : public std::exception
{
public:
    MySocketException(const string &msg, bool sysMsg = false) throw();
    virtual ~MySocketException() throw();
    virtual const char* ErrorDescription() const throw() { return errorMsg.c_str();}

protected:
    string errorMsg;

};

#endif