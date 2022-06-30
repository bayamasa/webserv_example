#ifndef CONFIG_HPP
# define CONFIG_HPP

#include <string>

class Config
{
private:
	
public:
	std::string location;
	Config();
	~Config();
	Config(const Config &other);
	Config &operator=(const Config &other);
};

#endif

