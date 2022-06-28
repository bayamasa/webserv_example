#include "Selector.hpp"

Selector::Selector()
{
}

void Selector::init(int listen_fd)
{
	_maxfd = listen_fd;
	FD_ZERO(&_readfds);
	FD_ZERO(&_writefds);
	FD_SET(listen_fd, &_readfds);
	_monitoring_read_fds.insert(listen_fd);
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

bool Selector::isSet(int fd)
{
	return (FD_ISSET(fd, &_readfds));
}

void Selector::setReadFd(int fd)
{
	_monitoring_read_fds.insert(fd);
	FD_SET(fd, &_readfds);
}

std::set<int> &Selector::GetMonitoringReadFds() {
	return _monitoring_read_fds;
}

std::set<int> &Selector::GetMonitoringWriteFds() {
	return _monitoring_write_fds;
}
