#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
struct DivisionByZero {};

int div2(int x, int y) {
	if (y == 0) throw DivisionByZero();
	return x / y;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int a, b, c;
	cin >> a >> b;
	try {
		c = div2(a, b);
	}
	catch (DivisionByZero) {
		cerr << "Error: Division by zero" << endl;
		return EXIT_FAILURE;
	}
	cout << c << endl;
	return EXIT_SUCCESS;
}
