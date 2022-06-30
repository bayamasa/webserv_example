#ifndef HTTPRESPONSEBUILDER_HPP
# define HTTPRESPONSEBUILDER_HPP

#include "Config.hpp"
#include "HttpRequestData.hpp"

class HttpResponseBuilder
{
private:
	Config _conf;
	HttpRequestData _data;
public:
	HttpResponseBuilder();
	HttpResponseBuilder(Config conf, HttpRequestData data);
	~HttpResponseBuilder();
	HttpResponseBuilder(const HttpResponseBuilder &other);
	HttpResponseBuilder &operator=(const HttpResponseBuilder &other);
};

#endif
