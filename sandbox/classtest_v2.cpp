#ifndef CLASSTEST_HPP
# define CLASSTEST_HPP

// getterの渡しを値渡しにすることで、private変数の破壊を防ぐ
#include <string>
#include <iostream>

class classtest
{
private:
	std::string _data;
public:
	classtest();
	~classtest();
	classtest(const classtest &other);
	classtest &operator=(const classtest &other);
	void SetData(std::string data);
	std::string GetData();
};

classtest::classtest()
{
}
classtest::~classtest()
{
}
classtest::classtest(const classtest &other)
{
	*this = other;
}
classtest &classtest::operator=(const classtest &other)
{
	if (this != &other)
	{
	}
	return *this;
}

void classtest::SetData(std::string data)
{
	_data = data;
}

std::string classtest::GetData()
{
	return _data;
}


int main(void)
{
	classtest c;
	c.SetData("helllo");
	std::string d = c.GetData();
	std::string hi = "hi";
	c.GetData().swap(hi);
	std::cout << d << std::endl;
	std::cout << c.GetData() << std::endl;
}
#endif

