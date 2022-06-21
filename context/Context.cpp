#include "Context.hpp"

Context::Context()
{
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

void Context::SetFilename(char const *value)
{
	filename = std::string(value);
}

const std::string &Context::GetFile() const
{
	return filename;
}
