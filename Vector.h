#pragma once
#include<vector>
#include<iostream>
#include<math.h>
#include<algorithm>
#include<string>
using namespace std;


  class Vector
{
public:
	Vector();
	~Vector();
	Vector(int _size , string _name);
	Vector(int _size);
	int getsize();
	void add(double _a[]);
	Vector operator =(const Vector& vec);//vector +
	Vector operator +(const Vector& vec);//vector +
	Vector operator -(const Vector& vec);//vector -
	double operator *(const Vector& vec);//vector dot
	Vector operator ^(const Vector& vec);//vector planenormal
	Vector Scalar_Multiplication(double Scalra);// vector 純量乘法
	double Norm();//vector 長度
	Vector Normalization();//vector 向量的规格化,让向量的长度等于1
	double Angle_between( Vector& vec);//vector 間角度
	double Triangle_area( Vector& vec);//vector 求三角形面積
	Vector Component_A_On_B(const Vector& vec);//vector 分量
	Vector Projection_A_On_B( Vector& vec);//vector 正射影
	bool   Parallel_judgement( Vector& vec);//vector 平行
	bool   Orthogonal_judgement( Vector& vec);//vector 垂直
	
	bool Linear_independent_judgement( Vector& vec);//兩向量線性獨立 -->做成 function 
	Vector Orthonormal_basis();//vector 正規化正交基底
	double *a;
private:
	
	int size;
	string name;
};

