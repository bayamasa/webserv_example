#include "webserv.hpp"

void	eventLoop(Context &context)
{
	int sock_fd, connected_fd;
	Socket sock;
	Selector selector;
	
	sock.init(&sock_fd);
	sock.bind(sock_fd, context);
	sock.listen(sock_fd);
	selector.init(sock_fd);
	
	for (;;)
	{
		selector.updateFds();
		if (selector.isListenFdReady())
		{
			sock.accept(sock_fd, &connected_fd);
			selector.setReadFd(connected_fd);
			
		}
			
		// read
		

	}
}
