#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

//02.09 / 0
class Two
{
	double a;
	double b;

public:
	Two(double x, double y) {
		if (x > y) {
			a = x;
			b = y;
		}
		else {
			a = y;
			b = x;
		}
	}

	double study(double x) {
		double res;
		if (x > a) {
			res = b;
			b = a;
			a = x;
		}
		else if (x > b) {
			res = b;
			b = x;
		}
		else res = x;
		return res;
	}

	void print() {
		cout << "a = " << a << " b = " << b;
	}
};


class Three : Two
{
	double c;
public:
	Three(double x, double y, double z) : Two(x, y), c(Two::study(z)) {}

	double study(double x) {
		double res;
		double temp;
		temp = Two::study(x);
		if (temp > c) {
			res = c;
			c = temp;
		}
		else res = temp;
		return res;
	}

	void print() {
		Two::print();
		cout << " c = " << c;
	}
};
