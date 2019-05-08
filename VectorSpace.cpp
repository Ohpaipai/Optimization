#include "VectorSpace.h"



VectorSpace::VectorSpace()
{
	Vectorsize = 0;
	vec.clear();
	name.clear();
}


VectorSpace::~VectorSpace()
{
	Vectorsize = 0;
	vec.clear();
	name.clear();
}

VectorSpace::VectorSpace(std::string _name, int _size, double * a)
{
	//use try catch
	name = _name;
	Vectorsize = _size;
	for (int i = 0; i < _size; i++)
	{
		vec.push_back(a[i]);
	}
	
}

VectorSpace::VectorSpace(std::string _name, int _size, std::vector<double> _vec)
{
	//use try catch
	name = _name;
	Vectorsize = _size;
	vec = _vec;
}

VectorSpace::VectorSpace(std::string _name)
{
	name = _name;
}

VectorSpace::VectorSpace(std::string _name, double a)
{
	name = _name;
	Vectorsize = 1;
	vec.push_back(a);
}

void VectorSpace::changename(std::string _name)
{
	name = _name;
}



VectorSpace::VectorSpace(std::string _name, int _size)
{
	//use try catch
	name = _name;
	Vectorsize = _size;
}

VectorSpace::VectorSpace(int _size)
{
	Vectorsize = _size;
	vec.resize(_size);
	for (int i = 0; i < _size; i++)
	{
		vec[i] = 0;
	}
}

void VectorSpace::addNumInSpace(double _num)
{
	vec.push_back(_num);
	Vectorsize += 1;
}

void VectorSpace::changeNumInSpace(double _num, int place)
{
	vec[place] = _num;
}

VectorSpace::VectorSpace(const VectorSpace & _vec)
{
	name = _vec.name;
	vec =_vec.vec;
	Vectorsize = _vec.Vectorsize;
}

int VectorSpace::getvectorsize()
{
	return Vectorsize;
}

void VectorSpace::deleteNumplace(int place)
{
	std::vector<double>newone;
	for (int i = 0; i <Vectorsize; i++)
	{
		if(i==place){}
		else newone.push_back(vec[i]);
	}
	vec.clear();
	vec = newone;
	Vectorsize -= 1;
}

double VectorSpace::getNumInSpace(int place)
{
	return vec[place];
}

std::string VectorSpace::getName()
{
	return name;
}

VectorSpace VectorSpace::operator+(VectorSpace & _vec)
{
	if (this->Norm() == 0.0)
		return _vec;
	else if (_vec.Norm() == 0.0)
		return *this;
	if (Vectorsize != _vec.Vectorsize)
		throw myException(vector_size_not_same, this->name + " and " + _vec.name);
	VectorSpace ans;
	ans.Vectorsize = Vectorsize;
	for (int i = 0; i <Vectorsize; i++)
	{
		ans.vec.push_back((vec[i] + _vec.vec[i]));
	}
	return ans;
}

VectorSpace VectorSpace::operator=(const VectorSpace & _vec)
{
	name = _vec.name;
	vec = _vec.vec;
	Vectorsize = _vec.Vectorsize;
	return *this;
}

VectorSpace VectorSpace::operator-(VectorSpace & _vec)
{
	if (this->Norm() == 0.0)
		return _vec;
	else if (_vec.Norm() == 0.0)
		return *this;
	if (Vectorsize != _vec.Vectorsize)
		throw myException(vector_size_not_same, this->name + " and " + _vec.name);
	VectorSpace ans;
	ans.Vectorsize = Vectorsize;
	for (int i = 0; i < Vectorsize; i++)
	{
		ans.vec.push_back((vec[i] - _vec.vec[i]));
	}
	return ans;
}

double VectorSpace::operator*(VectorSpace & _vec)
{
	if (this->Norm() == 0.0)
		return 0.0;
	else if (_vec.Norm() == 0.0)
		return 0.0;
	if (Vectorsize != _vec.Vectorsize)
		throw myException(vector_size_not_same, this->name + " and " + _vec.name);
	double ans=0;
		
	for (int i = 0; i < Vectorsize; i++)
	{
		ans += vec[i] * _vec.vec[i];
	}
	return ans;
}

VectorSpace VectorSpace::operator/(const double & _Scalar)
{
	if (_Scalar==0)
		throw myException(denominator_is_zero);
	VectorSpace ans(*this);
		
	for (int i = 0; i < Vectorsize; i++)
	{
		vec[i] /= _Scalar;
	}
	return ans;
}

VectorSpace VectorSpace::operator*(double & _Scalar)
{
	VectorSpace ans(*this);
	for (int i = 0; i < Vectorsize; i++)
	{
		ans.vec[i] *= _Scalar;
		
	}
	return ans;
}

VectorSpace VectorSpace::operator^(VectorSpace & _vec)
{
	if (Vectorsize != 3 && _vec.Vectorsize != 3)
		throw myException(cross_error);
	VectorSpace ans;
	ans.Vectorsize = Vectorsize;
	ans.vec.push_back(vec[1] * _vec.vec[2] - vec[2] * _vec.vec[1]);
	ans.vec.push_back((vec[0] * _vec.vec[2] - vec[2] * _vec.vec[0])*-1);
	ans.vec.push_back(vec[0] * _vec.vec[1] - vec[1] * _vec.vec[0]);
	return ans;
}

double VectorSpace::Norm()
{
	double ans = 0;
	for (int i = 0; i < Vectorsize; i++)
	{
		ans += vec[i] * vec[i];
	}
	ans = sqrt(ans);
	return ans;
}

VectorSpace VectorSpace::Normalization()
{
	
	double denomainater = this->Norm();
	if (denomainater == 0)
		throw myException(zero_vector_error, "Normalization");
	VectorSpace ans;
	ans.Vectorsize = Vectorsize;
	for (int i = 0; i < Vectorsize; i++)
	{
		ans.vec.push_back(vec[i] / denomainater);
	}
	return ans;
}

double VectorSpace::AngleBetween(VectorSpace & _vec)
{
	VectorSpace tem(*this);
	if (Vectorsize !=_vec.Vectorsize)
		throw myException(vector_size_not_same, this->name + " and " + _vec.name);
	else if (_vec.Norm() == 0 || tem.Norm() == 0)
		throw myException(zero_vector_error, "AngleBetween");
	/*else if (1 - std::abs(_vec.Norm()) <= 0.000001 || std::abs(_vec.Norm()) - 1 <= 0.000001 || 1 - std::abs(tem.Norm()) <= 0.000001 || std::abs(tem.Norm()) - 1 <= 0.000001)
	{
		throw "有0向量";
	}*/
	double ans = acos((tem*_vec) / (_vec.Norm()*tem.Norm()));
	//std::cout <<ans << std::endl;
	return RadtoAng(ans);
}

double VectorSpace::TriangleArea(VectorSpace & _vec)
{
	
	if (Vectorsize!= _vec.Vectorsize)
		throw myException(vector_size_not_same, this->name + " and " + _vec.name);
	else if (this->Norm()==0||_vec.Norm()==0)
		throw myException(zero_vector_error, "TriangleArea");
	else
	{
		if (Vectorsize == 2)
			return 0.5*this->Norm()*_vec.Norm()*RadtoAng(sin(this->AngleBetween(_vec)));
		else
		{
			//海龍公視
			VectorSpace a(*this);
			VectorSpace b(*this);
			for (int i = 0; i < Vectorsize; i++)
			{
				a.vec[i] = b.vec[i] - _vec.vec[i];
			}
			double s = (a.Norm() + b.Norm() + _vec.Norm()) / 2;
			double ans = sqrt(s*(s - a.Norm())*(s - b.Norm())*(s - _vec.Norm()));
			return ans;
		}
	}	
}

double VectorSpace::Component(VectorSpace & _vec)
{
	if (Vectorsize != _vec.Vectorsize)
		throw myException(vector_size_not_same, this->name + " and " + _vec.name);
	VectorSpace tem(*this);
	if(_vec.Norm()==0) 
		throw myException(zero_vector_error, "Component");
	double ans = ( tem * _vec);
	ans = ans / _vec.Norm();
		
	return ans;
}

VectorSpace VectorSpace::Projection(VectorSpace & _vec)
{
	if (Vectorsize != _vec.Vectorsize)
		throw myException(vector_size_not_same, this->name + " and " + _vec.name);
	if (_vec.Norm() == 0)
		throw myException(zero_vector_error, "Projection");
	VectorSpace tem(*this);
	VectorSpace ans(*this);
	double an = tem * _vec;
	an = an / _vec.Norm();
	ans = _vec.Normalization();
	ans = ans * an;
	return ans;
}

bool VectorSpace::Parallel(VectorSpace & _vec)
{
	
	if (Vectorsize != _vec.Vectorsize)
		throw myException(vector_size_not_same, this->name + " and " + _vec.name);
		
		
	VectorSpace A(*this),B(_vec);
	double p = A.Normalization()*B.Normalization();
	//std::cout << A << B;

	if (p == 0) return false;
	if (p == 1.0 || p == (-1.0))
		return true;
	else
	{
		if (1 - std::abs(p) <= 0.000001)
			return true;
		else
			return false;
	}
}

bool VectorSpace::Orthohonal(VectorSpace & _vec)
{
	if (Vectorsize != _vec.Vectorsize)
		throw myException(vector_size_not_same, this->name + " and " + _vec.name);
		
	double ans = *this*_vec;
	if (std::abs(ans - 0.0) <= 0.000001)return true;
	else return false;
	
}

double VectorSpace::vectorToDouble()
{
	return vec[0];
}

std::vector<VectorSpace> Orthonormalbasis(std::vector<VectorSpace> _vec)
{
	bool wrong = false;
	for (int i = 1; i <_vec.size(); i++)
	{
		if (_vec[i - 1].getvectorsize() != _vec[i].getvectorsize())
		{
			wrong = true;
			break;
		}
	}
	
	if (wrong)
		throw myException(vector_size_not_same, "Vectors");
	std::vector<VectorSpace>ans;
	ans.push_back(_vec[0]);
	//cout << ans[0] << endl;
	for (int i = 1; i <_vec.size(); i++)
	{
		VectorSpace tem(_vec[i].getvectorsize());
		//cout << tem;
		for (int j = 0; j < ans.size(); j++)
		{
				
			VectorSpace t;

			double a=(_vec[i] * ans[j])/( ans[j] * ans[j]);
		//	cout << a << endl;
		//	cout <<"behind t" <<ans[j] << endl;
			VectorSpace p(ans[j]);
			t = p*a;
				
		//	cout <<"after t"<<ans[j] << endl;
				
			tem = tem + t;
				
		}
		ans.push_back(_vec[i]-tem);
		//cout << ans.size()-1 << " " << ans[ans.size() - 2];
		//cout << ans.size()<<" "<<ans[ans.size() - 1];
	}
	//cout << "---------------------" << endl;
	for (int i = 0; i < ans.size(); i++)
	{
		//cout << ans[i];
		ans[i] = ans[i].Normalization();
	}
	return ans;
}



std::ostream & operator<<(std::ostream & os, const VectorSpace & _vec)
{
	os << "{";
	for (int i = 0; i <_vec.Vectorsize; i++)
	{
		if(i==0)
			os << "\t"<< std::setw(10) <<std::fixed<<std::setprecision(6)<< _vec.vec[i]  ;
		else
			os << ",\t" << std::setw(10) << std::fixed << std::setprecision(6) << _vec.vec[i];
			
	}
	os << "}" << std::endl;
	return os;
}
