#include "Config.hpp"

Config::Config()
{
}

Config::Config(std::string location, std::string root, std::string index)
{
	_location = location;
	_root = root;
	_index = index;
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

const std::string &Config::GetLocation() const
{
	return _location;
}

const std::string &Config::GetRoot() const
{
	return _root;
}

const std::string &Config::GetIndex() const
{
	return _index;
}
