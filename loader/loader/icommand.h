#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <string>
#include "iresponse.h"

template<class T>
class ICommand
{
public:
    ICommand() : mBuffer(0), mResponse(0) {};
    virtual ~ICommand() {};

    void send() throw(std::string)
    {
        ITransport *transport = ITransport::transport();
        if (!transport)
            throw std::string("Missing transport!");
    
        transport->send(mBuffer);

        std::string buf;
        transport->receive(buf);

        processResponse(buf);
    }
    
    IResponse<T> *response()
    {
        return mResponse;
    }

protected:
    virtual void processResponse(std::string &buf) = 0;

protected:
    T *mBuffer;
    IResponse<T> *mResponse;


};

#endif // ICOMMAND_H
