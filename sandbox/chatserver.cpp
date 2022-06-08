#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>

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
	for (;;) {
		int i, maxfd;
		// darwinにおけるmaxsizeのfd数(1024)を取る
		fd_set readfds;
		
		FD_ZERO(&readfds);
		FD_SET(s, &readfds);
		maxfd = s;
		for (i = 0; i < nclients; i++){
			// ここで何をやっているのかが明確にわからない
			FD_SET(clients[i], &readfds);
			if (clients[i] > maxfd){
				maxfd = clients[i];
			}
		}
		std::cout << "maxfd: " << maxfd << std::endl;
		if (select(maxfd+1, &readfds, NULL, NULL, NULL) < 0)
		{
			perror("select");
			exit(1);
		}
		
		// 新しい接続かどうか
		if (FD_ISSET(s, &readfds)) {
			struct sockaddr_in ca;
			socklen_t ca_len;
			int ws;
			
			ca_len = sizeof(ca);
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
			if (FD_ISSET(clients[i], &readfds)) {
				talks(clients[i]);
				break;
			}
		}
	}
}
