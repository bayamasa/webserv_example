#ifndef HTTPREQUESTDATA_HPP
# define HTTPREQUESTDATA_HPP

#include <string>

class HttpRequestData
{
private:
	std::string method_;
	std::string path_;
	std::string file_;
	bool        is_index_;
public:	
	HttpRequestData();
	HttpRequestData(std::string method, std::string path, std::string file, bool is_index);
	~HttpRequestData();
	HttpRequestData(const HttpRequestData &other);
	HttpRequestData &operator=(const HttpRequestData &other);
	const std::string &GetPath() const;
};

#endif
