#include "HttpRequestData.hpp"

HttpRequestData::HttpRequestData(){}

HttpRequestData::HttpRequestData(std::string method, std::string path, std::string file, bool is_index)
{
	method_ = method;
	path_ = path;
	file_ = file;
	is_index_ = is_index;
}

HttpRequestData::~HttpRequestData()
{
}
HttpRequestData::HttpRequestData(const HttpRequestData &other)
{
	*this = other;
}
HttpRequestData &HttpRequestData::operator=(const HttpRequestData &other)
{
	if (this != &other)
	{
	}
	return *this;
}
