#ifndef SOCKET_HPP
# define SOCKET_HPP
# include <arpa/inet.h>
# include <stdexcept>
# include <cstring>
# include <netinet/in.h>
# include "Context.hpp"

class Socket
{
private:
	static const int max_queue = 20;
public:
	Socket();
	~Socket();
	Socket(const Socket &other);
	Socket &operator=(const Socket &other);
	void init(int *sockfd);
	void bind(int sockfd, Context &context);
	void listen(int sock_fd);
	void accept(int sockfd, int *connected_fd);
};

#endif

