#ifndef HTTPRESPONSEBUILDER_HPP
# define HTTPRESPONSEBUILDER_HPP

#include "Config.hpp"
#include "HttpRequestData.hpp"

class HttpResponseBuilder
{
private:
	Config _conf;
	HttpRequestData _req_data;
public:
	HttpResponseBuilder();
	HttpResponseBuilder(Config conf, HttpRequestData req_data);
	~HttpResponseBuilder();
	HttpResponseBuilder(const HttpResponseBuilder &other);
	HttpResponseBuilder &operator=(const HttpResponseBuilder &other);
};

#endif
