#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<cctype>
#include<set>
#include<map>
#include<sstream>
#include<cmath>
/*sin='!' cos='@' tan='$' csc='%' sec='&' cot='#'  -='~'*/
const double phi = (1.0 + std::sqrt(5)) / 2.0;
const double resphi = 2 - phi;
typedef struct MyStruct
{
	double upperbound;
	double lowerbound;

}restrictVariable;
class Optimization
{
public:
	int priority(char);
	Optimization();
	Optimization(const Optimization&);
	~Optimization();
	Optimization(std::string);
	std::vector<std::string> toPostfix();//轉成中序式
	void getPostfix();//得到中序式
	double eval(std::map<std::string ,double>);//求解
	std::string dealstring(std::string);//處理輸入字串
	std::string NewEquation(std::map<std::string,std::string>);//創到新的equation(variable為equationn)
	bool judgeTrigonometric(char, char, char);//判斷是否接下去為三角函數
	double getNDimension();//得到有幾種變數
	std::string getinput();//輸入字串
	std::string getorignal();//處理後字串
	double GoldenSearch(double lowerbound,double middle,double upperbound,const double tau, double count);
	void Powell(std::map<std::string,double>initial, std::map<std::string,restrictVariable> rrestrict, double err,double count);
private:
	std::string orignal;//處理後字串
	std::string input;//原始輸入
	std::vector<std::string>postfix;//轉成後序式
	std::set<char>variable;//變數
	std::string stackSign;//符號stack
};

