#include "ConfigDTO.hpp"

ConfigDTO::ConfigDTO()
{
}

ConfigDTO::ConfigDTO(std::string location, std::string root, std::string index)
{
	_location = location;
	_root = root;
	_index = index;
	buildLocationConfDemo();
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

const std::string &ConfigDTO::GetLocation() const
{
	return _location_conf.uri_;
}

const std::string &ConfigDTO::GetRoot() const
{
	return _root;
}

const std::string &ConfigDTO::GetIndex() const
{
	return _index;
}

void ConfigDTO::buildLocationConfDemo()
{
	_location_conf.uri_ = "/";
	_location_conf.autoindex_ = true;
	_location_conf.root_ = std::string("html");
	_location_conf.allowed_methods_.push_back(std::string("GET"));
	_location_conf.indexes_.push_back(std::string("index.html"));
}
