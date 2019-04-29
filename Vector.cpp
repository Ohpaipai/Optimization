#include"Vector.h"

Vector::Vector()
{
	size = 0;
}

Vector::~Vector()
{
	
}

Vector::Vector( int _size, string _name)
{
	size = _size;
	name = _name;
	a = new double(_size);
	
	
}

Vector::Vector(int _size)
{
	a = new double(_size);
	size = _size;
	for (int i = 0; i < size; i++)
	{
		a[i] = 0;
	}
}

int Vector::getsize()
{
	return size;
}

void Vector::add(double _a[])
{
	for (int i = 0; i < size; i++)
	{
		this->a[i] = _a[i];
	}
}

Vector Vector::operator=(const Vector & vec)
{
	Vector ans(vec.size);
	for (int i = 0; i < vec.size; i++)
	{
		ans.a[i] = vec.a[i];
	}
	return ans;
}

Vector Vector::operator+(const Vector & vec)
{
	Vector ans(vec.size);
	for (int i = 0; i <this->size; i++)
	{
		ans.a[i] = vec.a[i]+this->a[i];
	}
	return ans;
}

Vector Vector::operator-(const Vector & vec)
{
	Vector ans(vec.size);
	for (int i = 0; i < this->size; i++)
	{
		ans.a[i] =  this->a[i]- vec.a[i] ;
	}
	return ans;
}

double Vector::operator*(const Vector & vec)
{
	double ans=0;
	for (int i = 0; i < this->size; i++)
	{
		ans += this->a[i] * vec.a[i];
	}
	return ans;
}

Vector Vector::operator^(const Vector & vec)
{
	if (this->size != 3 || vec.size != 3) return Vector(0);
	else {
		Vector ans(this->size);
		ans.a[0] = this->a[1] * vec.a[2] - this->a[2] * vec.a[1];
		ans.a[1] = this->a[0] * vec.a[2] - this->a[2] * vec.a[0];
		ans.a[2] = this->a[0] * vec.a[1] - this->a[1] * vec.a[0];
		return ans;

	}
	
}

Vector Vector::Scalar_Multiplication(double  Scalra)
{
	Vector ans;
	for (int i = 0; i < this->size; i++)
	{
		this->a[i] *= Scalra;
	}
	return ans;
}

double Vector::Norm()
{
	double ans=0;
	for (int i = 0; i < this->size; i++)
	{
		ans += this->a[i] * this->a[i];
	}
	return sqrt(ans);
}

Vector Vector::Normalization()
{
	double Denominator = this->Norm();
	Vector ans(this->size);
	for (int i = 0; i < this->size; i++)
	{
		ans.a[i] /= Denominator;
	}
	return ans;
}

double Vector::Angle_between(Vector & vec)
{
	Vector dot = *this;
	return acos((dot*vec)/(vec.Norm()*this->Norm()));
}



Vector Vector::Component_A_On_B(const Vector & vec)
{
	Vector ans=this->Scalar_Multiplication((-1)) + vec;
	
	return ans;
}

Vector Vector::Projection_A_On_B( Vector & vec)
{
	Vector ans(vec.size);
	double Denominator = *this*vec/vec.Norm();
	for (int i = 0; i < ans.size; i++)
	{
		ans.a[i] = vec.a[i] * Denominator;

	}
	return ans;
	
}

bool Vector::Parallel_judgement(Vector & vec) //(x/a)=(y/b)=(z/c)=constant
{
	bool ans = true;
	for (int i = 1; i <vec.size ; i++)
	{
		if (this->a[i - 1] / vec.a[i - 1] != this->a[i] / vec.a[i])
		{
			ans = false;
			break;
		}
	}
	return ans;
}

bool Vector::Orthogonal_judgement(Vector & vec)
{
	double ans = 0;
	for (int i = 0; i < vec.size; i++)
	{
		ans += vec.a[i]*this->a[i];
	}
	if (ans == 0) return true;
	else return false;
}

bool Vector::Linear_independent_judgement(Vector & vec)
{
	return false;
}




double Vector::Triangle_area( Vector & vec)
{
	
	return 0.5*this->Norm()*vec.Norm()*sin(this->Angle_between(vec));
}