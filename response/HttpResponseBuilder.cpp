#include "HttpResponseBuilder.hpp"

HttpResponseBuilder::HttpResponseBuilder()
{
}

HttpResponseBuilder::HttpResponseBuilder(ConfigDTO conf)
{
	conf_ = conf;
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
	
	std::vector<LocationConfig>::iterator i = conf_.GetLocation().begin();
	std::vector<LocationConfig>::iterator ie = conf_.GetLocation().end();
	
	for (; i != ie; i++)
	{
		(void)req;
		if ((*i).location_ == req.GetPath())
		{
			try
			{
				std::string dir = findFile();
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			
			
		}
	}
	return HttpResponse();
}
