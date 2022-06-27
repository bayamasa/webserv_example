#include "Selector.hpp"

Selector::Selector(int sockfd)
{
	_maxfd = sockfd;
	FD_ZERO(&_readfds);
	FD_ZERO(&_writefds);
	_time.tv_sec = timeout_sec;
	_time.tv_usec = 0;
	FD_SET(s, &_readfds);
}
Selector::~Selector()
{
}
Selector::Selector(const Selector &other)
{
	*this = other;
}
Selector &Selector::operator=(const Selector &other)
{
	if (this != &other)
	{
	}
	return *this;
}

void Selector::monitor() {
	if (select(_maxfd + 1, &_readfds, &_writefds, NULL, &_time) < 0)
		throw std::runtime_error("select error");
	
}
