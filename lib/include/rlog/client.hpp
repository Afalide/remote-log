
#ifndef RLOG_CLIENT_HPP
#define RLOG_CLIENT_HPP

#include <winsock2.h>
#include <sstream>
#include <inttypes.h>
#include "rlog/common.hpp"

RLOG_NS_BEGIN

struct resources_container;

class RLOG_API client
{
    SOCKET _socket;
    resources_container* _res;

    template<typename T> void _send_std(const T& data)
    {
        std::stringstream ss;
        ss << data;
        std::string str = ss.str();
        _send(str);
    }

    template<typename T> void _send_std(const T* data)
    {
        std::stringstream ss;
        ss << data; //displays pointer adress
        std::string str = ss.str();
        _send(str);
    }

    void _send(std::string& str);

public:

    static const char endl[];

    client(const char* ip, unsigned short port);
    virtual ~client();
    client& operator<< (const char*);
    client& operator<< (const char&);
    client& operator<< (const wchar_t*);
    client& operator<< (const int&);
    client& operator<< (const int64_t&);
    client& operator<< (const uint64_t&);
    client& operator<< (const float&);
    client& operator<< (const void*);



    
    
};

RLOG_NS_END

#endif //RLOG_CLIENT_HPP
