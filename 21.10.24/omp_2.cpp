#include <iostream>
#include <cstdlib>
#include <string>
#include <omp.h>
using namespace std;

const double PI = 3.141592653589793238463;

int main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	cin >> n;
	double t = omp_get_wtime();
	int res = 1; //сразу считаем 2
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

	
	double t2 = omp_get_wtime();
	double res2 = 1;
	int d;
	d = n / pow(4, 1.0 / 3);
	if (d % 2 == 0) d++;

#pragma omp parallel sections reduction(+:res2)
	{

#pragma omp section 
		{
			bool prime1;
			for (int k = 3; k < d; k += 2) {
				prime1 = true;
				for (int i = 3; i * i <= k; i += 2) {
					if (k % i == 0) {
						prime1 = false;
						break;
					}
				}
				if (prime1) res2++;
			}
		}
#pragma omp section 
		{
			bool prime2;
			for (int k = d; k <= n; k += 2) {
				prime2 = true;
				for (int i = 3; i * i <= k; i += 2) {
					if (k % i == 0) {
						prime2 = false;
						break;
					}
				}
				if (prime2) res2++;
			}
		}

	}
	cout << endl;
	cout << res2 << endl;
	cout << "Time: " << omp_get_wtime() - t2 << endl << endl;

	double t3 = omp_get_wtime();
	double res3 = 1;

#pragma omp parallel sections reduction(+:res3)
	{

#pragma omp section 
		{
			bool prime1;
			for (int k = 3; k <= n; k += 4) {
				prime1 = true;
				for (int i = 3; i * i <= k; i += 2) {
					if (k % i == 0) {
						prime1 = false;
						break;
					}
				}
				if (prime1) res3++;
			}
		}
#pragma omp section 
		{
			bool prime2;
			for (int k = 5; k <= n; k += 4) {
				prime2 = true;
				for (int i = 3; i * i <= k; i += 2) {
					if (k % i == 0) {
						prime2 = false;
						break;
					}
				}
				if (prime2) res3++;
			}
		}

	}
	cout << res3 << endl;
	cout << "Time: " << omp_get_wtime() - t3 << endl;
	return EXIT_SUCCESS;
}
