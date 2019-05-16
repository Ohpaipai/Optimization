#include"Optimization.h"

int Optimization::priority(char op)
{
	switch (op)
	{
		case '+':case '-': return (int)1;
		case '*':case '/': return 2;
		case'!':case'@':case'$':case '%':case '&':case '#':return 3;
		case '^': return 4;
		case '~': return 5;
		default:           return 0;
	}
}

Optimization::Optimization()
{
	orignal.clear();
	orignal = "";
	postfix.clear();
	variable.clear();
	stackSign.clear();
	input.clear();
	input = "";
}

Optimization::Optimization(const Optimization &a)
{
	orignal = a.orignal;
	variable = a.variable;
	postfix = a.postfix;
	stackSign = a.stackSign;
	input = a.input;
	initial = a.initial;
	rrestrict = a.rrestrict;
}

Optimization::~Optimization()
{
	orignal="";
	postfix.clear();
	variable.clear();
	stackSign.clear();
	input.clear();
}

Optimization::Optimization(std::string _input)
{
	input = _input;
	std::string sub = this->dealstring(input);
	orignal = sub;
	//std::cout << orignal << std::endl;
	postfix = this->toPostfix();

}

Optimization Optimization::operator=(const Optimization& a)
{
	orignal = a.orignal;
	variable = a.variable;
	postfix = a.postfix;
	stackSign = a.stackSign;
	input = a.input;
	initial = a.initial;
	rrestrict = a.rrestrict;
	return *this;
}

std::vector<std::string> Optimization::toPostfix()
{
	std::string stack;
	std::vector<std::string>tempostfix;
	int top = -1;
	for (int i = 0, j = 0; i != orignal.size(); i++)
	{
		/*std::cout << i << "--->";
		for (int j = 0; j <=top; j++)
		{
			std::cout << stack[j];
		}
		std::cout << std::endl;*/
		switch (orignal[i])
		{
		case '(':
			stack.push_back(orignal[i]);
			stackSign.push_back(orignal[i]);
			top++;
			break;
		case '+': case '-': case '*': case '/':case '^':case'!':case'@':case'$':case '%':case '&':case '#':case('~'):
			if (top > -1)
			{
				while ((priority(stack[top]) >= priority(orignal[i]))) {
					std::string tem = "";
					tem += stack[top];
					stack.pop_back();
					tempostfix.push_back(tem);
					j++;
					top--;
					if (top <= -1) break;
				}
			}
			stack.push_back(orignal[i]);
			stackSign.push_back(orignal[i]);
			top++;
			break;
		case ')':
			if (top > -1)
			{
				while (stack[top] != '(') { // �J ) ��X�� ( 
					std::string tem = "";
					tem += stack[top];
					stack.pop_back();
					tempostfix.push_back(tem);
					j++;
					top--;
					if (top <= -1) break;
				}
				stack.pop_back();
				top--;
				if (top <= -1) top = -1;
			}
			stackSign.push_back(orignal[i]);
			break;
		case ' ':
			break;
		default:
			std::string tem = "";
			while (i != orignal.size())
			{


				if (isdigit(orignal[i]) || orignal[i] == '.' || ((orignal[i] >= 65 && orignal[i] <= 90) || orignal[i] >= 97 && orignal[i] <= 122))
				{
					tem += orignal[i];
				}
				else
					break;
				i++;

			}
			if (tem.size() == 1 && ((tem[0] >= 65 && tem[0] <= 90) || tem[0] >= 97 && tem[0] <= 122)) //��ܬ�variable
			{
				variable.insert(tem[0]);
				initial.insert(std::pair<std::string, double>(tem, 0));
				restrictVariable a;
				a.lowerbound = 0;
				a.upperbound = 0;
				rrestrict.insert(std::pair<std::string, restrictVariable>(tem, a));

				/*rrestrict[tem]=a;
				initial[tem] = 0;*/
			}
			tempostfix.push_back(tem);
			j++;
			i--;
			break;
		}
	}
	while (top > -1)
	{
		std::string tem = "";
		tem += stack[top];
		stack.pop_back();
		tempostfix.push_back(tem);
		top--;
	}
	return tempostfix;
}

void Optimization::getPostfix()
{
	for (int i = 0; i < postfix.size(); i++)
	{
		std::cout << postfix[i] << " ";

	}
	std::cout << std::endl;
	/*for (int i = 0; i <stackSign.size(); i++)
	{
		std::cout <<stackSign[i] << " ";

	}
	std::cout << std::endl;*/
	return;
}

double Optimization::eval(std::map < std::string, double > var)
{
	std::vector<double> ans;
	int top = -1;
	for (int i = 0; i < postfix.size(); i++)
	{
		/*if (top != -1) {
			std::cout << top << "-->" << ans[top] << std::endl;
		}*/
		if (postfix[i] == "+")
		{
			if(top==-1)
			{ }
			else if (top == 0)
			{ }
			else {
				ans[top - 1] = ans[top] + ans[top - 1];
				ans.pop_back();
				top--;
			}
		}
		else if (postfix[i] == "-") {
			if (top == -1)
			{
			}
			else if (top == 0) //���t��
			{
				ans[top] *= -1;
			}
			else {
				ans[top - 1] = ans[top-1] - ans[top];
				ans.pop_back();
				top--;
			}
		}
		else if (postfix[i] == "~")
		{
			ans[top] *= -1;
		}
		else if (postfix[i] == "*") {
			if (top == -1)
			{
			}
			else if (top == 0) 
			{	
			}
			else {
				ans[top - 1] = ans[top] * ans[top - 1];
				ans.pop_back();
				top--;
			}
		}
		else if (postfix[i] == "/") {
			if (top == -1)
			{
			}
			else if (top == 0)
			{
			}
			else {
				if (ans[top - 1] == 0) 
					ans[top - 1] = 0;
				else
					ans[top - 1] = ans[top]/ans[top - 1];
				ans.pop_back();
				top--;
			}
		}
		else if (postfix[i] == "^") {
			if (top == -1)
			{
			}
			else if (top == 0)
			{
			}
			else {
				ans[top - 1] = std::pow(ans[top-1],ans[top]);
				ans.pop_back();
				top--;
			}
		}
		else if (postfix[i] == "!") { //sin
			if (top == -1)
			{
			}
			else {
				ans[top] = std::sin(ans[top]);
			}
		}
		else if (postfix[i] == "@") {//cos
			if (top == -1)
			{
			}
			else {
				ans[top] = std::cos(ans[top]);
			}
		}
		else if (postfix[i] == "$") {//tan
			if (top == -1)
			{
			}
			else {
				ans[top] = std::tan(ans[top]);
			}
		}
		else if (postfix[i] == "&") { //sec
			if (top == -1)
			{
			}
			else {
				ans[top] = (1.0 / std::sin(ans[top]));
			}
		}
		else if (postfix[i] == "%") {//csc
			if (top == -1)
			{
			}
			else {
				ans[top] = (1.0 / std::cos(ans[top]));
			}
		}
		else if (postfix[i] == "#") {//cot
			if (top == -1)
			{
			}
			else {
				ans[top] = (1.0/std::tan(ans[top]));
			}
		}
		else {
			if(postfix[i]=="("||postfix[i]==")")
			{ }
			else
			{
				if (postfix[i].size() == 1) {
					if ((postfix[i][0] >= 65 && postfix[i][0] <= 90) || (postfix[i][0] >= 97 && postfix[i][0] <= 122))
					{
						std::map<std::string, double>::iterator iter;
						iter = var.find(postfix[i]);
						if (iter != var.end())
						{
							ans.push_back(iter->second);
							top++;
						}
						else
						{
							ans.push_back(0);
							top++;
						}

					}
					else {
						std::stringstream num;
						double n;
						num << postfix[i];
						num >> n;
						ans.push_back(n);
						top++;
					}
				}
				else
				{
					std::stringstream num;
					double n;
					num << postfix[i];
					num >> n;
					ans.push_back(n);
					top++;
				}

			}
		}
		
	}
	return ans[0];
}

std::string Optimization::dealstring(std::string _input)
{
	std::string sub = "";
	for (int i = 0; i < _input.size(); i++)
	{
		if (((_input[i] >= 65 && _input[i] <= 90) || _input[i] >= 97 && _input[i] <= 122))
		{
			if (i + 2 < _input.size())
			{
				if (std::tolower(_input[i]) == 's'&&std::tolower(_input[i + 1]) == 'i'&&std::tolower(_input[i + 2]) == 'n')
				{
					if (sub.size() > 0)
					{
						if (isdigit(sub[sub.size() - 1]) || sub[sub.size() - 1] == ')' || ((sub[sub.size() - 1] >= 65 && sub[sub.size() - 1] <= 90) || sub[sub.size() - 1] >= 97 && sub[sub.size() - 1] <= 122))
						{
							sub.push_back('*');
							sub.push_back('!');
						}
						else
							sub.push_back('!');
					}
					else
						sub.push_back('!');
					i += 2;
				}
				else if (std::tolower(_input[i]) == 's'&&std::tolower(_input[i + 1]) == 'e'&&std::tolower(_input[i + 2]) == 'c')
				{
					if (sub.size() > 0)
					{
						if (isdigit(sub[sub.size() - 1]) || sub[sub.size() - 1] == ')' || ((sub[sub.size() - 1] >= 65 && sub[sub.size() - 1] <= 90) || sub[sub.size() - 1] >= 97 && sub[sub.size() - 1] <= 122))
						{
							sub.push_back('*');
							sub.push_back('&');
						}
						else
							sub.push_back('&');
					}
					else
						sub.push_back('&');
					i += 2;
					i += 2;
				}
				else if (std::tolower(_input[i]) == 'c'&&std::tolower(_input[i + 1]) == 'o'&&std::tolower(_input[i + 2]) == 's')
				{
					if (sub.size() > 0)
					{
						if (isdigit(sub[sub.size() - 1]) || sub[sub.size() - 1] == ')' || ((sub[sub.size() - 1] >= 65 && sub[sub.size() - 1] <= 90) || sub[sub.size() - 1] >= 97 && sub[sub.size() - 1] <= 122))
						{
							sub.push_back('*');
							sub.push_back('@');
						}
						else
							sub.push_back('@');
					}
					else
						sub.push_back('@');
					i += 2;
				}
				else if (std::tolower(_input[i]) == 'c'&&std::tolower(_input[i + 1]) == 's'&&std::tolower(_input[i + 2]) == 'c')
				{
					if (sub.size() > 0)
					{
						if (isdigit(sub[sub.size() - 1]) || sub[sub.size() - 1] == ')' || ((sub[sub.size() - 1] >= 65 && sub[sub.size() - 1] <= 90) || sub[sub.size() - 1] >= 97 && sub[sub.size() - 1] <= 122))
						{
							sub.push_back('*');
							sub.push_back('%');
						}
						else
							sub.push_back('%');
					}
					else
						sub.push_back('%');
					i += 2;
				}
				else if (std::tolower(_input[i]) == 'c'&&std::tolower(_input[i + 1]) == 'o'&&std::tolower(_input[i + 2]) == 't')
				{
					if (sub.size() > 0)
					{
						if (isdigit(sub[sub.size() - 1]) || sub[sub.size() - 1] == ')' || ((sub[sub.size() - 1] >= 65 && sub[sub.size() - 1] <= 90) || sub[sub.size() - 1] >= 97 && sub[sub.size() - 1] <= 122))
						{
							sub.push_back('*');
							sub.push_back('#');
						}
						else
							sub.push_back('#');
					}
					else
						sub.push_back('#');
					i += 2;
				}
				else if (std::tolower(_input[i]) == 't'&&std::tolower(_input[i + 1]) == 'a'&&std::tolower(_input[i + 2]) == 'n')
				{
					if (sub.size() > 0)
					{
						if (isdigit(sub[sub.size() - 1]) || sub[sub.size() - 1] == ')' || ((sub[sub.size() - 1] >= 65 && sub[sub.size() - 1] <= 90) || sub[sub.size() - 1] >= 97 && sub[sub.size() - 1] <= 122))
						{
							sub.push_back('*');
							sub.push_back('$');
						}
						else
							sub.push_back('$');
					}
					else
						sub.push_back('$');
					i += 2;
				}
				else
				{
					if (sub.size() > 0)
					{
						if (_input[i] == '^' || this->priority(_input[i]) == 1 || this->priority(_input[i]) == 2)
							sub.push_back(_input[i]);
						else if (sub[sub.size() - 1] == ')' || ((sub[sub.size() - 1] >= 65 && sub[sub.size() - 1] <= 90) || sub[sub.size() - 1] >= 97 && sub[sub.size() - 1] <= 122) || isdigit(sub[sub.size() - 1]))
						{
							if (_input[i] != ')')
							{
								sub.push_back('*');
								sub.push_back(_input[i]);
							}
							else
							{
								sub.push_back(_input[i]);
							}
						}
						else {
							sub.push_back(_input[i]);
						}
					}
					else
					{
						sub.push_back(_input[i]);
					}
				}

			}
			else {
				if (sub.size() > 0)
				{
					if (_input[i] == '^' || this->priority(_input[i]) == 1 || this->priority(_input[i]) == 2)
						sub.push_back(_input[i]);
					else if (sub[sub.size() - 1] == ')' || ((sub[sub.size() - 1] >= 65 && sub[sub.size() - 1] <= 90) || sub[sub.size() - 1] >= 97 && sub[sub.size() - 1] <= 122) || isdigit(sub[sub.size() - 1]))
					{
						if (_input[i] != ')')
						{
							sub.push_back('*');
							sub.push_back(_input[i]);
						}
						else
						{
							sub.push_back(_input[i]);
						}
					}
					else {
						sub.push_back(_input[i]);
					}
				}
				else
				{
					sub.push_back(_input[i]);
				}
			}


		}
		else if (_input[i] == '(')
		{
			if (sub.size() > 0)
			{

				if (sub[sub.size() - 1] == ')' || ((sub[sub.size() - 1] >= 65 && sub[sub.size() - 1] <= 90) || sub[sub.size() - 1] >= 97 && sub[sub.size() - 1] <= 122) || isdigit(sub[sub.size() - 1]))
				{
					if (_input[i] != ')')
					{
						sub.push_back('*');
						sub.push_back(_input[i]);
					}
					else
					{
						sub.push_back(_input[i]);
					}
				}
				else {
					sub.push_back(_input[i]);
				}
			}
			else
			{
				sub.push_back(_input[i]);
			}
		}
		else {
			if (_input[i] != ' ' && _input[i]!= '�@')
			{
				if (sub.size() > 0)
				{
					if ((sub[sub.size() - 1] == '(' || sub[sub.size() - 1] == '~'|| sub[sub.size() - 1]=='^' || sub[sub.size() - 1] == '*' || sub[sub.size() - 1] == '/' || priority(sub[sub.size() - 1]) ==3) && _input[i] == '-') //�ܭt��
						sub.push_back('~');
					else if (_input[i] == '-' && (this->priority(sub[sub.size() - 1]) == 1 || this->priority(sub[sub.size() - 1]) == 2))
					{
						sub.push_back('~');
					}
					else if (_input[i] == '^' || this->priority(_input[i]) == 1 || this->priority(_input[i]) == 2)
						sub.push_back(_input[i]);
					else if (sub[sub.size() - 1] == ')' || ((sub[sub.size() - 1] >= 65 && sub[sub.size() - 1] <= 90) || sub[sub.size() - 1] >= 97 && sub[sub.size() - 1] <= 122))
					{
						if (_input[i] != ')')
						{
							sub.push_back('*');
							sub.push_back(_input[i]);
						}
						else
						{
							sub.push_back(_input[i]);
						}
					}
					else {
						sub.push_back(_input[i]);
					}
				}
				else
				{
					if (_input[i] == '-')
						sub.push_back('~');
					else
					{
						sub.push_back(_input[i]);
					}
				}
			}

		}
	}

	std::string ans = "";
	int countdive = 0;
	for (int i = 0; i < sub.size(); i++)
	{
		if (sub[i] == '/')
		{
			countdive++;
		}
	}
	for (int j = 0; j < countdive; j++)
	{
		for (int i = 0; i < sub.size(); i++)
		{
			if (sub[i] == '/') {
				ans += "*(";

				i++;
				int quahao = 0;
				while (1)
				{

					if (quahao == 0 && (sub[i] == '-' || sub[i] == '+'))
					{
						break;

					}
					else {
						if (sub[i] == '(')
						{
							quahao++;

						}
						else if (sub[i] == ')')
						{
							quahao--;
						}
						if (sub[i] == '/') countdive++;
						ans += sub[i];

						if (i + 1 == sub.size()) break;
					}
					i++;

				}
				ans += ")^~1";

			}
			else {
				ans += sub[i];
			}
		}
		sub = ans;
		ans.clear();
		ans = "";
	}
	 /* if (countdive > 0)
	  {
		  std::cout << ans << std::endl;
		  sub = ans;
		  ans.clear();
		  ans = "";
		  goto again;

	  }
	  else {
		  sub = ans;
		  ans.clear();
		  ans = "";
	  }*/

	return sub;
}

std::string Optimization::NewEquation(std::map<std::string, std::string>_variable)
{
	std::string ans = "";
	for (int i = 0; i <orignal.size(); i++)
	{
		if (((orignal[i] >= 65 && orignal[i] <= 90) || orignal[i] >= 97 && orignal[i] <= 122))
		{
			std::set<char>::iterator it;
			std::map<std::string, std::string>::iterator iter;
			bool isFind = false;
			for (it=variable.begin();it!=variable.end();it++)
			{
				if (orignal[i] ==*it)
				{
					std::string tem = "";
					tem += *it;
					iter = _variable.find(tem);
					if (iter != _variable.end())//���
					{
						ans.push_back('(');
						ans += this->dealstring(iter->second);
						ans.push_back(')');
						isFind = true;
						break;
					}
				}

				
			}
			if (!isFind)
			{
				ans.push_back(orignal[i]);
			}
		}
		else {
			ans.push_back(orignal[i]);
		}

	}
	return ans;
}

bool Optimization::judgeTrigonometric(char a, char b, char c)
{
	if (a == 's'&&b == 'i'&&c == 'n')
	{
		return true;
	}
	else if (a== 's'&&b == 'e'&&c == 'c')
	{
		return true;
	}
	else if (a == 'c'&&b == 'o'&&c == 's')
	{
		return true;
	}
	else if (a == 'c'&&b == 's'&&c == 'c')
	{
		return true;
	}
	else if (a == 'c'&&b == 'o'&&c == 't')
	{
		return true;
	}
	else if (a == 't'&&b == 'a'&&c == 'n')
	{
		return true;
	}
	else
		return false;
}

int Optimization::getNDimension()
{
	return variable.size();
}

std::string Optimization::getinput()
{
	return input;
}

std::string Optimization::getorignal()
{
	return orignal;
}

double Optimization::GoldenSearch(double lowerbound, double middle, double upperbound, const double tau,double count)
{
	count++;
	/*
		lowerbound =leftbound
		upperbound =rightbound
		middle=left<middle<right
	*/
	double x;
	if (upperbound - middle > middle - lowerbound)
		x = middle + resphi * (upperbound - middle);
	else
		x = middle - resphi * (middle-lowerbound);
	if (abs(upperbound - lowerbound) < tau*(abs(middle) + abs(x))||count>=20)
		return (lowerbound + upperbound) / 2;
	std::map<std::string, double>fx;
	std::map<std::string, double>fb;
	std::string v = "";
	std::set<char>::iterator it=variable.begin();
	char a = *it;
	v +=a;
	fx.insert(std::pair<std::string, double>(v, x));
	fb.insert(std::pair<std::string, double>(v, middle));
	
	if (this->eval(fx) < this->eval(fb)) {
		if (upperbound - middle > middle - lowerbound) return this->GoldenSearch(middle, x, upperbound, tau,count);
		else return this->GoldenSearch(lowerbound, x, middle, tau,count);
	}
	else {
		if (upperbound - middle > middle - lowerbound) return this->GoldenSearch(lowerbound, middle, x, tau,count);
		else return this->GoldenSearch( x, middle,upperbound,tau,count);
	}

}

void Optimization::Powell(std::queue<std::map<std::string, double>> nvec,double err,int count)
{
	count++;
	std::map<std::string, double>newpush;
	std::map<std::string, double>Firstvec = initial;
	std::map<std::string, double>check;
	std::map<std::string, double>::iterator it_vec;
	std::map<std::string, double>::iterator it_intial;
	std::map<std::string, restrictVariable>::iterator it_restrict;
	double *NgoldenAns = new double[this->getNDimension()];
	double *FAns = new double[this->getNDimension()];
	double Finitial = this->eval(initial);
	std::queue<std::map<std::string, double>> newvec = nvec;
	newvec.pop();//�N�Ĥ@��pop��

	#pragma region �C�@�Ӻ��װ��d��
	for (int i = 0; i < this->getNDimension(); i++)
	{
		double upperbound = 2.22507e-308;
		double lowerbound = 1.79769e+308;
		std::string make = "";
		std::map<std::string, std::string> newequ;
		//��X��ɻP�s�@function
		for (it_vec = nvec.front().begin(); it_vec != nvec.front().end(); it_vec++)
		{
			for (it_intial = initial.begin(); it_intial != initial.end(); it_intial++)
			{
				if (it_intial->first == it_vec->first)//�O�_�ܼƤ@��
				{
					double low, high;
					//�P�_�����x�}�O�_��0
					//std::cout <<"test" <<it_vec->second << std::endl;
					if (it_vec->second == 0)
					{
						std::stringstream ss;
						std::string t;
						ss << it_intial->second;
						ss >> t;
						make = t;
						newequ.insert(std::pair<std::string, std::string>(it_intial->first, make));
					}
					else
					{
						
						std::stringstream ss, ss2;
						std::string t, t2;
						ss << it_vec->second;
						ss >> t;
						ss2 << it_intial->second;
						ss2 >> t2;
						make = t2;
						make += "+x*";
						make +=t;

						newequ.insert(std::pair<std::string, std::string>(it_intial->first, make));

						it_restrict = rrestrict.find(it_intial->first);
						low = (it_intial->second - it_restrict->second.upperbound)/ it_vec->second;
						high = (it_intial->second - it_restrict->second.lowerbound)/ it_vec->second;
						if (low < lowerbound) lowerbound = low;
						if (high > upperbound) upperbound = high;
					}
				}
			}
		}


		



		double middle = (upperbound - lowerbound) * phi;
		std::string ne = this->NewEquation(newequ);
		Optimization newop(ne);
		NgoldenAns[i] = newop.GoldenSearch(lowerbound, middle, upperbound, 1e-6, 0);
		for (it_vec = nvec.front().begin(); it_vec != nvec.front().end(); it_vec++) //����initial
		{
			for (it_intial = initial.begin(); it_intial != initial.end(); it_intial++)
			{
				if (it_intial->first == it_vec->first)//�O�_�ܼƤ@��
				{
					double judgeg=it_intial->second + NgoldenAns[i] * it_vec->second;//initial���� �P�_�W�L���
					it_restrict = rrestrict.find(it_intial->first);
					if (judgeg > it_restrict->second.upperbound) {
						it_intial->second = it_restrict->second.upperbound;
					}
					else if (judgeg < it_restrict->second.lowerbound) {
						it_intial->second = it_restrict->second.lowerbound;
					}
					else {
						it_intial->second = judgeg;
					}

				}
			}
		}

		FAns[i] = this->eval(initial);
		check = initial;


#pragma region cout
		std::cout << "------------------------------------------------------------------------------------\n";
		std::cout << "��" << count << "����" << i << "\n";
		std::cout << "GoldenSreach:" << NgoldenAns[i] << "\n";
		std::cout << "�W��:" << upperbound << " �U��:" << lowerbound << "\n";
		std::cout << "Vector��\n{ ";
		for (it_intial = initial.begin(); it_intial != initial.end(); it_intial++)
		{
			std::cout << it_intial->second << "  ";
		}
		std::cout << "}\n";
		std::cout << "F(x)=" << FAns[i] << "\n";
		std::cout << "------------------------------------------------------------------------------------\n";
#pragma endregion

		nvec.pop();
	}
	#pragma endregion

	#pragma region �d��new vertex
		//���ĤT��
		double upperbound = 2.22507e-308;
		double lowerbound = 1.79769e+308;
		std::string make = "";
		std::map<std::string, std::string> newequ;
		//��X��ɻP�s�@function
		int i = 0;
		for (it_intial = initial.begin(); it_intial != initial.end(); it_intial++)
			{
				
					double low, high;
					//�P�_�����x�}�O�_��0
					
						
						std::stringstream ss, ss2;
						std::string t, t2;
						ss <<NgoldenAns[i];
						ss >> t;
						ss2 << it_intial->second;
						ss2 >> t2;
						make = t2;
						make += "+x*";
						make += t;
						newequ.insert(std::pair<std::string, std::string>(it_intial->first, make));
						it_restrict = rrestrict.find(it_intial->first);
						newpush.insert(std::pair<std::string,double>(it_intial->first,NgoldenAns[i]));//�s�@�s�����d�I
						low = (it_intial->second - it_restrict->second.upperbound)/NgoldenAns[i];
						high = (it_intial->second - it_restrict->second.lowerbound)/ NgoldenAns[i];
						if (low < lowerbound) lowerbound = low;
						if (high > upperbound) upperbound = high;
				
				i++;
			}
		
		double middle = (upperbound - lowerbound) * phi;
		std::string ne = this->NewEquation(newequ);
		Optimization newop(ne);
		double FinalAns = newop.GoldenSearch(lowerbound, middle, upperbound, 1e-6, 0);
		
		i = 0;
		
			for (it_intial = initial.begin(); it_intial != initial.end(); it_intial++)
			{
				
					double judgeg = it_intial->second + NgoldenAns[i] * FinalAns;//initial����
					it_restrict = rrestrict.find(it_intial->first);
					if (judgeg > it_restrict->second.upperbound) {
						it_intial->second = it_restrict->second.upperbound;
					}
					else if (judgeg < it_restrict->second.lowerbound) {
						it_intial->second = it_restrict->second.lowerbound;
					}
					else {
						it_intial->second = judgeg;
					}

					i++;
				
			}
			double Finalfx = this->eval(initial);
		
		newvec.push(newpush);//�ĤT���I���N
		#pragma region cout
		std::cout << "------------------------------------------------------------------------------------\n";
		std::cout << "��" << count << "����" << this->getNDimension() << "\n";
		std::cout << "GoldenSreach:" << NgoldenAns[i] << "\n";
		std::cout << "�W��:" << upperbound << " �U��:" << lowerbound << "\n";
		std::cout << "Vector��\n{ ";
		for (it_intial = initial.begin(); it_intial != initial.end(); it_intial++)
		{
			std::cout << it_intial->second << "  ";
		}
		std::cout << "}\n";
		std::cout << "F(x)=" << Finalfx << "\n";
		std::cout << "------------------------------------------------------------------------------------\n";
#pragma endregion
	#pragma endregion

	#pragma region �ˬd�O�_�ŦX�d��
		if (count > 60)
		{
		#pragma region cout
		
			std::cout << "------------------------------------------------------------------------------------\n";
			std::cout << "Ans\n";
			std::cout << "Vector��\n{ ";
			for (it_intial = check.begin(); it_intial != check.end(); it_intial++)
			{
				std::cout << it_intial->second << "  ";
			}
			std::cout << "}\n";
			std::cout << "F(x)=" <<FAns[this->getNDimension()-1] << "\n";
			std::cout << "------------------------------------------------------------------------------------\n";
#pragma endregion
			return;
		}
		else if (std::abs((FAns[this->getNDimension()-1] - Finitial)) > err) {

			std::map<std::string, double>Tx;
			double check2 = 0;
			for (it_intial = check.begin(); it_intial != check.end(); it_intial++)
			{
				for (it_vec = Firstvec.begin(); it_vec != Firstvec.end(); it_vec++)
				{
					if (it_intial->first == it_vec->first)
					{
						check2 += std::pow((it_intial->second-it_vec->second),2);
					}
				}
			}
			if (check2 > err)
			{
				
				
				if (count%this->getNDimension() == 0)
				{
					std::queue<std::map<std::string, double>>restart;
					int g = 0;
					for (int k = 0; k < this->getNDimension(); k++)
					{
						std::map<std::string, double> newr;
						newr.clear();
						int j = 0;
						for (it_intial = check.begin(); it_intial != check.end(); it_intial++)
						{
							if (k == j) {
								
								newr.insert(std::pair<std::string, double>(it_intial->first, 1));
								std::cout << it_intial->first << "  " << 1 << "\n";
							}
							else {
								newr.insert(std::pair<std::string, double>(it_intial->first, 0));
								std::cout << it_intial->first << "  " << 0 << "\n";
							}
							j++;
						}
						restart.push(newr);
					}
					this->Powell(restart, err, count);
				}
				else
					this->Powell(newvec,err,count);
			}
			else {
#pragma region cout

				std::cout << "------------------------------------------------------------------------------------\n";
				std::cout << "Ans\n";
				std::cout << "Vector��\n{ ";
				for (it_intial = check.begin(); it_intial != check.end(); it_intial++)
				{
					std::cout << it_intial->second << "  ";
				}
				std::cout << "}\n";
				std::cout << "F(x)=" << FAns[this->getNDimension()-1] << "\n";
				std::cout << "------------------------------------------------------------------------------------\n";
#pragma endregion
			}
		}
		else {
#pragma region cout

			std::cout << "------------------------------------------------------------------------------------\n";
			std::cout << "Ans\n";
			std::cout << "Vector��\n{ ";
			for (it_intial = check.begin(); it_intial != check.end(); it_intial++)
			{
				std::cout << it_intial->second << "  ";
			}
			std::cout << "}\n";
			std::cout << "F(x)=" << FAns[this->getNDimension()-1] << "\n";
			std::cout << "------------------------------------------------------------------------------------\n";
#pragma endregion
		}
	#pragma endregion

		return;
}

std::string Optimization::differentiation(std::string destination)
{
	std::map<std::string, std::string>temofinterval;
	std::map<std::string, std::string>::iterator it;
	std::vector<std::string>output;
	std::vector<std::string> ans;
	int top = -1;
	for (int i = 0; i < postfix.size(); i++)
	{
		//std::cout <<i<<"�h��"<< postfix[i] << std::endl;
		if (isdigit(postfix[i][0]))//�ݨC��vector�Ĥ@��bit�O�_���Ʀr
		{
			temofinterval.insert(std::pair<std::string, std::string>(postfix[i], "0"));
			ans.push_back(postfix[i]);
			top++;
		}
		else if ((postfix[i][0] >= 65 && postfix[i][0] <= 90) || (postfix[i][0] >= 97 && postfix[i][0] <= 122))
		{
			if (postfix[i] == destination) {
				temofinterval.insert(std::pair<std::string, std::string>(postfix[i], "1"));
				ans.push_back(postfix[i]);
				top++;
			}
			else {
				temofinterval.insert(std::pair<std::string, std::string>(postfix[i], "0"));
				ans.push_back(postfix[i]);
				top++;
			}
		}
		else if (postfix[i] == "~") //�ܦ��t��
		{
			std::string t = ""; \
			std::string t2="-";
			it = temofinterval.find(ans[top]);
			t2 +=it->second;
			t += "-";
			t+=ans[top];
			ans[top] = t;
			temofinterval.insert(std::pair<std::string,std::string>(ans[top],t2));
		}
		else if (postfix[i] == "+"||postfix[i]=="-")
		{
			std::cout << "i" << i << postfix[i] << std::endl;
			std::string key = "";
			key += ans[top - 1];
			key += postfix[i];
			key += ans[top];
			key += "";

			std::string subarray = "(";
			it = temofinterval.find(ans[top - 1]);
			subarray += it->second;
			subarray += postfix[i];//�s���e+��
			it = temofinterval.find(ans[top]);
			subarray += it->second;
			subarray += ")";
			top--;
			ans.pop_back();
			ans[top] = key;
			temofinterval.insert(std::pair<std::string, std::string>(key, subarray));
		}
		else if(postfix[i]=="*")
		{
			//�L�e��+�L�᭱
			std::string key = "";
			key += ans[top - 1];
			key += "*";
			key += ans[top];

			std::string subarray = "(";
			it = temofinterval.find(ans[top - 1]);
			subarray += it->second;
			subarray += "*";
			subarray += ans[top];
			subarray += "+";//�s���e+��
			subarray += ans[top - 1];
			subarray += "*";
			it = temofinterval.find(ans[top]);
			subarray += it->second;
			subarray += ")";

			top--;
			ans.pop_back();
			ans[top] = key;
			temofinterval.insert(std::pair<std::string, std::string>(key,subarray));

			
		}
		else if (postfix[i] == "^")
		{
			//�~��*�W���L
			std::string key = "";
			key += ans[top - 1];
			key += "^";
			key += ans[top];


			std::string subarray = "(";
			std::stringstream ss;
			ss << ans[top];
			double a;
			ss >> a;
			a = a - 1;
			ss.clear();
			ss << a;
			std::string h;
			ss >> h;
			subarray += ans[top];
			subarray += "*";
			subarray += ans[top - 1];
			subarray += "^";
			subarray += h;
			subarray += "*";
			it = temofinterval.find(ans[top-1]);
			subarray += it->second;
			subarray += ")";
			top--;
			ans.pop_back();
			ans[top] = key;
			temofinterval.insert(std::pair<std::string, std::string>(key, subarray));



		}
		else if (postfix[i] == "!")
		{
			//�~��*�W���L
			std::string key = "";
			key +="!";
			key += ans[top];

			//�~��*�̭�
			std::string subarray = "(";
			subarray += "@";
			subarray += ans[top];
			subarray += "*";
			it = temofinterval.find(ans[top]);
			subarray += it->second;
			subarray += ")";
			
			ans[top] = key;
			temofinterval.insert(std::pair<std::string, std::string>(key, subarray));
		}
		else if (postfix[i] == "@")
		{
		//�~��*�W���L
		std::string key = "";
		key += "@";
		key += ans[top];

		//�~��*�̭�
		std::string subarray = "(";
		subarray += "-!";
		subarray += ans[top];
		subarray += "*";
		it = temofinterval.find(ans[top]);
		subarray += it->second;
		subarray += ")";

		ans[top] = key;
		temofinterval.insert(std::pair<std::string, std::string>(key, subarray));
		}
		else if (postfix[i] == "$")
		{
		//�~��*�W���L
		std::string key = "";
		key += "&";
		key += ans[top];

		//�~��*�̭�
		std::string subarray = "(";
		subarray += "&^2";
		subarray += ans[top];
		subarray += "*";
		it = temofinterval.find(ans[top]);
		subarray += it->second;
		subarray += ")";

		ans[top] = key;
		temofinterval.insert(std::pair<std::string, std::string>(key, subarray));
		}
		else if (postfix[i] == "%")
		{
		//�~��*�W���L
		std::string key = "";
		key += "%";
		key += ans[top];

		//�~��*�̭�
		std::string subarray = "(";
		subarray += "-%";
		subarray += ans[top];
		subarray += "*";
		it = temofinterval.find(ans[top]);
		subarray += it->second;
	

		subarray += "*#";
		subarray += ans[top];
		subarray += "*";
		it = temofinterval.find(ans[top]);
		subarray += it->second;
		subarray += ")";
		ans[top] = key;
		temofinterval.insert(std::pair<std::string, std::string>(key, subarray));
		}
		else if (postfix[i] == "&")
		{
		//�~��*�W���L
		std::string key = "";
		key += "&";
		key += ans[top];

		//�~��*�̭�
		std::string subarray = "(";
		subarray += "&";
		subarray += ans[top];
		subarray += "*";
		it = temofinterval.find(ans[top]);
		subarray += it->second;


		subarray += "*$";
		subarray += ans[top];
		subarray += "*";
		it = temofinterval.find(ans[top]);
		subarray += it->second;
		subarray += ")";
		ans[top] = key;
		temofinterval.insert(std::pair<std::string, std::string>(key, subarray));
		}
		else if (postfix[i] == "#")
		{
		//�~��*�W���L
		std::string key = "";
		key += "&";
		key += ans[top];

		//�~��*�̭�
		std::string subarray = "(";
		subarray += "-%^2";
		subarray += ans[top];
		subarray += "*";
		it = temofinterval.find(ans[top]);
		subarray += it->second;
		subarray += ")";

		ans[top] = key;
		temofinterval.insert(std::pair<std::string, std::string>(key, subarray));
		}
	}
	return temofinterval[ans[top]];
}

VectorSpace Optimization::gradient() {
	VectorSpace gradient_value(this->getNDimension());
	int index = 0;
	for (std::set<char>::iterator it = variable.begin(); it != variable.end(); it++) {
		std::string var = "";
		var += *it;
		Optimization partial_equation(this->differentiation(var));
		gradient_value.changeNumInSpace(partial_equation.eval(this->initial), index++);
	}
	return gradient_value;
}

std::vector<std::string> Optimization::steepDescent() {

	int count = 0; 
	std::map<std::string, std::string> many_to_one;
	VectorSpace current_point_gradient;
	VectorSpace current_point(this->getNDimension());
	double initial_point_gradient_norm;
	while (true) {
		std::cout << "count = " << count << std::endl;
		int i = 0;
		for (std::map<std::string, double>::iterator it = initial.begin(); it != initial.end(); it++)
			current_point.changeNumInSpace(it->second, i++);
		double current_point_norm = current_point.Norm();
		double negative = -1.0;
		current_point_gradient = this->gradient() * negative;
		if (count == 0) {
			initial_point_gradient_norm = current_point_gradient.Norm();
		}
		else if (current_point_gradient.Norm() < 1e-6 * initial_point_gradient_norm)
				break;
		restrictVariable alpha_bound;
		CalculationBound(alpha_bound, current_point_gradient);
		if (alpha_bound.lowerbound < 0.0)
			alpha_bound.lowerbound = 0.0;
		i = 0;
		for (std::map<std::string, double>::iterator it = initial.begin(); it != initial.end(); it++) {
			std::string cp_str = std::to_string(current_point.getNumInSpace(i));
			std::string h_str = std::to_string(current_point_gradient.getNumInSpace(i));
			if (current_point_gradient.getNumInSpace(i) >= 0.0)
				many_to_one[it->first] = cp_str + "+" + h_str + "*a";
			else
				many_to_one[it->first] = cp_str + h_str + "*a";
			i++;
		}
		Optimization one_dimension_func(NewEquation(many_to_one));
		double alpha = one_dimension_func.GoldenSearch(alpha_bound.lowerbound, 
			(alpha_bound.upperbound - alpha_bound.lowerbound)*0.5, 
			alpha_bound.upperbound, 1e-6, 0);
		std::cout << "alpha: " << alpha << std::endl;
		VectorSpace next_point(current_point + current_point_gradient * alpha);
		std::cout << "next point: " << next_point;
		i = 0;
		for (std::map<std::string, double>::iterator it = initial.begin(); it != initial.end(); it++)
			it->second = next_point.getNumInSpace(i++);
		if (count == 50)
			break;
		if ((next_point - current_point).Norm() < 1e-6 * current_point_norm)
			break;
		count++;
		
	}
	std::cout << "min : " << eval(initial) << std::endl;
	return std::vector<std::string>();
}

std::vector<std::string> Optimization::newton() {
	int count = 0;
	VectorSpace current_point_gradient;
	VectorSpace current_point(this->getNDimension());
	double initial_point_gradient_norm;
	while (true) {
		VectorSpace next_point(this->getNDimension());
		Matrix hessian(this->Hessianmatrix());
		int i = 0;
		for (std::map<std::string, double>::iterator it = initial.begin(); it != initial.end(); it++)
			current_point.changeNumInSpace(it->second, i++);
		current_point_gradient = this->gradient();
		double current_point_norm = current_point.Norm();
		Matrix hessian_inv = hessian.Inverse();
		Matrix next = current_point - hessian_inv * current_point_gradient;
		for (int i = 0; i < next.getRow(); i++)
			for (int j = 0; j < next.getcolumn(); j++)
				next_point.changeNumInSpace(next.getnuminMatrix(i, j), i*next.getcolumn() + j);
		std::cout << " Hessain : " << hessian << std::endl;
		std::cout << " Hessain inverse : " << hessian_inv << std::endl;
		std::cout << "x : " << next_point << std::endl;
		i = 0;
		for (std::map<std::string, double>::iterator it = initial.begin(); it != initial.end(); it++)
			it->second = next_point.getNumInSpace(i++);
		if (count == 0) {
			initial_point_gradient_norm = current_point_norm;
		}
		else if (current_point_gradient.Norm() < 1e-6 * initial_point_gradient_norm)
			break;
		if ((next_point - current_point).Norm() < 1e-6 * current_point_norm)
			break;
		count++;
		if (count == 10)
			break;
	}
	std::cout << "min : " << eval(initial) << std::endl;
	return std::vector<std::string>();
}

std::vector<std::string> Optimization::conjugateGradient() {
	
	int count = 0;
	std::map<std::string, std::string> many_to_one;
	VectorSpace current_point_gradient;
	VectorSpace previous_point_gradient;
	VectorSpace previous_s;
	VectorSpace current_point(this->getNDimension());
	double previous_value;
	while (true) {
		VectorSpace next_point(this->getNDimension());
		double negative = -1.0;
		int i = 0;
		for (std::map<std::string, double>::iterator it = initial.begin(); it != initial.end(); it++)
			current_point.changeNumInSpace(it->second, i++);
		current_point_gradient = this->gradient();
		VectorSpace current_s(this->getNDimension());
		if (count == 0) {
			current_s = current_point_gradient * negative;
		}
		else {
			double beta = current_point_gradient * current_point_gradient / (previous_point_gradient * previous_point_gradient);
			
			std::cout << "beta : " << beta << std::endl;
			current_s = current_point_gradient  * negative + previous_s * beta;
		}
		std::cout << "s : " << current_s;
		restrictVariable alpha_bound;
		CalculationBound(alpha_bound, current_s);
		if (alpha_bound.lowerbound < 0.0)
			alpha_bound.lowerbound = 0.0;
		i = 0;
		for (std::map<std::string, double>::iterator it = initial.begin(); it != initial.end(); it++) {
			std::string cp_str = std::to_string(current_point.getNumInSpace(i));
			std::string s_str = std::to_string(current_s.getNumInSpace(i));
			if (current_s.getNumInSpace(i) >= 0.0)
				many_to_one[it->first] = cp_str + "+" + s_str + "*a";
			else
				many_to_one[it->first] = cp_str + s_str + "*a";
			i++;
		}
		Optimization one_dimension_func(NewEquation(many_to_one));
		double interval[5];
		double interval_length = (alpha_bound.upperbound - alpha_bound.lowerbound) / 5.0;
		for (int i = 0; i < 4; i++) {
			interval[i] = alpha_bound.lowerbound + interval_length * i;
		}
		interval[4] = alpha_bound.upperbound;
		double alpha = 10000000000;
		for (int i = 0; i < 4; i++) {

			double temp = one_dimension_func.GoldenSearch(interval[i],
				(interval[i + 1] - interval[i]) * 0.5,
				interval[i + 1], 1e-6, 0);
			if (temp < alpha)
				alpha = temp;
		}
		std::cout << "alpha : " << alpha << std::endl;
		next_point = current_point + current_s * alpha;
		std::cout << "x : " << next_point;
		previous_point_gradient = current_point_gradient;
		previous_s = current_s;
		i = 0;
		for (std::map<std::string, double>::iterator it = initial.begin(); it != initial.end(); it++)
			it->second = next_point.getNumInSpace(i++);
		double current_value = this->eval(initial);
		if (count != 0) {
			if (abs(current_value - previous_value) < 1e-6)
				break;
			VectorSpace delta = next_point - current_point;
			if (delta * delta < 1e-6)
				break;
			VectorSpace next_point_gradient = this->gradient();
			if (next_point_gradient * next_point_gradient < 1e-6)
				break;
		}
		previous_value = current_value;
		if (count == 50)
			break;
		count++;
	}
	return std::vector<std::string>();
}
bool Optimization::insertInitialVariable(std::string _name, double _num)
{
	std::map<std::string, double>::iterator it;
	it = initial.find(_name);
	if (it == initial.end())
	{
		return false;
	}
	else {
		it->second = _num;
		return true;
	}
}

void Optimization::deleteinitial()
{
	initial.clear();
}
double Optimization::CalculationLowerbound(std::string name, double x, double y)
{
	std::map<std::string, double>::iterator it;
	it = initial.find(name);
	return (it->second - x) / y;
}

double Optimization::CalculationUpperbound(std::string name, double x, double y)
{

	std::map<std::string, double>::iterator it;
	it = initial.find(name);
	return (it->second - x) / y;
}
bool Optimization::insertEveryVariableRestrict(std::string _name, restrictVariable _num)
{
	std::map<std::string, restrictVariable>::iterator it;
	it = rrestrict.find(_name);
	if (it == rrestrict.end())
	{
		return false;
	}
	else {
		it->second = _num;
		return true;
	}
}

void Optimization::CalculationBound(restrictVariable &alpha_bound,VectorSpace h) {
	
	alpha_bound.lowerbound = -1e-100;
	alpha_bound.upperbound = 1e100;
	VectorSpace initial_point(this->getNDimension());
	int i = 0;
	for (std::map<std::string, double>::iterator it = initial.begin(); it != initial.end(); it++)
		initial_point.changeNumInSpace(it->second, i++);
	i = 0;
	for (std::map<std::string, restrictVariable>::iterator it = rrestrict.begin(); it != rrestrict.end(); it++) {
		
		double h_value = h.getNumInSpace(i);
		if (h_value == 0.0)
			continue;
		else if (h_value > 0.0) {
			double low, high;
			low = (it->second.lowerbound - initial_point.getNumInSpace(i)) / h.getNumInSpace(i);
			if (low > alpha_bound.lowerbound)
				alpha_bound.lowerbound = low;
			high = (it->second.upperbound - initial_point.getNumInSpace(i)) / h.getNumInSpace(i);
			if (high < alpha_bound.upperbound)
				alpha_bound.upperbound = high;
		}
		else {
			double low, high;
			high = (it->second.lowerbound - initial_point.getNumInSpace(i)) / h.getNumInSpace(i);
			if (high < alpha_bound.upperbound)
				alpha_bound.upperbound = high;
			low = (it->second.upperbound - initial_point.getNumInSpace(i)) / h.getNumInSpace(i);
			if (low > alpha_bound.lowerbound)
				alpha_bound.lowerbound = low;
		}
		i++;
	}
	
}

void Optimization::Quasi_Newton()
{
	std::map<std::string, restrictVariable>::iterator itr;


	std::map<std::string, double>::iterator iti;
	std::set<char>::iterator itv;
	iti = initial.begin();
	Matrix F("F", this->getNDimension(), this->getNDimension()); //���Hessian
	Matrix G("d", this->getNDimension(), 1);//INITIAL
	Matrix Ans("Ans", this->getNDimension(), 1);
	iti = initial.begin();
	for (int i = 0; i < this->getNDimension(); i++)
	{
		F.replaceNuminMatrix(i, i, 1);//Hessian�Ĥ@���@���x�}
		G.replaceNuminMatrix(i, 0, iti->second);//��INITIAL
		iti++;
	}
	Ans = G;
	int count = 0;
	double golden = 0;



	while (1)
	{
		Matrix difffirst("diff", this->getNDimension(), 1);//g^(k)
		iti = initial.begin();
		bool isbreak = true;
		for (int i = 0; i < this->getNDimension(); i++) //�L��
		{
			Optimization tem(this->differentiation(iti->first));
			double temnum = tem.eval(initial); //��Xgradient
			std::cout << iti->first << "�L��" << this->differentiation(iti->first) << std::endl;
			difffirst.replaceNuminMatrix(i, 0, temnum); //�P�_g^(k)==0
			if (std::abs(temnum) > 1e-6) {
				isbreak = false;
			}
			iti++;
		}
		if (isbreak || count >= 60) {//g^(k)==0 �άO���F60�����N
			std::cout << "Ans:\n";
			std::cout << "H==>\n" << F;
			std::cout << "�I��\n" << G;
			break;
		}
		else {
			std::cout << "��" << count << "������:\n";
			std::cout << "Golden==>" << golden << "\n";
			std::cout << "H==>\n" << F;
			std::cout << "�I��\n" << G;
			Matrix d = F * difffirst; //���Xd^(k)
			std::cout << difffirst;
			d = d * (-1);// d(k) = ��Fk g(k)

			std::string t;
			int k = 0;
			std::map<std::string, std::string>neweq;
			restrictVariable r;
			for (iti = initial.begin(); iti != initial.end(); iti++)
			{
				t.clear();
				std::stringstream ss;
				std::string e = "";
				ss << G.getnuminMatrix(k, 0);
				ss >> t;
				e += t;
				e += "+x*";
				ss.clear();
				ss.str("");
				ss << d.getnuminMatrix(k, 0);
				ss >> t;
				e += t;
				std::cout << e << std::endl; //���Xx^(k)+a*d^(k)
				neweq.insert(std::pair<std::string, std::string>(iti->first, e));
				//itr = rrestrict.find(iti->first);
				//double low = this->CalculationLowerbound(iti->first,itr->second.upperbound,G.getnuminMatrix(k,0)); //��Xgolden��������
				//double up= this->CalculationLowerbound(iti->first, itr->second.lowerbound, G.getnuminMatrix(k,0));
				//if (k == 0)
				//{
				//	r.lowerbound = low;
				//	r.upperbound = up;
				//}
				//else {
				//	if (r.lowerbound > low) r.lowerbound = low;
				//	if (r.upperbound < up)r.upperbound = up;
				//}
				k++;
			}
			Optimization newequ1(this->NewEquation(neweq));
			restrictVariable iif = newequ1.checkvanszerofive("x"); //�ݬO�_���򸹤��B���ܼ�
			if (iif.upperbound == 1.79769e+308) iif.upperbound = 100;
			if (iif.lowerbound == 2.22507e-308) iif.lowerbound = 0;
			newequ1.insertEveryVariableRestrict("x", iif);
			std::cout << "����" << iif.lowerbound << "   " << iif.upperbound << std::endl;
			golden = newequ1.GoldenSearch(iif.lowerbound, (iif.upperbound - iif.lowerbound) * phi, iif.upperbound, 1e-5, 0);//golden ��alpha
			Matrix g = G; //g^(K)��i��
			Matrix alphadiffg("al", this->getNDimension(), 1);
			iti = initial.begin();
			for (int i = 0; i < this->getNDimension(); i++)//�Ninitial�I��s G�]��s
			{
				iti->second += d.getnuminMatrix(i, 0) * golden;
				G.replaceNuminMatrix(i, 0, iti->second);
				iti++;
			}
			iti = initial.begin();
			for (int i = 0; i < this->getNDimension(); i++) //�D�Xdelta g^(k)=g^(k+1)-g^(k) 
			{
				Optimization tem(this->differentiation(iti->first));
				double temnum = tem.eval(initial);
				alphadiffg.replaceNuminMatrix(i, 0, (temnum - difffirst.getnuminMatrix(i, 0)));
				iti++;
			}
			Matrix alphax = d * (golden); //delta x^(k)=alpha*d^(k)
			//�U���B�J��dsp�t��k
			Matrix onemother = alphax.Transpose() * alphadiffg;
			Matrix twomother = alphadiffg.Transpose() * F * alphadiffg;
			Matrix twochild = F * alphadiffg;
			F = F + (alphax * alphax.Transpose()) / onemother.getnuminMatrix(0, 0) - ((F * alphadiffg) * twochild.Transpose()) / twomother.getnuminMatrix(0, 0);
			//F��s���� ���U�@���c�N
		}
		count++;
	}





	//Matrix Next;
	//itv = variable.begin();
	//iti = initial.begin();
	//for (int i = 0; i <this->getNDimension(); i++)
	//{
	//	F.replaceNuminMatrix(i, i, 1);
	//	std::string diffv="";
	//	diffv+= *itv;
	//	Ans.replaceNuminMatrix(i, 0, iti->second);
	//	Optimization diff(this->differentiation(diffv));
	//	G.replaceNuminMatrix(i, 0, diff.eval(initial));
	//	itv++;
	//	iti++;
	//	
	//} 
	////���x�}
	//Matrix D;
	//Next = Ans;
	//D = (F * (-1))*G;
	//int k = 0;
	//std::map<std::string, std::string>neweq;
	//neweq.clear();
	//std::string t = "";
	//restrictVariable r;//��golden�ұ���������
	//for (iti = initial.begin();iti!=initial.end();iti++)
	//{
	//	t.clear();
	//	std::stringstream ss;
	//	std::string e = "";
	//	ss << Ans.getnuminMatrix(k, 0);
	//	ss >> t;
	//	e += t;
	//	e+= "+x";
	//	ss.clear();
	//	ss.str("");
	//	ss << G.getnuminMatrix(k, 0);
	//	ss >> t;
	//	e += t;
	//	neweq.insert(std::pair<std::string, std::string>(iti->first,e));
	//	itr = rrestrict.find(iti->first);
	//	double low = this->CalculationLowerbound(iti->first,itr->second.upperbound,G.getnuminMatrix(k,0)); //��Xgolden��������
	//	double up= this->CalculationLowerbound(iti->first, itr->second.lowerbound, G.getnuminMatrix(k,0));
	//	if (k == 0)
	//	{
	//		r.lowerbound = low;
	//		r.upperbound = up;
	//	}
	//	else {
	//		if (r.lowerbound > low) r.lowerbound = low;
	//		if (r.upperbound < up)r.upperbound = up;
	//	}
	//	k++ ;
	//}

	//Optimization newequ1(this->NewEquation(neweq));
	//restrictVariable iif= newequ1.checkvanszerofive("x"); //�ݬO�_���򸹤��B���ܼ�
	//if (iif.upperbound == 1.79769e+308) iif.upperbound = r.upperbound;
	//if (iif.lowerbound == 2.22507e-308) iif.lowerbound = r.lowerbound;
	//newequ1.insertEveryVariableRestrict("x", iif);
	//double golden=newequ1.GoldenSearch(iif.lowerbound, (iif.upperbound - iif.lowerbound) * phi, iif.upperbound, 1e-5, 0);
	//Next = Next + D * golden;
	//k = 0;
	//for (iti = initial.begin(); iti != initial.end(); iti++)
	//{
	//	iti->second = Next.getnuminMatrix(k,0);
	//}
	////��X
	//std::cout << "��" << k << "������:\n";
	//std::cout << "Golden==>" << golden << "\n";
	//std::cout << "H==>\n" <<F<< "\n";
	//std::cout <<"�I��\n"<<Next << "\n";
	////
	//Matrix stepplus = D*golden; //�M��U��F ALPHAk
	//itv = variable.begin();
	//Matrix tg = G;
	//for (int i = 0; i < this->getNDimension(); i++)
	//{
	//	std::string diffv = "";
	//	diffv += *itv;
	//	Optimization diff(this->differentiation(diffv));
	//	tg.replaceNuminMatrix(i,0, diff.eval(initial));
	//	itv++;
	//}//x^(k+1)

	//Matrix m = stepplus.Transpose() * tg;
	//Matrix m1 = F * tg;
	//Matrix m2 = tg.Transpose() * F * tg;
	//F = F + (stepplus * stepplus.Transpose()) / m.getnuminMatrix(0, 0)-(m1*m1.Transpose())/m2.getnuminMatrix(0,0);







	//const double err = 1e-6;
	//const int strict = 60;
	//int count = 1;

	//Matrix coutf;
	//while (count < 60)
	//{
	//	itv = variable.begin();
	//	iti = initial.begin();
	//	bool isb = true;
	//	for (int i = 0; i < this->getNDimension(); i++)
	//	{
	//		
	//		std::string diffv = "";
	//		diffv += *itv;
	//		Optimization diff(this->differentiation(diffv));
	//		if(diff.eval(initial)>err) 
	//		{
	//			isb = false;
	//		}
	//		G.replaceNuminMatrix(i, 0, diff.eval(initial));
	//		itv++;
	//		iti++;

	//	}
	//	if (true)
	//		break;
	//	else {

	//		for (iti = initial.begin(); iti != initial.end(); iti++)
	//		{
	//			t.clear();
	//			std::stringstream ss;
	//			std::string e = "";
	//			ss << Ans.getnuminMatrix(k, 1);
	//			ss >> t;
	//			e += t;
	//			e += "+x";
	//			ss.clear();
	//			ss.str("");
	//			ss << G.getnuminMatrix(k, 1);
	//			ss >> t;
	//			e += t;
	//			neweq.insert(std::pair<std::string, std::string>(iti->first, e));
	//			itr = rrestrict.find(iti->first);
	//			double low = this->CalculationLowerbound(iti->first, itr->second.upperbound, G.getnuminMatrix(k, 1)); //��Xgolden��������
	//			double up = this->CalculationLowerbound(iti->first, itr->second.lowerbound, G.getnuminMatrix(k, 1));
	//			if (k == 0)
	//			{
	//				r.lowerbound = low;
	//				r.upperbound = up;
	//			}
	//			else {
	//				if (r.lowerbound > low) r.lowerbound = low;
	//				if (r.upperbound < up)r.upperbound = up;
	//			}
	//			k++;
	//		}

	//		Optimization newequ1(this->NewEquation(neweq));
	//		iif = newequ1.checkvanszerofive("x"); //�ݬO�_���򸹤��B���ܼ�
	//		if (iif.upperbound == 1.79769e+308) iif.upperbound = r.upperbound;
	//		if (iif.lowerbound == 2.22507e-308) iif.lowerbound = r.lowerbound;
	//		newequ1.insertEveryVariableRestrict("x", iif);
	//		golden = newequ1.GoldenSearch(iif.lowerbound, (iif.upperbound - iif.lowerbound) * phi, iif.upperbound, 1e-5, 0);
	//		Next = Next + D * golden;
	//		k = 0;
	//		for (iti = initial.begin(); iti != initial.end(); iti++)
	//		{
	//			iti->second = Next.getnuminMatrix(k, 1);
	//		}

	//		coutf = F;

	//		//��X
	//		std::cout << "��" << k << "������:\n";
	//		std::cout << "Golden==>" << golden << "\n";
	//		std::cout << "H==>\n" << F << "\n";
	//		std::cout << "�I��\n" << Next << "\n";
	//		//
	//		stepplus = D * golden; //�M��U��F ALPHAk
	//		itv = variable.begin();
	//		tg = G;
	//		for (int i = 0; i < this->getNDimension(); i++)
	//		{
	//			std::string diffv = "";
	//			diffv += *itv;
	//			Optimization diff(this->differentiation(diffv));
	//			tg.replaceNuminMatrix(i, 1, diff.eval(initial));
	//			itv++;
	//		}//x^(k+1)

	//		m = stepplus.Transpose() * tg;
	//		m1 = F * tg;
	//		m2 = tg.Transpose() * F * tg;
	//		F = F + (stepplus * stepplus.Transpose()) / m.getnuminMatrix(0, 0) - (m1 * m1.Transpose()) / m2.getnuminMatrix(0, 0);
	//	}
	//	count++;
	//}
	//std::cout << "Ans��\n";
	//std::cout << "H==>\n" << coutf << "\n";
	//std::cout << "�I��\n" << Next << "\n";

}



void Optimization::clearVariableRestrict()
{
	variable.clear();
}

Matrix Optimization::Hessianmatrix()
{
	std::string *rowname=new std::string[this->getNDimension()];
	std::string *columnname= new std::string[this->getNDimension()];
	std::set<char>::iterator IT_SET=variable.begin();
	for (int i = 0; i < this->getNDimension(); i++)
	{
		std::string n = "";
		n+= *IT_SET;
		rowname[i] = n;
		columnname[i] = n;
		IT_SET++;
	}
	Matrix ans("H",this->getNDimension(),this->getNDimension());
	for (int i = 0; i < this->getNDimension(); i++)
	{
		for (int j = 0; j < this->getNDimension(); j++)
		{
			std::string firstd = this->differentiation(rowname[i]);
			Optimization nextfx(firstd);
			std::string secondd = nextfx.differentiation(columnname[j]);
			Optimization finalfx(secondd);
			ans.replaceNuminMatrix(i, j, finalfx.eval(this->initial));
		}
	}
	return ans;
}
restrictVariable Optimization::checkvanszerofive(std::string input)
{
	restrictVariable ans;
	ans.lowerbound = 2.22507e-308;
	ans.upperbound = 1.79769e+308;
	std::vector<std::string> findrootfive;
	int brackets = 0;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '^')
		{
			std::string record = "";
			std::string a = "";

			int c = i;
			for (int j = i + 1; j < input.size(); j++)
			{
				c++;
				if (std::isdigit(input[j]) || input[j] == '.' || input[j] == '~')
				{
					a += input[j];
				}
				else break;
			}
			std::stringstream ss;
			ss << a;
			double ispointFive;
			ss >> ispointFive;
			bool havevariable = false;
			if (std::abs(ispointFive) < 1 && std::abs(ispointFive) != 0) //���}�ڸ�
			{
				/*std::reverse(a.begin(), a.end());
				record += a;
				record += '^';*/

				for (int j = i - 1; j >= 0; j--)
				{
					if (input[j] == ')')
					{
						brackets++;
					}
					else if (input[j] == '(')
					{
						brackets--;
					}

					if (((priority(input[i]) == 1 || priority(input[i]) == 2 || priority(input[i]) == 3) && brackets == 0) || brackets == 0)
					{
						if ((priority(input[i]) == 1 || priority(input[i]) == 2 || priority(input[i]) == 3))
						{
						}
						else record += input[j];
						break;
					}
					else
					{
						if ((input[j] >= 65 && input[j] <= 90) || input[j] >= 97 && input[j] <= 122)
						{
							havevariable = true;
						}
						record += input[j];
					}

				}
				std::reverse(record.begin(), record.end());
				i += 2;

				findrootfive.push_back(record);





				if (havevariable)
				{
					double comebine = 0;
					char next = '+';
					double variablecoef = 0;
					std::string text = "";
					int b = 0;
					bool upv = false;


					for (int j = 0; j < record.size(); j++)
					{

						if (std::isdigit(record[j]) || record[j] == '.')
						{
							text += record[j];
						}
						else if (priority(record[j]) == 1)
						{
							if (text == "")
							{
								next = record[j];

							}
							else if (upv) {
								std::stringstream ss;
								double templ;
								ss << text;
								ss >> templ;
								if (next == '+')
									variablecoef -= templ;
								else
									variablecoef += templ;
								text.clear();
								text = "";

							}
							else {
								std::stringstream ss;
								double templ;
								ss << text;
								ss >> templ;
								if (next == '+') comebine += templ;
								else comebine -= templ;
								next = record[j];
								text.clear();
								text = "";
								upv = false;
							}

						}
						else if (priority(record[j]) == '*' && ((record[j + 1] >= 65 && record[j + 1] <= 90) || record[j + 1] >= 97 && record[j + 1] <= 122))
						{
							upv = false;
							std::stringstream ss;
							double templ;
							ss << text;
							ss >> templ;
							text.clear();
							text = "";
							/*for (int k = j+2; k <record.size() ; k++)
							{
								if (k + 1 == record.size())
								{

								}
								else {


									if (priority(record[j]) == 1)
									{
										j = k - 1;

										break;
									}
									else {
										if (record[j] == '*')
										{
											if (text != "") {
												double r;
												ss.clear();
												ss << text;
												ss >> r;
												templ *= r;
												text = "";
											}
										}
										else if (record[j] == '^')
										{
											for (int l = k + 1; l < record.size(); l++)
											{
												if (priority(record[j]) == 1)
												{
													k = l - 1;
													break;
												}

											}
										}
										else {
											text += record[k];
										}
									}
								}
							}*/
							if (next == '+')
								variablecoef -= templ;
							else
								variablecoef += templ;
							j++;
						}
						else if ((record[j] >= 65 && record[j] <= 90) || (record[j] >= 97 && record[j] <= 122))
						{
							upv = true;
						}
					}
					if (text != "") {
						if (upv) {
							std::stringstream ss;
							double templ;
							ss << text;
							ss >> templ;
							if (next == '+')
								variablecoef -= templ;
							else
								variablecoef += templ;
							text.clear();
							text = "";

						}
						else {
							std::stringstream ss;
							double templ;
							ss << text;
							ss >> templ;
							if (next == '+') comebine += templ;
							else comebine -= templ;

							text.clear();
							text = "";
							upv = false;
						}
					}


					std::cout << "�Y��" << variablecoef << std::endl;
					std::cout << "�`��" << comebine << std::endl;
					double push = comebine / variablecoef;
					if (variablecoef < 0)
					{
						if (ans.upperbound > push)
						{
							ans.upperbound = push;
						}
					}
					else {
						if (ans.lowerbound < push)
						{
							ans.lowerbound = push;
						}
					}
				}

			}
		}
	}
	for (int i = 0; i < findrootfive.size(); i++)
	{
		std::cout << "���է��" << findrootfive[i] << std::endl;
	}


	std::cout << "���է��lll" << ans.lowerbound << std::endl;
	std::cout << "���է�uuu" << ans.upperbound << std::endl;
	return ans;
}