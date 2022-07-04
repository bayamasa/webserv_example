#include "response.h"

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	std::string location = "/";
	std::string root = "html";
	std::string index = "index.html";
	Config conf = Config(location, root, index);
	
	std::string method = "GET";
	std::string path = "/";
	std::string file = "index.html";
	bool is_index = true;
	HttpRequestData data = HttpRequestData(method, path, file, is_index);
	
	
	return 0;
}
