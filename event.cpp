#include "webserv.hpp"

#define MAX_CONNECTION 20
#define BUFF 1024

// ゆくゆくはこの関数自体がWebserverクラスのメソッドする
void	eventLoop(Context &context)
{
	int listen_fd, connected_fd;
	ssize_t recv_cnt, send_cnt;
	char *recv_msg[MAX_CONNECTION][BUFF];
	Socket sock;
	Selector selector;
	
	sock.init(&listen_fd);
	sock.bind(listen_fd, context);
	sock.listen(listen_fd);
	
	
	for (;;)
	{
		selector.init(listen_fd);
		selector.select();
		
		// read
		Selector::it it = selector.readFds().begin();
		Selector::ite ite = selector.readFds().end();
		for (; it != ite; it++)
		{
			if (*it == listen_fd)
			{
				// 多分いらないはず
				if (selector.isSet(listen_fd))
				{
					sock.accept(listen_fd, &connected_fd);
					selector.setReadFd(connected_fd);
				}
			}
			else if (*it != listen_fd)
			{
				//recv
				recv_cnt = recv(*it, recv_msg[*it], BUFF, 0);
				if (recv_cnt == -1)
					throw std::runtime_error("recv error");
				else if (recv_cnt == 0)
				{
					// EOF
					// EOFになるまでどこかのファイルに書き込み続けてもいいかも
					selector.writeFds().insert(*it);
					selector.readFds().erase(*it);
					shutdown(*it, SHUT_RD);
					continue;
				}			
			}
		}

		// write
		it = selector.writeFds().begin();
		ite = selector.writeFds().end();
		for (; it != ite; it++)
		{
			send_cnt = send(*it, recv_msg[*it], BUFF, 0);
			if (send_cnt != BUFF)
				throw std::runtime_error("send error");
			selector.writeFds().erase(*it);
			shutdown(*it, SHUT_RDWR);
			close(*it);
		}

	}
}
