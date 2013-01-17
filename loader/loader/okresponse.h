#ifndef OKRESPONSE_H
#define OKRESPONSE_H

#include <string>
#include "iresponse.h"

typedef IResponse<std::string> StringResponse;

class OKResponse : public StringResponse
{
public:
    OKResponse();
    ~OKResponse();

    std::string response();


protected:
    virtual std::string signature();

};

#endif // OKRESPONSE_H
