#ifndef CONFIG_HPP
# define CONFIG_HPP

#include <string.h>
#include <vector>

class Config
{
private:
	std::string host;
	std::string port;
	vector<std::string> server_names;
	vector<std::string> error_pages;
	std::string limit_client_body_size;
	Routes routes;
public:
	Config();
	~Config();
	Config(const Config &other);
	Config &operator=(const Config &other);
};

#endif
