#ifndef SELECTOR_HPP
# define SELECTOR_HPP

#include <stdexcept>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

class Selector
{
private:
	int _maxfd;
	fd_set _readfds;
	fd_set _writefds;
	struct timeval _time;
	static const int timeout_sec = 5;
public:
	Selector(int sock_fd);
	~Selector();
	Selector(const Selector &other);
	Selector &operator=(const Selector &other);
	void monitor();
};

#endif
