#pragma once
#include<iostream>
#include<math.h>
#include<string>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<sstream>
#include<map>
#include<fstream>
#include"Exception.h"
#define pi 3.14159265359
#define RadtoAng(N) N*180/pi
#define AngtoRad(N) N*pi/180
	
class VectorSpace
{
public:
	VectorSpace();
	~VectorSpace();
	VectorSpace(std::string _name, int _size, double *a);
	VectorSpace(std::string _name, int _size, std::vector<double>_vec);
	VectorSpace(std::string _name);
	VectorSpace(std::string _name, double a); 
	void changename(std::string _name);
	VectorSpace(std::string _name,int _size);
	VectorSpace(int _size);
	void addNumInSpace(double _num);
	void changeNumInSpace(double _num, int place);
	VectorSpace(const VectorSpace& _vec);
	friend std::ostream& operator<<(std::ostream& os, const VectorSpace&);
	int getvectorsize();
	void deleteNumplace(int place);
	double getNumInSpace(int place);
	std::string getName();
	VectorSpace operator +(VectorSpace& _vec);
	VectorSpace operator =(const VectorSpace& _vec);
	VectorSpace operator -(VectorSpace& _vec);
double operator *( VectorSpace& _vec); //¤º¿n
	VectorSpace operator /(const double& _Scalar);
	VectorSpace operator *(double& _Scalar);
	VectorSpace operator ^(VectorSpace& _vec);
double Norm();
	VectorSpace Normalization();
	double AngleBetween(VectorSpace& _vec);
	double TriangleArea(VectorSpace& _vec);
	double Component(VectorSpace& _vec);
	VectorSpace Projection(VectorSpace& _vec);
	bool Parallel(VectorSpace &_vec);
	bool Orthohonal(VectorSpace&_vec);
	double vectorToDouble();
	//Linear_independent judgement
private:
	std::vector<double>vec;
	std::string name;
	int Vectorsize;
};

std::vector<VectorSpace> Orthonormalbasis(std::vector<VectorSpace> _vec);