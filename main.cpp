#include "webserv.hpp"

void init(Context &context)
{
	ConfigReader configReader = ConfigReader();
	configReader.Read(context.GetFilename(), context.GetConfig());
	
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
	// loop(context);
	return 0;
}

