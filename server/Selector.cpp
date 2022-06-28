#include "Selector.hpp"

Selector::Selector()
{
}

void Selector::init(int sock_fd)
{
	_maxfd = sock_fd;
	_listen_fd = sock_fd;
	FD_ZERO(&_readfds);
	FD_ZERO(&_writefds);
	FD_SET(_listen_fd, &_readfds);
	_monitoring_read_fds.insert(_listen_fd);
	_time.tv_sec = timeout_sec;
	_time.tv_usec = 0;
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

void Selector::updateFds() {
	if (select(_maxfd + 1, &_readfds, &_writefds, NULL, &_time) < 0)
		throw std::runtime_error("select error");
}

bool Selector::isListenFdReady()
{
	return (FD_ISSET(_listen_fd, &_readfds));
}

void Selector::setReadFd(int fd)
{
	_monitoring_read_fds.insert(fd);
	FD_SET(fd, &_readfds);
	// fdsetに入っているfdを自前でも管理する必要がある
}
