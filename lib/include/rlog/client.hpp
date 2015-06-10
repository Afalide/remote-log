
#ifndef RLOG_CLIENT_HPP
#define RLOG_CLIENT_HPP

#include <winsock2.h>
#include <sstream>
#include "rlog/common.hpp"

RLOG_NS_BEGIN

struct resources_container;

class RLOG_API client
{
    SOCKET _socket;
    //resources_p _resources;
    resources_container* _res;

    template<typename T> void _send_std(const T& data)
    {
        std::stringstream ss;
        ss << data;
        std::string str = ss.str();
        _send(str);
        //std::cout << "will send (&) : [" << str << "]" << std::endl;
    }

    template<typename T> void _send_std(const T* data)
    {
        std::stringstream ss;
        ss << data;
        std::string str = ss.str();
        _send(str);
        //std::cout << "will send (*) : [" << str << "]" << std::endl;
    }

    void _send(std::string& str);

public:
    client(const char* ip, unsigned short port);
    virtual ~client();

    client& operator<< (const char*);
    client& operator<< (const char&);
    client& operator<< (const int&);
    client& operator<< (const float&);
    client& operator<< (const void*);
};

RLOG_NS_END

#endif //RLOG_CLIENT_HPP
