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
