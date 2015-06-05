
#include "rlog/init.hpp"

#ifndef WIN32_LEAN_AND_MEAN 
#define WIN32_LEAN_AND_MEAN
#endif

#include <iostream>
#include <string>
#include <windows.h> //MAKEWORD
#include <winsock2.h>
#include <ws2tcpip.h> //InetPton

#pragma comment(lib, "ws2_32.lib")

RLOG_NS::init::init()
{
    //initialize the winsock library (v2.2)

    WORD requested_version = MAKEWORD(2, 2);
    WSADATA ws_data;
    int result;

    result = ::WSAStartup(requested_version, &ws_data);
    if(0 != result)
    {
        std::cout << "failed to initialize winsock library"
            << " (code " << result << ")" << std::endl;
        return;
    }

    WORD loaded_version = ws_data.wVersion;
    if(LOBYTE(loaded_version) != 2 || HIBYTE(loaded_version) != 2)
    {
        std::cout << "the loaded winsock is not version 2.2"
            << " (got " << LOBYTE(loaded_version) << "."
            << HIBYTE(loaded_version) << ")" << std::endl;
        return;
    }

    std::cout << "started winsock lib" << std::endl;

    ////create a socket

    //int ip_version = AF_INET;      //ipv4
    //int socket_type = SOCK_STREAM;  //tcp socket
    //int protocol = IPPROTO_TCP;  //tcp protocol

    //SOCKET s = ::socket(ip_version, socket_type, protocol);
    //if(INVALID_SOCKET == s)
    //{
    //    std::cout << "failed to create a socket" << std::endl;
    //    return;
    //}


    ////infos of a server

    //sockaddr_in server_infos;
    //in_addr     server_ip;

    //std::memset(&server_infos, 0, sizeof(sockaddr_in));
    //std::memset(&server_ip, 0, sizeof(in_addr));

    //result = ::InetPton(AF_INET, L"127.0.0.1", &server_ip);
    //if(SOCKET_ERROR == result)
    //{
    //    std::cout << "failed to create socket ip infos" << std::endl;
    //    return;
    //}

    //server_infos.sin_family = AF_INET;
    //server_infos.sin_addr = server_ip;
    //server_infos.sin_port = htons(3001);

    ////bind the server ip to this socket

    //result = ::bind(s, reinterpret_cast<const sockaddr*>(&server_infos), sizeof(sockaddr_in));
    //if(SOCKET_ERROR == result)
    //{
    //    std::cout << "failed to bind server infos to socket" << std::endl;
    //    return;
    //}

    ////put the socket in a listening state

    //result = listen(s, 10); //10 client connections max
    //if(SOCKET_ERROR == result)
    //{
    //    std::cout << "failed to set listen state of socket" << std::endl;
    //    return;
    //}

    ////accept client connections

    //sockaddr_in client_sockaddr;
    //int client_sockaddr_size = sizeof(sockaddr_in);
    //std::memset(&client_sockaddr, 0, client_sockaddr_size);

    //while(true)
    //{
    //    std::cout << "waiting for connection..." << std::endl;
    //    if(NULL == ::accept(s, reinterpret_cast<sockaddr*>(&client_sockaddr), &client_sockaddr_size))
    //    {
    //        std::cout << "failed to read client IP address" << std::endl;
    //        return;
    //    }

    //    //a client is connected

    //    wchar_t client_ip_buf [20];
    //    ::InetNtop(AF_INET, &(client_sockaddr.sin_addr), client_ip_buf, sizeof(client_ip_buf));
    //    std::wstring client_ip_w(client_ip_buf);
    //    std::string client_ip(client_ip_w.begin(), client_ip_w.end());

    //    std::cout << "got client connection from " << client_ip << ":" << client_sockaddr.sin_port << std::endl;
    //}

    ////close the server socket

    //::closesocket(s);

    ////unload the winsock library

    //::WSACleanup();
}

RLOG_NS::init::~init()
{
    ::WSACleanup();
    std::cout << "stopped winsock lib" << std::endl;
}
