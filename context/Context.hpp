#ifndef CONTEXT_HPP
# define CONTEXT_HPP

#include <string>
#include "../conf/conf.hpp"

class Context
{
private:
	std::string filename;
	// configの値は初期値から変化しないのでスタック領域
	// めちゃめちゃでかいデータ入れられる可能性があったら変える
	Config config;
public:
	Context();
	~Context();
	Context(const Context &other);
	Context &operator=(const Context &other);
	const std::string &GetFilename() const;
	void SetFilename(char const *value);
	Config& GetConfig();
	void SetConfig(Config &value);
};

#endif
