#include "HttpResponseBuilder.hpp"

HttpResponseBuilder::HttpResponseBuilder()
{
}

HttpResponseBuilder::HttpResponseBuilder(ConfigDTO conf)
{
	_conf.push_back(conf);
}

HttpResponseBuilder::~HttpResponseBuilder()
{
}
HttpResponseBuilder::HttpResponseBuilder(const HttpResponseBuilder &other)
{
	*this = other;
}
HttpResponseBuilder &HttpResponseBuilder::operator=(const HttpResponseBuilder &other)
{
	if (this != &other)
	{
	}
	return *this;
}

HttpResponse &HttpResponseBuilder::build(HttpRequestData req)
{
	itr i = _conf.begin();
	itr ie = _conf.end();
	for (; i != ie; i++)
	{
		// if ((*i).GetLocation() == req.GetPath())
		// {
		// 	std::string dir = find_dir();
		// }
	}
}
