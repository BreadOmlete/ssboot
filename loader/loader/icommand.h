#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <string>
#include "iresponse.h"

template<class T>
class ICommand
{
public:
    ICommand();
    virtual ~ICommand();

    void send() throw(std::string);
    IResponse<T> *response();

protected:
    virtual void processResponse(std::string &buf) = 0;

protected:
    T *mBuffer;
    IResponse<T> *mResponse;


};

#endif // ICOMMAND_H
