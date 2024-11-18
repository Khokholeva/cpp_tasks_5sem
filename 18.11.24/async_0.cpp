#include <iostream>
#include <future>
#include <chrono>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
using namespace std::chrono;
const int n = 100'000'000;

int block_size(int threads)
{
	return n / threads + (n % threads ? 1 : 0);
}
double f(double t) {
	return 1 / (1 + t * t);
}
double pi_part(int f_i, int l_i) {
	double res = 0;
	for (int i = f_i; i < min(l_i, n); i++) {
		res += f((2.0 * i + 1) / 2 / n);
	}
	return res;
}
void MultiThreadTable(int threads)
{
	vector<future <double>> fut(threads);
	int bl_size = block_size(threads);
	int first_index = 0;
	int i = 0;
	double ans = 0;
	while (first_index < n)
	{
		fut[i] = async(pi_part, first_index, first_index + bl_size);
		first_index += bl_size;
		i++;
	}
	for (int j = 0; j < i; ++j)
		ans += fut[j].get();
	cout << setprecision(10) << ans * 4 / n << endl;
}
int main()
{
	cout << "1 thread" << endl;
	int threads = 1;
	auto start = steady_clock::now();
	MultiThreadTable(threads);
	auto finish = steady_clock::now();

	cout << duration_cast <milliseconds> (finish - start).count() << "ms " << endl << endl;

	cout << "8 threads" << endl;
	threads = 8;
	start = steady_clock::now();
	MultiThreadTable(threads);
	finish = steady_clock::now();

	cout << duration_cast <milliseconds> (finish - start).count() << "ms " << endl;
	
}
