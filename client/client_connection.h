#pragma once

#include <iostream>
#include <WS2tcpip.h>

//client needs an IP and port to connect to
class ClientConnection
{
private:

	WSADATA _wsaData{}; //WSAData holder. Data written when "startServer()" function is called
	sockaddr_in _socketAddress; 
	SOCKET _socket{ INVALID_SOCKET };

	
	std::string _ipAddress;
	unsigned short _port;
	int _socketAddressLength{ sizeof(_socketAddress) };

	//Terminates program with error message specified by argument and WSAGetLastError()
	static void reportError(const std::string& message);
	
	

public:

	//constructor to initialize socket address
	ClientConnection(const std::string& ipAddress, unsigned short int port);
	~ClientConnection();

	void makeSocket();
	void startConnection();
	void stopConnection();
	void sendData();
	bool isSocketValid(SOCKET& socket);
	


};