#include"Optimization.h"
int main() {
	std::string a="7+x^2-3*x*y+3.25*y^2-4*y";
	std::string b = "3*-1";
	Optimization c(b);
	Optimization z(a);
	z.getPostfix();
	std::map<std::string, double>map;
	map.insert(std::pair<std::string, double>("y",2));
	map.insert(std::pair<std::string, double>("x",3));
	std::cout << z.eval(map) << std::endl;
	std::cout << "test"<<std::pow(0, -1) << std::endl;
	restrictVariable r;
	r.lowerbound = -50;
	r.upperbound = 70;
	restrictVariable r2;
	r2.lowerbound = -70;
	r2.upperbound = 70;
	std::map<std::string,restrictVariable>map2;
	map2.insert(std::pair<std::string, restrictVariable>("y", r));
	map2.insert(std::pair<std::string, restrictVariable>("x", r));
	Optimization e(z.differentiation("x"));
	Optimization d(e.differentiation("x"));
	std::cout << e.eval(map) << std::endl;
	std::cout << d.eval(map) << std::endl;
	z.insertInitialVariable("x", 50);
	z.insertInitialVariable("y", 30);
	z.insertEveryVariableRestrict("x", r);
	z.insertEveryVariableRestrict("y", r2);
	std::map<std::string, double>x;
	x.insert(std::pair<std::string, double>("x", 1));
	x.insert(std::pair<std::string, double>("y", 0));
	std::map<std::string, double>x2;
	x2.insert(std::pair<std::string, double>("x", 0));
	x2.insert(std::pair<std::string, double>("y", 1));
	std::queue<std::map<std::string, double>>n;
	n.push(x);
	n.push(x2);
	z.Powell(n,1e-6,0);
	/*std::map<std::string, std::string>map2;
	map2.insert(std::pair<std::string, std::string>("y","1+2x"));
	std::cout << z.NewEquation(map2) << std::endl;*/
	system("pause");
	return 0;
	
}

