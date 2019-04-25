#pragma once
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<math.h>
#include<ctype.h>
const double  phi = (1 + std::sqrt(5)) / 2;
const double  resphi = (2 - phi);







typedef struct MyStruct
{
	std::string name;//變數名 x or y or z...
	double exponential;//次方

	bool operator ==(MyStruct& p)  //判斷是否一樣
	{
		if (this->name == p.name&&p.exponential == this->exponential) return true;
		else return false;
	}
	MyStruct operator =(MyStruct &tem) {//=
		this->name = tem.name;
		this->exponential = tem.exponential;
		return *this;
	}

}Variance; //放置幾次方(變數項)


typedef struct MyStruct2
{
	std::string mathName;//可能為sinx cosx 之類的
	double coefficient;//係數

	bool operator ==( MyStruct2& p)  //判斷是否一樣
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
		ans.mathName = this->mathName + tem.mathName; //是否有更佳方法?
		return ans;
	}
}Coefficient; //放置coef



class LinkVariance
{
public:
	
	bool operator ==( LinkVariance _var); //是否變數一樣
	LinkVariance operator =(LinkVariance &tem);//=
	~LinkVariance();
	LinkVariance();
	LinkVariance(Variance);
	void insert(Variance);//新增
	LinkVariance(const LinkVariance &tem);//複製
	void Delete(Variance);//刪除
	LinkVariance operator*(LinkVariance tem);
	std::vector<Variance>variable;  //多個變數項
	friend std::ostream& operator<<(std::ostream& os, const LinkVariance&);
};









class LinkEquation
{
public:
	LinkEquation();//初始化
	~LinkEquation();
	LinkEquation(const LinkEquation&);//複製
	LinkEquation(LinkVariance _var, Coefficient _coe);//初始化
	void insert(LinkVariance _var, Coefficient _coe);//新增資料
	void Delete(LinkVariance _var, Coefficient _coe);//刪除資料

	LinkEquation operator*(LinkEquation tem);//*
	LinkEquation operator+(LinkEquation tem);//+
	LinkEquation operator-(LinkEquation tem);//-
	friend std::ostream& operator<<(std::ostream& os, const LinkEquation&);
	double Fxans(double);
	double GoldenSectionSearch(double lowBound, double middle, double upperBound, double tau);
	
private:
	std::vector<LinkVariance>Polynomial; //3 
	std::vector<Coefficient>Polynomial_coef;// x^3
	//互相對應 vector size兩個必定相同
};

