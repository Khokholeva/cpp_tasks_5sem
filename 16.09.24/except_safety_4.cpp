#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>
using namespace std;

struct Foo {
	static int count;
	int id;
	Foo() {
		id = ++count;
		if (id == 7) throw "Id = 7"s;
		cout << "Creating id " << id << endl;
		
	}
	~Foo() {
		cout << "Deleting id " << id << endl;
	}
};

int Foo::count = 0;

int main()
{
	setlocale(LC_ALL, "Russian");
	
	try {
		Foo loc_ar[10];
	}
	catch (string msg) {
		cerr << "Error: " << msg << endl;
	}
	return EXIT_SUCCESS;
}
