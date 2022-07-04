#ifndef HTTPRESPONSEBUILDER_HPP
# define HTTPRESPONSEBUILDER_HPP

#include "Config.hpp"
#include "HttpRequestData.hpp"
#include "HttpResponse.hpp"
#include <vector>

class HttpResponseBuilder
{
private:
	std::vector<Config> _conf;
	typedef std::vector<Config>::iterator itr;
public:
	HttpResponseBuilder();
	HttpResponseBuilder(Config conf);
	~HttpResponseBuilder();
	HttpResponseBuilder(const HttpResponseBuilder &other);
	HttpResponseBuilder &operator=(const HttpResponseBuilder &other);
	HttpResponse &build(HttpRequestData req);
};

#endif
