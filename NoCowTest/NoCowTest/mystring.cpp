#include <iostream>
#include <string>
#include <cstring>
#include <vector>
void print(const std::string &str)
{
	std::cout << str << std::endl;
}
class mystring
{
public:
	mystring(const char *str = "")
	{
		print("constructed");
		if (str == NULL) {
			str_ = new char[1];
			str_[0] = NULL;
			sz_ = 0;
		}
		else {
			sz_ = strlen(str);
			str_ = new char[sz_+1];
			strcpy(str_, str);
		}
	}

	mystring(const mystring &rhs) {
		print("Copy constructed.");
		sz_ = rhs.sz_;
		str_ = new char[rhs.sz_ + 1];
		strcpy(str_, rhs.str_);
	}
	mystring(mystring &&rhs) {
		print("Copy constructed.&&");
		sz_ = rhs.sz_;
		str_ = rhs.str_;
		rhs.sz_ = 0;
		rhs.str_ = nullptr;
	}
	mystring &operator=(const mystring &rhs) {
		print("operator=");
		if (this == &rhs)
			return *this;
		mystring tmp(rhs);
		std::swap(this->sz_, tmp.sz_);
		std::swap(this->str_, tmp.str_);
		return *this;
	}
	mystring &operator=(mystring &&rhs) {
		print("operator=&&");
		if (this == &rhs)
			return *this;
		std::swap(this->sz_, rhs.sz_);
		std::swap(this->str_, rhs.str_);
		return *this;
	}

	~mystring()
	{
		print("deconstructed.");
		delete str_;
	}
	const char *c_str()
	{
		return str_;
	}
private:
	char *str_;
	size_t sz_;
};

mystring getString()
{
	return "hello world";
}

int main(int argc, char *argv[])
{
	mystring str1 = "hello";
	mystring str2 = "world";
	str1 = str2;    //operator=& copy construct&
	print(str1.c_str());
	print(str2.c_str());
	mystring ms;
	ms = getString();   //operator& copy construct&
	print(ms.c_str());
	mystring ok(std::move(ms));  //copy construct &&
	
	std::vector<mystring> vecms;
	
	vecms.emplace_back("Haha");  //原地构造，没有copy_construct &&
	vecms.push_back("Hehe");     //调用copy_construct &&

	std::vector<mystring> vec;
	vec = std::move(vecms);
	std::cout << vecms.size() << std::endl;
	vec.emplace(vec.begin(), "wyg");//插入
	for (auto &au : vec)
		print(au.c_str());
	mystring tst;
	tst = mystring("hello");    //operator=&&

	return 0;

}