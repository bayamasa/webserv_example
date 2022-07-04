#include "Config.hpp"

ConfigDTO::ConfigDTO()
{
}
ConfigDTO::~ConfigDTO()
{
}
ConfigDTO::ConfigDTO(const ConfigDTO &other)
{
	*this = other;
}
ConfigDTO &ConfigDTO::operator=(const ConfigDTO &other)
{
	if (this != &other)
	{
	}
	return *this;
}

void ConfigDTO::SetHost(std::string &host)
{
	_host = host.c_str();
}

void ConfigDTO::SetPort(std::string port)
{
	_port = stoul(port);
}

void ConfigDTO::SetServerName(std::string server_name)
{
	_server_names.push_back(server_name);
}

void ConfigDTO::SetErrorPage(std::string error_page)
{
	_error_pages.push_back(error_page);
}

void ConfigDTO::SetLimitClientBodySize(std::string limit_client_body_size)
{
	_limit_client_body_size = limit_client_body_size;
}

std::string ConfigDTO::GetHost()
{
	return _host;
}

unsigned int ConfigDTO::GetPort()
{
	return _port;
}
