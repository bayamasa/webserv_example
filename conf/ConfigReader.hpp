#ifndef CONFIGREADER_HPP
# define CONFIGREADER_HPP

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Config.hpp"

#define CONFIG_ATTR_MAX 10
#define LINE_MAX_BUFFER 1024

typedef std::vector<std::string>::iterator itr;

class ConfigReader
{
private:
	// char line[LINE_MAX_BUFFER];
	std::map<std::string, bool> config_attr;
public:
	ConfigReader();
	~ConfigReader();
	ConfigReader(const ConfigReader &other);
	ConfigReader &operator=(const ConfigReader &other);
	void Read(const std::string &filename, Config &config);
	class IOException : public std::exception {
	public:
		const char *what() const throw();
	};
};

#endif
