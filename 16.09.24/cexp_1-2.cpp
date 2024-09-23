#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

//1
constexpr int power(int x, int y) {
	int res = 1;
	for (int i = 0; i < y; i++) {
		res *= x;
	}
	return res;
}

const int x = 5, y = 3;
int xtoy = power(x, y);

//2
constexpr int cnk(int n, int k) {
	if (n < k) return 0;
	int res = 1;
	for (int i = 0; i < k;  i++) {
		res *= (n - i);
	}
	for (int i = 2; i <= k; i++) {
		res /= i;
	}
	return res;
}

int n = 6, k = 2;
int nfork = cnk(n, k);


int main()
{
	setlocale(LC_ALL, "Russian");
	cout << xtoy << endl;
	cout << nfork << endl;
	return EXIT_SUCCESS;
}
