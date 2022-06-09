#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define PORTNO_BUFSIZE	30
#define BUFFERSIZE		1024

int tcp_acc_port(int portno, int ip_version)
{
	struct addrinfo hints, *ai;
	char portno_str[PORTNO_BUFSIZE];
	int err, s, on, pf;
	
	switch (ip_version)
	{
	case 4:
		pf = PF_INET;
		break;
	case 6:
		pf = PF_INET6;
		break;
	default:
		fprintf(stderr, "bad ip version\n");
	}
	snprintf(portno_str, sizeof(portno_str), "%d", portno);
	memset(&hints, 0, sizeof(hints));
	ai = NULL;
	hints.ai_family = pf;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;
	if ((err = getaddrinfo(NULL, portno_str, &hints, &ai)))
	{
		fprintf(stderr, "bad portno %d ? %s \n", portno, gai_strerror(err));
		return -1;
	}
	if ((s = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol)) < 0)
	{
		perror("socket");
		return -1;
	}
	if (bind(s, ai->ai_addr, ai->ai_addrlen) < 0)
	{
		perror("bind");
		fprintf(stderr, "Port number %d\n", portno);
		close(s);
		return -1;
	}
	on = 1;
	if ( setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
	{
		perror("setsockopt");
		close(s);
		return -1;
	}
	if (listen(s, 5) < 0)
	{
		perror("listen");
		close(s);
		return -1;
	}
	freeaddrinfo(ai);
	return s;
}

#define HOST_NAME_MAX 256

void print_my_host_port_http(int portno)
{
	char hostname[HOST_NAME_MAX + 1];
	gethostname(hostname, HOST_NAME_MAX);
	hostname[HOST_NAME_MAX] = 0;
	printf("run telnet %s %d \n", hostname, portno);
}

void sockaddr_print(struct sockaddr *addrp, socklen_t addr_len)
{
	char host[BUFFERSIZE];
	char port[BUFFERSIZE];
	
	if ( getnameinfo(addrp, addr_len, host, sizeof(host), port, sizeof(port), NI_NUMERICHOST|NI_NUMERICSERV) < 0)
		return;
	if (addrp->sa_family == PF_INET)
		printf("%s:%s", host, port);
	else
		printf("nothing done");
}

void tcp_peeraddr_print(int com)
{
	struct sockaddr addr;
	socklen_t addr_len;
	
	addr_len = sizeof(addr);
	if (getpeername(com, (struct sockaddr *)&addr, &addr_len) < 0)
	{
		perror("tcp_peeraddr_print");
		return;
	}
	printf("[%d] connection (fd==%d) from ", getpid(), com);
	sockaddr_print((struct  sockaddr *)&addr, addr_len);
	printf("\n");
}

void tcp_sockaddr_print(int com)
{
	struct sockaddr_in addr;
	socklen_t addr_len;
	
	addr_len = sizeof(addr);
	if ( getsockname(com, (struct sockaddr *)&addr, &addr_len) < 0)
	{
		perror("tcp_peeraddr_print");
		return;
	}
	printf("[%d] accepting (fd==%d) to ", getpid(), com);
	sockaddr_print((struct sockaddr *)&addr, addr_len);
	printf("\n");
	
}

int fdopen_sock(int sock, FILE **in, FILE **out)
{
	int sock2;
	if ((sock2=dup(sock)) < 0)
		return -1;
	if ((*in = fdopen(sock2, "r")) == NULL)
	{
		close(sock2);
		return -1;
	}
	if ((*out = fdopen(sock, "w")) == NULL)
	{
		fclose(*in);
		*in = 0;
		return -1;
	}
	// bufferingの抑止
	setvbuf(*out, (char *)NULL, _IONBF, 0);
	return 0;
}

int echo_receive_request(char *line, size_t size, FILE *in)
{
	if (fgets(line, size, in))
	{
		return(strlen(line));
	}
	else
	{
		if (ferror(in))
			return -1;
		else
			return 0;
	}
}

void echo_send_reply(char *line, FILE *out)
{
	fprintf(out, "%s", line);
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

int http_receive_request(FILE *in)
{
	char requestline[BUFFERSIZE];
	char rheader[BUFFERSIZE];
	
	if (fgets(requestline, BUFFERSIZE, in) == 0)
	{
		printf("No request line.\n");
		return 0;
	}
	chomp(requestline);
	printf("requestline is [%s]\n", requestline);
	while (fgets(rheader, BUFFERSIZE, in))
	{
		chomp(rheader);
		if (strcmp(rheader, "") == 0)
			break;
		printf("Ignored: %s\n", rheader);
	}
	if (strchr(requestline, '<') || strstr(requestline, ".."))
	{
		printf("Dangerous request line found.\n");
		return 0;
	}
	return 1;
}

void http_send_reply(FILE *out)
{
	fprintf(out, "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n");
	fprintf(out, "<html><head></head><body>hello.</body></html>\n");
}

void http_send_reply_bad_request(FILE *out)
{
	fprintf(out, "HTTP/1.0 400 Bad Request\r\nContent-Type: text/html\r\n\r\n");
	fprintf(out, "<html><head></head><body>400 Bad Request</body></html>\n");
}

bool http_receive_request_and_send_reply(int com)
{
	FILE *in, *out;
	
	if (fdopen_sock(com, &in, &out) < 0)
	{
		perror("fdopen");
		exit(1);
	}
	if (http_receive_request(in))
	{
		http_send_reply(out);
	}
	else
	{
		http_send_reply_bad_request(out);
	}
	printf("[%d] Replied\n",getpid());
	fclose(in);
	fclose(out);
	return true;
}

int find_maxfds(fd_set *fds)
{
	int i, maxfds;
	for (i = FD_SETSIZE; i>= 0; i--)
	{
		if (FD_ISSET(i, fds))
		{
			return(i + 1);
		}
	}
	return 0;
}

void echo_server(int portno, int ip_version)
{
	int acc, com;
	fd_set readfds, readfds_save;
	int i, n, maxfds, next_maxfds;
	
	acc = tcp_acc_port(portno, ip_version);
	if (acc < 0)
	{
		perror("acc:");
		exit(1);
	}
	
	print_my_host_port_http(portno);
	tcp_sockaddr_print(acc);
	FD_ZERO(&readfds_save);
	FD_SET(acc, &readfds_save);
	maxfds = next_maxfds = acc + 1;
	for (;;)
	{
		readfds = readfds_save;
		if ((n = select(maxfds, &readfds, 0, 0, 0)) == 0)
		{
			perror("select");
			exit(1);
		}
		if (FD_ISSET(acc, &readfds))
		{
			FD_CLR(acc, &readfds);
			printf("[%d] accepting incoming connections (acc==%d) ...\n", getpid(), acc);
			if ((com = accept(acc, 0, 0)) < 0)
			{
				perror("accept");
				exit(-1);
			}
			FD_SET(com, &readfds_save);
			if (com+1 > maxfds)
				next_maxfds = com+1;
			tcp_peeraddr_print(com);
		}
		for (i = 0; i < maxfds; i++)
		{
			if (FD_ISSET(i, &readfds))
			{
				if (http_receive_request_and_send_reply(i))
				{
					printf("[%d] connection (fd==%d) closed.\n", getpid(), i);
					close(i);
					FD_CLR(i, &readfds_save);
					if (maxfds == i+1)
					{
						next_maxfds = find_maxfds(&readfds_save);
					}
				}
			}
		}
		maxfds = next_maxfds;
		
	}
	
}

int main(int argc, char const *argv[])
{
	int portno, ip_version;
	
	if (!(argc == 2 || argc == 3)) {
		fprintf(stderr, "Usage: %s portno {ipversion}\n", argv[0]);
		exit(1);
	}
	portno = strtol(argv[1], 0, 10);
	if (argc == 3)
		ip_version = strtol(argv[2], 0, 10);
	else
		ip_version = 46;
	echo_server(portno, ip_version);
	return 0;
}

