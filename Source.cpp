#include"Optimization.h"
int main() {
	std::string a="2x^2+!xy+3";
	Optimization z(a);
	z.getPostfix();
	std::map<std::string, double>map;
	map.insert(std::pair<std::string, double>("y",1));
	map.insert(std::pair<std::string, double>("x",1));
	std::cout << z.eval(map) << std::endl;
	std::cout << "test"<<std::pow(0, -1) << std::endl;
	restrictVariable r;
	r.lowerbound = 0;
	r.upperbound = 5;
	std::map<std::string,restrictVariable>map2;
	map2.insert(std::pair<std::string, restrictVariable>("y", r));
	map2.insert(std::pair<std::string, restrictVariable>("x", r));
	Optimization e(z.differentiation("x"));
	Optimization d(e.differentiation("x"));
	std::cout << e.eval(map) << std::endl;
	std::cout << d.eval(map) << std::endl;
	//z.Powell(map,map2,1e-8,0);
	/*std::map<std::string, std::string>map2;
	map2.insert(std::pair<std::string, std::string>("y","1+2x"));
	std::cout << z.NewEquation(map2) << std::endl;*/
	system("pause");
	return 0;
	
}

