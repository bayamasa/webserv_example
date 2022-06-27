#include "webserv.hpp"

int main(int argc, char const *argv[])
{
	Context context;
	try
	{
		args_handling(argc, argv);
		context.SetFilename(argv[1]);
	}
	catch(const char *str)
	{
		std::cerr << str << std::endl;
		exit(EXIT_FAILURE);
	}
	init(context);
	eventLoop(context);
	return 0;
}

