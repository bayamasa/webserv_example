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

void Socket::init(int *sock_fd) 
{
	int yes = 1;
	if ((*sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw std::runtime_error("socket error");
	if (setsockopt(*sock_fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&yes, sizeof(yes)) == -1) 
		throw std::runtime_error("setsockopt error");
}

void Socket::bind(int sock_fd, Context &context)
{
	struct sockaddr_in sa;
	std::memset(&sa, 0, sizeof(sa));
	sa.sin_len = sizeof(sa);
	sa.sin_port = htons(context.GetConfig().GetPort());
	sa.sin_addr.s_addr = inet_addr(context.GetConfig().GetHost().c_str());
	
	if (::bind(sock_fd, (struct sockaddr *)&sa, sizeof(sa)) == -1)
		throw std::runtime_error("bind error");
}

void Socket::listen(int sock_fd)
{
	if (::listen(sock_fd, max_queue))
		throw std::runtime_error("listen error");
}

void Socket::accept(int sockfd, int *connected_fd)
{
	if ((*connected_fd = ::accept(sockfd, NULL, NULL)) == -1) {
		throw std::runtime_error("accept error");
	}
}
