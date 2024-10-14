#include <iostream>
#include <cstdlib>
#include <string>
#include <omp.h>
using namespace std;
!программу нужно писать для своего колва процесссоров = колву section
const double PI = 3.141592653589793238463;
int n = 100000000;
double* sins = new double[n];
double* sins_par = new double[n];
int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Последовательно" << endl;
	double t = omp_get_wtime();
	for (int i = 0; i < n; i++) {
		sins[i] = sin(i * PI / 2 / n);
	}
	cout << "Time: " << omp_get_wtime() - t << endl;

	//12 веток
	cout << "12 Веток" << endl;
	double t2 = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section 
		{
			for (int i = 0; i < n / 12; i++) {
				sins_par[i] = sin(i * PI / 2 / n);
			}
		}
#pragma omp section 
		{
			for (int i = n / 12; i < 2 * n / 12; i++) {
				sins_par[i] = sin(i * PI / 2 / n);
			}
		}
#pragma omp section 
		{
			for (int i = 2 * n / 12; i < 3 * n / 12; i++) {
				sins_par[i] = sin(i * PI / 2 / n);
			}
		}
#pragma omp section 
		{
			for (int i = 3 * n / 12; i < 4 * n / 12; i++) {
				sins_par[i] = sin(i * PI / 2 / n);
			}
		}
#pragma omp section 
		{
			for (int i = 4 * n / 12; i < 5 * n / 12; i++) {
				sins_par[i] = sin(i * PI / 2 / n);
			}
		}
#pragma omp section 
		{
			for (int i = 5 * n / 12; i < 6 * n / 12; i++) {
				sins_par[i] = sin(i * PI / 2 / n);
			}
		}
#pragma omp section 
		{
			for (int i = 6 * n / 12; i < 7 * n / 12; i++) {
				sins_par[i] = sin(i * PI / 2 / n);
			}
		}
#pragma omp section 
		{
			for (int i = 7 * n / 12; i < 8 * n / 12; i++) {
				sins_par[i] = sin(i * PI / 2 / n);
			}
		}
#pragma omp section 
		{
			for (int i = 8 * n / 12; i < 9 * n / 12; i++) {
				sins_par[i] = sin(i * PI / 2 / n);
			}
		}
#pragma omp section 
		{
			for (int i = 9 * n / 12; i < 10 * n / 12; i++) {
				sins_par[i] = sin(i * PI / 2 / n);
			}
		}
#pragma omp section 
		{
			for (int i = 10 * n / 12; i < 11 * n / 12; i++) {
				sins_par[i] = sin(i * PI / 2 / n);
			}
		}
#pragma omp section 
		{
			for (int i = 11 * n / 12; i < n; i++) {
				sins_par[i] = sin(i * PI / 2 / n);
			}
		}
	}
	cout << "Time: " << omp_get_wtime() - t2 << endl;

	return EXIT_SUCCESS;
}
