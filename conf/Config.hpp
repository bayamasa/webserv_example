#ifndef CONFIG_HPP
# define CONFIG_HPP

#include <string>
#include <vector>
#include "Routes.hpp"

typedef std::vector<std::string> vec_st;

class Config
{
private:
	std::string host;
	std::string port;
	vec_st server_names;
	vec_st error_pages;
	std::string limit_client_body_size;
	// Routes routes;
public:
	Config();
	~Config();
	Config(const Config &other);
	Config &operator=(const Config &other);
	void SetHost(std::string value);
	void SetPort(std::string value);
	void SetServerName(std::string value);
	void SetErrorPage(std::string value);
	void SetLimitClientBodySize(std::string value);
};

#endif
