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
	std::cout << orignal << std::endl;
	postfix = this->toPostfix();

}

std::vector<std::string> Optimization::toPostfix()
{
	std::string stack;
	std::vector<std::string>tempostfix;
	int top = -1;
	for (int i = 0,j=0; i!=orignal.size(); i++)
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
					while ((priority(stack[top]) >=priority(orignal[i]))) {
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
					while (stack[top] != '(') { // 遇 ) 輸出至 ( 
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
				while (i!=orignal.size())
				{
					
					
					if (isdigit(orignal[i]) || orignal[i] == '.' || ((orignal[i] >= 65 && orignal[i] <= 90) || orignal[i] >= 97 && orignal[i] <= 122))
					{
						tem+= orignal[i];
					}
					else
						break;
					i++;
					
				}
				if (tem.size() == 1 && ((tem[0] >= 65 && tem[0] <= 90) || tem[0] >= 97 && tem[0] <= 122)) //表示為variable
				{
					
					variable.insert(tem[0]);
				}
				tempostfix.push_back(tem);
				j++;
				i--;
				break;
		}
	}


	while (top>-1)
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
			else if (top == 0) //有負號
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
			if (_input[i] != ' ' && _input[i]!= '　')
			{
				if (sub.size() > 0)
				{
					if ((sub[sub.size() - 1] == '(' || sub[sub.size() - 1] == '~'|| sub[sub.size() - 1]=='^' || sub[sub.size() - 1] == '*' || sub[sub.size() - 1] == '/' || priority(sub[sub.size() - 1]) ==3) && _input[i] == '-') //變負號
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
					if (iter != _variable.end())//找到
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
	newvec.pop();//將第一個pop掉

	#pragma region 每一個維度做查找
	for (int i = 0; i < this->getNDimension(); i++)
	{
		double upperbound = 2.22507e-308;
		double lowerbound = 1.79769e+308;
		std::string make = "";
		std::map<std::string, std::string> newequ;
		//找出邊界與製作function
		for (it_vec = nvec.front().begin(); it_vec != nvec.front().end(); it_vec++)
		{
			for (it_intial = initial.begin(); it_intial != initial.end(); it_intial++)
			{
				if (it_intial->first == it_vec->first)//是否變數一樣
				{
					double low, high;
					//判斷做的矩陣是否為0
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
		for (it_vec = nvec.front().begin(); it_vec != nvec.front().end(); it_vec++) //改變initial
		{
			for (it_intial = initial.begin(); it_intial != initial.end(); it_intial++)
			{
				if (it_intial->first == it_vec->first)//是否變數一樣
				{
					double judgeg=it_intial->second + NgoldenAns[i] * it_vec->second;//initial改變 判斷超過邊界
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
		std::cout << "第" << count << "次之" << i << "\n";
		std::cout << "GoldenSreach:" << NgoldenAns[i] << "\n";
		std::cout << "上界:" << upperbound << " 下界:" << lowerbound << "\n";
		std::cout << "Vector為\n{ ";
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

	#pragma region 查找new vertex
		//做第三次
		double upperbound = 2.22507e-308;
		double lowerbound = 1.79769e+308;
		std::string make = "";
		std::map<std::string, std::string> newequ;
		//找出邊界與製作function
		int i = 0;
		for (it_intial = initial.begin(); it_intial != initial.end(); it_intial++)
			{
				
					double low, high;
					//判斷做的矩陣是否為0
					
						
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
						newpush.insert(std::pair<std::string,double>(it_intial->first,NgoldenAns[i]));//製作新的探查點
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
				
					double judgeg = it_intial->second + NgoldenAns[i] * FinalAns;//initial改變
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
		
		newvec.push(newpush);//第三次點取代
		#pragma region cout
		std::cout << "------------------------------------------------------------------------------------\n";
		std::cout << "第" << count << "次之" << this->getNDimension() << "\n";
		std::cout << "GoldenSreach:" << NgoldenAns[i] << "\n";
		std::cout << "上界:" << upperbound << " 下界:" << lowerbound << "\n";
		std::cout << "Vector為\n{ ";
		for (it_intial = initial.begin(); it_intial != initial.end(); it_intial++)
		{
			std::cout << it_intial->second << "  ";
		}
		std::cout << "}\n";
		std::cout << "F(x)=" << Finalfx << "\n";
		std::cout << "------------------------------------------------------------------------------------\n";
#pragma endregion
	#pragma endregion

	#pragma region 檢查是否符合範圍
		if (count > 60)
		{
		#pragma region cout
		
			std::cout << "------------------------------------------------------------------------------------\n";
			std::cout << "Ans\n";
			std::cout << "Vector為\n{ ";
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
				std::cout << "Vector為\n{ ";
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
			std::cout << "Vector為\n{ ";
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
		//std::cout <<i<<"多少"<< postfix[i] << std::endl;
		if (isdigit(postfix[i][0]))//看每個vector第一個bit是否為數字
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
		else if (postfix[i] == "~") //變成負號
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
			subarray += postfix[i];//連鎖綠前+後
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
			//微前面+微後面
			std::string key = "";
			key += ans[top - 1];
			key += "*";
			key += ans[top];

			std::string subarray = "(";
			it = temofinterval.find(ans[top - 1]);
			subarray += it->second;
			subarray += "*";
			subarray += ans[top];
			subarray += "+";//連鎖綠前+後
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
			//外圍*上內微
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
			//外圍*上內微
			std::string key = "";
			key +="!";
			key += ans[top];

			//外面*裡面
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
		//外圍*上內微
		std::string key = "";
		key += "@";
		key += ans[top];

		//外面*裡面
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
		//外圍*上內微
		std::string key = "";
		key += "&";
		key += ans[top];

		//外面*裡面
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
		//外圍*上內微
		std::string key = "";
		key += "%";
		key += ans[top];

		//外面*裡面
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
		//外圍*上內微
		std::string key = "";
		key += "&";
		key += ans[top];

		//外面*裡面
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
		//外圍*上內微
		std::string key = "";
		key += "&";
		key += ans[top];

		//外面*裡面
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

void Optimization::insertInitialVariable(std::string _name, double _num)
{
	
	std::map<std::string, double>::iterator it;
	it = initial.find(_name);
	if (it == initial.end())
	{
		initial.insert(std::pair<std::string, double>(_name, _num));
	}
	else {
		it->second = _num;
	}
}

void Optimization::deleteinitial()
{
	initial.clear();
}

void Optimization::insertEveryVariableRestrict(std::string _name, restrictVariable _num)
{
	


	std::map<std::string, restrictVariable>::iterator it;
	it = rrestrict.find(_name);
	if (it == rrestrict.end())
	{
		rrestrict.insert(std::pair<std::string, restrictVariable>(_name, _num));
	}
	else {
		it->second = _num;
	}
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
