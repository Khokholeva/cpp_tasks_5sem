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
const int n = 10'000'000;

int block_size(int threads)
{
	return n / threads + (n % threads ? 1 : 0);
}

int remainder(string s) {
	int ans = 0;
	int size = s.size();
	for (int i = 0; i < size; i++) {
		ans = (ans * 10 + s[i] - '0') % 17;
	}
	return ans;
}
int remainder_thread(string s, int threads, int first_index){
	int bl_size = min(block_size(threads), n - first_index);
	string task = s.substr(first_index, bl_size);
	
	int rems[16];
	int d = 1;
	for (int i = 0; i < 16; i++) {
		rems[i] = d;
		d = (d * 10) % 17;
	}

	int r = remainder(task);
	int deg = rems[(n - first_index - bl_size) % 16]; 
	return (r * deg) % 17;

}

void MultiThreadCalc(string s, int threads)
{
	vector<future <int>> fut(threads);
	int s_size = s.size();
	int bl_size = block_size(threads);
	int first_index = 0;
	int i = 0;
	int ans = 0;

	

	while (first_index < s_size)
	{
		fut[i] = async(remainder_thread, s, threads, first_index);
		first_index += bl_size;
		i++;
	}
	for (int j = 0; j < i; ++j)
		ans += fut[j].get();
	ans %= 17;
	cout << ans << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	string s = to_string(rand() % 9 + 1);
	for (int i = 0; i < n - 1; i++) s += to_string(rand() % 10);

	cout << "1 thread" << endl;
	int threads = 1;
	auto start = steady_clock::now();
	MultiThreadCalc(s, threads);
	auto finish = steady_clock::now();

	cout << duration_cast <milliseconds> (finish - start).count() << "ms " << endl << endl;

	cout << "8 threads" << endl;
	threads = 8;
	start = steady_clock::now();
	MultiThreadCalc(s, threads);
	finish = steady_clock::now();

	cout << duration_cast <milliseconds> (finish - start).count() << "ms " << endl;
	
}
