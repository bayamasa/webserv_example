#include "webserv.hpp"

int main(int argc, char const *argv[])
{
	try
	{
		args_handling(argc, argv);
	}
	catch(const char *str)
	{
		std::cerr << str << std::endl;
		exit(EXIT_FAILURE);
	}
	
	
	return 0;
}

