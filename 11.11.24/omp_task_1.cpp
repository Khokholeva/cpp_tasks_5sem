#include <iostream>
#include <cstdlib>
#include <string>
#include <omp.h>
#include <iomanip>
using namespace std;

const double eps = 1e-10;
double f(double x)
{
	return 1 / (1 + x * x);
}

double integr(double a, double b, double(*op)(double)) {
	double h = (b - a) / 10;
	double res = 0;
	for (int i = 0; i < 10; i++) {
		res += h * (f(a + h * i) + f(a + h * (i + 1))) / 2;
	}
	return res;
}

double integral(double a, double b, double(*op)(double)) {
	double full = integr(a, b, op);
	double c = a + (b - a) / 2;
	double left = integr(a, c, op);
	double right = integr(c, b, op);
	if (abs(full - left - right) <= eps) return full;
	left = integral(a, c, op);
	right = integral(c, b, op);
	return left + right;
}

double integral_task(double a, double b, double(*op)(double)) {
	double full = integr(a, b, op);
	double c = a + (b - a) / 2;
	double left = integr(a, c, op);
	double right = integr(c, b, op);
	if (abs(full - left - right) <= eps) return full;

#pragma omp task shared(left)
	left = integral_task(a, c, op);

#pragma omp task shared(right)
	right = integral_task(c, b, op);

#pragma omp taskwait
	return left + right;
}


int main()
{
	setlocale(LC_ALL, "Russian");

	double t = omp_get_wtime();
	cout << setprecision(10) << integral(0, 1, f) << endl;
	cout << omp_get_wtime() - t << endl << endl; 

	t = omp_get_wtime();
#pragma omp parallel
	{
#pragma omp single
		{
			cout << setprecision(10) << integral_task(0, 1, f) << endl;
		}
	}
	cout << omp_get_wtime() - t << endl;
	return EXIT_SUCCESS;
}
