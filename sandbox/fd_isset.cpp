#include <sys/select.h>
#include <iostream>

int main(int argc, char const *argv[])
{
	fd_set set;
	FD_SET(10, &set);
	std::cout << "FD_ISSET(5, &set): " << FD_ISSET(10, &set) << std::endl;
	return 0;
}
