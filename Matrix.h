#pragma once
#include"VectorSpace.h"




typedef struct MyStruct
{
	bool up;
	std::string A;
	VectorSpace B;
}re;


//(2*x^1* 1) + 1 - (0 * x^ 0.5 + 2 * (0.5 * x ^ -0.5 * 1))


class Matrix
{
public:
	Matrix();
	~Matrix();
	Matrix(const Matrix& _matrix);
	Matrix(std::string _name);
	Matrix(std::string _name, int _row, int _column, std::vector<std::vector<double>>_matrix);
	Matrix(std::string _name, int _row, int _column, std::vector<VectorSpace>_matrix);
	Matrix(int _row, int _column, VectorSpace _vec);
	Matrix(std::string _name, int _row, int _column, VectorSpace _vec);
	Matrix(std::string _name, int _row, int _column);
	Matrix(int _row, int _column);
	Matrix(int _row, int _column, int n);
	void changename(std::string _name);
	friend std::ostream& operator<<(std::ostream& os, const Matrix&);
	void addRow(double *a, int _size);
	void addRow(std::vector<double> _tem, int _size);
	void addRow(VectorSpace _tem, int _size);
	void addColumn(double *a, int _size);
	void addColumn(std::vector<double> _tem, int _size);
	void addColumn(VectorSpace _tem, int _size);
	void replaceNuminMatrix(int row, int column, double _num);
	double getnuminMatrix(int _row, int _column);
	void deleterow(int _row);
	void deletecolumn(int _column);
	int getcolumn();
	int getRow();
	std::string getName();
	Matrix operator +(const Matrix&_matrix);
	Matrix operator -(const Matrix&_matrix);
	Matrix operator *(const Matrix&_matrix);
	Matrix operator *(const double&_Scalar);
	Matrix operator /(const double&_Scalar);
	Matrix operator =(const Matrix&_matrix);
	Matrix operator ^(const double&_Scalar);
	Matrix Transpose();
	double determinants();
	Matrix adjoint();
	Matrix Inverse();
	double Rank();
	Matrix eigenMatrix(double);
	re  linear_system(VectorSpace _vec);
	void rr(int, int, double*, bool*, VectorSpace, bool noans, re anst);
	std::map<double, re> eigenvalueAndeigenvectorUnder3();
	std::map<double, re> powerMethod();
	Matrix Guass();
	double matrixToDouble();
	Matrix leastSquare(Matrix a);
	//least square
private:
	bool juge(Matrix b);

	std::vector<std::vector<double>>matrix;
	int row;
	int column;
	std::string name;
};



bool Linear_independent(std::vector<VectorSpace> _vec);
bool Linear_independent(int howmany, VectorSpace *_vec);
//std::string leastSquare(std::vector<VectorSpace> _vec);
//std::string leastSquare(int howmany, VectorSpace *_vec);