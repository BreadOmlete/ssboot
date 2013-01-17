#include "itransport.h"
#include "icommand.h"


template<class T>
ICommand<T>::ICommand() : mBuffer(0), mResponse(0)
{
}

template<class T>
ICommand<T>::~ICommand()
{
}

template<class T>
void ICommand<T>::send() throw(std::string)
{
    ITransport *transport = ITransport::transport();
    if (!transport)
        throw std::string("Missing transport!");

    transport->send(mBuffer);

    std::string buf;
    transport->receive(buf);

    processResponse(buf);
}

template<class T>
IResponse<T> *ICommand<T>::response()
{
    return mResponse;
}
