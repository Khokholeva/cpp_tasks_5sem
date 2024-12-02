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

double Sum(double pos[][2], int f_i, int threads)
{
	double res = 0;
	int opers = 0;
	for (int i = f_i; i < n; i+=threads) {
		for (int j = i + 1; j < n; j++) {
			for (int k = j + 1; k < n; k++) {
				double x1 = pos[i][0],
					y1 = pos[i][1],
					x2 = pos[j][0],
					y2 = pos[j][1],
					x3 = pos[k][0],
					y3 = pos[k][1];
				res += 0.5 * abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
				opers++;
			}
		}
	}
	cout << opers << endl;
	return res;
}

void MultiThreadSum(double pos[][2], int threads)
{
	vector<future <double>> fut(threads);
	int i = 0;
	double ans = 0;

	while (i < min(threads, n))
	{
		fut[i] = async(Sum, pos, i, threads);
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
