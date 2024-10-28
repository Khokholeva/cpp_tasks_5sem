#include <iostream>
#include <cstdlib>
#include <string>
#include <omp.h>
#include <iomanip>
using namespace std;

const int a = 10000, b = 10000;
double M[a][b];
double x[b];
double res[a];
double res2[a];

int main()
{
	setlocale(LC_ALL, "Russian");

	//Ввод
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			M[i][j] = 10 * i + j;
		}
	}
	for (int j = 0; j < b; j++) {
		x[j] = j + 3;
	}

	cout << "Последовательно" << endl;
	double t = omp_get_wtime();
	for (int i = 0; i < a; i++) {
		res[i] = 0;
		for (int j = 0; j < b; j++) {
			res[i] += M[i][j] * x[j];
		}
	}
	cout << "Time: " << omp_get_wtime() - t << endl;

	cout << endl << "Parallel" << endl;
	double t2 = omp_get_wtime();

#pragma omp parallel 
	{
		int id = omp_get_thread_num();
		int num = omp_get_num_threads();
		for (int i = id; i < a; i+=num) {
			res2[i] = 0;
			for (int j = 0; j < b; j++) {
				res2[i] += M[i][j] * x[j];
			}
		}
	}
	cout << "Time: " << omp_get_wtime() - t2 << endl;

	//Проверка результата для небольших размеров
	/*
	cout << "Проверка результата" << endl;
	cout << "M" << "\t\t";
	for (int i = 1; i < b; i++) cout << "\t";
	cout << "x\t\tres\t\tres2" << endl;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			cout << M[i][j] << '\t';
		}
		cout << "\t";
		if (i < b) cout << x[i];
		cout << "\t\t" << res[i] << "\t\t" << res2[i];
		cout << endl;
	}
	for (int j = a; j < b; j++) {
		for (int j = 0; j < b; j++) {
			cout << '\t';
		}
		cout << "\t\t" << x[j] << endl;
	}
	*/

	return EXIT_SUCCESS;
}
