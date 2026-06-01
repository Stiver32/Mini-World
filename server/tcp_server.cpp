#include "tcp_server.h"
#include <iostream>
#include <stdexcept>

//Checks whether socket is valid
bool TCPServer::isSocketValid(SOCKET& socket)
{
    if(socket == INVALID_SOCKET)
    {
        reportError("Socket is invalid!");
        return false;
    }
    return true;
}

// reports an error using WSAGetLastError() and the provided error message. Throws exception
void TCPServer::reportError(const std::string& errorMessage)
{
    int lastError = WSAGetLastError();
    std::cerr << "WSAGetLastError: " << lastError << std::endl;

    throw std::runtime_error(errorMessage);
}


// parameterized constructor for initializing IP, Port variables, and assigning required values.
TCPServer::TCPServer(const std::string& ipAddress, unsigned short int port) : _ipAddress(ipAddress),_port(port)
{
    
}