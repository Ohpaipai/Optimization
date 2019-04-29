#include"Matrix.h"

Matrix operator*( VectorSpace &vec, Matrix&_matrix);
Matrix operator*(Matrix&_matrix, VectorSpace &vec);
Matrix operator+(VectorSpace &vec, Matrix&_matrix);
Matrix operator+(Matrix&_matrix, VectorSpace &vec);
Matrix operator-(Matrix&_matrix, VectorSpace &vec);
Matrix operator-(VectorSpace &vec, Matrix&_matrix);