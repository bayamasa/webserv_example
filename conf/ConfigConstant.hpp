#ifndef CONFIGCONSTANT_HPP
# define CONFIGCONSTANT_HPP

#include <string>

class ConfigConstant
{
private:
	std::string			value;
	bool				declared;
	bool				required;
public:
	ConfigConstant();
	ConfigConstant(std::string v);
	~ConfigConstant();
	ConfigConstant(const ConfigConstant &other);
	ConfigConstant &operator=(const ConfigConstant &other);
	std::string GetValue();
};

#endif
