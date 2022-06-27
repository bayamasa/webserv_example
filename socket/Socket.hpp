#ifndef SOCKET_HPP
# define SOCKET_HPP
# include <arpa/inet.h>
# include <stdexcept>
# include <netinet/in.h>
// # include <sys/socket.h>

class Socket
{
private:
	int _socket_fd;
public:
	Socket();
	~Socket();
	Socket(const Socket &other);
	Socket &operator=(const Socket &other);
	void init();
	void bind();
};

#endif

