#ifndef SELECTOR_HPP
# define SELECTOR_HPP

#include <stdexcept>
#include <time.h>
#include <sys/types.h>
#include <set>
#include <unistd.h>

class Selector
{
private:
	int _maxfd;
	int _listen_fd;
	fd_set _readfds;
	fd_set _writefds;
	
	struct timeval _time;
	static const int timeout_sec = 5;
	std::set<int> _monitoring_read_fds;
	std::set<int> _monitoring_write_fds;
public:
	Selector();
	~Selector();
	Selector(const Selector &other);
	Selector &operator=(const Selector &other);
	void init(int sock_fd);
	void updateFds();
	bool isListenFdReady();
	void setReadFd(int fd);
};

#endif
