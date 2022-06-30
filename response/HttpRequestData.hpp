#ifndef HTTPREQUESTDATA_HPP
# define HTTPREQUESTDATA_HPP

#include <string>

class HttpRequestData
{
private:

public:
	std::string _method;
	std::string _url;
	HttpRequestData();
	~HttpRequestData();
	HttpRequestData(const HttpRequestData &other);
	HttpRequestData &operator=(const HttpRequestData &other);
};

#endif
