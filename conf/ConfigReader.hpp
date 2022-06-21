#ifndef CONFIGREADER_HPP
# define CONFIGREADER_HPP

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "Config.hpp"

#define CONFIG_ATTR_MAX 10
#define LINE_MAX_BUFFER 1024

class ConfigReader
{
private:
	char line[LINE_MAX_BUFFER];
	std::map<std::string, bool> config_attr(CONFIG_ATTR_MAX);
public:
	ConfigReader();
	~ConfigReader();
	ConfigReader(const ConfigReader &other);
	ConfigReader &operator=(const ConfigReader &other);
	Read(std::string filename, Config config);
	class IOException : public std::exception {
	public:
		const char *what() const throw();
	};
};

#endif
