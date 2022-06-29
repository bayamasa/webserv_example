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
					// iteratorのループの内部で要素が追加された場合、その要素を含めたループが回る
					selector.setReadFd(connected_fd);
					std::cout << "set connected fd: " << connected_fd << std::endl;
				}
			}
			else if (*it != listen_fd)
			{
				// TODO:後でselectorとわける
				if (selector.isSet(*it))
				{
					//recv
					std::cout << "recv it: " << *it << std::endl;
					recv_cnt = recv(*it, recv_msg[*it], BUFF, 0);
					std::cout << recv_msg[*it] << std::endl;
					if (recv_cnt == -1)
						throw std::runtime_error("recv error");
					else if (recv_cnt == 0)
					{
						// EOFになるまでどこかのファイルに書き込み続けてもいいかも
						std::cout << "writeFd add: " << *it << std::endl;
						selector.writeFds().insert(*it);
						// selector.readFds().erase(*it);
						shutdown(*it, SHUT_RD);
						continue;
					}
					selector.writeFds().insert(*it);
				}
			}
		}

		// write
		it = selector.writeFds().begin();
		ite = selector.writeFds().end();
		while (it != ite)
		{
			send_cnt = send(*it, recv_msg[*it], BUFF, 0);
			if (send_cnt != BUFF)
				throw std::runtime_error("send error");
			it = selector.writeFds().erase(it);
			shutdown(*it, SHUT_RDWR);
			close(*it);
		}

	}
}
