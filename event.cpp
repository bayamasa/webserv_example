#include "webserv.hpp"

void	eventLoop(Context &context)
{
	int sock_fd;
	
	Socket sock;
	
	sock.init(&sock_fd);
	sock.bind(sock_fd, context);
	sock.listen(sock_fd);
	
	
}
