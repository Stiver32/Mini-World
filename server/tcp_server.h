#pragma once

#include <string>
#include <WS2tcpip.h>

class TCPServer
{
private:
	// "sockadrr_in" is a struct that contains:
	// 
	// short            sin_family;    e.g. AF_INET -> IPv4 address family(IPv6 address family is AF_INET6).
	// unsigned short   sin_port;      e.g. htons(49152) -> Port number is converted to Network Byte Order (big-endian).
	// struct in_addr   sin_addr;      e.g. inet_pton("127.0.0.1") -> IP address is converted to binary in Network Byte Order.
	// char             sin_zero[8];   -> Reserved for system use. A WSK application should set the contents of this array to zero.
	//  
	// and the format of "sin_addr" is:
	// 
	// struct in_addr {
	//	unsigned long s_addr;  // Must be set with "inet_pton()". 
	//						   // "inet_pton()" converts the IPv4 or IPv6 IP Address format to binary form.                      
	//};

	sockaddr_in _socketAddress;
	// Buffer size. Note the possibility of packet loss increases with buffer size (for non-localhost apps).
	static const unsigned int buffer_size{ 1024 };

	std::string _ipAddress{};
	std::string _serverMessage{};
	unsigned short _port{};
	int _socketAddressLength{ sizeof(_socketAddress) };

	
	SOCKET _socket{ INVALID_SOCKET }; // Main socket variable for binding and listening
	SOCKET _newSocket{ INVALID_SOCKET }; // Temp socket variable for after accepting connection from a host
	long _incomingMessage{};
	WSADATA _wsaData{}; //WSAData holder. Data written when "startServer()" function is called

	//Terminates program with error message specified by argument and WSAGetLastError()
	static void reportError(const std::string& message);

public:

	//parameters of constructor are used to initialize '_socket_address' variable
	TCPServer(const std::string& ipAddress, unsigned short int port);
	~TCPServer();

	//Functions for communication declared
	void startServer();
	void closeServer();
	void acceptConnection(SOCKET& newSocket);
	void buildResponse(const std::string& message);
	void sendResponse();
	void startListen();
	
	bool isSocketValid(SOCKET& socket);

	//Function to change IP address and port after initializing an object
	void changeIpPort(const std::string& ipAddress, unsigned short int port);

};