#include"Optimization.h"
int main() {
	std::string a="-1.35ysin(yy)+y9+y(7+6)y";
	Optimization z(a);
	z.getPostfix();
	std::map<std::string, double>map;
	map.insert(std::pair<std::string, double>("y",1));
	std::cout << z.eval(map);
	system("pause");
	return 0;
	
}

