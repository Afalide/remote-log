
#include <ws2tcpip.h>
#include "rlog/client.hpp"
#include "rlog/internal/resources_container.hpp"

RLOG_NS::client::client(const char* ip, unsigned short port)
    : _socket(0)
    , _res(nullptr)
    //, _resources(resources::get_instance())
{
    _res = new resources_container;

    //create the client socket

    int ip_version    = AF_INET;      //ipv4
    int socket_type   = SOCK_STREAM;  //tcp socket
    int protocol      = IPPROTO_TCP;  //tcp protocol

    _socket = ::socket(ip_version, socket_type, protocol);
    if(INVALID_SOCKET == _socket)
    {
        std::cout << "failed to create a socket" << std::endl;
        return;
    }

    //infos of a server

    sockaddr_in server_infos;
    in_addr     server_ip;

    ::memset(&server_infos, 0, sizeof(sockaddr_in));
    ::memset(&server_ip, 0, sizeof(in_addr));

    int result = ::InetPton(AF_INET, ip, &server_ip);
    if(SOCKET_ERROR == result)
    {
        std::cout << "failed to create socket ip infos" << std::endl;
        return;
    }

    server_infos.sin_family = AF_INET;
    server_infos.sin_addr = server_ip;
    server_infos.sin_port = htons(port);

    //connect to the server

    std::cout << "::connect ";
    result = ::connect(_socket, reinterpret_cast<const sockaddr*>(&server_infos), sizeof(sockaddr_in));
    if(SOCKET_ERROR == result)
    {
        std::cout << "failed (SOCKET_ERROR)" << std::endl;
        return;
    }
    else
    {
        std::cout << "success" << std::endl;
    }
}

RLOG_NS::client::~client()
{
    if(nullptr != _res)
    {
        delete _res;
        _res = nullptr;
    }

    if(0 != _socket)
    {
        ::closesocket(_socket);
    }
}

void
RLOG_NS::client::_send(std::string& str)
{
    std::cout << "::send ";

    int len = static_cast<int>(str.length()) +1;
    int result = ::send(_socket, str.c_str(), len, 0);
    if(SOCKET_ERROR == result)
    {
        std::cout << "failed (SOCKET_ERROR)" << std::endl;
        return;
    }
    else
    {
        std::cout << "success" << std::endl;
    }

    //do
    //{
    //    char buf[5];
    //    ::memset(buf, 0, sizeof(buf));
    //    std::cout << "waiting for server to reply..." << std::endl;
    //    int result = recv(_socket, buf, sizeof(buf), 0);
    //    if(result > 0)
    //        std::cout << "reply: " << buf << std::endl;
    //    else if(result == 0)
    //        std::cout << "Connection closed" << std::endl;
    //    else
    //        std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
    //} while(result > 0);
}

const char
RLOG_NS::client::endl[] = {'\r','\n'};

RLOG_NS::client&
RLOG_NS::client::operator<<(const char* data)
{
    _send_std(data);
    return *this;
}

RLOG_NS::client&
RLOG_NS::client::operator<<(const char& data)
{
    _send_std(data);
    return *this;
}

RLOG_NS::client&
RLOG_NS::client::operator<<(const int& data)
{
    _send_std(data);
    return *this;
}

RLOG_NS::client&
RLOG_NS::client::operator<<(const float& data)
{
    _send_std(data);
    return *this;
}

RLOG_NS::client&
RLOG_NS::client::operator<<(const void* data)
{
    _send_std(data);
    return *this;
}