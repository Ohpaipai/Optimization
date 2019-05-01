#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<cctype>
#include<set>
#include<map>
#include<sstream>
/*sin='!' cos='@' tan='$' csc='%' sec='&' cot='#'*/


class Optimization
{
public:
	int priority(char);
	Optimization();
	Optimization(const Optimization&);
	~Optimization();
	Optimization(std::string);
	std::vector<std::string> toPostfix();
	void getPostfix();
	double eval(std::map<std::string ,double>);
	bool judgeTrigonometric(char, char, char);
private:
	std::string orignal;
	std::vector<std::string>postfix;
	std::set<char>variable;
	std::string stackSign;
};

