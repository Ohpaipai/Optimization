#pragma once
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<math.h>
#include<ctype.h>
#include"VectorAndMatrix.h"
#include"Equation.h"
const double  phi = (1 + std::sqrt(5)) / 2;
const double  resphi = (2 - phi);
const double  w = 0.38197;






typedef struct MyStruct
{
	std::string name;//�ܼƦW x or y or z...
	double exponential;//����

	bool operator ==(MyStruct& p)  //�P�_�O�_�@��
	{
		if (this->name == p.name&&p.exponential == this->exponential) return true;
		else return false;
	}
	MyStruct operator =(MyStruct &tem) {//=
		this->name = tem.name;
		this->exponential = tem.exponential;
		return *this;
	}

}Variance; //��m�X����(�ܼƶ�)


typedef struct MyStruct2
{
	std::string mathName;//�i�ରsinx cosx ������
	double coefficient;//�Y��

	bool operator ==( MyStruct2& p)  //�P�_�O�_�@��
	{
		if (this->mathName==p.mathName&&this->coefficient==p.coefficient) return true;
		else return false;
	}
	MyStruct2 operator =(MyStruct2 &tem) { //=
		this->mathName = tem.mathName;
		this->coefficient = tem.coefficient;
		return *this;
	}
	MyStruct2 operator *(MyStruct2 &tem) { //*
		MyStruct2 ans;
		ans.coefficient = this->coefficient*tem.coefficient;
		ans.mathName = this->mathName + tem.mathName; //�O�_����Τ�k?
		return ans;
	}
}Coefficient; //��mcoef



class LinkVariance
{
public:
	
	bool operator ==( LinkVariance _var); //�O�_�ܼƤ@��
	LinkVariance operator =(LinkVariance &tem);//=
	~LinkVariance();
	LinkVariance();
	LinkVariance(Variance);
	void insert(Variance);//�s�W
	LinkVariance(const LinkVariance &tem);//�ƻs
	void Delete(Variance);//�R��
	LinkVariance operator*(LinkVariance tem);
	std::vector<Variance>variable;  //�h���ܼƶ�
	friend std::ostream& operator<<(std::ostream& os, const LinkVariance&);
};









class LinkEquation
{
public:
	LinkEquation();//��l��
	~LinkEquation();
	LinkEquation(const LinkEquation&);//�ƻs
	LinkEquation(LinkVariance _var, Coefficient _coe);//��l��
	void insert(LinkVariance _var, Coefficient _coe);//�s�W���
	void Delete(LinkVariance _var, Coefficient _coe);//�R�����

	LinkEquation operator*(LinkEquation tem);//*
	LinkEquation operator+(LinkEquation tem);//+
	LinkEquation operator-(LinkEquation tem);//-
	friend std::ostream& operator<<(std::ostream& os, const LinkEquation&);
	double Fxans(std::string , double);
	double TwoFxans(std::string, std::string, double , double); //�T����Ƥ䴩x&y
	double GoldenSectionSearch(double lowBound, double middle, double upperBound, double tau, std::string _name);
	LinkEquation Powell2Golden(std::string, std::string,LinkEquation, double);//string�� �A�ҭn�a�J�Ʀr ,Linkequation���A�|�a�J����{��
	void Powell(std::string ,std::string,double,double,bool find);
	void PowellForUpDown(double _x,double _y);
	
private:
	std::vector<LinkVariance>Polynomial; //3 
	std::vector<Coefficient>Polynomial_coef;// x^3
	//���۹��� vector size��ӥ��w�ۦP
	double up;
	double down;
};

