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
	if ((_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw std::runtime_error("socket error");
}

void Socket::bind()
{
	int yes = 1;
	if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&yes, sizeof(yes)) == -1) 
		throw std::runtime_error("setsockopt error");		
}
