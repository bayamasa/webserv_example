#include "ConfigReader.hpp"

ConfigReader::ConfigReader()
{
	std::string config_key[CONFIG_ATTR_MAX] = {
		"host",
		"port",
		"server_names",
		"error_pages",
		"limit_client_body_size",
		"routes"
	};
	
	for (size_t i = 0; i < CONFIG_ATTR_MAX; i++)
	{
		config_attr[config_key[i]] = false;
	}
}

ConfigReader::~ConfigReader()
{
}
ConfigReader::ConfigReader(const ConfigReader &other)
{
	*this = other;
}
ConfigReader &ConfigReader::operator=(const ConfigReader &other)
{
	if (this != &other)
	{
	}
	return *this;
}

void ConfigReader::Read(std::string &filename, Config &config)
{
	std::vector<std::string> tmp;
	std::string line;
	

	std::ifstream ifs(filename);
	if (ifs.fail())
		throw IOException();
    while (getline(ifs, line)){
        tmp.push_back(line);
    }

	
	for (std::vector<std::string>::iterator itr = tmp.begin(), e = tmp.end(); itr != e; ++itr) 
	{
		std::stringstream ss(*itr);
		std::string key, value;
		std::getline(ss, key, ' ');
		std::getline(ss, value);
	}
	
	(void)config;
}

const char *ConfigReader::IOException::what() const throw()
{
	return "cannot read config file";
}

