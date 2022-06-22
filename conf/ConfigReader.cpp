#include "ConfigReader.hpp"

ConfigReader::ConfigReader()
{
	conf[HOST] = ConfigConstant("host");
	conf[PORT] = ConfigConstant("port");
	conf[SERVER_NAMES] = ConfigConstant("server_names");
	conf[ERROR_PAGES] = ConfigConstant("error_pages");
	conf[LIMIT_CLIENT_BODY_SIZE] = ConfigConstant("limit_client_body_size");
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

bool ConfigReader::isConfigOption(std::string key)
{
	// std::map<std::string, int>::key_compare comp = conf_attr_enum.key_comp();

	for (int i = 0; i < conf_max_num; i++)
	{
		if (conf[i].GetValue() == key)
		{
			return true;
		}
	}
	return false;
}

void ConfigReader::set(std::string key, std::string value, Config &config)
{

	for (int i = 0; i < CONFIG_ATTR_MAX; i++)
	{
		if (conf[i].GetValue() == key)
		{
			switch (i)
			{
				case HOST:
					config.SetHost(value);
					break;
				case PORT:
					config.SetPort(value);
					break;
				case SERVER_NAMES:
					config.SetServerName(value);
					break;
				case ERROR_PAGES:
					config.SetErrorPage(value);
				case LIMIT_CLIENT_BODY_SIZE:
					config.SetLimitClientBodySize(value);
				default:
					break;
			}
		}
	}
	
}

void ConfigReader::Read(const std::string &filename, Config &config)
{
	std::vector<std::string> tmp;
	std::string line;
	
	std::ifstream ifs(filename);
	if (ifs.fail())
		throw IOException();
    while (getline(ifs, line)){
        tmp.push_back(line);
    }

	for (itr i = tmp.begin(), e = tmp.end(); i != e; ++i) 
	{
		std::stringstream ss(*i);
		std::string key, value;
		std::getline(ss, key, ' ');
		std::getline(ss, value);
		if (isConfigOption(key))
			set(key, value, config);
	}
	
}

const char *ConfigReader::IOException::what() const throw()
{
	return "cannot read config file";
}

