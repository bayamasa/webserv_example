#include "ConfigOptionConstant.hpp"

ConfigOptionConstant::ConfigOptionConstant()
{
}

ConfigOptionConstant::ConfigOptionConstant(std::string v)
{
	_name = v;
	_declared = false;
	_required = false;
}
ConfigOptionConstant::~ConfigOptionConstant()
{
}
ConfigOptionConstant::ConfigOptionConstant(const ConfigOptionConstant &other)
{
	*this = other;
}
ConfigOptionConstant &ConfigOptionConstant::operator=(const ConfigOptionConstant &other)
{
	if (this != &other)
	{
	}
	return *this;
}

std::string ConfigOptionConstant::GetName() {
	return _name;
}
