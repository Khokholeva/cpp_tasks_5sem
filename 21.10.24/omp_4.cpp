#include <iostream>
#include <cstdlib>
#include <string>
#include <omp.h>
using namespace std;

НЕ копировать все, здесь лишнее, разберитесь что зачем
const int n = 2000, m = 2000, p = 1000;
double A[n][m];
double B_T[p][m];
double B[m][p];
double res1[n][p];
double res2[n][p];
double res_par[n][p];

int main()
{
	setlocale(LC_ALL, "Russian");
	//заполнение A, B
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			A[i][j] = i * 10 + j;
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < p; j++) {
			B_T[j][i] = j;
			B[i][j] = j;
		}
	}

	//очистка res
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j++) {
			res1[i][j] = 0;
			res2[i][j] = 0;
			res_par[i][j] = 0;
		}
	}

	//Последовательно 
	double t1 = omp_get_wtime();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < p; k++) {
				res1[i][k] += A[i][j] * B[j][k];
			}
		}
	}

	cout << "Time: " << omp_get_wtime() - t1 << endl;

	//Последовательно с трансп
	double t2 = omp_get_wtime();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j++) {
			for (int k = 0; k < m; k++) {
				res2[i][j] += A[i][k] * B_T[j][k];
			}
		}
	}
	cout << "Time: " << omp_get_wtime() - t2 << endl;
	//Вывод для проверки
	/*
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << A[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < p; j++) {
			cout << B_T[j][i] << '\t';
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j++) {
			cout << res1[i][j] << '\t';
		}
		cout << endl;
	}
	*/

	//параллельно
	double t3 = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section 
		{
			double t2 = omp_get_wtime();
			for (int i = 0; i < n; i+=4) {
				for (int j = 0; j < p; j++) {
					for (int k = 0; k < m; k++) {
						res_par[i][j] += A[i][k] * B_T[j][k];
					}
				}
			}
		}
#pragma omp section 
		{
			double t2 = omp_get_wtime();
			for (int i = 1; i < n; i+=4) {
				for (int j = 0; j < p; j++) {
					for (int k = 0; k < m; k++) {
						res_par[i][j] += A[i][k] * B_T[j][k];
					}
				}
			}
		}
#pragma omp section 
		{
			double t2 = omp_get_wtime();
			for (int i = 2; i < n; i+=4) {
				for (int j = 0; j < p; j++) {
					for (int k = 0; k < m; k++) {
						res_par[i][j] += A[i][k] * B_T[j][k];
					}
				}
			}
		}
#pragma omp section 
		{
			double t2 = omp_get_wtime();
			for (int i = 3; i < n; i+=4) {
				for (int j = 0; j < p; j++) {
					for (int k = 0; k < m; k++) {
						res_par[i][j] += A[i][k] * B_T[j][k];
					}
				}
			}
		}
	}
	cout << "Time: " << omp_get_wtime() - t3 << endl;

	return EXIT_SUCCESS;
}
