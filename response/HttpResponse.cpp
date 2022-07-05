#include "HttpResponse.hpp"

HttpResponse::HttpResponse()
{
}

HttpResponse::HttpResponse(std::string response, std::size_t response_size)
{
	response_ = response;
	response_size_ = response_size;
}

HttpResponse::~HttpResponse()
{
}
HttpResponse::HttpResponse(const HttpResponse &other)
{
	*this = other;
}
HttpResponse &HttpResponse::operator=(const HttpResponse &other)
{
	if (this != &other)
	{
	}
	return *this;
}
