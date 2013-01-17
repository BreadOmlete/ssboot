#include "itransport.h"

ITransport *ITransport::mTransport = 0;

ITransport::ITransport()
{
}

ITransport::~ITransport()
{
}

ITransport *ITransport::transport()
{
    return mTransport;
}
