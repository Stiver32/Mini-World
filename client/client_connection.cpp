#include "client_connection.h"

ClientConnection::ClientConnection(const std::string& ipAddress, unsigned short int port) : _ipAddress(ipAddress),_port(port)
{
	_socketAddress.sin_family = AF_INET; //"AF_INET" stands for ipv4 communication protocol
	_socketAddress.sin_port = htons(_port); //_port variable is converted to Network Byte Order for proper communicatio
	int returnValue = inet_pton(AF_INET, _ipAddress.c_str(), &_socketAddress.sin_addr.s_addr);
}

void ClientConnection::makeSocket()
{
    //winsock is started with vers 2.0, process info is then written to _wsadata
    if (WSAStartup(MAKEWORD(2, 0), &_wsaData) != 0)
    {
        reportError("WSAStartup failed!");
    }
    else//attempt to assign socket to _socket with ipv4 and tcp specs
    {
        _socket = socket(AF_INET, SOCK_STREAM, 0);
        isSocketValid(_socket);

    }
}

void ClientConnection::startConnection()
{
    // Winsock connect() establishes connection to a specified socket using a TCP/IP address and port
    // returns zero on success or SOCKET_ERROR on failure
    if (connect(_socket, (sockaddr*)&_socketAddress, _socketAddressLength) == SOCKET_ERROR)
    {
        reportError("connection failed!");
    }
}

void ClientConnection::stopConnection()
{
    if (closesocket(_socket, (sockaddr*)&_socketAddress, &_socketAddressLength);

}

void ClientConnection::sendData()
{
}


// reports an error using WSAGetLastError() and the provided error message. Throws exception
void ClientConnection::reportError(const std::string& errorMessage)
{
    int lastError = WSAGetLastError();
    std::cerr << "WSAGetLastError: " << lastError << std::endl;

    throw std::runtime_error(errorMessage);
}

//Checks whether socket is valid
bool ClientConnection::isSocketValid(SOCKET& socket)
{
    if (socket == INVALID_SOCKET)
    {
        reportError("Socket is invalid!");
        return false;
    }
    return true;
}