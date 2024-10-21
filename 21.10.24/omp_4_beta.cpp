#include <iostream>
#include <cstdlib>
#include <string>
#include <omp.h>
using namespace std;

const int n = 10, m = 5, p = 10;
double A[n][m];
double B[m][p];
double res1[n][p];
double res2[n][p];

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
			B[i][j] = j;
		}
	}

	//очистка res
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j++) {
			res1[i][j] = 0;
			res2[i][j] = 0;
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
			cout << B[i][j] << '\t';
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

	return EXIT_SUCCESS;
}
