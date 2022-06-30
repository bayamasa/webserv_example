#include "HttpRequestData.hpp"

HttpRequestData::HttpRequestData()
{
	_method = "GET";
	_url = "/index";
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
