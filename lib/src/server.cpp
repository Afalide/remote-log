
#include <winsock2.h>
#include <ws2tcpip.h>
#include "rlog/server.hpp"
#include "rlog/internal/resources_container.hpp"

RLOG_NS::server::server()
    : _res(nullptr)
{
    _res = new resources_container;
}

RLOG_NS::server::~server()
{
    if(nullptr != _res)
    {
        delete _res;
        _res = nullptr;
    }
}

void RLOG_NS::server::listen(const char* ip, unsigned short port)
{
    //create the server socket

    int ip_version    = AF_INET;      //ipv4
    int socket_type   = SOCK_STREAM;  //tcp socket
    int protocol      = IPPROTO_TCP;  //tcp protocol

    SOCKET server_socket = ::socket(ip_version, socket_type, protocol);
    if(INVALID_SOCKET == server_socket)
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

    //bind the server ip to this socket

    result = ::bind(server_socket, reinterpret_cast<const sockaddr*>(&server_infos), sizeof(sockaddr_in));
    if(SOCKET_ERROR == result)
    {
        std::cout << "failed to bind server infos to socket" << std::endl;
        return;
    }

    //put the socket in a listening state

    result = ::listen(server_socket, 10); //10 client connections max
    if(SOCKET_ERROR == result)
    {
        std::cout << "failed to set listen state of socket" << std::endl;
        return;
    }

    //accept connections

    SOCKET        client_socket;
    sockaddr_in   client_sockaddr_in;
    int           client_sockaddr_in_size = sizeof(sockaddr_in);

    std::memset(&client_sockaddr_in, 0, client_sockaddr_in_size);

    while(true)
    {
        std::cout << "::accept";
        client_socket = ::accept(server_socket
                                 , reinterpret_cast<sockaddr*>(&client_sockaddr_in)
                                 , &client_sockaddr_in_size);

        if(NULL == client_socket)
        {
            std::cout << " fail (code " << ::WSAGetLastError() << ")" << std::endl;
            continue;
        }
        else
        {
            char client_ip[20];
            unsigned short client_port = 0;
            ::InetNtop(AF_INET, &(client_sockaddr_in.sin_addr), client_ip, sizeof(client_ip));
            client_port = client_sockaddr_in.sin_port;
            std::cout << " success (from " << client_ip << ":" << client_port << ")" << std::endl;
        }

        char buf[200];

        while(true)
        {
            ::memset(buf, 0, sizeof(buf));
            //::Sleep(10);

            //std::cout << "::recv ";
            int result = ::recv(client_socket, buf, sizeof(buf), 0);
            if(SOCKET_ERROR == result)
            {
                //std::cout << "failed (SOCKET_ERROR)(code " << ::WSAGetLastError() << ")" << std::endl;
                std::cout << "::recv failed (SOCKET_ERROR)(code " << ::WSAGetLastError() << ")" << std::endl;
                ::closesocket(client_socket);
                break;
            }
            else if(0 == result)
            {
                //std::cout << "failed (graceful close)" << std::endl;
                std::cout << "::recv failed (graceful close)" << std::endl;
                ::closesocket(client_socket);
                break;
            }
            else
            {
                //std::cout << "success (recieved " << result << ")" << std::endl;
            }

            //std::cout << "[";
            //for(int i=0; i<result; i++)
            //{
            //    if('\0' == buf[i])
            //    {
            //        std::cout << "_";
            //    }
            //    else
            //    {
            //        std::cout << buf[i];
            //    }
            //}
            //std::cout << "]" << std::endl;

            for(int i=0; i<result; i++)
            {
                if('\0' == buf[i])
                {
                    continue;
                    //buf[i] = '_';
                }
                
                std::cout << buf[i];
            }
        }
    }
}
