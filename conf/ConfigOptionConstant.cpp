#include "ConfigOptionConstant.hpp"

ConfigOptionConstant::ConfigOptionConstant()
{
}

ConfigOptionConstant::ConfigOptionConstant(std::string v)
{
	_name = v;
	_declared = false;
	_required = false;
	std::cout << _name << std::endl;
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
		_name = other.GetName();
	}
	return *this;
}

std::string ConfigOptionConstant::GetName() const{
	// std::cout << _name << std::endl;
	return _name;
}
