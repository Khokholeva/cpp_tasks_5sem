#include <iostream>
#include <cstdlib>
#include <string>
#include <omp.h>
#include <iomanip>
#include <list>
#include <fstream>
using namespace std;

struct Pair {
	int n;
	bool b;
	Pair(int d): n(d){}
};

bool isPrime(int n) {
	for (int i = 2; i * i <= n; i++) 
		if (n % i == 0)  return false;
	return true;
}
void processNode(Pair& p) {
	p.b = isPrime(p.n);
}

void processList(list<Pair> &l, void (*f) (Pair &)) {
	list<Pair>::iterator i;
	for (i = l.begin(); i != l.end(); i++)
		processNode(*i);
}

void processListTask(list<Pair>& l, void (*f) (Pair&)) {
#pragma omp task shared(l)
	{
		list<Pair>::iterator i;
		for (i = l.begin(); i != l.end(); i++) {
			processNode(*i);
			i++;
			if (i == l.end()) break;
		}
	}
#pragma omp task shared(l)
	{
		list<Pair>::iterator i;
		for (i = ++l.begin(); i != l.end(); i++) {
			processNode(*i);
			i++;
			if (i == l.end()) break;
		}
	}
#pragma omp taskwait
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	const int MAX_N = 300000, MIN_N = 100000, step = 10000;
	int n, d;
	list<Pair> l, l_t;
	ofstream fout("list.txt");
	fout << (MAX_N - MIN_N) / step + 1 << endl;

	for (n = MIN_N; n <= MAX_N; n += step) {
		fout << n << " ";
		l.clear();
		l_t.clear();
		for (int i = 0; i < n; i++)
		{
			d = rand() % 100;
			l.push_back(Pair(d));
			l_t.push_back(Pair(d));
		}
		double t = omp_get_wtime();
		processList(l, processNode);
		fout << omp_get_wtime() - t << " ";

		t = omp_get_wtime();

#pragma omp parallel
		{
#pragma omp single
			{
				processListTask(l_t, processNode);
			}
		}
		fout << omp_get_wtime() - t << endl;

		list<Pair>::iterator i = l.begin(), j = l_t.begin();
		for (int k = 0; k < n; k++) {
			if ((*i).b != (*j).b) cout << (*i).n << endl;
			i++;
			j++;
		}
	}

	return EXIT_SUCCESS;
}
