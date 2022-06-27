#include "Socket.hpp"

Socket::Socket()
{
}
Socket::~Socket()
{
}
Socket::Socket(const Socket &other)
{
	*this = other;
}
Socket &Socket::operator=(const Socket &other)
{
	if (this != &other)
	{
	}
	return *this;
}

void Socket::init() 
{
	int yes = 1;
	if ((_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw std::runtime_error("socket error");
	if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&yes, sizeof(yes)) == -1) 
		throw std::runtime_error("setsockopt error");
}

void Socket::bind(Context &context)
{
	struct sockaddr_in sa;
	std::memset(&sa, 0, sizeof(sa));
	sa.sin_len = sizeof(sa);
	sa.sin_port = htons(context.GetConfig().GetPort());
	sa.sin_addr.s_addr = htonl(context.GetConfig().GetHost());
	
	if (::bind(_socket_fd, (struct sockaddr *)&sa, sizeof(sa)) == -1)
		throw std::runtime_error("bind error");
}

void Socket::listen()
{
	if (::listen(_socket_fd, max_queue))
		throw std::runtime_error("listen error");
}
