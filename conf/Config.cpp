#include "Config.hpp"

Config::Config()
{
}
Config::~Config()
{
}
Config::Config(const Config &other)
{
	*this = other;
}
Config &Config::operator=(const Config &other)
{
	if (this != &other)
	{
	}
	return *this;
}

void Config::SetHost(std::string &host)
{
	_host = host.c_str();
}

void Config::SetPort(std::string port)
{
	_port = stoul(port);
}

void Config::SetServerName(std::string server_name)
{
	_server_names.push_back(server_name);
}

void Config::SetErrorPage(std::string error_page)
{
	_error_pages.push_back(error_page);
}

void Config::SetLimitClientBodySize(std::string limit_client_body_size)
{
	_limit_client_body_size = limit_client_body_size;
}

std::string Config::GetHost()
{
	return _host;
}

unsigned int Config::GetPort()
{
	return _port;
}
