#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

struct OutOfMemory {};
struct OutOfRange {};

struct Vector {
	int size;
	double* ar;
	Vector(int n)  {
		if (n > 2000000000) throw OutOfMemory();
		size = n;
		ar = new double[n];
	}
	~Vector() { delete[] ar; }
	double& operator[] (int i) {
		if (i < 0 || i >= size) throw OutOfRange();
		return ar[i];
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	int n, i;
	double d;
	try {
		cin >> n;
		Vector v(n);
		cin >> i >> d;
		v[i] = d;
		
	}
	catch (OutOfMemory) {
		cerr << "Error: Out of memory" << endl;
		return EXIT_FAILURE;
	}
	catch (OutOfRange) {
		cerr << "Error: index out of range" << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
