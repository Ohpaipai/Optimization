#include "Matrix.h"



Matrix::Matrix()
{
	row = 0;
	column = 0;
	name.clear();
	matrix.clear();
}


Matrix::~Matrix()
{
	row = 0;
	column = 0;
	for (int i = 0; i < matrix.size(); i++)
	{
		matrix[i].clear();
	}
	matrix.clear();
	name.clear();
}

Matrix::Matrix(const Matrix & _matrix)
{
	name = _matrix.name;

	row = _matrix.row;
	column = _matrix.column;
	matrix = _matrix.matrix;
}

Matrix::Matrix(std::string _name)
{
	row = 0;
	column = 0;
	name = _name;

}


Matrix::Matrix(std::string _name, int _row, int _column, std::vector<std::vector<double>> _matrix)
{
	row = _row;
	column = _column;
	name = _name;
	matrix.resize(row);
	for (int i = 0; i < row; i++)
	{
		matrix[i].resize(column);
		for (int j = 0; j < column; j++)
		{
			matrix[i][j] = _matrix[i][j];
		}
	}
}

Matrix::Matrix(std::string _name, int _row, int _column, std::vector<VectorSpace> _matrix)
{
	row = _row;
	column = _column;
	name = _name;
	matrix.resize(row);
	for (int i = 0; i < row; i++)
	{
		matrix[i].resize(column);
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++) {
			matrix[i][j] = _matrix[i].getNumInSpace(j);
		}
	}

}

Matrix::Matrix(int _row, int _column, VectorSpace  _vec)
{
	row = _row;
	column = _column;
	matrix.resize(row);
	for (int i = 0; i < row; i++)
	{
		matrix[i].resize(column);
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++) {
			matrix[i][j] = _vec.getNumInSpace(i);
		}
	}
}

Matrix::Matrix(std::string _name, int _row, int _column, VectorSpace  _vec)
{
	row = _row;
	column = _column;
	name = _name;
	matrix.resize(row);
	for (int i = 0; i < row; i++)
	{
		matrix[i].resize(column);
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++) {
			matrix[i][j] = _vec.getNumInSpace(i);
		}
	}
}

Matrix::Matrix(std::string _name, int _row, int _column)
{
	row = _row;
	column = _column;
	name = _name;
	matrix.resize(row);
	for (int i = 0; i < row; i++)
	{
		matrix[i].resize(column);
		for (int j = 0; j < column; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

Matrix::Matrix(int _row, int _column)
{
	row = _row;
	column = _column;
	matrix.resize(row);
	for (int i = 0; i < row; i++)
	{
		matrix[i].resize(column);
		for (int j = 0; j < column; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

Matrix::Matrix(int _row, int _column, int n)
{
	row = _row;
	column = _column;
	matrix.resize(row);
	for (int i = 0; i < row; i++)
	{
		matrix[i].resize(column);
		for (int j = 0; j < column; j++)
		{
			matrix[i][j] = n;
		}
	}
}

void Matrix::changename(std::string _name)
{
	name = _name;
}

void Matrix::addRow(double * a, int _size)
{
	
	if (_size != column)
		throw myException(column_not_same);
	std::vector<double>tem;
	for (int i = 0; i < _size; i++)
	{
		tem.push_back(a[i]);
	}
	row += 1;
	matrix.push_back(tem);
}

void Matrix::addRow(std::vector<double> _tem, int _size)
{
	if (_size != column)
		throw myException(column_not_same);
	row += 1;
	matrix.push_back(_tem);
}
void Matrix::addRow(VectorSpace _tem, int _size)
{
	if (_size != column)
		throw myException(column_not_same);
	std::vector<double>tem;
	for (int i = 0; i < _size; i++)
	{
		tem.push_back(_tem.getNumInSpace(i));
	}
	row += 1;
	matrix.push_back(tem);
}
void Matrix::addColumn(double * a, int _size)
{
	if (_size != row)
		throw myException(row_not_same);
	for (int i = 0; i < _size; i++)
	{
		matrix[i].push_back(a[i]);
	}
	column += 1;
}
void Matrix::addColumn(std::vector<double> _tem, int _size)
{
	if (_size != row)
		throw myException(row_not_same);
	for (int i = 0; i < _size; i++)
	{
		matrix[i].push_back(_tem[i]);
	}
	column += 1;
}
void Matrix::addColumn(VectorSpace _tem, int _size)
{
	if (_size != row)
		throw myException(row_not_same);
	for (int i = 0; i < _size; i++)
	{
		matrix[i].push_back(_tem.getNumInSpace(i));
	}
	column += 1;
}
void Matrix::replaceNuminMatrix(int row, int column, double _num)
{
	matrix[row][column] = _num;
}
double Matrix::getnuminMatrix(int _row, int _column)
{
	return matrix[_row][_column];
}
void Matrix::deleterow(int _row)
{
	std::vector <std::vector<double>>tem;
	for (int i = 0; i < row; i++)
	{
		if (i == _row) {}
		else tem.push_back(matrix[i]);
	}
	row -= 1;
	matrix = tem;
}
void Matrix::deletecolumn(int _column)
{
	std::vector <std::vector<double>>tem;
	for (int i = 0; i < row; i++)
	{
		std::vector<double>t;
		for (int j = 0; j < column; j++)
		{
			if (j == _column) {}
			else t.push_back(matrix[i][j]);
		}
		tem.push_back(t);
	}
	column += 1;
	matrix = tem;
}
int Matrix::getcolumn()
{
	return column;
}
int Matrix::getRow()
{
	return row;
}
std::string Matrix::getName()
{
	return name;
}
Matrix Matrix::operator+(const Matrix & _matrix)
{
	if (row != _matrix.row || column != _matrix.column)
		throw myException(row_not_same);
	Matrix ans(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++) {
			ans.matrix[i][j] = matrix[i][j] + _matrix.matrix[i][j];
		}
	}
	return ans;
}
Matrix Matrix::operator-(const Matrix & _matrix)
{
	if (row != _matrix.row || column != _matrix.column)
		throw myException(row_not_same);
	Matrix ans(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++) {
			ans.matrix[i][j] = matrix[i][j] - _matrix.matrix[i][j];
		}
	}
	return ans;
}
Matrix Matrix::operator*(const Matrix & _matrix)
{
	if (column != _matrix.row)
		throw myException(row_and_col_not_same);
	Matrix ans(row, _matrix.column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < _matrix.column; j++) {
			//std::cout << ans.matrix[i][j] << std::endl;
			for (int k = 0; k < _matrix.row; k++)
			{
				//std::cout << matrix[i][k] << std::endl;
				//std::cout << _matrix.matrix[k][j] << std::endl;
				ans.matrix[i][j] += matrix[i][k] * _matrix.matrix[k][j];
				//std::cout << matrix[i][j] << std::endl;
			}
		}
	}
	//std::cout << ans;
	return ans;
}
Matrix Matrix::operator*(const double & _Scalar)
{
	Matrix ans(*this);
	for (int i = 0; i < ans.row; i++)
	{
		for (int j = 0; j < ans.column; j++)
		{
			ans.matrix[i][j] *= _Scalar;
		}
	}
	return ans;
}
Matrix Matrix::operator/(const double & _Scalar)
{
	if (_Scalar == 0)
		throw myException(denominator_is_zero);
	Matrix ans(*this);
	for (int i = 0; i < ans.row; i++)
	{
		for (int J = 0; J < ans.column; J++)
		{
			ans.matrix[i][J] /= _Scalar;
		}
	}
	return ans;
}
Matrix Matrix::operator=(const Matrix & _matrix)
{
	name = _matrix.name;
	row = _matrix.row;
	column = _matrix.column;
	matrix = _matrix.matrix;
	return *this;
}
Matrix Matrix::operator^(const double & _Scalar)
{
	if (column != row)
		throw myException(row_and_col_not_same);
	if (_Scalar == 1)
	{
		Matrix ans(row, column);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++) {
				if (j == i)ans.matrix[i][j] = 1;
				else matrix[i][j] = 0;
			}
		}
		return ans;
	}
	else {
		Matrix ans(row, column);
		Matrix tem = *this;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++) {
				if (j == i)ans.matrix[i][j] = 1;
				else matrix[i][j] = 0;
			}
		}
		for (int i = 0; i < _Scalar; i++)
		{
			ans = ans * tem;
		}
		return ans;
	}
}
Matrix Matrix::Transpose()
{
	Matrix ans;
	//cout << *this << endl;
	//cout << "-----------------" << endl;
	for (int i = 0; i < column; i++)
	{
		std::vector<double>tem;
		for (int j = 0; j < row; j++)
		{
			tem.push_back(this->matrix[j][i]);
		}
		ans.matrix.push_back(tem);
	}
	//cout << ans << endl;
	//cout << "-----------------" << endl;
	int tem = column;
	ans.column = row;
	ans.row = tem;
	return  ans;

}
double Matrix::determinants()
{
	if (row != column)
		throw myException(row_and_col_not_same);
	Matrix tem(*this);
	if (tem.column == tem.row) {
		if (row == 1) return matrix[0][0];
		if (row == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		double Max_row, Max_column;//maxrow為最大數字的column值 column為最大排
		double tmp;     //交換用
		double sw;   //存中間值
		int sign = 0;//看變號
		int i = 0, j = 0, k = 0;

#pragma region 註解
		for (i = 0; i < tem.column - 1; i++) {
			Max_column = i;
			Max_row = tem.matrix[i][i];
			for (j = i + 1; j < tem.column; j++) {
				//cout << abs(Max_row) << "   " << abs(tem.mt[j].a[i]) << endl;
				if (abs(Max_row) < abs(tem.matrix[j][i])) {
					Max_row = tem.matrix[j][i];

					Max_column = j;
				}
			}
			if (abs(Max_row) < 0.000001) {
				return NULL;
			}
			if (Max_column != i)
			{
				sign++;
				for (j = i; j < tem.column; j++) {

					tmp = tem.matrix[i][j];

					tem.matrix[i][j] = tem.matrix[Max_column][j];

					tem.matrix[Max_column][j] = tmp;
				}
				//cout << tem << endl;
			}
			for (j = i + 1; j < tem.column; j++) {
				sw = tem.matrix[j][i] / tem.matrix[i][i];
				for (k = i; k < tem.column; k++)
					tem.matrix[j][k] = tem.matrix[j][k] - tem.matrix[i][k] * sw;
			}
			//cout << tem << endl;
			//cout<<"next"<<endl;
		}
#pragma endregion
		//int R = 0;
		//int C = 0;
		////file4 << "first" << R << "  " << C << "\n" << tem << "///////////////////////////////////////\n";
		//while (R < tem.row&&C < tem.column)
		//{
		//	/*	if (R == 2 && C == 2) {
		//			std::cout << "Dasd" << std::endl;
		//			std::cout << "Dsadasdasdsadsad\n";
		//			std::cout << tem.matrix[2][2] << std::endl;
		//		}*/

		//	if (std::abs(tem.matrix[R][C]) == 0 /*|| std::abs(tem.matrix[R][C])<=0.000001*/)// pivot不為0
		//	{

		//		bool all0 = true;
		//		//if (R + 1 == tem.row) break;
		//		for (int i = R + 1; i < tem.row; i++)
		//		{
		//			if (tem.matrix[i][C] != 0)
		//			{
		//				for (int j = 0; j < tem.column; j++)
		//				{
		//					double c = tem.matrix[i][j];
		//					tem.matrix[i][j] = tem.matrix[R][j];
		//					tem.matrix[R][j] = c;
		//				}
		//				sign++;
		//				all0 = false;
		//				//file4 << "change" << R << "  " << C << "\n" << tem << "///////////////////////////////////////\n";
		//				break;
		//			}
		//		}
		//		if (all0 == true)
		//		{
		//			C++;
		//		}
		//	}
		//	else {

		//		for (int y2reduce = R + 1; y2reduce < tem.row; y2reduce++)
		//		{
		//			double mother = tem.matrix[y2reduce][C] / tem.matrix[R][C];
		//			for (int x = C; x < tem.column; x++)
		//			{
		//				tem.matrix[y2reduce][x] -= tem.matrix[R][x] * mother;
		//				if (std::abs(tem.matrix[y2reduce][x]) <= 11e-6)
		//				{
		//					tem.matrix[y2reduce][x] = 0;
		//				}
		//			}
		//		}
		//		//file4 << R << "   " << C << "\n" << tem << "///////////////////////////////////////\n";
		//		R++;
		//		C++;

		//	}

		//}			//cout << tem << endl;
		double ans = 1;

		for (i = 0; i < this->column; i++)

			ans *= tem.matrix[i][i];

		if (sign % 2 == 0)
			return ans;
		else
			return ans * (-1);
	}
}
Matrix Matrix::adjoint()
{
	if (row != column)
		throw myException(row_and_col_not_same);
	Matrix ans(row, column);
	int NegatineOrPositive = 1;
	for (int i = 0; i < this->column; i++)
	{
		if (i % 2 == 0)  NegatineOrPositive = 1;
		else  NegatineOrPositive = 0;

		for (int j = 0; j < this->column; j++)
		{
			Matrix tempmt;
			for (int y = 0; y < row; y++)
			{
				std::vector<double>t;
				for (int x = 0; x < column; x++)
				{
					if (y == i || x == j) {
					}
					else
					{
						t.push_back(matrix[y][x]);
					}

				}
				if (t.size() != 0) {
					tempmt.matrix.push_back(t);
				}



			}
			tempmt.column = column - 1;
			tempmt.row = row - 1;
			//cout << tempmt << endl;
			//cout << "--------" << endl;
			if (NegatineOrPositive % 2 == 0)
				ans.matrix[i][j] = tempmt.determinants()*(-1);
			else
				ans.matrix[i][j] = tempmt.determinants()*(1);

			NegatineOrPositive++;

			//cout << ans << endl;
		}

	}
	//std::cout <<"ddd\n"<< ans;
	Matrix re = ans.Transpose();
	//std::cout << re;
	return 	re;
}
Matrix Matrix::Inverse()
{
	if (row != column)
		throw myException(row_and_col_not_same);
	Matrix tem(*this);
	Matrix d(tem.row, tem.column, 0);
	for (int i = 0; i < tem.row; i++)
	{
		d.matrix[i][i] = 1;
	}
	int R = 0;
	int C = 0;
	while (R < tem.row&&C < tem.column)
	{
		/*	if (R == 2 && C == 2) {
				std::cout << "Dasd" << std::endl;
				std::cout << "Dsadasdasdsadsad\n";
				std::cout << tem.matrix[2][2] << std::endl;
			}*/
			//std::cout << d;
		if (std::abs(tem.matrix[R][C]) == 0 /*|| std::abs(tem.matrix[R][C])<=0.000001*/)// pivot不為0
		{

			bool all0 = true;
			//if (R + 1 == tem.row) break;
			for (int i = R + 1; i < tem.row; i++)
			{
				if (tem.matrix[i][C] != 0)
				{
					for (int j = 0; j < tem.column; j++)
					{
						double c = tem.matrix[i][j];
						tem.matrix[i][j] = tem.matrix[R][j];
						tem.matrix[R][j] = c;
						///////////////////////
						double rer = d.matrix[i][j];
						d.matrix[i][j] = d.matrix[R][j];
						d.matrix[R][j] = rer;
					}
					all0 = false;
					break;
				}
			}
			if (all0 == true)
			{
				C++;
			}
		}
		else {


			for (int y2reduce = R + 1; y2reduce < tem.row; y2reduce++)
			{
				double mother = tem.matrix[y2reduce][C] / tem.matrix[R][C];
				for (int x = C; x < tem.column; x++)
				{
					tem.matrix[y2reduce][x] -= tem.matrix[R][x] * mother;

					if (std::abs(tem.matrix[y2reduce][x]) <= 11e-6)
					{
						tem.matrix[y2reduce][x] = 0;
					}

				}
				for (int x = 0; x < tem.column; x++)
				{
					d.matrix[y2reduce][x] -= d.matrix[R][x] * mother;
					if (std::abs(d.matrix[y2reduce][x]) <= 11e-6)
					{
						d.matrix[y2reduce][x] = 0;
					}
				}
			}
			R++;
			C++;

		}

	}

	//std::cout << d;
	bool detequal0 = false;
	for (int i = 0; i < tem.row; i++)
	{
		if (tem.matrix[i][i] == 0)
		{
			detequal0 = true;
			throw myException(det_is_zero);
		}
		else {
			double mother = tem.matrix[i][i];
			for (int j = 0; j < tem.column; j++) //那一行變成1
			{
				tem.matrix[i][j] /= mother;
				d.matrix[i][j] /= mother;
			}
		}
	}


	if (detequal0 == false)
	{
		for (int i = tem.row - 1; i >= 0; i--)
		{
			//std::cout << i << "變為1\n" << tem<<d ;
			for (int k = i - 1; k >= 0; k--)
			{
				double mother = tem.matrix[k][i];
				//std::cout << "mothyer " << mother << std::endl;
				for (int l = 0; l < tem.column; l++)
				{
					tem.matrix[k][l] -= mother * tem.matrix[i][l];
					d.matrix[k][l] -= mother * d.matrix[i][l];
					if (std::abs(tem.matrix[k][l]) <= 11e-6)
					{
						tem.matrix[k][l] = 0;
					}
					if (std::abs(d.matrix[k][l]) <= 11e-6)
					{
						d.matrix[k][l] = 0;
					}
				}
			}
			//std::cout << i << "做完\n" << tem<<d ;

		}


		//std::cout << tem;
		return d;
	}
#pragma region 原版
	//VectorSpace a(tem.row);
//for (int i = 0; i <tem.row; i++)
//{
//	a.changeNumInSpace(1,i);
////	std::cout << a;
//	re record=tem.linear_system(a);
//	for (int j = 0; j < tem.row; j++)
//	{
//		d.matrix[j][i] = record.B.getNumInSpace(j);
//	}
//}
//std::cout << d;

//std::cout <<"inverse 初始\n" <<ans;
//Matrix anss = ans.adjoint();
//std::cout <<"我的adj\n" <<ans;
/*double denomainater = this->determinants();
if (denomainater == 0) return anss;
else {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			anss.matrix[i][j] /= denomainater;
		}
	}
	return anss;
}*/
#pragma endregion
}
double Matrix::Rank()
{

	Matrix tem(*this);
	//std::cout << tem;
	tem = tem.Guass();

	//std::cout << "rank:"<< std::endl<<tem << std::endl;
	//std::cout <<"看"<<tem.column << " " << tem.row << std::endl;
	int rank = 0;
	for (int i = 0; i < tem.row; i++)
	{
		bool allzero = true;
		for (int j = 0; j < tem.column; j++)
		{

			//std::cout << "幹" << tem.matrix[i][j] << std::endl;


			if (std::abs(tem.matrix[i][j]) >= 1e-6) {
				/*allzero = false;*/
				rank++;
				break;
			}
		}

		if (rank >= tem.row || rank >= tem.column)
		{
			break;
		}
		//if (allzero==true)
		//{
		//  //rank--;
		//}
	}

	return rank;

}
Matrix Matrix::eigenMatrix(double a)
{
	Matrix ans(*this);
	//std::cout <<"第一"<< ans;
	for (int q = 0; q < row; q++)
	{

		ans.matrix[q][q] -= a;

	}
	//std::cout << ans;
	return ans;
}
re Matrix::linear_system(VectorSpace _vec)
{
	re A;
	if (row != _vec.getvectorsize())
		throw myException(row_and_col_not_same);

	Matrix tem(*this);
	double *a = new double[tem.row];
	for (int i = 0; i < tem.row; i++)
	{
		a[i] = _vec.getNumInSpace(i);
	}
	tem.addColumn(a, tem.row);
	tem = tem.Guass();
	//std::cout << tem;
	//std::string *variance = new std::string[tem.column];
	bool *variance = new bool[tem.column];
	double *variancenum = new double[tem.column];
	for (int i = 0; i < tem.column; i++)
	{
		variancenum[i] = 1;
		std::stringstream ss;
		ss << (i + 1);
		std::string t;
		ss >> t;
		//variance[i] = "x"+t;
		variance[i] = false;
		//cout << variance[i] << endl;
	}
	//		tem.column += 1;
	//		for (int i = 0; i < row; i++)
	//		{
	//			tem.matrix[i].push_back(-1 * _vec.getNumInSpace(i));
	//		}
	//		int nowColumn = 0;
	//		double mult = 0;
	//		for (int _row = 0; _row < tem.row; _row++)
	//		{
	//			//std::cout << "test\n" << tem;
	//			//std::cout << tem;
	//			//cout << _row << "   " << endl << tem;
	//			if (tem.matrix[_row][nowColumn] != 0)
	//			{
	//				for (int _column = nowColumn; _column < tem.row; _column++)
	//				{
	//					if (_column != _row) {
	//						mult = tem.matrix[_column][_row] / tem.matrix[_row][nowColumn];
	//
	//						for (int i = nowColumn; i < tem.column; i++)
	//						{
	//							tem.matrix[_column][i] -= mult * tem.matrix[_row][i];
	//							/*if (tem.matrix[_column][i] < 0.000001)
	//							{
	//								tem.matrix[_column][i] = 0;
	//							}*/
	//
	//						}
	//						//cout << mult << "  " << endl << tem;
	//					}
	//				}
	//				nowColumn++;
	//			}
	//			else
	//			{
	//				if (_row == tem.row - 1) break;
	//				bool allzero = true;
	//				bool istriangle = false;
	//				for (int _column = _row + 1; _column < tem.row; _column++)
	//				{
	//					if (_column == tem.row - 1) {
	//						if (tem.matrix[_column][_row] == 0)
	//						{
	//							istriangle = true;
	//						}
	//					}
	//					if (tem.matrix[_column][_row] != 0) { //row->nowcolumn?
	//						std::vector<double>change = tem.matrix[_column];
	//						tem.matrix[_column] = tem.matrix[_row];
	//						tem.matrix[_row] = change;
	//						allzero = false;
	//						break;
	//					}
	//				}
	//				if (allzero) {
	//					if (istriangle == false)
	//					{
	//						_row--;
	//						nowColumn++;
	//					}
	//				}
	//			}
	//		}
	//
	//
	//	/*	
	//		for (int i = 0; i < tem.row; i++)
	//		{
	//			for (int j = 0; j < tem.column; j++)
	//			{
	//				if (tem.matrix[i][j] <= 0.000001)
	//				{
	//					tem.matrix[i][j] = 0;
	//				}
	//			}
	//		}
	//*/
	//
	//
	//		//////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//
	//		//std::cout <<"test\n" <<tem;
	VectorSpace temvec(row);
	for (int i = 0; i < row; i++)
	{
		//cout << tem.matrix[i][tem.column - 1] << endl;
		temvec.changeNumInSpace(tem.matrix[i][tem.column - 1], i);
		tem.matrix[i].pop_back();
	}
	tem.column -= 1;
	//std::cout << "tem     " << std::endl<< temvec << std::endl;
	//std::cout << tem << std::endl;
	re ans;

	ans.up = false;

	//判斷是否有0列
	int R = tem.row - 1;
	int C = tem.column - 1;
	bool noans = false;
	for (int i = 0; i < tem.row; i++)
	{
		bool allzero = true;
		for (int j = 0; j < tem.column; j++)
		{
			if (tem.matrix[i][j] != 0)
			{
				//std::cout << tem.matrix[i][j] << "\n";
				if (std::abs(tem.matrix[i][j]) >= 1e-6)
				{
					allzero = false;
					break;
				}
				else {

				}

			}
		}
		if (allzero)
		{
			if (temvec.getNumInSpace(i) != 0) //00000->2
			{
				ans.up = true;
				ans.A = "線性對應無到有無解";
				throw myException(no_solution);
			}
			else
			{
				R--;

				if (tem.column == tem.row)//方陣
				{
					//variance[i] = true;
					variancenum[i] = 1;
				}
				else if (tem.column > tem.row)
				{
					for (int k = i + 1; k < column; k++)
					{
						//variance[k] = true;
						variancenum[k] = 1;
					}
				}
				else {
					//variance[i] = true;
					variancenum[i] = 1;
				}
				//tem.deleterow(i);
			}
		}

	}
	//做linearsystem
	for (int i = R; i >= 0; i--)
	{

		double mother = tem.matrix[i][i];
		if (mother == 0)
		{
			for (int z = R + 1; z < tem.column; z++)
			{
				mother = tem.matrix[R][z];
				if (mother != 0)
				{
					double kid = temvec.getNumInSpace(i);
					for (int j = z + 1; j <= C; j++)
					{
						kid -= variancenum[j] * tem.matrix[i][j];
					}
					if (variance[z])
					{
						if (variancenum[z] != (kid / mother))
						{
							ans.up = true;
							noans = true;
							ans.A = "無解";
							throw myException(no_solution);
						}
					}
					else {
						variance[z] = true;
						variancenum[z] = (kid / mother);
					}
					break;
				}
			}
		}
		else {
			double kid = temvec.getNumInSpace(i);
			for (int j = i + 1; j <= C; j++)
			{
				kid -= variancenum[j] * tem.matrix[i][j];
			}
			if (variance[i])
			{
				if (variancenum[i] != (kid / mother))
				{
					ans.up = true;
					noans = true;
					ans.A = "無解";
					throw myException(no_solution);
				}
			}
			else {
				variance[i] = true;
				variancenum[i] = (kid / mother);
			}
		}
	}
	//tem.rr(R, C, variancenum, variance, temvec, noans, ans);

	if (!noans)
	{
		for (int i = 0; i < column; i++)
		{
			ans.B.addNumInSpace(variancenum[i]);
		}

	}
	else {
		throw myException(no_solution);
	}

#pragma region 原版
	//if (tem.column == tem.row) //是否為方陣
//{
//	for (int i = tem.row - 1; i >= 0; i--)
//	{
//		if (temvec.getNumInSpace(i) != 0 && tem.matrix[i][i] == 0 && ans.up == false) //是否 有全0但是解不是0狀態
//		{
//			ans.up = true;
//			ans.A = "有理解不存在";
//			return ans;
//		}
//		else if (temvec.getNumInSpace(i) != 0 && tem.matrix[i][i] != 0) //正常有解
//		{
//			ans.up = false;
//			for (int j = tem.column-1; j > i; j--)
//			{
//				temvec.changeNumInSpace(temvec.getNumInSpace(i)-variancenum[j]*tem.matrix[i][j],i);
//			}
//			variancenum[i] = temvec.getNumInSpace(i) / tem.matrix[i][i];
//		}
//		else //無限多種可能解
//		{
//			ans.up = true;

//			std::string phrase="";
//			std::map<std::string, double> coefficent;
//			std::map<std::string, double>::iterator iter;
//			std::string text = "";
//			for (int j = tem.column - 1; j >i; j--)//處理問題
//			{
//				//字串分析
//				std::stringstream ss;
//				
//				
//					
//				for (int k = 0; k <variance[j].size(); k++)
//				{
//					/*iter = coefficent.find("c");
//					if (iter == coefficent.end()) {
//						coefficent.insert(std::pair<std::string, double>("c", 0));
//					}*/
//					if (variance[j][k] == 'x')//遇到x
//					{

//						ss.clear();
//						ss << text;
//						double _num=1;
//						ss >> _num;
//						std::string text_v ="";
//						while (variance[j][k]!=' '||variance[j][k]!='\0')
//						{
//							if (variance[j][k] == ' '|| variance[j][k] == '\0') break;
//							text_v += variance[j][k];
//							//cout << i << text_v << "|||||" << endl;
//							k++;
//							if (k == variance[j].size()) break;
//						}
//						//text_v += '\0';

//						/*for (int i = 1; i <text_v.size(); i++)
//						{
//							if (text_v[i]==32) {
//								text_v[i] = '\0';
//								break;
//							}
//						}*/
//						/*for (iter = coefficent.begin(); iter != coefficent.end(); iter++)
//						{
//							cout << iter->first << "|||" << iter->second << endl;
//						}*/
//					//	cout << i << text_v << "|||||" << endl;
//						iter = coefficent.find(text_v);

//						if (iter == coefficent.end()) {

//							coefficent.insert(std::pair<std::string, double>(text_v,tem.matrix[i][j]*_num));
//						}
//						else {
//							//cout << iter->second << endl;
//							double n =iter->second;
//							n+= tem.matrix[i][j] * _num;
//							iter->second = n;
//						}
//						
//						text.clear();
//					}
//					else if (variance[j][k] == 'c')//遇到+
//					{
//						ss << text;
//						double _num=1;
//						ss >> _num;
//						iter = coefficent.find("c");
//						if (iter == coefficent.end()) {
//							coefficent.insert(std::pair<std::string, double>("c", tem.matrix[i][j] * _num));
//						}
//						else {
//							iter->second += tem.matrix[i][j] * _num;
//						}
//						text.clear();
//					}
//					else
//					{
//						if (variance[j][k] == ' ' || variance[j][k] == '+') {}
//						else
//						{
//							text += variance[j][k];
//						}

//						
//					}
//				}
//				

//			

//			}
//			///////////////////////////
//			//移向
//			/*iter = coefficent.find("c");
//			if (iter == coefficent.end()) {
//				coefficent.insert(std::pair<std::string, double>("c",temvec.getNumInSpace(i)));
//			}
//			else {
//				iter->second += temvec.getNumInSpace(i);
//				std::cout << iter->second << std::endl;
//			}*/


//			if(tem.matrix[i][i]==0)
//			{ 
//				std::map<std::string, double>::iterator itrs;
//				std::string small="z99999999999";
//				int smallnum = 0;
//				int smllcof = 0;
//				std::string deletename = "";
//				for (iter = coefficent.begin(); iter != coefficent.end(); iter++)//找出最小的
//				{
//					if (iter->first != "c")
//					{
//						if (iter->first < small) {
//							small = iter->first;
//							deletename = iter->first;
//							itrs = iter;
//							std::string comp="";
//							for (int q = 1; q < iter->first.size(); q++)
//							{
//								comp += iter->first[q];
//							}
//							std::stringstream w;
//							w << comp;
//							w >> smallnum;
//							smllcof = iter->second;
//						}
//					}
//				}
//			
//				/*iter = coefficent.find("c");
//				if (iter == coefficent.end()) {
//					coefficent.insert(std::pair<std::string, double>("c", 0));
//				}*/
//			

//				for (iter = coefficent.begin(); iter != coefficent.end(); iter++)
//				{
//					if (iter->first != deletename) {
//						std::stringstream ss;
//						std::string into;
//						if (iter->first == "c") {
//							//std::cout << temvec.getNumInSpace(i) << std::endl;
//							double _num = (temvec.getNumInSpace(i) - iter->second) / smllcof;
//							ss << _num;
//							ss >> into;
//						}
//						else
//						{
//							double _num = iter->second*(-1) / smllcof;
//							ss << _num;
//							ss >> into;
//						}
//						phrase += into;
//						phrase += iter->first;
//						iter++;

//						if (iter == coefficent.end())
//						{
//							phrase += '\0';

//						}
//						else
//						{
//							
//								
//								phrase += " + ";
//							
//						}
//						iter--;
//					}
//				}

//				variance[smallnum-1] = phrase;
//				std::cout << variance[smallnum - 1] << std::endl;
//				/*for (int m = variance[smallnum-1].size(); m >=0; m--)
//				{
//					if (variance[smallnum - 1][m] == '+')
//					{

//					}
//				}*/
//				
//			}
//			else {

//				iter = coefficent.find("c");
//				if (iter == coefficent.end()) {
//					coefficent.insert(std::pair<std::string, double>("c", 0));
//				}

//				for (iter = coefficent.begin(); iter != coefficent.end(); iter++)
//				{
//					std::stringstream ss;
//					std::string into;
//					if (iter->first == "c") {
//						double _num = (temvec.getNumInSpace(i) - iter->second) / tem.matrix[i][i];
//						ss << _num;
//						ss >> into;
//					}
//					else
//					{
//						double _num = iter->second*(-1) / tem.matrix[i][i];
//						ss << _num;
//						ss >> into;
//					}
//					phrase += into;
//					phrase += iter->first;
//					iter++;
//					if (iter == coefficent.end())
//					{
//						phrase += '\0';

//					}
//					else
//						phrase += " + ";
//					iter--;
//				}

//				
//				variance[i] = phrase;
//			}
//		}
//		
//	





//	}

//	if (ans.up)
//	{
//		for (int i = 0; i < tem.row; i++)
//		{
//			for (int j = variance[i].size()-1; j >=0 ; j--)
//			{
//				bool anything = false;
//				while (1) {
//				//	std::cout << variance[i][j] << std::endl;
//					if ((variance[i][j] >= 48 & variance[i][j] <= 57) || variance[i][j] == 'c')
//					{
//						anything = true;
//						//variance[i][j + 1] = '\0';
//						for (int v = j+1; v <=variance[i].size() - 1; v++)
//						{
//							variance[i][v] = '\0';
//						}
//						break;
//					}
//					j--;
//				}
//				if (anything) {
//					break;
//				}
//			}
//			if (i == 0)
//			{
//				ans.A += "{ ";
//				ans.A +=variance[i];

//			}
//			else if (i + 1 == tem.row)
//			{
//				ans.A += " , ";
//				ans.A += variance[i];
//				ans.A += " }";
//			}
//			else
//			{
//				ans.A += " , ";
//				ans.A += variance[i];
//			}
//		}
//	}
//	else
//	{
//		for (int i = 0; i < tem.column; i++)
//		{
//			ans.B.addNumInSpace(variancenum[i]);
//		}
//	}


//}
//else
//{

//	for (int i = tem.row - 1; i >= 0; i--)
//	{
//		//check allrow
//		bool allzero = true;
//		for (int j = 0; j < tem.column; j++)
//		{
//			if (tem.matrix[i][j] != 0)
//			{
//				allzero = false;
//				break;
//			}
//		}
//		

//			if (allzero) {
//				ans.up = true;
//				ans.A = "有理解不存在";
//				return ans; 
//			}
//			else //無限多種可能解
//			{
//				ans.up = true;

//				std::string phrase = "";
//				std::map<std::string, double> coefficent;
//				std::map<std::string, double>::iterator iter;
//				std::string text = "";
//				for (int j = tem.column - 1; j > i; j--)//處理問題
//				{
//					//字串分析
//					std::stringstream ss;

//					//std::cout <<j<<" "<<variance[j] << std::endl;

//					for (int k = 0; k < variance[j].size(); k++)
//					{
//						
//						iter = coefficent.find("c");
//						if (iter == coefficent.end()) {
//							coefficent.insert(std::pair<std::string, double>("c", 0));
//						}

//						if (variance[j][k] == 'x')//遇到x
//						{
//							ss.clear();
//							//ss.str ="";
//							//std::cout << text << std::endl;
//							ss << text;
//							double _num = 1;
//							ss >> _num;
//							//std::cout << _num << std::endl;
//							std::string text_v = "";
//							while (variance[j][k] != ' ' || variance[j][k] != '\0')
//							{
//								if (variance[j][k] == ' ' || variance[j][k] == '\0') break;
//								text_v += variance[j][k];
//								//cout << i << text_v << "|||||" << endl;
//								k++;
//								if (k == variance[j].size()) break;
//							}
//							//text_v += '\0';

//							/*for (int i = 1; i <text_v.size(); i++)
//							{
//								if (text_v[i]==32) {
//									text_v[i] = '\0';
//									break;
//								}
//							}*/
//							/*for (iter = coefficent.begin(); iter != coefficent.end(); iter++)
//							{
//								cout << iter->first << "|||" << iter->second << endl;
//							}*/
//							//	cout << i << text_v << "|||||" << endl;
//							iter = coefficent.find(text_v);

//							if (iter == coefficent.end()) {

//								coefficent.insert(std::pair<std::string, double>(text_v, tem.matrix[i][j] * _num));
//							}
//							else {
//							//	std::cout<<"     "<<iter->first<<"   " <<iter->second<< std::endl;
//								//std::cout << j << " " << variance[j] << std::endl;
//								double n = iter->second;
//							//	std::cout <<  _num <<std::endl;
//								n += tem.matrix[i][j] * _num;
//								iter->second = n;
//								
//							}

//							text.clear();
//						}
//						else if (variance[j][k] == 'c')//遇到+
//						{
//							ss << text;
//							double _num = 1;
//							ss >> _num;
//							iter = coefficent.find("c");
//							if (iter == coefficent.end()) {
//								coefficent.insert(std::pair<std::string, double>("c", tem.matrix[i][j] * _num));
//							}
//							else {
//								iter->second += tem.matrix[i][j] * _num;
//							}
//							text.clear();
//						}
//						else
//						{
//							if (variance[j][k] == ' ' || variance[j][k] == '+') {}
//							else
//							{
//								text += variance[j][k];
//							}


//						}
//					}




//				}
//				///////////////////////////
//				//移向
//				/*iter = coefficent.find("c");
//				if (iter == coefficent.end()) {
//					coefficent.insert(std::pair<std::string, double>("c",temvec.getNumInSpace(i)));
//				}
//				else {
//					iter->second += temvec.getNumInSpace(i);
//					std::cout << iter->second << std::endl;
//				}*/


//				if (tem.matrix[i][i] == 0)
//				{
//					std::map<std::string, double>::iterator itrs;
//					std::string small = "z99999999999";
//					int smallnum = 0;
//					int smllcof = 0;
//					std::string deletename = "";
//					for (iter = coefficent.begin(); iter != coefficent.end(); iter++)//找出最小的
//					{
//						if (iter->first != "c")
//						{
//							if (iter->first < small) {
//								small = iter->first;
//								deletename = iter->first;
//								itrs = iter;
//								std::string comp = "";
//								for (int q = 1; q < iter->first.size(); q++)
//								{
//									comp += iter->first[q];
//								}
//								std::stringstream w;
//								w << comp;
//								w >> smallnum;
//								smllcof = iter->second;
//							}
//						}
//					}

//					iter = coefficent.find("c");
//					if (iter == coefficent.end()) {
//						coefficent.insert(std::pair<std::string, double>("c", 0));
//					}


//					for (iter = coefficent.begin(); iter != coefficent.end(); iter++)
//					{
//						if (iter->first != deletename) {
//							std::stringstream ss;
//							std::string into;
//							if (iter->first == "c") {
//								//std::cout << temvec.getNumInSpace(i) << std::endl;
//								double _num = (temvec.getNumInSpace(i) - iter->second) / smllcof;
//								ss << _num;
//								ss >> into;
//							}
//							else
//							{
//								double _num = iter->second*(-1) / smllcof;
//								ss << _num;
//								ss >> into;
//							}
//							phrase += into;
//							phrase += iter->first;
//							iter++;

//							if (iter == coefficent.end())
//							{
//								phrase += '\0';

//							}
//							else
//							{


//								phrase += " + ";

//							}
//							iter--;
//						}
//					}

//					variance[smallnum - 1] = phrase;

//					/*for (int m = variance[smallnum-1].size(); m >=0; m--)
//					{
//						if (variance[smallnum - 1][m] == '+')
//						{

//						}
//					}*/

//				}
//				else {
//					iter = coefficent.find("c");
//					if (iter == coefficent.end()) {
//						coefficent.insert(std::pair<std::string, double>("c", 0));
//					}

//					for (iter = coefficent.begin(); iter != coefficent.end(); iter++)
//					{
//						std::stringstream ss;
//						std::string into;
//						if (iter->first == "c") {
//							double _num = (temvec.getNumInSpace(i) - iter->second) / tem.matrix[i][i];
//							ss << _num;
//							ss >> into;
//						}
//						else
//						{
//							//std::cout<< iter->first << "    :    "<<iter->second<< std::endl;
//							//std::cout << iter->first << std::endl;
//							double _num = iter->second*(-1) / tem.matrix[i][i];
//							ss << _num;
//							ss >> into;
//						}
//						
//						phrase += into;
//						phrase += iter->first;
//						iter++;
//						if (iter == coefficent.end())
//						{
//							phrase += '\0';

//						}
//						else
//							phrase += " + ";
//						iter--;
//					}

//					variance[i] = phrase;
//				}
//			}
//		
//	}
//	if (ans.up)
//	{
//		for (int i = 0; i < tem.column; i++)
//		{
//			for (int j = variance[i].size() - 1; j >= 0; j--)
//			{
//				bool anything = false;
//				while (1) {
//					//	std::cout << variance[i][j] << std::endl;
//					if ((variance[i][j] >= 48 & variance[i][j] <= 57) || variance[i][j] == 'c')
//					{
//						anything = true;
//						//variance[i][j + 1] = '\0';
//						for (int v = j + 1; v <= variance[i].size() - 1; v++)
//						{
//							variance[i][v] = '\0';
//						}
//						break;
//					}
//					j--;
//				}
//				if (anything) {
//					break;
//				}
//			}
//			if (i == 0)
//			{
//				ans.A += "{ ";
//				ans.A += variance[i];

//			}
//			else if (i + 1 == tem.column)
//			{
//				ans.A += " , ";
//				ans.A += variance[i];
//				ans.A += " }";
//			}
//			else
//			{
//				ans.A += " , ";
//				ans.A += variance[i];
//			}
//		}
//	}
//	else
//	{
//		for (int i = 0; i < tem.column; i++)
//		{
//			ans.B.addNumInSpace(variancenum[i]);
//		}
//	}

//}

#pragma endregion
	return ans;
}

void Matrix::rr(int R, int C, double *variancenum, bool *variance, VectorSpace temvec, bool noans, re ans)
{
	Matrix tem(*this);
	if (R < 0)return;
	if (R >= tem.row) return;
	double mother = tem.matrix[R][R];
	if (mother == 0)
	{
		return tem.rr(R + 1, C, variancenum, variance, temvec, noans, ans);
	}
	else {
		double kid = temvec.getNumInSpace(R);
		for (int j = R + 1; j <= C; j++)
		{
			kid -= variancenum[j] * tem.matrix[R][j];
		}
		if (variance[R])
		{
			if (variancenum[R] != (kid / mother))
			{
				ans.up = true;
				noans = true;
				ans.A = "無解";
				throw myException(no_solution);
			}
		}
		else {
			variance[R] = true;
			variancenum[R] = (kid / mother);
		}
	}
	return tem.rr(R - 1, C, variancenum, variance, temvec, noans, ans);
}

std::map<double, re> Matrix::eigenvalueAndeigenvectorUnder3()
{


	if (row != column)
		throw myException(not_square_matrix);
	else if (row > 3)
		throw myException(not_power_method);
	if (row == 2) {
		std::map<double, re>ans;
		std::map<double, re>::iterator it;
		VectorSpace vec(2);
		if (((matrix[0][0] + matrix[1][1])*(matrix[0][0] + matrix[1][1]) - 4 * (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0])) < 0)
			throw myException(complex_error);
		double x1 = ((matrix[0][0] + matrix[1][1]) + sqrt((matrix[0][0] + matrix[1][1])*(matrix[0][0] + matrix[1][1]) - 4 * (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]))) / 2;
		double x2 = ((matrix[0][0] + matrix[1][1]) - sqrt((matrix[0][0] + matrix[1][1])*(matrix[0][0] + matrix[1][1]) - 4 * (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]))) / 2;
		Matrix tem(*this);
		Matrix a;
		a = tem.eigenMatrix(x1);
		re first = a.linear_system(vec);
		it = ans.find(x1);
		if (it == ans.end()) {
			ans.insert(std::pair<double, re>(x1, first));
		}
		a = tem.eigenMatrix(x2);
		re two = a.linear_system(vec);
		it = ans.find(x2);
		if (it == ans.end()) {
			ans.insert(std::pair<double, re>(x2, two));
		}
		return ans;
	}
	else
	{
		/*double p1 = 1;
		double p2 = -1*(matrix[0][0] + matrix[1][1] + matrix[2][2]);
		double p3 =  -1*(matrix[2][0]* matrix[0][1]- matrix[1][2]* matrix[2][1]+ matrix[0][1] * matrix[1][0]- matrix[0][0] * matrix[1][1]- matrix[1][1] * matrix[2][2]- matrix[0][0] * matrix[2][2]);
		double p4 = -1*(matrix[0][1] * matrix[1][2] * matrix[2][0] -
					matrix[0][1] * matrix[1][1] * matrix[2][0] +
					matrix[0][0] * matrix[1][2] * matrix[2][1] -
					matrix[0][2] * matrix[1][0] * matrix[2][1]+
			matrix[0][0] * matrix[1][1] * matrix[2][2]-
			matrix[0][1] * matrix[1][0] * matrix[2][2]);*/
		double p1 = 1;
		double p2 = -1 * (matrix[0][0] + matrix[1][1] + matrix[2][2]);
		double p3 = (matrix[0][0] * matrix[2][2] + matrix[1][1] * matrix[2][2] + matrix[0][0] * matrix[1][1] - matrix[0][2] * matrix[2][0] - matrix[0][1] * matrix[1][0] - matrix[1][2] * matrix[2][1]);
		/*double p4 = -1 * (matrix[0][0] * matrix[1][1] * matrix[2][2] -
			matrix[0][2] * matrix[1][1] * matrix[2][0] -
			matrix[0][1] * matrix[1][0] * matrix[2][2] -
			matrix[0][0] * matrix[1][2] * matrix[2][1]);*/
		double p4 = -1 * (matrix[0][0] * matrix[1][1] * matrix[2][2] +
			matrix[0][1] * matrix[1][2] * matrix[2][0] +
			matrix[0][2] * matrix[1][0] * matrix[2][1] -
			matrix[0][2] * matrix[1][1] * matrix[2][0] -
			matrix[0][1] * matrix[1][0] * matrix[2][2] -
			matrix[0][0] * matrix[1][2] * matrix[2][1]
			);
		std::cout << p1 << "\n" << p2 << "\n" << p3 << "\n" << p4 << "\n";
		double A = p2 * p2 - 3 * p1*p3;
		double B = p2 * p3 - 9 * p1*p4;
		double C = p3 * p3 - 3 * p2*p4;
		double judge = B * B - 4 * A*C;
		if (judge > 0) throw myException(complex_error);
		else
		{

			double Q = (p2*p2 - 3 * p3) / 9;
			double R = (2 * p2*p2*p2 - 9 * p3*p2 + 27 * p4) / 54;
			double theata = RadtoAng(acos(R / sqrt(Q*Q*Q)));
			double a1 = theata + 360;
			a1 /= 3;
			double a2 = theata - 360;
			a2 /= 3;
			double x1 = -2 * sqrt(Q)*cos(AngtoRad(theata / 3)) - p2 / 3;
			double x2 = -2 * sqrt(Q)*cos(AngtoRad(a1)) - p2 / 3;
			double x3 = -2 * sqrt(Q)*cos(AngtoRad(a2)) - p2 / 3;
			Matrix tem(*this);
			Matrix a;
			std::map<double, re>ans;
			std::map<double, re>::iterator it;
			VectorSpace vec(3);
			a = tem.eigenMatrix(x1);
			re first = a.linear_system(vec);
			it = ans.find(x1);
			if (it == ans.end()) {
				ans.insert(std::pair<double, re>(x1, first));
			}
			////
			a = tem.eigenMatrix(x2);
			re Two = a.linear_system(vec);
			it = ans.find(x2);
			if (it == ans.end()) {
				ans.insert(std::pair<double, re>(x2, Two));
			}
			////
			a = tem.eigenMatrix(x3);
			re Two2 = a.linear_system(vec);
			it = ans.find(x3);
			if (it == ans.end()) {
				ans.insert(std::pair<double, re>(x3, Two2));
			}
			return ans;
		}
	}
}
std::map<double, re> Matrix::powerMethod()
{

	if (row != column)
		throw myException(not_square_matrix);
	Matrix tefm(column, 1, 1);
	Matrix t(*this);
	//std::cout << tefm << t;
	Matrix X = t * tefm;
	Matrix X2 = t * X;
	//std::cout << X2 << "////////////////////\n";
	while (!(X2.juge(X)))
	{
		//std::cout << "dasdasd\n" << X;
		X = X2;
		X2 = t * X2;
		for (int i = 0; i < X2.column; i++)
		{
			double as = X2.getnuminMatrix(0, i);

			for (int j = 0; j < X2.row; j++)
			{
				double _num = X2.getnuminMatrix(j, i) / as;
				//std::cout << "qw" <<_num << std::endl;
				X2.replaceNuminMatrix(j, i, _num);

			}
		}
		//std::cout << X2<<"////////////////////\n";
	}
	//std::cout <<"dasdasd\n"<< X2;
	//for (int i = 0; i < X2.column; i++)
	//{
	//	double as= X2.getnuminMatrix(0, i);
	//	
	//	for (int j = 0; j < X2.row; j++)
	//	{
	//		double _num =X2.getnuminMatrix(j, i) / as;
	//		//std::cout << "qw" <<_num << std::endl;
	//		X2.replaceNuminMatrix(j, i, _num);
	//		
	//	}
	//}
	//std::cout <<"dasdasd\n"<< X2;
	re first;
	Matrix tem(*this);
	first.up = false;
	VectorSpace anss;
	for (int i = 0; i < X2.row; i++)
	{
		for (int j = 0; j <= 0; j++)
		{
			anss.addNumInSpace(X2.matrix[i][j]);
		}
	}
	first.B = anss;
	Matrix p = X2.Transpose();
	Matrix pp = (t*X2);
	Matrix l = pp.Transpose();
	Matrix ans1 = l * X2;
	Matrix ans2 = p * X2;
	double ans = ans1.getnuminMatrix(0, 0) / ans2.getnuminMatrix(0, 0);

	/*Matrix a;
	a = tem.eigenMatrix(ans);
	VectorSpace vec(row);*/

	std::map<double, re>an;
	std::map<double, re>::iterator it;
	it = an.find(ans);
	if (it == an.end()) {
		an.insert(std::pair<double, re>(ans, first));
	}
	return an;
}
Matrix Matrix::Guass()
{
	Matrix tem(*this);
	/*std::fstream file4;
	file4.open("ans.txt", std::ios::out);*/
#pragma region 註解
	//int nowColumn = 0;//現在column
//int whererow = 0;//現在row
//double mult = 0;
//file4 << "處使" << nowColumn << "\n" << tem << "///////////////////////////////////////\n";
//for (int _row = 0; _row < tem.row; _row++)
//{
//	
//	//std::cout << _row << "\n" << tem;
//	//cout << _row << "   " << endl << tem;
//	if (tem.matrix[whererow][nowColumn] != 0) //判斷每次做高斯的第一個是否為0
//	{
//		//std::cout << tem.matrix[_row][nowColumn] << std::endl;
//		//std::cout << nowColumn << "&" << _row << std::endl;
//		for (int _row2 = whererow+1; _row2 < tem.row; _row2++)
//		{
//		
//			if (_row2 !=whererow)
//			{
//				mult = (tem.matrix[_row2][nowColumn] / tem.matrix[whererow][nowColumn]);
//				//std::cout << mult << "  " << std::endl;
//				for (int i = nowColumn; i < tem.column; i++)
//				{
//					tem.matrix[_row2][i] -= mult * tem.matrix[whererow][i];
//				/*	if (tem.matrix[_row2][i] <=1e-14|| tem.matrix[_row2][i] == -0.00)
//					{
//						tem.matrix[_row2][i] = 0;
//					}*/

//				}
//				//std::cout << mult << "  " << std::endl ;
//			}

//		}
//		file4 << _row << nowColumn << "\n" << tem << "///////////////////////////////////////\n";

//		nowColumn++;
//		whererow++;
//	}
//	else
//	{
//		//std::cout << "hhh\n";
//		if (_row == tem.row - 1) break;
//		bool allzero = true;
//		bool istriangle = false;
//		//std::cout << tem.matrix[_row][nowColumn] << std::endl;
//		for (int y = _row + 1; y < tem.row; y++)
//		{
//			if (y == tem.row - 1) {
//				if (tem.matrix[y][_row] == 0)
//				{
//					istriangle = true;
//				}
//			}
//			if (tem.matrix[y][nowColumn] != 0) { //row->nowcolumn?
//				/*std::cout << tem.matrix[y][_row] << std::endl;*/
//				for (int i = 0; i < tem.column; i++)
//				{
//					double change = tem.matrix[y][i];
//					tem.matrix[y][i] = tem.matrix[_row][i];
//					tem.matrix[_row][i] = change;
//				}
//				/*std::vector<double>change = tem.matrix[y];
//				
//				tem.matrix[y] = tem.matrix[_row];
//				tem.matrix[_row] = change;*/
//				allzero = false;
//				file4 << "change"<<_row<<"  " << nowColumn << "\n" << tem << "///////////////////////////////////////\n";
//				//std::cout << "caheck"<<" "<<nowColumn<<" "<<_row<<"\n";
//				_row--;
//				break;

//			}
//		}
//		if (allzero) {
//			if (istriangle == false)
//			{
//				//std::cout << "hhh\n";
//				_row--;
//				nowColumn++;
//			}
//		}
//	}
//	//std::cout << "asdasd\n";

//}
//std::cout << "over\n";  
#pragma endregion


	int R = 0;
	int C = 0;
	//file4 << "first" << R << "  " << C << "\n" << tem << "///////////////////////////////////////\n";
	while (R < tem.row&&C < tem.column)
	{
		/*	if (R == 2 && C == 2) {
				std::cout << "Dasd" << std::endl;
				std::cout << "Dsadasdasdsadsad\n";
				std::cout << tem.matrix[2][2] << std::endl;
			}*/

		if (std::abs(tem.matrix[R][C]) == 0 /*|| std::abs(tem.matrix[R][C])<=0.000001*/)// pivot不為0
		{

			bool all0 = true;
			//if (R + 1 == tem.row) break;
			for (int i = R + 1; i < tem.row; i++)
			{
				if (tem.matrix[i][C] != 0)
				{
					for (int j = 0; j < tem.column; j++)
					{
						double c = tem.matrix[i][j];
						tem.matrix[i][j] = tem.matrix[R][j];
						tem.matrix[R][j] = c;
					}
					all0 = false;
					//file4 << "change" << R << "  " << C << "\n" << tem << "///////////////////////////////////////\n";
					break;
				}
			}
			if (all0 == true)
			{
				C++;
			}
		}
		else {

			for (int y2reduce = R + 1; y2reduce < tem.row; y2reduce++)
			{
				double mother = tem.matrix[y2reduce][C] / tem.matrix[R][C];
				for (int x = C; x < tem.column; x++)
				{
					tem.matrix[y2reduce][x] -= tem.matrix[R][x] * mother;
					if (std::abs(tem.matrix[y2reduce][x]) <= 11e-6)
					{
						tem.matrix[y2reduce][x] = 0;
					}
				}
			}
			//file4 << R <<"   " <<C << "\n" << tem << "///////////////////////////////////////\n";
			R++;
			C++;

		}

	}






	return tem;
}

double Matrix::matrixToDouble()
{
	return matrix[0][0];
}

Matrix Matrix::leastSquare(Matrix a)
{
	/*std::fstream file4;
	file4.open("ans.txt", std::ios::out);*/
	Matrix tem(*this);
	Matrix temT = tem.Transpose();
	//std::cout << temT;
	Matrix T = temT * tem;
	//std::cout << T.column<<" "<<T.row<<"\n";
	//std::cout << T;
	Matrix tinverse = T.Inverse();
	//file4 << tinverse;
	//std::cout << "dasdasd\n";
	//T = T.Inverse();
	//std::cout << tinverse ;
	//std::cout << T;
	//std::cout << temT;
	Matrix X = tinverse * temT;
	//file4 << X;
   //std::cout << X;
   //std::cout << a;
	Matrix ans = X * a;

	/* file4 << X;
	 file4<<a;*/
	 //std::cout <<"dsadsad\n" <<ans;
	return ans;

}

bool Matrix::juge(Matrix b)
{
	Matrix tem(*this);
	Matrix tem2(b);
	//std::cout << "tem\n" << tem;
	//std::cout << "tem2\n" << tem2;
	for (int i = 0; i < column; i++)
	{
		double as = tem.getnuminMatrix(0, i);
		double as2 = tem2.getnuminMatrix(0, i);
		for (int j = 0; j < row; j++)
		{
			double _num = tem.getnuminMatrix(j, i) / as;
			//std::cout << "qw" <<_num << std::endl;
			tem.replaceNuminMatrix(j, i, _num);
			_num = tem2.getnuminMatrix(j, i) / as2;
			tem2.replaceNuminMatrix(j, i, _num);
		}
	}
	bool rrr = true;
	/*std::cout <<"tem\n" <<tem;
	std::cout <<"tem2\n" << tem2;*/
	Matrix ans = tem - tem2;

	for (int i = 0; i < column; i++)
	{
		if (std::abs(ans.getnuminMatrix(row - 1, i)) > 1e-6)
		{
			rrr = false;
			break;

		}
	}


	return rrr;
}
std::ostream & operator<<(std::ostream & os, const Matrix &A)
{
	for (int i = 0; i < A.row; i++)
	{
		for (int j = 0; j < A.column; j++) {
			if (j == A.column - 1) os << std::left << std::setw(10) << std::fixed << std::setprecision(6) << A.matrix[i][j];
			else os << std::left << std::setw(10) << std::fixed << std::setprecision(6) << A.matrix[i][j] << "\t";
		}
		os << "\r\n";
	}
	os << "\r\n";
	return os;
}

bool Linear_independent(std::vector<VectorSpace> _vec)
{
	Matrix tem("tem", _vec.size(), _vec[0].getvectorsize(), _vec);
	tem = tem.Guass();
	////cout << tem;
	//int nowColumn = 0;
	//double mult = 0;
	//for (int _row = 0; _row < tem.getRow(); _row++)
	//{
	//	//cout << _row << "   " << endl << tem;
	//	if (tem.getnuminMatrix(_row,nowColumn) != 0)
	//	{
	//		for (int _column = nowColumn; _column < tem.getRow(); _column++)
	//		{
	//			if (_column != _row) {
	//				mult = tem.getnuminMatrix(_column,_row) / tem.getnuminMatrix(_row, nowColumn);

	//				for (int i = nowColumn; i < tem.getcolumn(); i++)
	//				{
	//					
	//					tem.replaceNuminMatrix(_column, i, tem.getnuminMatrix(_column,i) - mult*tem.getnuminMatrix(_row, i));

	//				}
	//				//cout << mult << "  " << endl << tem;
	//			}
	//		}
	//		nowColumn++;
	//	}
	//	else
	//	{
	//		if (_row == tem.getRow() - 1) break;
	//		bool allzero = true;
	//		bool istriangle = false;
	//		for (int _column = _row + 1; _column < tem.getRow(); _column++)
	//		{
	//			if (_column == tem.getRow() - 1) {
	//				if (tem.getnuminMatrix(_column,_row) == 0)
	//				{
	//					istriangle = true;
	//				}
	//			}
	//			if (tem.getnuminMatrix(_column, _row) != 0) { //row->nowcolumn?
	//				std::vector<double>change;
	//				for (int i = 0; i <tem.getcolumn(); i++)
	//				{
	//					change.push_back(tem.getnuminMatrix(_column, i));
	//				}
	//				
	//				for (int i = 0; i < tem.getcolumn(); i++)
	//				{
	//					//change.push_back(tem.getnuminMatrix(_column, i));
	//					tem.replaceNuminMatrix(_column, i,tem.getnuminMatrix(_row, i));
	//				}
	//				for (int i = 0; i < tem.getcolumn(); i++)
	//				{
	//					//change.push_back(tem.getnuminMatrix(_column, i));
	//					tem.replaceNuminMatrix(_row, i, change[i]);
	//				}
	//				//tem.matrix[_column] = tem.matrix[_row];
	//				//tem.matrix[_row] = change;
	//				allzero = false;
	//				break;
	//			}
	//		}
	//		if (allzero) {
	//			if (istriangle == false)
	//			{
	//				_row--;
	//				nowColumn++;
	//			}
	//		}
	//	}
	//}

	//cout << tem << endl;
	/*有0列代表可以組合出為ld 否則li*/
	bool ans = true;
	for (int i = 0; i < tem.getRow(); i++)
	{
		bool allzero = true;
		for (int j = 0; j < tem.getcolumn(); j++)
		{
			if (tem.getnuminMatrix(i, j) != 0) {
				allzero = false;
				break;
			}
		}

		if (allzero == true)
		{
			ans = false;
			break;
		}

	}
	//cout << tem;
	return ans;
}

bool Linear_independent(int howmany, VectorSpace *_vec)
{
	std::string nm = "name";
	int m = _vec[0].getvectorsize();
	Matrix tem(howmany, m, *_vec);
	tem = tem.Guass();
	////cout << tem;
	//int nowColumn = 0;
	//double mult = 0;
	//for (int _row = 0; _row < tem.getRow(); _row++)
	//{
	//	//cout << _row << "   " << endl << tem;
	//	if (tem.getnuminMatrix(_row, nowColumn) != 0)
	//	{
	//		for (int _column = nowColumn; _column < tem.getRow(); _column++)
	//		{
	//			if (_column != _row) {
	//				mult = tem.getnuminMatrix(_column, _row) / tem.getnuminMatrix(_row, nowColumn);

	//				for (int i = nowColumn; i < tem.getcolumn(); i++)
	//				{

	//					tem.replaceNuminMatrix(_column, i, tem.getnuminMatrix(_column, i) - mult * tem.getnuminMatrix(_row, i));

	//				}
	//				//cout << mult << "  " << endl << tem;
	//			}
	//		}
	//		nowColumn++;
	//	}
	//	else
	//	{
	//		if (_row == tem.getRow() - 1) break;
	//		bool allzero = true;
	//		bool istriangle = false;
	//		for (int _column = _row + 1; _column < tem.getRow(); _column++)
	//		{
	//			if (_column == tem.getRow() - 1) {
	//				if (tem.getnuminMatrix(_column, _row) == 0)
	//				{
	//					istriangle = true;
	//				}
	//			}
	//			if (tem.getnuminMatrix(_column, _row) != 0) { //row->nowcolumn?
	//				std::vector<double>change;
	//				for (int i = 0; i < tem.getcolumn(); i++)
	//				{
	//					change.push_back(tem.getnuminMatrix(_column, i));
	//				}

	//				for (int i = 0; i < tem.getcolumn(); i++)
	//				{
	//					//change.push_back(tem.getnuminMatrix(_column, i));
	//					tem.replaceNuminMatrix(_column, i, tem.getnuminMatrix(_row, i));
	//				}
	//				for (int i = 0; i < tem.getcolumn(); i++)
	//				{
	//					//change.push_back(tem.getnuminMatrix(_column, i));
	//					tem.replaceNuminMatrix(_row, i, change[i]);
	//				}
	//				//tem.matrix[_column] = tem.matrix[_row];
	//				//tem.matrix[_row] = change;
	//				allzero = false;
	//				break;
	//			}
	//		}
	//		if (allzero) {
	//			if (istriangle == false)
	//			{
	//				_row--;
	//				nowColumn++;
	//			}
	//		}
	//	}
	//}

	//cout << tem << endl;
	/*有0列代表可以組合出為ld 否則li*/
	bool ans = true;
	for (int i = 0; i < tem.getRow(); i++)
	{
		bool allzero = true;
		for (int j = 0; j < tem.getcolumn(); j++)
		{
			if (tem.getnuminMatrix(i, j) != 0) {
				allzero = false;
				break;
			}
		}

		if (allzero == true)
		{
			ans = false;
			break;
		}

	}
	//cout << tem;
	return ans;
}

//std::string leastSquare(std::vector<VectorSpace> _vec)
//{
//	//X  = (A^(T)A)^(-1)A^(T)Y 
//	Matrix tem("tem", _vec.size(), _vec[0].getvectorsize(), _vec);
//	//std::cout << tem;
//	
//	Matrix fx(tem.getRow(),1);
//
//	//std::cout << fx;
//	for (int i = 0; i < tem.getRow(); i++)
//	{
//		fx.replaceNuminMatrix(i,0, tem.getnuminMatrix(i,tem.getcolumn()-1));
//		tem.replaceNuminMatrix(i, tem.getcolumn() - 1,1);
//	}
//	//std::cout << tem;
//	//std::cout << fx;
//	Matrix temT = tem.Transpose();
//	
//	Matrix T = temT * tem;
//	//std::cout << T;
//	T = T.Inverse();
//	//std::cout << T;
//	//std::cout << temT;
//	Matrix X = T * temT;
//	//std::cout << X;
//	//std::cout << fx;
//	X = X * fx;
//	//std::cout << X;
//	std::string ans = "y = ";
//	for (int i = 0; i <X.getRow(); i++)
//	{
//		std::stringstream ss;
//		std::string record;
//		ss<< X.getnuminMatrix(i, 0);
//		ss >> record;
//		ss.clear();
//		ss.str("");
//		ans += record;
//		if (i + 1 != X.getRow())
//		{
//			ss << (i + 1);
//			ss >> record;
//			ans += 'x';
//			ans += record;
//			ans += " + ";
//		}
//	}
//	return ans;
//}
//
//std::string leastSquare(int howmany, VectorSpace * _vec)
//{
//	//X  = (A^(T)A)^(-1)A^(T)Y 
//	Matrix tem(howmany,_vec[0].getvectorsize() , *_vec);
//	//std::cout << tem;
//
//	Matrix fx(tem.getRow(), 1);
//
//	//std::cout << fx;
//	for (int i = 0; i < tem.getRow(); i++)
//	{
//		fx.replaceNuminMatrix(i, 0, tem.getnuminMatrix(i, tem.getcolumn() - 1));
//		tem.replaceNuminMatrix(i, tem.getcolumn() - 1, 1);
//	}
//	//std::cout << tem;
//	//std::cout << fx;
//	Matrix temT = tem.Transpose();
//
//	Matrix T = temT * tem;
//	//std::cout << T;
//	T = T.Inverse();
//	//std::cout << T;
//	//std::cout << temT;
//	Matrix X = T * temT;
//	//std::cout << X;
//	//std::cout << fx;
//	X = X * fx;
//	//std::cout << X;
//	std::string ans = "y = ";
//	for (int i = 0; i < X.getRow(); i++)
//	{
//		std::stringstream ss;
//		std::string record;
//		ss << X.getnuminMatrix(i, 0);
//		ss >> record;
//		ss.clear();
//		ss.str("");
//		ans += record;
//		if (i + 1 != X.getRow())
//		{
//			ss << (i + 1);
//			ss >> record;
//			ans += 'x';
//			ans += record;
//			ans += " + ";
//		}
//	}
//	return ans;
