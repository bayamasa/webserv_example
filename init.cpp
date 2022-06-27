#include "webserv.hpp"

void init(Context &context)
{
	ConfigReader configReader = ConfigReader();
	configReader.Read(context.GetFilename(), context.GetConfig());
}
