#include <iostream>
#include <cstdlib>
#include <string>
#include <omp.h>
#include <iomanip>
using namespace std;

const double PI = 3.141592653589793238463;
//0
int n = 100000000;
double* sins = new double[n];
double* sins_par = new double[n];

//1
double f(double t) {
	return 1 / (1 + t * t);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	//0
	/*
	
	double d = PI / 2 / n;
	cout << "0" << endl;
	cout << "Последовательно" << endl;
	double t = omp_get_wtime();
	for (int i = 0; i < n; i++) {
		sins[i] = sin(i * d);
	}
	cout << "Time: " << omp_get_wtime() - t << endl;

	cout << "Параллельно" << endl;
	double t2 = omp_get_wtime();
#pragma omp parallel for schedule(static)
	for (int i = 0; i < n; i++) {
		sins_par[i] = sin(i * d);
	}
	
	cout << "Time: " << omp_get_wtime() - t2 << endl;
	*/
	//1
	
	cout << "1" << endl;
	int m = 500000000;
	//cin >> m;
	double t, t2;
	cout << "Последовательно" << endl;
	double res = 0;
	t = omp_get_wtime();
	for (int i = 0; i < m; i++) {
		res += f((2.0 * i + 1) / 2 / m);
	}
	res = res * 4 / m;
	cout << "Pi = " << setprecision(15) << res << endl;
	cout << "Time: " << omp_get_wtime() - t << endl;

	double res2 = 0;
	cout << "Параллельно" << endl;
	t2 = omp_get_wtime();
#pragma omp parallel for schedule(static) reduction(+:res2)
	for (int i = 0; i < m; i++) {
		res2 += f((2.0 * i + 1) / 2 / m);
	}
	res2 = res2 * 4 / m;
	cout << "Pi = " << setprecision(15) << res2 << endl;
	cout << "Time: " << omp_get_wtime() - t2 << endl;
	
	return EXIT_SUCCESS;
}
