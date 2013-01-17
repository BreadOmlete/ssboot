#include "okresponse.h"

OKResponse::OKResponse() : StringResponse()
{
}

OKResponse::~OKResponse()
{
}

std::string OKResponse::response()
{
    return "OK";
}

std::string OKResponse::signature()
{
    return "OKResponse";
}
