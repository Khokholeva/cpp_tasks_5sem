#include <iostream>
#include <future>
#include <chrono>
#include <vector>
#include <cmath>
// для ввода текста в строку для поиска
#include<fstream>
#include <sstream> 
using namespace std;
using namespace std::chrono;
const int n = 50;

int block_size(int threads)
{
	return n / threads + (n % threads ? 1 : 0);
}

double Sum(double pos[][2], int a, int b) 
{
	double res = 0;
	for (int i = a; i < b; i++) {
		for (int j = i+1; j < n; j++) {
			for (int k = j+1; k < n; k++) {
				double x1 = pos[i][0],
					y1 = pos[i][1],
					x2 = pos[j][0],
					y2 = pos[j][1],
					x3 = pos[k][0],
					y3 = pos[k][1];
				res += 0.5 * abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
			}
		}
	}
	return res;
}

double Sum_thread(double pos[][2], int threads, int first_index) {
	int bl_size = min(block_size(threads), n - first_index);
	return Sum(pos, first_index, first_index + bl_size);

}

void MultiThreadSum(double pos[][2], int threads)
{
	vector<future <double>> fut(threads);
	int bl_size = block_size(threads);
	int first_index = 0;
	int i = 0;
	double ans = 0;

	while (first_index < n)
	{
		fut[i] = async(Sum_thread, pos, threads, first_index);
		first_index += bl_size;
		i++;
	}
	for (int j = 0; j < i; ++j)
		ans += fut[j].get();
	cout << ans << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	double pos[n][2];
	for (int i = 0; i < n; i++) {
		//cin >> pos[i][0] >> pos[i][1];
		pos[i][0] = 1.0 * (rand() % 2000) / 200;
		pos[i][1] = 1.0 * (rand() % 2000) / 200;
		//cout << pos[i][0] << " " << pos[i][1] << endl;
	}
	
	cout << "1 thread" << endl;
	int threads = 1;
	auto start = steady_clock::now();
	MultiThreadSum(pos, threads);
	auto finish = steady_clock::now();

	cout << duration_cast <milliseconds> (finish - start).count() << "ms " << endl << endl;

	cout << "8 threads" << endl;
	threads = 8;
	start = steady_clock::now();
	MultiThreadSum(pos, threads);
	finish = steady_clock::now();

	cout << duration_cast <milliseconds> (finish - start).count() << "ms " << endl;
	
}
