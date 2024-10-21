#include <iostream>
#include <cstdlib>
#include <string>
#include <omp.h>
using namespace std;

const int n = 20000, m = 10000;
double A[n][m];
double x[m];
double res[n];

int main()
{
	setlocale(LC_ALL, "Russian");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			A[i][j] = i * 10 + j;
		}
	}
	for (int j = 0; j < m; j++) {
		x[j] = j + 3;
	}

	//Последовательно
	double t1 = omp_get_wtime();
	for (int i = 0; i < n; i++) {
		res[i] = 0;
		for (int j = 0; j < m; j++) {
			res[i] += A[i][j] * x[j];
		}
	}
	
	cout << "Time: " << omp_get_wtime() - t1 << endl;

	//Вывод для проверки
	/*
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << A[i][j] << '\t';
		}
		cout << "\t\t";
		if (i < m) {
			cout << x[i];
		}
		cout << "\t\t" << res[i];
		cout << endl;
	}
	for (int j = n; j < m; j++) {
		for (int j = 0; j < m; j++) {
			cout << '\t';
		}
		cout << "\t\t" << x[j] << endl;
	}
	*/

	//Параллельно
	double t2 = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section 
		{
			for (int i = 0; i < n; i+=4) {
				res[i] = 0;
				for (int j = 0; j < m; j++) {
					res[i] += A[i][j] * x[j];
				}
			}
		}
#pragma omp section 
		{
			for (int i = 1; i < n; i+=4) {
				res[i] = 0;
				for (int j = 0; j < m; j++) {
					res[i] += A[i][j] * x[j];
				}
			}
		}
#pragma omp section 
		{
			for (int i = 2; i < n; i += 4) {
				res[i] = 0;
				for (int j = 0; j < m; j++) {
					res[i] += A[i][j] * x[j];
				}
			}
		}
#pragma omp section 
		{
			for (int i = 3; i < n; i += 4) {
				res[i] = 0;
				for (int j = 0; j < m; j++) {
					res[i] += A[i][j] * x[j];
				}
			}
		}
	}
	cout << "Time: " << omp_get_wtime() - t2 << endl;
	return EXIT_SUCCESS;
}
