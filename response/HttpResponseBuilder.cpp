#include "HttpResponseBuilder.hpp"

HttpResponseBuilder::HttpResponseBuilder()
{
}

HttpResponseBuilder::HttpResponseBuilder(ConfigDTO conf)
{
	conf_ = conf;
	t_abspath.exists = false;
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

// 基本的に文字列操作はmallocを使いたくないのでstringに変換して行いたい
void HttpResponseBuilder::findAbsPath(std::string dir, std::string file)
{
	DIR				*dirp;
	struct dirent	*ent;
	char			*cwd;
	std::string		fullpath;
	
	cwd = getcwd(NULL, 0);
	
	fullpath = std::string(cwd) + std::string("/") + dir;
	free(cwd);
	std::cout << "fullpath" << fullpath << std::endl;
	
	
	dirp = opendir(fullpath.c_str());
	if (dirp == NULL)
		throw std::runtime_error("directory not found");
	while ((ent = readdir(dirp)) != NULL)
	{
		if (ent->d_name == file.c_str())
		{
			t_abspath.filepath = fullpath + std::string("/") + file;
			t_abspath.exists = true;
			break;
		}
	}
	closedir(dirp);
}

void HttpResponseBuilder::findFilepath(HttpRequestData req)
{
	std::vector<LocationConfig>::iterator i = conf_.GetLocation().begin();
	std::vector<LocationConfig>::iterator ie = conf_.GetLocation().end();

	for (; i != ie; i++)
	{
		if ((*i).location_ == req.GetPathDir())
		{
			findAbsPath((*i).root_ + (*i).location_, req.GetPathFile());
		}
	}
	if (!t_abspath.exists)
		throw std::runtime_error("file not found");
}

void HttpResponseBuilder::readFile()
{
	std::ifstream ifs(t_abspath.filepath);
	std::string line;
	
	if (ifs.fail())
		throw std::ios_base::failure("file input error");
    while (std::getline(ifs, line)){
        read_str_ << line;
    }
}

HttpResponse HttpResponseBuilder::build(HttpRequestData req)
{
	try
	{
		findFilepath(req);
		readFile();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return HttpResponse("hello", 5);
}
