#ifndef SOCKET_HPP
# define SOCKET_HPP
# include <arpa/inet.h>
# include <stdexcept>
# include <cstring>
# include <netinet/in.h>
# include "Context.hpp"

class Socket
{
private:
	int _socket_fd;
	static const int max_queue = 20;
public:
	Socket();
	~Socket();
	Socket(const Socket &other);
	Socket &operator=(const Socket &other);
	void init();
	void bind(Context &context);
	void listen();
};

#endif

