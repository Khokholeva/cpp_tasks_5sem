#include <iostream>
#include <cstdlib>
#include <string>
#include <omp.h>
#include <iomanip>
using namespace std;


int main()
{

	setlocale(LC_ALL, "Russian");

	int n = 1000000;
	//cin >> n;
	double t = omp_get_wtime();
	int res = 1;
	bool prime;
	for (int k = 3; k <= n; k += 2) {
		prime = true;
		for (int i = 3; i * i <= k; i += 2) {
			if (k % i == 0) {
				prime = false;
				break;
			}
		}
		if (prime) res++;
	}
	cout << res << endl;
	cout << "Time: " << omp_get_wtime() - t << endl;

	cout << endl << "Parallel" << endl;
	double t2 = omp_get_wtime();
	int res2 = 1;
	
#pragma omp parallel 
	{
		int id = omp_get_thread_num();
		int num = omp_get_num_threads();
		int res = 0;
		bool prime;
		for (int k = 2*id + 3; k <= n; k += 2*num) {
			prime = true;
			for (int i = 3; i * i <= k; i += 2) {
				if (k % i == 0) {
					prime = false;
					break;
				}
			}
			if (prime) res++;
		}
#pragma omp atomic 
		res2 += res;
	}

	cout << res2 << endl;
	cout << "Time: " << omp_get_wtime() - t2 << endl;


	return EXIT_SUCCESS;
}
