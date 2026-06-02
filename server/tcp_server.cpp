#include "tcp_server.h"
#include <string>
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
    //the _socketAddress instance of 'sockaddr_in' is assigned protocol specifications
    _socketAddress.sin_family = AF_INET; //"AF_INET" stands for ipv4 communication protocol
    _socketAddress.sin_port = htons(_port); //_port variable is converted to Network Byte Order for proper communication

    //IP Addr is converted from standard dot notation to integer value in format 'unsigned long'
    int returnValue = inet_pton(AF_INET, _ipAddress.c_str(), &_socketAddress.sin_addr.s_addr);
    if(returnValue == -1)
    {
        reportError("Numeric conversion of IP Address failed.");
    }
    else if (returnValue == 0)
    {
        std::cout << "IP notation is not valid ipv4 or ipv6 dotted-decimal address string" << std::endl;
    }

    //server message is set by 'buildResponse'
    buildResponse("Packet is received here and here is the package.");
}

//update _serverMessage variable with provided argument
void TCPServer::buildResponse(const std::string& message)
{
    _serverMessage = message;
}

//close the socket
TCPServer::~TCPServer()
{
    if(_socket != INVALID_SOCKET)
    {
        closesocket(_socket);
        _socket = INVALID_SOCKET;
    }
    if(_newSocket != INVALID_SOCKET)
    {
        closesocket(_newSocket);        
        _newSocket = INVALID_SOCKET;
        

        WSACleanup();
    }
}

//Start server with IPv4 and TCP protocols
void TCPServer::startServer()
{
    //winsock is started with vers 2.0, process info is then written to _wsadata
    if(WSAStartup(MAKEWORD(2,0), &_wsaData) != 0)
    {
        reportError("WSAStartup failed!");
    }
    else//attempt to assign socket to _socket with ipv4 and tcp specs
    {
        _socket = socket(AF_INET, SOCK_STREAM,0);
        if(isSocketValid(_socket))
        {
            //it is safe to cast sockaddr_in to sockaddr* (opposite is also true)
            if(bind(_socket, (sockaddr*)&_socketAddress, _socketAddressLength) == SOCKET_ERROR)
            {
                reportError("WSAStartup failed!");
            }
        }
    } 
}

//close the bound socket
void TCPServer::closeServer()
{
    if(_socket != INVALID_SOCKET)
    {
        closesocket(_socket);
        _socket = INVALID_SOCKET;
    }
    if(_newSocket != INVALID_SOCKET)
    {
        closesocket(_newSocket);
        _newSocket = INVALID_SOCKET;
    }
}


// listens on the specific socket and sends message if communication is established
void TCPServer::startListen()
{
    if(isSocketValid(_socket))
    {
        //listens on socket and accepts up to 20 connections at max capacity
        if(listen(_socket,20) == SOCKET_ERROR)
        {
            reportError("Socket listening failed!");
        }
        std::cout << "\n*** Listening on ADDRESS: " << _ipAddress << ", PORT: " << _port << " ***\n";
        int bytesReceived;

        while(true)
        {
            std::cout << "\n------------ Waiting for new connection ---------------------\n";
            // _socket variable is only used to listen on the specific port. 
            // The _newSocket variable is used when a connection is made on that port
            // It manages different comms on the same port using different 'Descriptors'
            acceptConnection(_newSocket);

            //The received message on new socket is written to 'buffer' variable, and size is stored in 'bytesReceived'
            char buffer[TCPServer::buffer_size]{0};
            bytesReceived = recv
        }
    }
}