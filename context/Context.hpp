#ifndef CONTEXT_HPP
# define CONTEXT_HPP

#include <string>
#include "../conf/conf.hpp"

class Context
{
private:
	std::string filename;
	Config config;
	
public:
	Context();
	~Context();
	Context(const Context &other);
	Context &operator=(const Context &other);
	void SetFilename(char const *value);
	const std::string &GetFile() const;
};

#endif
