#include "ConfigReader.hpp"

ConfigReader::ConfigReader()
{
	const config_key = {
		"host",
		"port",
		"server_names",
		"error_pages",
		"limit_client_body_size",
		"routes"
	}
	
	for (size_t i = 0; i < CONFIG_ATTR_MAX; i++)
	{
		config_attr.insert(std::make_pair(config_key[i], false));
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

vector<std::string> blankSeparator(char *line)
{
	
	std::string key;
	std::string value;
	std::string::size_type pos;

	key = std::string(line);
	pos = key.find(" ");
	key.erase(pos);
}

Config *ConfigReader::Read(std::string filename)
{
	FILE *fp;
	
	fp = fopen(filename.c_str(), "r");
	if (fp == NULL)
		throw IOException;
	// 一旦一行にBuffer以上の文字が入っている場合は考えない
	while (fgets(line, LINE_MAX_BUFFER, fp) != NULL)
	{
		if(feof(fp))
			break;
		
		
	}
	
	
}

const char *ConfigReader::IOException::what() const throw()
{
	return "cannot read config file";
}

