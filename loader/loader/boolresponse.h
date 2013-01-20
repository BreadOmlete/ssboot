#ifndef BOOLRESPONSE_H
#define BOOLRESPONSE_H

#include <string>
#include "iresponse.h"

class BoolResponse : public StringResponse
{
public:
    BoolResponse();
    ~BoolResponse();

    std::string response();


protected:
    virtual std::string signature();

};

#endif // OKRESPONSE_H
