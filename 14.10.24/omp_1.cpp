#include <iostream>
#include <cstdlib>
#include <string>
#include <omp.h>
#include <iomanip>
using namespace std;

double f(double t) {
	return 1 / (1 + t * t);
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	double t, t2;
	cin >> n;
	while (n != -1) {
		cout << "Последовательно" << endl;
		t = omp_get_wtime();
		double res = 0;
		for (int i = 0; i < n; i++) {
			res += f((2.0 * i + 1) / 2 / n);
		}
		res = res * 4 / n;
		cout << "Pi = " << setprecision(15) << res << endl;
		cout << "Time: " << omp_get_wtime() - t << endl;

		//12 веток
		
		cout << "12 Веток" << endl;
		t2 = omp_get_wtime();
		double res1 = 0;
		
#pragma omp parallel sections reduction(+:res1)
		{
#pragma omp section 
			{
				for (int i = 0; i < n / 12; i++) {
					res1 += f((2.0 * i + 1) / 2 / n);
				}
			}
#pragma omp section 
			{
				for (int i = n / 12; i < 2 * n / 12; i++) {
					res1 += f((2.0 * i + 1) / 2 / n);
				}
			}
#pragma omp section 
			{
				for (int i = 2 * n / 12; i < 3 * n / 12; i++) {
					res1 += f((2.0 * i + 1) / 2 / n);
				}
			}
#pragma omp section 
			{
				for (int i = 3 * n / 12; i < 4 * n / 12; i++) {
					res1 += f((2.0 * i + 1) / 2 / n);
				}
			}
#pragma omp section 
			{
				for (int i = 4 * n / 12; i < 5 * n / 12; i++) {
					res1 += f((2.0 * i + 1) / 2 / n);
				}
			}
#pragma omp section 
			{
				for (int i = 5 * n / 12; i < 6 * n / 12; i++) {
					res1 += f((2.0 * i + 1) / 2 / n);
				}
			}
#pragma omp section 
			{
				for (int i = 6 * n / 12; i < 7 * n / 12; i++) {
					res1 += f((2.0 * i + 1) / 2 / n);
				}
			}
#pragma omp section 
			{
				for (int i = 7 * n / 12; i < 8 * n / 12; i++) {
					res1 += f((2.0 * i + 1) / 2 / n);
				}
			}
#pragma omp section 
			{
				for (int i = 8 * n / 12; i < 9 * n / 12; i++) {
					res1 += f((2.0 * i + 1) / 2 / n);
				}
			}
#pragma omp section 
			{
				for (int i = 9 * n / 12; i < 10 * n / 12; i++) {
					res1 += f((2.0 * i + 1) / 2 / n);
				}
			}
#pragma omp section 
			{
				for (int i = 10 * n / 12; i < 11 * n / 12; i++) {
					res1 += f((2.0 * i + 1) / 2 / n);
				}
			}
#pragma omp section 
			{
				for (int i = 11 * n / 12; i < n; i++) {
					res1 += f((2.0 * i + 1) / 2 / n);
				}
			}
		}
		res1 = res1 * 4 / n;
		cout << "Pi = " << setprecision(15) << res1 << endl;
		cout << "Time: " << omp_get_wtime() - t2 << endl;
		cout << endl;
		cin >> n;
  }
	return EXIT_SUCCESS;
}
