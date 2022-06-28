#ifndef SELECTOR_HPP
# define SELECTOR_HPP

#include <stdexcept>
#include <time.h>
#include <sys/types.h>
#include <set>
#include <unistd.h>
#include <iostream>

class Selector
{
private:
	int _maxfd;
	fd_set _readfds_avail;
	fd_set _writefds_avail;
	
	struct timeval _time;
	static const int timeout_sec = 5;
	std::set<int> _read_fds_monitor;
	std::set<int> _write_fds_monitor;
public:
	typedef std::set<int>::iterator it;
    typedef std::set<int>::iterator ite;
	Selector();
	~Selector();
	Selector(const Selector &other);
	Selector &operator=(const Selector &other);
	void init(int sock_fd);
	void select();
	bool isSet(int fd);
	void setReadFd(int fd);
	std::set<int> &readFds();
	std::set<int> &writeFds();
	void convertMonitorToFDSET();
	void deleteUnavailFDs();
	void updateMaxfds();
};

#endif
