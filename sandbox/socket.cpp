#include <netinet/in.h>
#include <cstring>

int main(void)
{
	int sd;
	sd = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in sa;
	std::memset(&sa, 0, sizeof(sa));
	sa.sin_len = sizeof(sa);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(80);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(sd, (struct sockaddr *)&sa, sizeof(sa));
	
	int ns;
	struct sockaddr_in ca;
	socklen_t calen;
	calen = sizeof(ca);
	ns = accept(sd, (struct sockaddr *)&ca, &calen);
}
