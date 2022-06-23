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
#include "conf.hpp"

#define CONFIG_ATTR_MAX 6
#define LINE_MAX_BUFFER 1024
#define HOST 0
#define PORT 1
#define SERVER_NAMES 2
#define ERROR_PAGES 3
#define LIMIT_CLIENT_BODY_SIZE 4

typedef std::vector<std::string>::iterator itr;

class ConfigReader
{
private:
	static const int conf_max_num = 5;
	ConfigOption _conf_opts[ConfigReader::conf_max_num];
	void set(std::string key, std::string value, Config &config);
	bool isConfigOption(std::string key);
	
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

// const std::string ConfigReader::conf_attr[CONFIG_ATTR_MAX] = {
// 	"host",
// 	"port",
// 	"server_names",
// 	"error_pages",
// 	"limit_client_body_size",
// 	"routes"
// };

#endif
