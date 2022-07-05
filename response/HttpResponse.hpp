#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

#include <string>
#include <sstream>

class HttpResponse
{
private:
	// string最大文字数は4611686018427387897
	// https://cpprefjp.github.io/reference/string/basic_string/max_size.html
	// なので一旦エラーハンドリングとかはなしで。
	std::string response_;
	std::size_t response_size_;
public:
	HttpResponse();
	HttpResponse(std::string response, std::size_t response_size);
	~HttpResponse();
	HttpResponse(const HttpResponse &other);
	HttpResponse &operator=(const HttpResponse &other);
};

#endif

