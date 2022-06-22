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

void Config::SetHost(std::string value)
{
	host = value;
}

void Config::SetPort(std::string value)
{
	port = value;
}

void Config::SetServerName(std::string value)
{
	server_names.push_back(value);
}

void Config::SetErrorPage(std::string value)
{
	error_pages.push_back(value);
}

void Config::SetLimitClientBodySize(std::string value)
{
	limit_client_body_size = value;
}
