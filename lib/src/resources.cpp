
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "rlog/resources.hpp"
#include "smartp/smartp.hpp"

RLOG_NS::resources_p RLOG_NS::resources::_instance = nullptr;

RLOG_NS::resources::resources()
{
    //initialize the winsock library (v2.2)

    WORD requested_version = MAKEWORD(2, 2);
    WSADATA ws_data;
    int result;

    result = ::WSAStartup(requested_version, &ws_data);
    if(0 != result)
    {
        std::cout 
            << "failed to initialize winsock library"
            << " (code " << result << ")" << std::endl;
        return;
    }

    WORD loaded_version = ws_data.wVersion;
    if(LOBYTE(loaded_version) != 2 || HIBYTE(loaded_version) != 2)
    {
        std::cout 
            << "the loaded winsock is not version 2.2"
            << " (got " << LOBYTE(loaded_version) << "."
            << HIBYTE(loaded_version) << ")" << std::endl;
        return;
    }
}

RLOG_NS::resources::~resources()
{
    //clean the winsock library

    ::WSACleanup();
}

RLOG_NS::resources_p 
RLOG_NS::resources::get_instance()
{
    if(nullptr == _instance)
        _instance = new resources;

    return _instance;
}
