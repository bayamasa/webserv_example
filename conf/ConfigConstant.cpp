#include "ConfigConstant.hpp"

ConfigConstant::ConfigConstant()
{
}

ConfigConstant::ConfigConstant(std::string v)
{
	value = v;
	declared = false;
	required = false;
}
ConfigConstant::~ConfigConstant()
{
}
ConfigConstant::ConfigConstant(const ConfigConstant &other)
{
	*this = other;
}
ConfigConstant &ConfigConstant::operator=(const ConfigConstant &other)
{
	if (this != &other)
	{
	}
	return *this;
}

std::string ConfigConstant::GetValue() {
	return value;
}
