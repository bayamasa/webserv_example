#ifndef ConfigOptionConstant_HPP
# define ConfigOptionConstant_HPP

#include <string>
#include <iostream>

class ConfigOptionConstant
{
private:
	std::string			_name;
	bool				_declared;
	bool				_required;
public:
	ConfigOptionConstant();
	ConfigOptionConstant(std::string v);
	~ConfigOptionConstant();
	ConfigOptionConstant(const ConfigOptionConstant &other);
	ConfigOptionConstant &operator=(const ConfigOptionConstant &other);
	std::string GetName() const;
};

#endif
