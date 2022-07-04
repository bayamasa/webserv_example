#ifndef CONFIG_HPP
# define CONFIG_HPP

#include <string>
#include <vector>
#include <iostream>
#include "Routes.hpp"

typedef std::vector<std::string> vec_st;

class ConfigDTO
{
private:
	std::string _host;
	unsigned int _port;
	vec_st _server_names;
	vec_st _error_pages;
	std::string _limit_client_body_size;
	// Routes routes;
public:
	ConfigDTO();
	~ConfigDTO();
	ConfigDTO(const ConfigDTO &other);
	ConfigDTO &operator=(const ConfigDTO &other);
	void SetHost(std::string &host);
	void SetPort(std::string port);
	void SetServerName(std::string server_name);
	void SetErrorPage(std::string error_page);
	void SetLimitClientBodySize(std::string limit_client_body_size);
	std::string GetHost();
	unsigned int GetPort();
};

#endif
