#include <iostream>
#include <future>
#include <chrono>
#include <vector>
#include <cmath>
#include <thread>
#include <mutex>
using namespace std::this_thread;
using namespace std;
using namespace std::chrono;

int object;
bool work1 = true, work2 = true, flag = false;
vector<int> fact, cons;
mutex m;

vector<int> fact_ids;

void factory() {
	while (work1) {
		if (flag) {
			sleep_for(milliseconds(rand() % 100));
		}
		else { 
			object = rand();
			fact.push_back(object);
			flag = true;
		}
	}
}

void consumer() {
	while (work2) {
		if (flag) {
			cons.push_back(object);
			flag = false;
		}
		else {
			sleep_for(milliseconds(rand() % 100));
		}
	}
}

void check_all() {
	thread f1(factory);
	thread f2(factory);
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

void factory_m() {
	while (work1) {
		m.lock();
		if (flag) {
			m.unlock();
			sleep_for(milliseconds(rand() % 100));
		}
		else {
			object = rand();
			fact.push_back(object);
			flag = true;
			m.unlock();
		}
	}
}

void consumer_m() {
	while (work2) {
		m.lock();
		if (flag) {
			cons.push_back(object);
			flag = false;
			m.unlock();
		}
		else {
			m.unlock();
			sleep_for(milliseconds(rand() % 100));
		}
	}
}

void check_all_m() {
	cout << "Base check_all_m" << endl;
	thread f1(factory_m);
	thread f2(factory_m);
	thread c1(consumer_m);
	thread c2(consumer_m);
	thread c3(consumer_m);
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
//Все что после этой функции до main не часть задания, а эксперименты с работой rand()

void factory_m_test(int id) {
	int timer;
	while (work1) {
		m.lock();
		if (flag) {
			timer = rand();
			cout << id << ": waiting, timer " << timer << endl;
			m.unlock();
			sleep_for(milliseconds(timer % 100));
		}
		else {
			object = rand();
			cout << id << ": adding, object " << object << endl;
			fact.push_back(object);
			fact_ids.push_back(id);
			flag = true;
			m.unlock();
		}
	}
}

void factory_m_test_b(int id) {
	srand(id);
	int timer;
	while (work1) {
		m.lock();
		if (flag) {
			timer = rand();
			cout << id << ": waiting, timer " << timer << endl;
			m.unlock();
			sleep_for(milliseconds(timer % 100));
		}
		else {
			object = rand();
			cout << id << ": adding, object " << object << endl;
			fact.push_back(object);
			fact_ids.push_back(id);
			flag = true;
			m.unlock();
		}
	}
}

void check_all_m_test() {
	cout << "check_all_m with ids" << endl;
	thread f1(factory_m_test, 1);
	thread f2(factory_m_test, 2);
	thread c1(consumer_m);
	thread c2(consumer_m);
	thread c3(consumer_m);
	sleep_for(1s);
	work1 = false;
	work2 = false;
	f1.join();
	f2.join();
	c1.join();
	c2.join();
	c3.join();
	cout << "Factory" << endl;
	for (auto x : fact_ids)
		cout << x << "\t";
	cout << endl;
	for (auto x : fact)
		cout << x << "\t";
	cout << endl << "Consumer" << endl;
	for (auto x : cons)
		cout << x << "\t";
	cout << endl << endl;
}

void check_all_m_test_b() {
	cout << "check_all_m with ids and per-id randomization" << endl;
	thread f1(factory_m_test_b, 1);
	thread f2(factory_m_test_b, 2);
	thread c1(consumer_m);
	thread c2(consumer_m);
	thread c3(consumer_m);
	sleep_for(1s);
	work1 = false;
	work2 = false;
	f1.join();
	f2.join();
	c1.join();
	c2.join();
	c3.join();
	cout << "Factory" << endl;
	for (auto x : fact_ids)
		cout << x << "\t";
	cout << endl;
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
	fact.clear();
	cons.clear();
	work1 = true;
	work2 = true;
	flag = false;

	check_all_m_test();
	fact.clear();
	cons.clear();
	fact_ids.clear();
	work1 = true;
	work2 = true;
	flag = false;

	check_all_m_test_b();
	fact.clear();
	cons.clear();
	fact_ids.clear();
	
}
