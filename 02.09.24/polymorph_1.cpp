#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class Payment 
{
	string address;

public:
	Payment(string s): address(s) {}
	virtual double calculate() = 0;
	virtual ~Payment() {}
};

class Heat : public Payment 
{
	double area;

public:
	Heat(string s, double a): Payment(s), area(a) {}
	double calculate() {
		return 50 * area;
	}
};

class Water : public Payment
{
	int people;

public:
	Water(string s, int p) : Payment(s), people(p) {}
	double calculate() {
		return 200 * people;
	}
};
class Electricity : public Payment
{
	double kwh;

public:
	Electricity(string s, double k) : Payment(s), kwh(k) {}
	double calculate() {
		return 5 * kwh;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");

	Payment* bill[7];
	Heat* heat_1 = new Heat("1, A street", 150);
	Heat* heat_2 = new Heat("2, A street", 80);
	Water*  water_1 = new Water("1, A street", 4);
	Water* water_2 = new Water("2, A street", 2);
	Water* water_3 = new Water("3, A street", 3);
	Electricity* elec_1 = new Electricity("1, A street", 30);
	Electricity* elec_2 = new Electricity("2, A street", 75.6);
	bill[0] = heat_1;
	bill[1] = heat_2;
	bill[2] = water_1;
	bill[3] = water_2;
	bill[4] = water_3;
	bill[5] = elec_1;
	bill[6] = elec_2;

	double res = 0;
	double t;
	for (int i = 0; i < 7; i++) {
		t = bill[i]->calculate();
		cout << "Pos " << i+1 << ": " << t << endl;
		res += t;
	}
	cout << "Total payment: " << res << endl;
  
  for (int i = 0; i < 7; i++) {
		delete bill[i];
	}
  
  return EXIT_SUCCESS;
}
