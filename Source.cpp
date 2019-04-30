#include"Equation.h"
int main() {

	LinkEquation q,w;
	Variance a;
	Variance a1;
	a1.exponential = 2;
	a1.name = "x";
	a.exponential = 3;
	a.name = "y";
	Coefficient b;
	Coefficient b1;
	b1.coefficient = 7;
	b.coefficient = 4;
	LinkVariance p(a);
	q.insert(p, b);
	LinkVariance n(a1);
	LinkEquation m;
	m.insert(n,b1);
	q.insert(n, b1);
	w = q-m;
	std::cout << q<<m<<w;
	q=q.Powell2Golden("x","y",m,1);
	std::cout << q;
	system("pause");
	return 0;
}