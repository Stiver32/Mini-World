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

// Function for changing the IP Address and Port value after object initialization.
void TCPServer::changeIpPort(const std::string& ip_address, unsigned short int port)
{
    if (!(ip_address == _ipAddress && port == _port))
    {
        // Closes the old socket and assigns IP and Port values provided by user.
        if (_socket != INVALID_SOCKET)
        {
            if (closesocket(_socket) == SOCKET_ERROR)
            {
                reportError("Socket is not properly closed.");
            }
            _socket = INVALID_SOCKET;
        }

        _ipAddress = ip_address;
        _port = port;

        _socketAddress.sin_port = htons(_port);

        int return_value = inet_pton(AF_INET, _ipAddress.c_str(), &_socketAddress.sin_addr.s_addr);
        if (return_value == -1)
        {
            reportError("Numeric conversion of the IP Address has failed.");
        }
        else if (return_value == 0)
        {
            std::cout << "IP notation is not a valid IPv4 or IPv6 dotted-decimal address string." << std::endl;
        }



    }
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
        
    }
    WSACleanup();
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
                reportError("socket bind failed!");
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
    if (isSocketValid(_socket))
    {
        //listens on socket and accepts up to 20 connections at max capacity
        if (listen(_socket, 20) == SOCKET_ERROR)
        {
            reportError("Socket listening failed!");
        }
        std::cout << "\n*** Listening on ADDRESS: " << _ipAddress << ", PORT: " << _port << " ***\n";
        int bytesReceived;

        //start waiting for clients/connections
        while (true){
            std::cout << "\n------------ Waiting for new connection ---------------------\n";
            
            // _socket variable is only used to listen on the specific port. 
            // The _newSocket variable is used when a connection is made on that port
            // It manages different comms on the same port using different 'Descriptors'
            acceptConnection(_newSocket);
            
            //while client is connected
            while (true) { 
                
                char buffer[TCPServer::buffer_size]{ 0 };
                //The received message on new socket is written to 'buffer' variable, and size is stored in 'bytesReceived'
                bytesReceived = recv(_newSocket, buffer, TCPServer::buffer_size - 1, 0);
                
                if (bytesReceived == 0){
                    std::cout << "client closed connection." << std::endl;
                    if (closesocket(_newSocket) == SOCKET_ERROR){
                        reportError("Socket is not properly closed.");
                    }
                    _newSocket = INVALID_SOCKET;
                    break;
                }
                else if (bytesReceived == SOCKET_ERROR){
                    std::cout << "Failed to receive bytes from client socket connection." << std::endl;
                    if (closesocket(_newSocket) == SOCKET_ERROR){
                        reportError("Socket is not properly closed.");
                    }
                    _newSocket = INVALID_SOCKET;
                    break;
                }
                buffer[bytesReceived] = '\0'; //null termination char is added to end of array

                // if message is received, it will be printed
                std::cout << "=---------------- Received request from client -------------------------=\n";
                std::cout << "The request of the Client is: " << buffer << std::endl;

                // After receiving client response, the server transmits a response
                sendResponse();
            }
        }
    }
    else
    {
        std::cout << "Socket is invalid. Please create a proper socket with 'startServer()'." << std::endl;
    }

}

// Accepts connection by creating new socket representing a speicifc client connection
void TCPServer::acceptConnection(SOCKET& newSocket)
{
    // The communication is established on a different socket variable if connection request is made on the listening socket (_socket variable)
    newSocket = accept(_socket, (sockaddr*)&_socketAddress, &_socketAddressLength);
    if (newSocket == INVALID_SOCKET)
    {
        std::cout << "Server failed to accept the incoming connection from ADDRESS: " << _ipAddress << ", PORT: " << _port << "\n";
        std::cout << "WSAGetLastError(): " << WSAGetLastError() << std::endl;
    }
}

// Sends response to the client
void TCPServer::sendResponse()
{
    size_t totalBytesSent = 0;
    size_t messageLength = _serverMessage.size();
    const char* messageBuffer = _serverMessage.c_str();

    // The send() function may not always send all data. This loop continues until all data is sent
    while (totalBytesSent < messageLength)
    {  
        int bytesSent = send(_newSocket, messageBuffer + totalBytesSent, messageLength - totalBytesSent, 0);
        if (bytesSent == SOCKET_ERROR)
        {
            std::cerr << "Failed to send response to client. WSAGetLastError: " << WSAGetLastError() << std::endl;
            return;
        }
        else
        {
            totalBytesSent += bytesSent;
        }
    }
    if (totalBytesSent == _serverMessage.size())
    {
        std::cout << ("=--------------- Server response sent to client successfully ---------------=\n") << std::endl;
    }
}