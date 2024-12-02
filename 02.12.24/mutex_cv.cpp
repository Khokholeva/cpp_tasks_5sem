#include <iostream>
#include <future>
#include <chrono>
#include <vector>
#include <cmath>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std::this_thread;
using namespace std;
using namespace std::chrono;

queue<int> q;
int temp;
bool work1 = true, work2 = true;
vector<int> fact, cons;
mutex m;

vector<int> fact_ids;

void factory(int id) {
	srand(id);
	while (work1) {
		temp = rand();
		q.push(temp);
		fact.push_back(temp);
		sleep_for(milliseconds(rand() % 100));
	}
}

void consumer() {
	while (work2) {
		if (!q.empty()) {
			cons.push_back(q.front());
			q.pop();
		}
		else {
			sleep_for(milliseconds(rand() % 100));
		}
	}
}

void check_all() {
	cout << "check_all" << endl;
	thread f1(factory, 1);
	thread f2(factory, 2);
	thread c1(consumer);
	thread c2(consumer);
	thread c3(consumer);
	sleep_for(1s);
	work1 = false;
	work2 = false;
	f1.join();
	f2.join();
	c1.join();
	c2.join();
	c3.join();
	for (auto x : fact)
		cout << x << " ";
	cout << endl;
	for (auto x : cons)
		cout << x << " ";
	cout << endl;

}

void factory_m(int id) {
	srand(id);
	while (work1) {
		m.lock();
		temp = rand();
		q.push(temp);
		fact.push_back(temp);
		//cout << id << " Adding " << temp << endl;
		m.unlock();
		sleep_for(milliseconds(rand() % 100));
	}
}

void consumer_m(int id) {
	while (work2) {
		m.lock();
		if (!q.empty()) {
			cons.push_back(q.front());
			//cout << id << " Taking " << q.front() << endl;
			q.pop();
			m.unlock();
		}
		else {
			m.unlock();
			sleep_for(milliseconds(rand() % 100));
		}
	}
}

void check_all_m() {
	cout << "check_all_m" << endl;
	thread f1(factory_m, 1);
	thread f2(factory_m, 2);
	thread c1(consumer_m, 3);
	thread c2(consumer_m, 4);
	thread c3(consumer_m, 5);
	sleep_for(1s);
	work1 = false;
	work2 = false;
	f1.join();
	f2.join();
	c1.join();
	c2.join();
	c3.join();
	cout << "Factory" << endl;
	for (auto x : fact)
		cout << x << "\t";
	cout << endl << "Consumer" << endl;
	for (auto x : cons)
		cout << x << "\t";
	cout << endl << endl;

}

mutex m2;
condition_variable cv;
int cons_count = 0;


bool f_c(){
	return !q.empty();
}

void factory_cv(int id) {
	srand(id);
	while (work1 or cons_count > 0) {
		{
			unique_lock<mutex> l(m2);
			temp = rand();
			q.push(temp);
			fact.push_back(temp);
			//cout << id << " Adding " << temp << endl;
			cv.notify_one();
		}
		sleep_for(milliseconds(rand() % 100));
	}

}

void consumer_cv(int id) {
	while (work2) {
		{
			unique_lock<mutex> l(m2);

			//cout << id << " starting wait" << endl;
			cons_count++;
			cv.wait(l, f_c);
			//cout << id << " ending wait" << endl;
			cons.push_back(q.front());
			//cout << id << " Taking " << q.front() << endl;
			q.pop();
			cons_count--;
		}
		//sleep_for(milliseconds(rand() % 100));
	}
}

void check_all_cv() {
	cout << "check_all_cv" << endl;
	thread f1(factory_cv, 1);
	thread f2(factory_cv, 2);
	thread c1(consumer_cv, 3);
	thread c2(consumer_cv, 4);
	thread c3(consumer_cv, 5);
	sleep_for(1s);
	work1 = false;
	work2 = false;
	f1.join();
	f2.join();
	c1.join();
	c2.join();
	c3.join();
	cout << "Factory" << endl;
	for (auto x : fact)
		cout << x << "\t";
	cout << endl << "Consumer" << endl;
	for (auto x : cons)
		cout << x << "\t";
	cout << endl << endl;

}

int main()
{
	setlocale(LC_ALL, "Russian");
	check_all_m();
	cons.clear();
	fact.clear();
	while (!q.empty()) q.pop();
	work1 = true;
	work2 = true;
	check_all_cv();
	cons.clear();
	fact.clear();
	while (!q.empty()) q.pop();
	work1 = true;
	work2 = true;
	check_all();
}
