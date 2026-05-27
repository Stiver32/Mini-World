#pragma once

#include <string>
#include <WS2tcpip.h>

class tcp_server
{
private:

	sockaddr_in m_socket_address;
	// You can change the buffer size as you want (max is 64k). The possibility of packet loss increases with buffer size (for non-localhost applications).
	static const unsigned int buffer_size{ 1024 };

	std::string m_ip_address{};
	unsigned short m_port{};
	std::string m_server_message{};
	int m_socket_address_length{ sizeof(m_socket_address) };


};