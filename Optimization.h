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
	std::vector<std::string> toPostfix();//�ন���Ǧ�
	void getPostfix();//�o�줤�Ǧ�
	double eval(std::map<std::string ,double>);//�D��
	std::string dealstring(std::string);//�B�z��J�r��
	std::string NewEquation(std::map<std::string,std::string>);//�Ш�s��equation(variable��equationn)
	bool judgeTrigonometric(char, char, char);//�P�_�O�_���U�h���T�����
	double getNDimension();//�o�즳�X���ܼ�
	std::string getinput();//��J�r��
	std::string getorignal();//�B�z��r��
	double GoldenSearch(double lowerbound,double middle,double upperbound,const double tau, double count);
	void Powell(std::map<std::string,double>initial, std::map<std::string,restrictVariable> rrestrict, double err,double count);
private:
	std::string orignal;//�B�z��r��
	std::string input;//��l��J
	std::vector<std::string>postfix;//�ন��Ǧ�
	std::set<char>variable;//�ܼ�
	std::string stackSign;//�Ÿ�stack
};

