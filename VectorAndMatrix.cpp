#include "VectorAndMatrix.h"

Matrix operator*( VectorSpace &vec,  Matrix & _matrix)
{

	
		std::string name = "name";
		int n = vec.getvectorsize();
		Matrix tem(n, 1, vec);
		Matrix ans;
		ans = tem * _matrix;
		return ans;
	
}

Matrix operator*(Matrix & _matrix, VectorSpace & vec)
{
	
		std::string name = "name";
		int n = vec.getvectorsize();
		Matrix tem(n, 1, vec);
		Matrix ans;
		ans = _matrix * tem;
		return ans;


}

Matrix operator+(VectorSpace & vec, Matrix & _matrix)
{
	
		std::string name = "name";
		int n = vec.getvectorsize();
		Matrix tem(n, 1, vec);
		Matrix ans;
		ans = _matrix + tem;
		return ans;
	
	
}

Matrix operator+(Matrix & _matrix, VectorSpace & vec)
{

	std::string name = "name";
	int n = vec.getvectorsize();
	Matrix tem(n, 1, vec);
	Matrix ans;
	ans = tem + _matrix;
	return ans;
}

Matrix operator-(Matrix & _matrix, VectorSpace & vec)
{
	std::string name = "name";
	int n = vec.getvectorsize();
	Matrix tem(n, 1, vec);
	Matrix ans;
	ans =  _matrix-tem;
	return ans;
}

Matrix operator-(VectorSpace & vec, Matrix & _matrix)
{
	std::string name = "name";
	int n = vec.getvectorsize();
	Matrix tem(n, 1, vec);
	Matrix ans;
	ans = tem-_matrix;
	return ans;
}
