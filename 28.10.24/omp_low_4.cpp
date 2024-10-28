#include <iostream>
#include <cstdlib>
#include <string>
#include <omp.h>
#include <iomanip>
using namespace std;

const int n = 1000, m = 500, p = 1000;
double A[n][m];
double B[m][p];
double C[n][p], C_par[n][p];

int main()
{
	setlocale(LC_ALL, "Russian");

	//Ввод
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			A[i][j] = i * 10 + j;
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < p; j++) {
			B[i][j] = i * 10 + j;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j++) {
			C[i][j] = 0;
			C_par[i][j] = 0;
		}
	}

	cout << "Последовательно" << endl;
	double t = omp_get_wtime();
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < p; k++) {
			for (int j = 0; j < m; j++) {
				C[i][k] += A[i][j] * B[j][k];
			}
		}
	}
	cout << "Time: " << omp_get_wtime() - t << endl;

	cout << endl << "Parallel" << endl;
	double t2 = omp_get_wtime();

#pragma omp parallel 
	{
		int id = omp_get_thread_num();
		int num = omp_get_num_threads();
		for (int i = id; i < n; i+=num) {
			for (int k = 0; k < p; k++) {
				for (int j = 0; j < m; j++) {
					C_par[i][k] += A[i][j] * B[j][k];
				}
			}
		}
	}
	cout << "Time: " << omp_get_wtime() - t2 << endl;

	//Проверка результата для небольших размеров
	/*
	cout << "A" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << A[i][j] << '\t';
		}
		cout << endl;
	}
	cout << "B" << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < p; j++) {
			cout << B[i][j] << '\t';
		}
		cout << endl;
	}
	cout << "C" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j++) {
			cout << C[i][j] << '\t';
		}
		cout << endl;
	}
	cout << "C_par" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j++) {
			cout << C_par[i][j] << '\t';
		}
		cout << endl;
	}
	*/

	return EXIT_SUCCESS;
}
