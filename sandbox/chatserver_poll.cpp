#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <poll.h>

enum {
	SERVER_PORT = 12345,
	NQUEUESIZE = 5,
	MAXNCLIENTS = 10,
};

int clients[MAXNCLIENTS];
// 現在接続しているクライアント
int nclients = 0;

void sorry(int ws) {
	char *message = "Sorry, it's full.\n";
	
	write(ws, message, std::strlen(message));
}

void delete_client(int ws) {
	int i;
	
	for (int i = 0; i < nclients; i++)
	{
		if (clients[i] == ws) {
			clients[i] = clients[nclients - 1];
			nclients--;
			break;
		}
	}
}

void talks(int ws) {
	int i, cc;
	char c;
	
	do {
		if ((cc = read(ws, &c, 1)) == -1) {
			perror("read");
			exit(1);
		} else if (cc == 0) {
			shutdown(ws, SHUT_RDWR);
			close(ws);
			delete_client(ws);
			fprintf(stderr, "Connection closed on descripter %d.\n", ws);
			return;
		}
		for (i = 0; i < nclients; i++)
			write(clients[i], &c, 1);
	} while (c != '\n');
}

int main(void)
{
	int s, soval;
	struct sockaddr_in sa;
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	soval = 1;
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1) {
		perror("setsockopt");
		exit(1);
	}
	memset(&sa, 0, sizeof(sa));
	sa.sin_len = sizeof(sa);
	sa.sin_port = htons(SERVER_PORT);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(s, (struct sockaddr *)&sa, sizeof(sa)) == -1)
	{
		perror("bind");
		exit(1);
	}
	if (listen(s, NQUEUESIZE)) {
		perror("listen");
	}
	fprintf(stderr, "Ready.\n");
	struct pollfd targets[MAXNCLIENTS + 1];
	
	for (;;) {
		int i, maxfd, count;
		// darwinにおけるmaxsizeのfd数(1024)を取る
		fd_set readfds;
		
		count = 0;
		targets[count].fd = s;
		targets[count].events = POLLIN;
		count++;
		
		for (i = 0; i < nclients; i++){
			// clientsをreadfdsに追加
			if (clients[i] != -1)
			{
				targets[count].fd = clients[i];
				targets[count].events = POLLIN;
				count++;
			}
		}
		//第一引数は見張るfdに1足した値を入れる(個数ではない)
		if (poll(targets, count, NULL) < 0)
		{
			perror("select");
			exit(1);
		}
		
		// 新しい接続かどうか
		if (targets[0].revents & POLLIN) {
			struct sockaddr_in ca;
			socklen_t ca_len;
			int ws;
			
			ca_len = sizeof(ca);
			// 新しい接続であればfd新しく作って格納
			if ((ws = accept(s, (struct sockaddr *)&ca, &ca_len)) == -1) {
				perror("accept");
				continue;
			}
			if (nclients >= MAXNCLIENTS) {
				//もう満杯
				sorry(ws);
				shutdown(ws, SHUT_RDWR);
				close(ws);
				fprintf(stderr, "Refused a new connection.\n");
			} else {
				clients[nclients] = ws;
				nclients++;
				fprintf(stderr, "Accepted a connection on descripter %d.\n", ws);
			}
		}
		for (i = 0; i < nclients; i++) {
			if (targets[i].revents & (POLLIN | POLLERR)) {
				talks(clients[i]);
				break;
			}
		}
	}
}
