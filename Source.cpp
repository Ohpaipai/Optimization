#include"Optimization.h"
int main() {
	std::string a="-1.35ysin(sin(--yy))+y9+y(7+6)y";
	Optimization z(a);
	z.getPostfix();
	std::map<std::string, double>map;
	map.insert(std::pair<std::string, double>("y",1));
	std::cout << z.eval(map)<<std::endl;
	std::map<std::string, std::string>map2;
	map2.insert(std::pair<std::string, std::string>("y","1+2x"));
	std::cout << z.NewEquation(map2) << std::endl;
	system("pause");
	return 0;
	
}

