#pragma once
#include <string>
#include <exception>

class Myexception :public std::exception//自定义错误类
{
public:
	Myexception(std::string s)
	{
		error = s;
	}

	const char* what()const
	{
		return  error.c_str();
	}

	std::string error;
};
