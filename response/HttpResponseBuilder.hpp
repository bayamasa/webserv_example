#ifndef HTTPRESPONSEBUILDER_HPP
# define HTTPRESPONSEBUILDER_HPP

#include "ConfigDTO.hpp"
#include "HttpRequestData.hpp"
#include "HttpResponse.hpp"
#include <vector>

class HttpResponseBuilder
{
private:
	ConfigDTO conf_;
public:
	HttpResponseBuilder();
	HttpResponseBuilder(ConfigDTO conf);
	~HttpResponseBuilder();
	HttpResponseBuilder(const HttpResponseBuilder &other);
	HttpResponseBuilder &operator=(const HttpResponseBuilder &other);
	HttpResponse &build(HttpRequestData req);
	std::string findFile(std::string filename);
};

#endif
