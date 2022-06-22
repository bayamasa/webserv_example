#include "ConfigReader.hpp"

ConfigReader::ConfigReader()
{
	// defineの各パラメータと一致している
	// std::string config_key[CONFIG_ATTR_MAX] = {
	// 	"host",
	// 	"port",
	// 	"server_names",
	// 	"error_pages",
	// 	"limit_client_body_size",
	// 	"routes"
	// };

	
	for (size_t i = 0; i < CONFIG_ATTR_MAX; i++)
		conf_attr_decleared[conf_attr[i]] = false;
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

	for (int i = 0; i < CONFIG_ATTR_MAX; i++)
	{
		if (conf_attr[i] == key)
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
		if (conf_attr[i] == key)
		{
			switch (i)
			{
			case HOST:
				config.SetHost(value);
				break;
			case PORT:
				
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

