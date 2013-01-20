#include "boolresponse.h"

BoolResponse::BoolResponse() : StringResponse()
{
}

BoolResponse::~BoolResponse()
{
}

std::string BoolResponse::response()
{
    return "OK";
}

std::string BoolResponse::signature()
{
    return "BoolResponse";
}
