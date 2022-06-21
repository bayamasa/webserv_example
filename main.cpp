#include "webserv.hpp"

void init(Context &context)
{
	ConfigReader *configReader = new ConfigReader();
	// context.GetFilename();	
	(void)context;
	(void)configReader;
}

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
	// loop();
	return 0;
}

