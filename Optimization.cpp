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
			if (sub.size() > 0)
			{
				if (sub[sub.size()-1]=='~') //變負號
					sub.push_back('~');
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

void Optimization::Powell(std::map<std::string, double> initial, std::map<std::string, restrictVariable> rrestrict, std::queue<std::map<std::string, double>> nvec,double err,double count)
{
	std::map<std::string, double>::iterator it_vec;
	std::map<std::string, double>::iterator it_intial;
	std::map<std::string, restrictVariable>::iterator it_restrict;
	double *NgoldenAns = new double[this->getNDimension()];
	for (int i = 0; i <=this->getNDimension(); i++)
	{
		if (i == this->getNDimension()) //做第三次查找
		{

		}
		else { //其他次
			double upperbound= 2.22507e-308;
			double lowerbound= 1.79769e+308;

			std::string make = "";
			std::map<std::string, std::string> newequ;
			//找出邊界與製作function
			for (it_vec=nvec.front().begin();it_vec!=nvec.front().end();it_vec++)
			{
				if (it_vec->second != 0)
				{

				}
			}

		}

	}
	

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
			std::string t = "";
			t += "-";
			t+=ans[top];
			ans[top] = t;
		}
		else if (postfix[i] == "+"||postfix[i]=="-")
		{
			std::string key = "";
			key += ans[top - 1];
			key += "+";
			key += ans[top];
			key += "";

			std::string subarray = "";
			it = temofinterval.find(ans[top - 1]);
			subarray += it->second;
			subarray += "+";//連鎖綠前+後
			it = temofinterval.find(ans[top]);
			subarray += it->second;
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
