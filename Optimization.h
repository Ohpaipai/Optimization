#pragma once
//#include<iostream>
//#include<vector>
//#include<string>
#include<cctype>
#include<set>
//#include<map>
//#include<sstream>
//#include<cmath>
#include<queue>
#include<limits>
#include"VectorAndMatrix.h"
/*sin='!' cos='@' tan='$' csc='%' sec='&' cot='#'  -='~'*/
const double phi = (1.0 + std::sqrt(5)) / 2.0;
const double resphi = 2 - phi;
typedef struct test
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
	Optimization operator=(const Optimization& a);
	std::vector<std::string> toPostfix();//轉成中序式
	void getPostfix();//得到中序式
	double eval(std::map<std::string ,double>);//求解
	std::string dealstring(std::string);//處理輸入字串
	std::string NewEquation(std::map<std::string,std::string>);//創到新的equation(variable為equationn)
	bool judgeTrigonometric(char, char, char);//判斷是否接下去為三角函數
	int getNDimension();//得到有幾種變數
	std::string getinput();//輸入字串
	std::string getorignal();//處理後字串
	double GoldenSearch(double lowerbound,double middle,double upperbound,const double tau, double count);//黃金探查
	void Powell(std::queue<std::map<std::string, double>> nvec, double err,int count);//powell
	std::string differentiation(std::string destination);//維分
	VectorSpace gradient(); // 計算目前點的梯度值
	std::vector<std::string> steepDescent();
	std::vector<std::string> newton();
	std::vector<std::string> conjugateGradient();
	bool insertInitialVariable(std::string,double);//新增initial單變數的起始值 如果新曾一樣的key直接取代
	void deleteinitial();//清空initial
	bool insertEveryVariableRestrict(std::string, restrictVariable);//新增ariable的限制 如果新曾一樣的key直接取代
	double CalculationLowerbound(std::string name, double x, double y);//x=我的限制上屆 y是除的參數
	double CalculationUpperbound(std::string name, double x, double y);//x=我的限制下屆 y是除的參數
	void CalculationBound(restrictVariable&, VectorSpace);
	void Quasi_Newton();
	
	void clearVariableRestrict();//清空variable
	Matrix  Hessianmatrix();
	restrictVariable checkvanszerofive(std::string);

private:
	std::string orignal;//處理後字串
	std::string input;//原始輸入
	std::vector<std::string>postfix;//轉成後序式
	std::set<char>variable;//變數
	std::string stackSign;//符號stack
	std::map<std::string, double> initial;//每個初始值
	std::map<std::string, restrictVariable> rrestrict;//variable限制
};

