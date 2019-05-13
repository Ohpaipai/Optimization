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
	std::vector<std::string> toPostfix();//�ন���Ǧ�
	void getPostfix();//�o�줤�Ǧ�
	double eval(std::map<std::string ,double>);//�D��
	std::string dealstring(std::string);//�B�z��J�r��
	std::string NewEquation(std::map<std::string,std::string>);//�Ш�s��equation(variable��equationn)
	bool judgeTrigonometric(char, char, char);//�P�_�O�_���U�h���T�����
	int getNDimension();//�o�즳�X���ܼ�
	std::string getinput();//��J�r��
	std::string getorignal();//�B�z��r��
	double GoldenSearch(double lowerbound,double middle,double upperbound,const double tau, double count);//�������d
	void Powell(std::queue<std::map<std::string, double>> nvec, double err,int count);//powell
	std::string differentiation(std::string destination);//����
	VectorSpace gradient(); // �p��ثe�I����׭�
	std::vector<std::string> steepDescent();
	std::vector<std::string> newton();
	std::vector<std::string> conjugateGradient();
	bool insertInitialVariable(std::string,double);//�s�Winitial���ܼƪ��_�l�� �p�G�s���@�˪�key�������N
	void deleteinitial();//�M��initial
	bool insertEveryVariableRestrict(std::string, restrictVariable);//�s�Wariable������ �p�G�s���@�˪�key�������N
	double CalculationLowerbound(std::string name, double x, double y);//x=�ڪ�����W�� y�O�����Ѽ�
	double CalculationUpperbound(std::string name, double x, double y);//x=�ڪ�����U�� y�O�����Ѽ�
	void CalculationBound(restrictVariable&, VectorSpace);
	void Quasi_Newton();
	
	void clearVariableRestrict();//�M��variable
	Matrix  Hessianmatrix();
	restrictVariable checkvanszerofive(std::string);

private:
	std::string orignal;//�B�z��r��
	std::string input;//��l��J
	std::vector<std::string>postfix;//�ন��Ǧ�
	std::set<char>variable;//�ܼ�
	std::string stackSign;//�Ÿ�stack
	std::map<std::string, double> initial;//�C�Ӫ�l��
	std::map<std::string, restrictVariable> rrestrict;//variable����
};

