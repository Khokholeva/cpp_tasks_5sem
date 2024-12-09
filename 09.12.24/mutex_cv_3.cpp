#include <iostream>
#include <future>
#include <chrono>
#include <vector>
#include <cmath>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <stack>
#include <deque>
using namespace std::this_thread;
using namespace std;
using namespace std::chrono;

//3
template<class T>
class Threadsafe_stack
{
private:
	stack<T> s;
	mutex m;
	condition_variable cv;
public:
	void push(T value) {
		lock_guard<mutex> l(m);
		s.push(value);
		cv.notify_one();
	}
	void pop(T& value) {
		unique_lock<mutex> l(m);
		cv.wait(l, [this] {return !s.empty(); });
		value = s.top();
		s.pop();
	}
	bool empty() {
		lock_guard<mutex> l(m);
		return s.empty();
	}

};

template<class T>
class Threadsafe_deque
{
private:
	deque<T> d;
	mutex m;
	condition_variable cv;
public:
	void push_back(T value) {
		lock_guard<mutex> l(m);
		d.push_back(value);
		cv.notify_one();
	}
	void push_front(T value) {
		lock_guard<mutex> l(m);
		d.push_front(value);
		cv.notify_one();
	}
	void pop_back(T& value) {
		unique_lock<mutex> l(m);
		cv.wait(l, [this] {return !d.empty(); });
		value = d.back();
		d.pop_back();
	}
	void pop_front(T& value) {
		unique_lock<mutex> l(m);
		cv.wait(l, [this] {return !d.empty(); });
		value = d.front();
		d.pop_front();
	}
	bool empty() {
		lock_guard<mutex> l(m);
		return d.empty();
	}

};

Threadsafe_stack<int> st;

void f(int id) {
	srand(id);
	for (int i = 0; i < 5; i++) {
		st.push(id* 100 + i);
		sleep_for(milliseconds(rand() % 100));
	}
}

Threadsafe_deque<int> dq;

void fa(int id) {
	srand(id);
	for (int i = 0; i < 5; i++) {
		dq.push_back(id * 100 + i);
		sleep_for(milliseconds(rand() % 100));
	}
}

void fb(int id) {
	srand(id);
	for (int i = 0; i < 5; i++) {
		dq.push_front(id * 100 + i);
		sleep_for(milliseconds(rand() % 100));
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	//check_all_ts();
	thread f1(f, 1);
	thread f2(f, 2);
	thread f3(f, 3);
	f1.join();
	f2.join();
	f3.join();
	int x;
	for (int i = 0; i < 15; i++) {
		st.pop(x);
		cout << x << " ";
	}
	cout << endl;
	thread f4(fa, 1);
	thread f5(fa, 2);
	thread f6(fb, 3);
	thread f7(fb, 4);
	f4.join();
	f5.join();
	f6.join();
	f7.join();
	
	for (int i = 0; i < 20; i++) {
		dq.pop_back(x);
		cout << x << " ";
	}

}
