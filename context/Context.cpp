#include "Context.hpp"

Context::Context()
{
	config = Config();
}
Context::~Context()
{
}
Context::Context(const Context &other)
{
	*this = other;
}
Context &Context::operator=(const Context &other)
{
	if (this != &other)
	{
	}
	return *this;
}

const std::string &Context::GetFilename() const
{
	return filename;
}

void Context::SetFilename(char const *value)
{
	filename = std::string(value);
}

Config& Context::GetConfig() {
	return config;
}

void Context::SetConfig(Config &value)
{
	config = value;
}
