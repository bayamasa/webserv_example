#ifndef CONFIG_HPP
# define CONFIG_HPP

#include <string>

class Config
{
private:
	std::string _location;
	std::string _root;
	std::string _index;
public:
	Config();
	Config(std::string location, std::string _root, std::string _index);
	~Config();
	Config(const Config &other);
	Config &operator=(const Config &other);
	const std::string &GetLocation() const;
	const std::string &GetRoot() const;
	const std::string &GetIndex() const;
};

#endif

