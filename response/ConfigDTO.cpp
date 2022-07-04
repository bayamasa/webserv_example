#include "ConfigDTO.hpp"

ConfigDTO::ConfigDTO()
{
	buildDemoConf();
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

std::vector<LocationConfig> &ConfigDTO::GetLocation()
{
	return locations_;
}

void ConfigDTO::buildDemoConf()
{
	locations_.at(0).location_ = "/";
	locations_.at(0).root_ = "/html";
	locations_.at(0).allowed_methods_.push_back("GET");
	locations_.at(0).autoindex_ = true;
	locations_.at(0).indexes_.push_back("index.html");
	locations_.at(0).cgi_path_ = std::string();
}
