#include "client_connection.h"

ClientConnection::ClientConnection(const std::string& ipAddress, unsigned short int port) : _ipAddress(ipAddress),_port(port)
{
	_socketAddress.sin_family = AF_INET; //"AF_INET" stands for ipv4 communication protocol
	_socketAddress.sin_port = htons(_port); //_port variable is converted to Network Byte Order for proper communicatio
	int returnValue = inet_pton(AF_INET, _ipAddress.c_str(), &_socketAddress.sin_addr.s_addr);
}

ClientConnection::~ClientConnection()
{
    if (_socket != INVALID_SOCKET)
    {
        closesocket(_socket);
        _socket = INVALID_SOCKET;
    }
    WSACleanup();
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
    if (_socket != INVALID_SOCKET)
    {
        if (closesocket(_socket) == SOCKET_ERROR)
        {
            reportError("closesocket function failed with error: %ld\n");
            
        }
        _socket = INVALID_SOCKET;
    }
    WSACleanup();
}

void ClientConnection::sendData(const std::string& input)
{
    size_t totalBytesSent = 0;
    size_t dataLength = input.size();
    const char* inputBuffer = input.c_str();

    // The send() function may not always send all data. This loop continues until all data is sent
    while (totalBytesSent < dataLength)
    {
        int bytesSent = send(_socket, inputBuffer + totalBytesSent, dataLength - totalBytesSent, 0);
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
    if (totalBytesSent == input.size())
    {
        std::cout << ("=--------------- Data sent to server successfully ---------------=\n") << std::endl;
    }
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