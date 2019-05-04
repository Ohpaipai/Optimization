#include"Optimization.h"
int main() {
	std::string a="3+(x-1.5*y)^2+(y-2)^2";
	Optimization z(a);
	z.getPostfix();
	std::map<std::string, double>map;
	map.insert(std::pair<std::string, double>("y",0.5));
	map.insert(std::pair<std::string, double>("x",0.5));
	std::cout << z.eval(map) << std::endl;
	restrictVariable r;
	r.lowerbound = 0;
	r.upperbound = 5;
	std::map<std::string,restrictVariable>map2;
	map2.insert(std::pair<std::string, restrictVariable>("y", r));
	map2.insert(std::pair<std::string, restrictVariable>("x", r));
	z.Powell(map,map2,1e-8,0);
	/*std::map<std::string, std::string>map2;
	map2.insert(std::pair<std::string, std::string>("y","1+2x"));
	std::cout << z.NewEquation(map2) << std::endl;*/
	system("pause");
	return 0;
	
}

