#ifndef CONFIG_HPP
# define CONFIG_HPP

#include <string>
#include <vector>
#include "Routes.hpp"

class Config
{
private:
	std::string host;
	std::string port;
	std::vector<std::string> server_names;
	std::vector<std::string> error_pages;
	std::string limit_client_body_size;
	// Routes routes;
public:
	Config();
	~Config();
	Config(const Config &other);
	Config &operator=(const Config &other);
};

#endif
