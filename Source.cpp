#include"Equation.h"
int main() {

	LinkEquation q,w;
	Variance a;
	a.exponential = 3;
	a.name = "y";
	Coefficient b;
	b.coefficient = 4;
	LinkVariance p(a);
	q.insert(p, b);
	w = q - q;
	std::cout << q<<w;

	system("pause");
	return 0;
}