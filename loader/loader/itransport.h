#ifndef ITRANSPORT_H
#define ITRANSPORT_H

#include <string>

class ITransport
{
public:
    ITransport();
    virtual ~ITransport();

    virtual void send(std::string &buf) throw(std::string) = 0;
    virtual void receive(std::string &buf) throw(std::string) = 0;
    virtual void setTimeout(int timeout_ms) = 0;

    static ITransport *transport();


protected:
    static ITransport *mTransport;

};

#endif // ITRANSPORT_H
