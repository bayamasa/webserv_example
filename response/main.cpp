#include "response.h"

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	//conf
	std::string location = "/";
	std::string root = "html";
	std::string index = "index.html";
	Config conf = Config(location, root, index);
	
	//http request data
	std::string method = "GET";
	std::string path = "/";
	std::string file = "index.html";
	bool is_index = true;
	HttpRequestData data = HttpRequestData(method, path, file, is_index);

	//builder
	HttpResponseBuilder builder = HttpResponseBuilder(conf);
	
	return 0;
}
