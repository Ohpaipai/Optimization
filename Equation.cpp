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

void LinkEquation::Powell(std::string intitialname1, std::string intitialname2,double initialx, double initialy,bool find)
{
	if (find)
		return;

	double initialans = this->TwoFxans(intitialname1, intitialname2, initialx, initialy);
	//先從initial name方向探索
	LinkEquation togolden;//要做gliden的equation
	Variance v1; //常數
	v1.exponential = 0;
	v1.name = "c";
	LinkVariance v2; //對應到常數向
	v2.insert(v1);
	Coefficient c1;
	c1.coefficient = initialx;
	togolden.insert(v2,c1);
	////////////////////////////////
	Variance v3; //非常數
	v3.exponential = 1;
	v3.name = intitialname1;
	LinkVariance v4;//對應到非常數項
	v4.insert(v3);
	Coefficient c3;
	c3.coefficient = initialx;
	togolden.insert(v4, c3);

	LinkEquation to;
	to = this->Powell2Golden(intitialname1,intitialname2,togolden,initialy); //做出方程式(要拿來做golden search)
	double upbound = initialx - up;
	double down = initialy - down;
	double zobig_1=to.GoldenSectionSearch(upbound, w, down, 1e-6,intitialname1);//第一次golden
	double firstvec1x = initialx + zobig_1;
	double firstvec1y = initialy;
	double fFirstans = this->TwoFxans(intitialname1,intitialname2,firstvec1x,firstvec1y); //第一次探索值

	std::cout << "First\n{ " << firstvec1x << " , " << firstvec1y << " }\n" << "F(X) = " << fFirstans << std::endl;
	//對第一個探索結束

	//對第二個開始探索
	LinkEquation togolden2;//要做gliden的equation
	Variance v1_2; //常數
	v1_2.exponential = 0;
	v1_2.name = "c";
	LinkVariance v2_2; //對應到常數向
	v2.insert(v1_2);
	Coefficient c1_2;
	c1_2.coefficient = firstvec1y;
	togolden.insert(v2_2, c1_2);
	////////////////////////////////
	Variance v3_2; //非常數
	v3_2.exponential = 1;
	v3_2.name = intitialname2;
	LinkVariance v4_2;//對應到非常數項
	v4_2.insert(v3_2);
	Coefficient c3_2;
	c3_2.coefficient = firstvec1x;
	togolden2.insert(v4_2, c3_2);
	LinkEquation to_2;
	to_2 = this->Powell2Golden(intitialname2,intitialname1,togolden2,firstvec1x);
	double upbound_2 = firstvec1x - up;
	double down_2 = firstvec1y - down;
	double zobig_2 = to.GoldenSectionSearch(upbound_2, w, down_2, 1e-6, intitialname2);//第二次golden
	double twovec1x = firstvec1x ;
	double twovec1y = firstvec1y+zobig_2;
	double fTwotans = this->TwoFxans(intitialname1, intitialname2, twovec1x,twovec1y); //第二次探索值
	//第二次探索結束

	std::cout << "Two\n{ " << twovec1x << " , " << twovec1y << " }\n" << "F(X) = " << fTwotans << std::endl;
	
	//判斷是否達到查找終點
	//判斷是否到回傳目的
	double judge1 = std::abs(fTwotans - initialx);
	double judge2 = std::abs(std::pow((twovec1x - initialx), 2) + std::pow((twovec1y-initialy),2));
	if (judge1 > 1e-8&&judge2 > 1e-8) {
		std::cout << "Ans\n{ " << twovec1x << " , " << twovec1y << " }\n";
		find = true;
		return;
	}
	else {
		//未找到
		double triangle1 = initialans- fFirstans;
		double triangle2 = fFirstans- fTwotans;
		double Trianglem = std::min(triangle1,triangle2);
		double rejectx = 2 * twovec1x - initialx;
		double rejecty = 2 * twovec1y - initialy;
		double newf = this->TwoFxans(intitialname1, intitialname2, rejectx, rejecty);
		if (newf < initialans)
		{
			if ((initialans - 2 * fTwotans + newf)*std::pow((initialans - fTwotans - Trianglem), 2) < (((Trianglem*(std::pow((initialans - newf), 2))) / 2)))
			{

				//對第三個進行探索
				double finaldive = 1;
				for (int i = 0; i < this->Polynomial_coef.size(); i++)
				{
					finaldive *= this->Polynomial_coef[i].coefficient;
				}
				LinkEquation togolden3;
				Variance v1_3; //常數
				v1_3.exponential = 0;
				v1_3.name = "c";
				LinkVariance v2_3; //對應到常數向
				v2_3.insert(v1_3);
				Coefficient c1_3;
				c1_3.coefficient = twovec1x;
				togolden.insert(v2_3, c1_3);
				////////////////////////////////
				Variance v3_3; //非常數
				v3_3.exponential = 1;
				v3_3.name = "x";
				LinkVariance v4_3;//對應到非常數項
				v4_3.insert(v3_3);
				Coefficient c3_3;
				c3_3.coefficient = zobig_1;
				togolden3.insert(v4_3, c3_3);
				LinkEquation to_3;
				to_3 = this->Powell2Golden("x", intitialname2, togolden3, 1);
				LinkEquation togolden4;
				Variance v1_4; //常數
				v1_4.exponential = 0;
				v1_4.name = "c";
				LinkVariance v2_4; //對應到常數向
				v2_3.insert(v1_4);
				Coefficient c1_4;
				c1_3.coefficient = twovec1y;
				togolden.insert(v2_4, c1_4);
				////////////////////////////////
				Variance v3_4; //非常數
				v3_4.exponential = 1;
				v3_4.name = "c";
				LinkVariance v4_4;//對應到非常數項
				v4_4.insert(v3_4);
				Coefficient c3_4;
				c3_4.coefficient = zobig_2;
				togolden4.insert(v4_4, c3_4);
				LinkEquation to_4;
				to_4 = this->Powell2Golden("x", intitialname1, togolden4, 1);

				LinkEquation finale = to_3 * to_4; //最後的equation
				for (int i = 0; i < finale.Polynomial_coef.size(); i++)
				{
					finale.Polynomial_coef[i].coefficient /= finaldive;
				}
				double upbound_3 = (twovec1x - up) / zobig_1;
				double down_3 = (twovec1y - down) / zobig_2;
				double zobig_3 = finale.GoldenSectionSearch(upbound_3, w, down_3, 1e-6, "x");//第三次golden
				double finalx = twovec1x + zobig_3 * zobig_1;//這次尋找最後的點x
				double finaly = twovec1y + zobig_3 * zobig_2;//這次尋找最後y
				double fThirdans = this->TwoFxans(intitialname1, intitialname2, finalx, finaly); //第三次探索值
				std::cout << "Three\n{ " << finalx << " , " << finaly << " }\n" << "F(X) = " <<fThirdans << std::endl;
				this->Powell(intitialname1, intitialname2, finalx, finaly, find);
			}
			else {
				this->Powell(intitialname1, intitialname2, twovec1x, twovec1y, find);
			}
		}
		else {
			this->Powell(intitialname1, intitialname2, twovec1x, twovec1y, find);
			
		}

	}
	return;
}

void LinkEquation::PowellForUpDown(double _x, double _y)
{
	up = _x;
	down = _y;
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
