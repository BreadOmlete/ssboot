#ifndef IRESPONSE_H
#define IRESPONSE_H

#include <string>

template<class T>
class IResponse
{
public:
    IResponse() {};
    virtual ~IResponse() {};

    virtual T response() = 0;

    inline bool operator==(const IResponse<T>& x) { return x.signature() == signature(); }
    inline bool operator!=(const IResponse<T>& x) { return x.signature() != signature(); }

protected:
    virtual std::string signature() = 0;

};

typedef IResponse<std::string> StringResponse;

#endif // IRESPONSE_H
