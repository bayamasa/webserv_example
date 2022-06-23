#include "ConfigOption.hpp"

ConfigOption::ConfigOption()
{
}

ConfigOption::ConfigOption(std::string v)
{
	value = v;
	declared = false;
	required = false;
}
ConfigOption::~ConfigOption()
{
}
ConfigOption::ConfigOption(const ConfigOption &other)
{
	*this = other;
}
ConfigOption &ConfigOption::operator=(const ConfigOption &other)
{
	if (this != &other)
	{
	}
	return *this;
}

std::string ConfigOption::GetValue() {
	return value;
}
