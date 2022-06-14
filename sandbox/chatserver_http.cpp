#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>

#define BUFFERSIZE		10240

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

char *chomp(char *str)
{
	int len;
	len = strlen(str);
	if (len >= 2 && str[len-2] == '\r' && str[len-1] == '\n')
	{
		str[len-2] = str[len-1] = 0;
	}
	else if (len >= 1 && (str[len - 1] == '\r' || str[len - 1] == '\n'))
		str[len - 1] = 0;
	return str;
}

int http_receive_request(int in)
{
	char requestline[BUFFERSIZE];
	char rheader[BUFFERSIZE];
	size_t cc;
	
	char *no_req = "No request line.\n";
	char *bad_request = "HTTP/1.0 400 Bad Request\r\nContent-Type: text/html\r\n\r\n<html><head></head><body>400 Bad Request</body></html>\n";
	char *ok_header = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n<html><head></head><body>hello</body></html>\n";
	char *body_prefix = "<html><head></head><body>";
	char *body_suffix = "</body></html>\n";
	
	int i = 0;
	char c;
	do {
		if ((cc = recv(in, &c, 1, 0)) == -1) {
			perror("recv");
			exit(1);
		} else if (in == 0) {
			fprintf(stderr, "recv end requestline %d.\n");
			return -1;
		}
		requestline[i] = c;
		i++;
		// std::cout << "c:" << c << std::endl;
	} while (c != '\n');
	requestline[i] = '\0';
	chomp(requestline);
	i = 0;
	printf("requestline is [%s]\n", requestline);
	do {
		if ((cc = recv(in, &c, 1, 0)) == -1) {
			perror("recv");
			exit(1);
		} else if (in == 0) {
			fprintf(stderr, "recv end header");
			return -1;
		}
		rheader[i] = c;
		i++;
	} while (c != '\n');
	chomp(rheader);
	printf("rheader is [%s]\n", rheader);
	send(in, ok_header, strlen(ok_header), 0);
	// send(in, "a", 1, 0);
	// send(in, bad_request, sizeof(bad_request), 0);
	// std::cout << "hihi" << std::endl;
	
	// if ((cc = recv(in, &requestline, 1)) == -1) {
	// 	perror("recv");
	// 	exit(1);
	// } else if (cc == 0) {
	// 	printf(no_req);
	// 	send(in, bad_request, sizeof(bad_request), 0);
	// 	return 0;
	// }
	// std::cerr << "req" << requestline << std::endl;
	// while (cc != 0)
	// {
	// 	cc = recv(in, &requestline, BUFFERSIZE, 0);
	// 	std::cout << "aaaa" << std::endl;
	// 	if (cc == -1) {
	// 		std::cout << "send error" << std::endl;
	// 		perror("recv");
	// 		exit(1);
	// 	} else if (cc == 0) {
	// 		std::cout << "send no naka" << std::endl;
	// 		send(in, ok_header, sizeof(ok_header), 0);
	// 		send(in, body_prefix, sizeof(body_prefix),0);
	// 		send(in, &requestline, sizeof(requestline), 0);
	// 		send(in, body_suffix, sizeof(body_suffix),0);			
	// 	}
	// 	std::cout << "cc: " << cc << std::endl;
	// 	std::cout << requestline << std::endl;
	// }
	// std::cout << "while no soto" << std::endl;
	// if (fgets(requestline, BUFFERSIZE, in) == 0)
	// {
	// 	printf("No request line.\n");
	// 	return 0;
	// }
	// if ((cc = recv(in, &c, 1, 0)) == -1) {
	// 	perror("recv");
	// 	exit(1);
	// }
	// chomp(requestline);
	// printf("requestline is [%s]\n", requestline);
	// while (fgets(rheader, BUFFERSIZE, in))
	// {
	// 	chomp(rheader);
	// 	if (strcmp(rheader, "") == 0)
	// 		break;
	// 	printf("Ignored: %s\n", rheader);
	// }
	// if (strchr(requestline, '<') || strstr(requestline, ".."))
	// {
	// 	printf("Dangerous request line found.\n");
	// 	return 0;
	// }
	// return 1;
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
		// socketをreadfdsに追加
		FD_SET(s, &readfds);
		maxfd = s;
		for (i = 0; i < nclients; i++){
			// clientsをreadfdsに追加
			FD_SET(clients[i], &readfds);
			if (clients[i] > maxfd){
				maxfd = clients[i];
			}
		}
		std::cout << "maxfd: " << maxfd << std::endl;
		//第一引数は見張るfdに1足した値を入れる(個数ではない)
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
			if (FD_ISSET(clients[i], &readfds)) {
				http_receive_request(clients[i]);
				shutdown(clients[i], SHUT_RDWR);
				close(clients[i]);
				delete_client(clients[i]);
				fprintf(stderr, "Connection closed on descripter %d.\n", clients[i]);
			}
		}
	}
}
