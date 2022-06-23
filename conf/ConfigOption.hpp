#ifndef ConfigOption_HPP
# define ConfigOption_HPP

#include <string>

class ConfigOption
{
private:
	std::string			value;
	bool				declared;
	bool				required;
public:
	ConfigOption();
	ConfigOption(std::string v);
	~ConfigOption();
	ConfigOption(const ConfigOption &other);
	ConfigOption &operator=(const ConfigOption &other);
	std::string GetValue();
};

#endif
