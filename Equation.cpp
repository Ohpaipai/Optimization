#include "Equation.h"



//LinkEquation


LinkEquation::LinkEquation()
{
	Polynomial.clear();
	Polynomial_coef.clear();
}

LinkEquation::~LinkEquation()
{
	Polynomial.clear();
	Polynomial_coef.clear();
}

LinkEquation::LinkEquation(const LinkEquation &tem)
{
	this->Polynomial.clear();
	this->Polynomial_coef.clear();
	for (int i = 0; i <tem.Polynomial.size(); i++)
	{
		this->Polynomial.push_back(tem.Polynomial[i]);
		this->Polynomial_coef.push_back(tem.Polynomial_coef[i]);
	}
}

LinkEquation::LinkEquation(LinkVariance _var,Coefficient _coe)
{
	Polynomial.push_back(_var);
	Polynomial_coef.push_back(_coe);
}

void LinkEquation::insert(LinkVariance _var, Coefficient _coe)
{
	std::vector<LinkVariance>::iterator Vit;
	std::vector<Coefficient>::iterator Cit;

	bool isFind = false;  
	for (int i = 0; i < Polynomial_coef.size(); i++) //先查找是否有一樣的variance 有一樣的就相加起來
	{
		if (_var==this->Polynomial[i])
		{
			if (this->Polynomial_coef[i].mathName == _coe.mathName)
			{
				this->Polynomial_coef[i].coefficient += _coe.coefficient;
				if (this->Polynomial_coef[i].coefficient == 0 && this->Polynomial_coef[i].mathName == "") //coef要是為0(前提是mathname為"")
				{
					this->Delete(this->Polynomial[i], this->Polynomial_coef[i]);
				}
				isFind = true;
				break;
			}
		}
	}
	if (!isFind) { //未找到
		Polynomial.push_back(_var);
		Polynomial_coef.push_back(_coe);
	}




}

void LinkEquation::Delete(LinkVariance _var, Coefficient _coe)
{
	std::vector<LinkVariance>::iterator Vit;
	std::vector<Coefficient>::iterator Cit;

	//bool isFind = false;
	//for (int i = 0; i < Polynomial_coef.size(); i++) //先查找是否有一樣的
	//	if (_var == this->Polynomial[i])
	//	{
	//		if (this->Polynomial_coef[i].mathName == _coe.mathName)
	//		{
	//			isFind = true;
	//			break;
	//		}
	//	}
	//}

	for(Vit=Polynomial.begin(),Cit=Polynomial_coef.begin();Vit!=Polynomial.end(),Cit!=Polynomial_coef.end();Vit++,Cit++)
	{
		if (*Vit == _var && _coe == *Cit)
		{
			Polynomial.erase(Vit);
			Polynomial_coef.erase(Cit);
			break;
		}
	}
}

LinkEquation LinkEquation::operator*(LinkEquation tem)
{
	LinkEquation ans;
	for (int i = 0; i < this->Polynomial.size(); i++) //(x+y)(x+y)
	{
		for (int j = 0; j < tem.Polynomial.size(); j++)
		{
			Coefficient ctem;
			ctem= this->Polynomial_coef[i]*tem.Polynomial_coef[j];
			LinkVariance vtem;
			vtem = this->Polynomial[i] * tem.Polynomial[j];
			//std::cout << vtem;
			ans.insert(vtem,ctem); //新增
		}
	}
	return ans;
}

LinkEquation LinkEquation::operator+(LinkEquation tem)
{
	LinkEquation ans(*this);
	for (int i = 0; i < tem.Polynomial.size(); i++)
	{
		ans.insert(tem.Polynomial[i], tem.Polynomial_coef[i]);
	}
	return ans;
}

LinkEquation LinkEquation::operator-(LinkEquation tem)
{
	LinkEquation ans(*this);
	for (int i = 0; i < tem.Polynomial.size(); i++)
	{
		tem.Polynomial_coef[i].coefficient *= -1; //將後面全部乘上-1
		ans.insert(tem.Polynomial[i], tem.Polynomial_coef[i]);
	}
	return ans;
}

double LinkEquation::Fxans(std::string _name,double x)
{
	double ans = 0;
	for (int i = 0; i < this->Polynomial.size(); i++)
	{
		double t=0;
		double tem=1;
		std::string func = "";

		if (this->Polynomial_coef[i].mathName != "") //有三角函數的話
		{
			for (int j = 0; j < this->Polynomial_coef[i].mathName.size(); j++)
			{
				func += tolower(this->Polynomial_coef[i].mathName[j]); //先找出是哪種
				std::string m = "";
				int c = 0;
				for (int count = i+1; count < this->Polynomial_coef[i].mathName.size(); count++)
				{
					if (this->Polynomial_coef[i].mathName[count] != 's' || this->Polynomial_coef[i].mathName[count] != 'c')
						m += this->Polynomial_coef[i].mathName[count];
					c++;
				}
				
				if (_name ==m )
				{
					if (func == "sin")
						t += this->Polynomial_coef[i].coefficient*std::sin(x);
					else if (func == "cos")
						t += this->Polynomial_coef[i].coefficient*std::cos(x);
					else if (func == "tan")
						t += this->Polynomial_coef[i].coefficient*std::tan(x);
					else if (func == "csc")
						t += this->Polynomial_coef[i].coefficient*((double)1 / std::sin(x));
					else if (func == "sec")
						t += this->Polynomial_coef[i].coefficient*((double)1 / std::cos(x));
					else if (func == "cot")
						t += this->Polynomial_coef[i].coefficient*((double)1 / std::tan(x));
				}
				i += c;
			}
			
		}
		else
		{
			t = this->Polynomial_coef[i].coefficient;
		}
		for (int j = 0; j < this->Polynomial[i].variable.size(); j++)
		{
			if (this->Polynomial[i].variable[i].name != "c")
			{
				tem *= std::pow(x, this->Polynomial[i].variable[i].exponential);
			}
		}
		ans += (tem*t); //相加
	}
	return ans;
}

double LinkEquation::TwoFxans(std::string _name, std::string _nname, double x, double y)
{
	double ans = 0;
	for (int i = 0; i < this->Polynomial.size(); i++)
	{
		double t = 0;
		double tem = 1;
		std::string func = "";

		if (this->Polynomial_coef[i].mathName != "") //有三角函數的話
		{
			for (int j = 0; j < this->Polynomial_coef[i].mathName.size(); j++)
			{
				func += tolower(this->Polynomial_coef[i].mathName[j]); //先找出是哪種
				std::string m = "";
				int c = 0;
				for (int count = i + 1; count < this->Polynomial_coef[i].mathName.size(); count++)
				{
					if (this->Polynomial_coef[i].mathName[count] != 's' || this->Polynomial_coef[i].mathName[count] != 'c')
						m += this->Polynomial_coef[i].mathName[count];
					c++;
				}
				if (_name == m)
				{
					if (func == "sin")
						t += this->Polynomial_coef[i].coefficient*std::sin(AngtoRad(x));
					else if (func == "cos")
						t += this->Polynomial_coef[i].coefficient*std::cos(AngtoRad(x));
					else if (func == "tan")
						t += this->Polynomial_coef[i].coefficient*std::tan(AngtoRad(x));
					else if (func == "csc")
						t += this->Polynomial_coef[i].coefficient*((double)1 / std::sin(AngtoRad(x)));
					else if (func == "sec")
						t += this->Polynomial_coef[i].coefficient*((double)1 / std::cos(AngtoRad(x)));
					else if (func == "cot")
						t += this->Polynomial_coef[i].coefficient*((double)1 / std::tan(AngtoRad(x)));
				}
				else {
					if (_nname == m)
					{
						if (func == "sin")
							t += this->Polynomial_coef[i].coefficient*std::sin(AngtoRad(y));
						else if (func == "cos")
							t += this->Polynomial_coef[i].coefficient*std::cos(AngtoRad(y));
						else if (func == "tan")
							t += this->Polynomial_coef[i].coefficient*std::tan(AngtoRad(y));
						else if (func == "csc")
							t += this->Polynomial_coef[i].coefficient*((double)1 / std::sin(AngtoRad(y)));
						else if (func == "sec")
							t += this->Polynomial_coef[i].coefficient*((double)1 / std::cos(AngtoRad(y)));
						else if (func == "cot")
							t += this->Polynomial_coef[i].coefficient*((double)1 / std::tan(AngtoRad(y)));
					}
				}
				i += c;
			}

		}
		else
		{
			t = this->Polynomial_coef[i].coefficient;
		}
		for (int j = 0; j < this->Polynomial[i].variable.size(); j++)
		{
			if (this->Polynomial[i].variable[i].name != "c")
			{
				if (_name == this->Polynomial[i].variable[i].name)
					tem *= std::pow(x, this->Polynomial[i].variable[i].exponential);
				else
					tem *= std::pow(y, this->Polynomial[i].variable[i].exponential);
			}
		}
		ans += (tem*t); //相加
	}
	return ans;
}

double LinkEquation::GoldenSectionSearch(double lowBound, double middle, double upperBound, double tau, std::string _name)
{
	{
		double x;
		if (upperBound - middle > middle - lowBound)
			x = middle + resphi * (upperBound - middle);
		else
			x = middle - resphi * (middle - lowBound);
		if (std::abs(upperBound - lowBound) < tau*(std::abs(middle) + std::abs(x)))
			return (lowBound + upperBound) / 2;
		if (this->Fxans( _name,x) < this->Fxans( _name,middle)) {
			if (upperBound - middle > middle - lowBound) return this->GoldenSectionSearch(middle,x,upperBound,tau, _name);
			else return this->GoldenSectionSearch(lowBound, x,middle, tau,_name);
		}
		else {
			if (upperBound - middle > middle - lowBound) return this->GoldenSectionSearch(lowBound,middle,x, tau, _name);
			else return this->GoldenSectionSearch(x,middle,upperBound, tau, _name);
		}
	}
}

LinkEquation LinkEquation::Powell2Golden(std::string _name, std::string _nname, LinkEquation fun, double x)
{
	LinkEquation ans;
	for (int i = 0; i < this->Polynomial.size(); i++)
	{
		
		std::string func = "";
	
		//if (this->Polynomial_coef[i].mathName != "") //有三角函數的話 
		//{
		//	for (int j = 0; j < this->Polynomial_coef[i].mathName.size(); j++)
		//	{
		//		func += tolower(this->Polynomial_coef[i].mathName[j]); //先找出是哪種
		//		std::string m = "";
		//		int c = 0;
		//		for (int count = i + 1; count < this->Polynomial_coef[i].mathName.size(); count++)
		//		{
		//			if (this->Polynomial_coef[i].mathName[count] != 's' || this->Polynomial_coef[i].mathName[count] != 'c')
		//				m += this->Polynomial_coef[i].mathName[count];
		//			c++;
		//		}
		//		if (_nname == m)
		//		{
		//			if (func == "sin")
		//				t += this->Polynomial_coef[i].coefficient*std::sin(AngtoRad(x));
		//			else if (func == "cos")
		//				t += this->Polynomial_coef[i].coefficient*std::cos(AngtoRad(x));
		//			else if (func == "tan")
		//				t += this->Polynomial_coef[i].coefficient*std::tan(AngtoRad(x));
		//			else if (func == "csc")
		//				t += this->Polynomial_coef[i].coefficient*((double)1 / std::sin(AngtoRad(x)));
		//			else if (func == "sec")
		//				t += this->Polynomial_coef[i].coefficient*((double)1 / std::cos(AngtoRad(x)));
		//			else if (func == "cot")
		//				t += this->Polynomial_coef[i].coefficient*((double)1 / std::tan(AngtoRad(x)));
		//		}
		//	
		//		i += c;
		//	}

		//} //coef處理
		
			
			/*	Coefficient a;
				a.mathName = "";
				a.coefficient = this->Polynomial_coef[i].coefficient;
				Variance b;
				b.name = "c";
				LinkVariance c;
				c.insert(b);
				group.insert(c, a);
				LinkEquation group2;*/
				double regesterNum = this->Polynomial_coef[i].coefficient;
				LinkEquation tem(fun);
		//非coef處理
		for (int j = 0; j < this->Polynomial[i].variable.size(); j++)
		{
			if (_nname == this->Polynomial[i].variable[j].name) //正常數值
			{
				regesterNum *= pow(x, this->Polynomial[i].variable[j].exponential);
			}
			else if(_name==this->Polynomial[i].variable[j].name)//要形成的新方程式
			{
				for (int k = 0; k <this->Polynomial[i].variable[j].exponential-1; k++)
				{
					tem = tem * fun;//方程式自己*
				}
			}
		}
		for (int k = 0; k <tem.Polynomial_coef.size(); k++)
		{
			tem.Polynomial_coef[k].coefficient *= regesterNum;//將成成出來方程式都常上細數
		}
		ans = ans + tem;//每次結果相加
		
	}
	return ans;
}

void LinkEquation::Powell(std::string intitialname1, std::string intitialname2,double initialx, double initialy)
{


}






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







// LinkVariance
bool LinkVariance::operator==( LinkVariance _var)
{
	if (this->variable.size() != _var.variable.size())
	{
		return false;
	}
	else {
		bool ans = true;
		for (int i = 0; i < variable.size(); i++)
		{
			for (int j = 0; j < variable.size(); j++)
			{
				if (!(this->variable[i] == _var.variable[j]))
				{
					ans = false;
					break;
				}
			}
			if (ans == false) {
				break;
			}
		}
		return ans;
	}
}

LinkVariance LinkVariance::operator=(LinkVariance & tem)
{
	LinkVariance ans;
	this->variable.clear();
	for (int i = 0; i < tem.variable.size(); i++)
	{	
		//std::cout << tem.variable[i];
		ans.variable.push_back(tem.variable[i]);
		this->variable.push_back(tem.variable[i]);
		//std::cout << ans.variable[i];
	}
	return ans;
}

LinkVariance::~LinkVariance()
{
	variable.clear();
}

LinkVariance::LinkVariance()
{
	variable.clear();
}

LinkVariance::LinkVariance(Variance _var)
{
	variable.push_back(_var);
}

void LinkVariance::insert(Variance _var)
{
	std::vector<Variance>::iterator iter;
	bool find = false;
	for (iter = variable.begin(); iter != variable.end(); iter++) //先查找是否有一樣的variance 有一樣的就變成兩倍
	{
		if (*iter == _var) {
			iter->exponential *= 2;
			find = true;
			break;
		}
		else if (iter->name == _var.name)
		{
		
				iter->exponential += _var.exponential;
				find = true;
				break;
			
		}
		
	}
	if (find == false) {
		variable.push_back(_var);
	}
	return;
}

LinkVariance::LinkVariance(const LinkVariance &tem)
{
	this->variable.clear(); //先清空後放入
	for (int i = 0; i < tem.variable.size(); i++)
	{
		this->variable.push_back(tem.variable[i]);
	}
}

void LinkVariance::Delete(Variance _var)
{
	std::vector<Variance>::iterator iter;
	
	for (iter = variable.begin(); iter != variable.end(); iter++) //先查找是否有一樣的variance 有一樣的就變成兩倍
	{
		if (*iter == _var) {
			variable.erase(iter);
			break;
		}
	}

	return;
}

LinkVariance LinkVariance::operator*(LinkVariance tem)
{
	LinkVariance ans(*this);
	for (int i = 0; i < tem.variable.size(); i++)
	{
		ans.insert(tem.variable[i]);
		
	}
	
	return ans;
}

std::ostream & operator<<(std::ostream & os, const LinkVariance &tem)
{
	for (int i = 0; i <tem.variable.size(); i++)
	{
		os << tem.variable[i].name << "^" << tem.variable[i].exponential;
	}
	os<<std::endl;
	return os;
}

std::ostream & operator<<(std::ostream & os, const LinkEquation &tem)
{
	for (int i = 0; i < tem.Polynomial_coef.size(); i++)
	{
		os << tem.Polynomial_coef[i].coefficient;
		if(tem.Polynomial_coef[i].mathName!="") os << tem.Polynomial_coef[i].mathName;
		for (int j = 0; j < tem.Polynomial[i].variable.size(); j++)
		{
			if(tem.Polynomial[i].variable[j].name!="c")
				os << tem.Polynomial[i].variable[j].name <<"^"<<tem.Polynomial[i].variable[j].exponential;
			else
				os << tem.Polynomial[i].variable[j].name ;
		}
		if (i + 1 != tem.Polynomial_coef.size()) os << " + ";
		
	}
	os << std::endl;
	return os;
}
