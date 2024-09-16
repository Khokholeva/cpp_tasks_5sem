#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <filesystem>
using namespace std;

struct NoFile {};

void print_f(string name) {
	if (!std::filesystem::exists(name)) throw NoFile();

	ifstream myfile;
	myfile.open(name);
	cout << myfile.rdbuf();
}

int main()
{
	setlocale(LC_ALL, "Russian");
	string s;
	cin >> s;
	try {
		print_f(s);
	}
	catch (NoFile) {
		cerr << "Error: File does not exist" << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
