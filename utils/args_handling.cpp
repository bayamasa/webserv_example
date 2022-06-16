#include "utils.hpp"

void args_handling(int argc,const char *argv[])
{
	if (argc != 2)
	{
		throw "usage <exec file> <config file>";
	}
	(void) argv;
}
