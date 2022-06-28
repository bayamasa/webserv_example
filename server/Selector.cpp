#include "Selector.hpp"

Selector::Selector()
{
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

void Selector::init(int listen_fd)
{
	_maxfd = listen_fd;
	FD_ZERO(&_readfds_avail);
	FD_ZERO(&_writefds_avail);

	// FD_SET(listen_fd, &_readfds_avail);
	_read_fds_monitor.insert(listen_fd);
	_time.tv_sec = timeout_sec;
	_time.tv_usec = 0;
}

void Selector::deleteUnavailFDs()
{
	it it = _read_fds_monitor.begin();
	ite ite = _read_fds_monitor.end();
	for (; it != ite; it++)
	{
		if (!FD_ISSET(*it, &_readfds_avail))
		{
			std::cout << "delete read_fd " << *it << std::endl;
			_read_fds_monitor.erase(*it);
		}
	}
	it = _write_fds_monitor.begin();
	ite = _write_fds_monitor.end();
	for (; it != ite; it++)
	{
		if (!FD_ISSET(*it, &_writefds_avail))
		{
			std::cout << "delete write_fd " << *it << std::endl;
			_write_fds_monitor.erase(*it);
		}
	}
}

void Selector::updateMaxfds()
{
	int maxfd;

	it it = _read_fds_monitor.begin();
	ite ite = _read_fds_monitor.end();
	for (; it != ite; it++)
	{
		maxfd = std::max(maxfd, *it);
	}
	it = _write_fds_monitor.begin();
	ite = _write_fds_monitor.end();
	for (; it != ite; it++)
	{
		maxfd = std::max(maxfd, *it);
	}
	_maxfd = maxfd;
}

void Selector::select() 
{
	convertMonitorToFDSET();
	updateMaxfds();
	if (::select(_maxfd + 1, &_readfds_avail, &_writefds_avail, NULL, &_time) < 0)
		throw std::runtime_error("select error");
	deleteUnavailFDs();
}

bool Selector::isSet(int fd)
{
	return (FD_ISSET(fd, &_readfds_avail));
}

void Selector::setReadFd(int fd)
{
	_read_fds_monitor.insert(fd);
}

std::set<int> &Selector::readFds() {
	return _read_fds_monitor;
}

std::set<int> &Selector::writeFds() {
	return _write_fds_monitor;
}

void Selector::convertMonitorToFDSET() {
	// read fd
	it it = _read_fds_monitor.begin();
	ite ite = _read_fds_monitor.end();
	for (; it != ite; it++)
	{
		FD_SET(*it, &_readfds_avail);
	}
	// write fd
	it = _write_fds_monitor.begin();
	ite = _write_fds_monitor.end();
	for (; it != ite; it++)
	{
		FD_SET(*it, &_writefds_avail);
	}
}
