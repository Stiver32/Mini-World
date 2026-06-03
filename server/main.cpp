#include <iostream>
#include <stdexcept>
#include "..\server\tcp_server.h"


// Once the object is created, the socket is initialized with IPv4 and TCP specifications.
// If the user wants to change the IP Address and port, the "change_ip_port()" function must be called.
// This function closes the prior socket variable (descriptor), creates a new one, and assigns the IP address and port values with conversions.

int main()
{
	try
	{
		TCPServer tcpHandler{ "127.0.0.1", 8080 };
		// You can change the IP Address and Port as you want after initialization, like:
		// tcpHandler.changeIpPort("127.0.0.1", 9090);

		tcpHandler.startServer();

		// You can change the message that will be sent to the host.
		// tcp_handler.build_response("Hi there!");

		// The maximum number of queued connections is 20, and after receiving and sending data, the connection with that specific host will be closed.
		tcpHandler.startListen();

	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}