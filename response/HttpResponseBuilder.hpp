#ifndef HTTPRESPONSEBUILDER_HPP
# define HTTPRESPONSEBUILDER_HPP

#include "ConfigDTO.hpp"
#include "HttpRequestData.hpp"
#include "HttpResponse.hpp"
#include <vector>
#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <ios>

class HttpResponseBuilder
{
private:
	ConfigDTO conf_;
	struct s_abspath
	{
		std::string filepath;
		bool		exists;
	} t_abspath;
	std::stringstream read_str_;
public:
	HttpResponseBuilder();
	HttpResponseBuilder(ConfigDTO conf);
	~HttpResponseBuilder();
	HttpResponseBuilder(const HttpResponseBuilder &other);
	HttpResponseBuilder &operator=(const HttpResponseBuilder &other);
	HttpResponse build(HttpRequestData req);
	void findFilepath(HttpRequestData req);
	void findAbsPath(std::string dir, std::string file);
	void readFile();
};

#endif
