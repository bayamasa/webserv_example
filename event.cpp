#include "webserv.hpp"

#define MAX_CONNECTION 20
#define BUFF 1024

// ゆくゆくはこの関数自体がWebserverクラスのメソッドする
void	eventLoop(Context &context)
{
	int listen_fd, connected_fd;
	ssize_t recv_cnt;
	char *recv_msg[MAX_CONNECTION][BUFF];
	Socket sock;
	Selector selector;
	
	sock.init(&listen_fd);
	sock.bind(listen_fd, context);
	sock.listen(listen_fd);
	
	
	for (;;)
	{
		selector.init(listen_fd);
		selector.updateFds();
		if (selector.isSet(listen_fd))
		{
			sock.accept(listen_fd, &connected_fd);
			selector.setReadFd(connected_fd);
		}
		// read
		Selector::it it = selector.GetMonitoringReadFds().begin();
		Selector::ite ite = selector.GetMonitoringReadFds().end();
		for (; it != ite; it++)
		{
			if (*it != listen_fd)
			{
				//recv
				recv_cnt = recv(*it, recv_msg[*it], BUFF, 0);
				if (recv_cnt == -1)
					throw std::runtime_error("recv error");
				else if (recv_cnt == 0)
					// EOF
					// EOFになるまでどこかのファイルに書き込み続けてもいいかも
				else
					// 書き込み可能にする
					selector.GetMonitoringWriteFds().insert(*it);
			}
		}

		// write
		
		

	}
}
