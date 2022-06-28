#include "ConfigReader.hpp"

ConfigReader::ConfigReader()
{
	_conf_opts[HOST] = ConfigOptionConstant("host");
	_conf_opts[PORT] = ConfigOptionConstant("port");
	_conf_opts[SERVER_NAMES] = ConfigOptionConstant("server_names");
	_conf_opts[ERROR_PAGES] = ConfigOptionConstant("error_pages");
	_conf_opts[LIMIT_CLIENT_BODY_SIZE] = ConfigOptionConstant("limit_client_body_size");
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

bool ConfigReader::isConfigOptionConstant(std::string key)
{
	// std::cout << key << std::endl;
	for (int i = 0; i < conf_max_num; i++)
	{
		// std::cout << _conf_opts[i].GetName() << std::endl;
		if (_conf_opts[i].GetName() == key)
		{
			return true;
		}
	}
	return false;
}

void ConfigReader::set(std::string key, std::string value, Config &config)
{

	for (int i = 0; i < conf_max_num; i++)
	{
		if (_conf_opts[i].GetName() == key)
		{
			switch (i)
			{
				case HOST:
					std::cout << "host set" << std::endl;
					config.SetHost(value);
					break;
				case PORT:
					std::cout << "port set" << std::endl;
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
		if (isConfigOptionConstant(key))
			set(key, value, config);
	}
	
}

const char *ConfigReader::IOException::what() const throw()
{
	return "cannot read config file";
}

