#include <iostream>
#include <future>
#include <chrono>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;
using namespace std::chrono;

int block_size(int threads, int n)
{
	return n / threads + (n % threads ? 1 : 0);
}

int Find(string s, string what, int a, int b) {
	int l = what.size();
	string test;
	int res = 0;
	for (int i = a; i < b; i++) {
		test = s.substr(i, l);
		if (test == what) res++;
	}
	return res;
}

void MultiThreadFind(int threads, string s, string what)
{
	vector<future <int>> fut(threads);
	int s_size = s.size();
	int bl_size = block_size(threads, s_size);
	int first_index = 0;
	int i = 0;
	int ans = 0;
	while (first_index < s_size)
	{
		fut[i] = async(Find, s, what, first_index, min(first_index + bl_size, s_size));
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
	string s = "", what = "the";
	ifstream file("bible.txt");
	string line;
	while (std::getline(file, line))
	{
		s += line + " ";
	}
	cout << "Длина строки: " << s.size() << endl << endl;
	cout << "1 thread" << endl;
	int threads = 1;
	auto start = steady_clock::now();
	MultiThreadFind(threads, s, what);
	auto finish = steady_clock::now();

	cout << duration_cast <milliseconds> (finish - start).count() << "ms " << endl << endl;

	cout << "8 threads" << endl;
	threads = 8;
	start = steady_clock::now();
	MultiThreadFind(threads, s, what);
	finish = steady_clock::now();

	cout << duration_cast <milliseconds> (finish - start).count() << "ms " << endl;
	
}
