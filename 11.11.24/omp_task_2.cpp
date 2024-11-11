#include <iostream>
#include <cstdlib>
#include <string>
#include <omp.h>
#include <iomanip>
using namespace std;

const int n = 1000;

int partition(int a[n], int l, int r)
{
	int i = l - 1, j = r; 
	int v = a[r];
	while (true)
	{
		while (a[++i] < v);
		while (v < a[--j])
			if (j == l) 
				break;
		if (i >= j)
			break;
		swap(a[i], a[j]);
	}
	swap(a[i], a[r]);
	return i;
}

void qsort(int a[n], int l, int r)
{
	if (l >= r) return;
	int i = partition(a, l, r);
	qsort(a, l, i - 1);
	qsort(a, i + 1, r);
}


int partition_task(int a[n], int l, int r)
{
	int i = l - 1, j = r;
	int v = a[r];
	while (true)
	{
#pragma omp task shared(i)
		while (a[++i] < v);

#pragma omp task shared(j)
		while (v < a[--j])
			if (j == l)
				break;

#pragma omp taskwait

		if (i >= j)
			break;
		swap(a[i], a[j]);
	}
	swap(a[i], a[r]);
	return i;
}

void qsort_task(int a[n], int l, int r)
{
	if (l >= r) return;
	int i = partition(a, l, r);
#pragma omp task
	qsort_task(a, l, i - 1);
#pragma omp task
	qsort_task(a, i + 1, r);
#pragma omp taskwait
}

void qsort_task_b(int a[n], int l, int r)
{
	if (l >= r) return;
	int i = partition_task(a, l, r);
#pragma omp task
	qsort_task_b(a, l, i - 1);
#pragma omp task
	qsort_task_b(a, i + 1, r);
#pragma omp taskwait
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int a[n], b[n], c[n];
	for (int i = 0; i < n; i++) {
		a[i] = rand() % 1000;
		b[i] = a[i];
		c[i] = a[i];
	}

	double t = omp_get_wtime();
	qsort(a, 0, n - 1);
	cout << omp_get_wtime() - t << endl; 
	if (n <= 20) {
		for (int x : a)
			cout << x << " ";
		cout << endl;
	}
	cout << endl;

	t = omp_get_wtime();
#pragma omp parallel
	{
#pragma omp single
		{
			qsort_task(b, 0, n - 1);
		}
	}
	cout << omp_get_wtime() - t << endl;
	if (n <= 20) {
		for (int x : b)
			cout << x << " ";
		cout << endl;
	}
	cout << endl;

	t = omp_get_wtime();
#pragma omp parallel
	{
#pragma omp single
		{
			qsort_task_b(c, 0, n - 1);
		}
	}
	cout << omp_get_wtime() - t << endl;
	if (n <= 20) {
		for (int x : c)
			cout << x << " ";
		cout << endl;
	}
	cout << endl;

	return EXIT_SUCCESS;
}
