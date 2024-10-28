#include <iostream>
#include <cstdlib>
#include <string>
#include <omp.h>
#include <iomanip>
using namespace std;

const int a = 1000;
double M[a][a + 1];
double M_par[a][a + 1];
double M_for[a][a + 1];
double M_low[a][a + 1];
double ans[a];
void generate_sys() {
	int x, y;
	double t;
	
	//приводим к единичной
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < a+1; j++) M[i][j] = 0;
	}
	for (int i = 0; i < a; i++) {
		M[i][i] = 1;
	}
	//200 случайных элементарных преобразований
	for (int k = 0; k < 100; k++)
	{
		x = rand() % a;
		y = rand() % a;
		t = rand() * 2.0 / RAND_MAX - 1.0;
		for (int j = 0; j < a; j++) {
			M[y][j] -= M[x][j] * t;
		}
	}
	for (int k = 0; k < 100; k++)
	{
		x = rand() % a;
		y = rand() % a;
		t = rand() * 2.0 / RAND_MAX - 1.0;
		for (int i = 0; i < a; i++) {
			M[i][y] -= M[i][x] * t;
		}
	}
	//случайный набор неизвестных
	for (int i = 0; i < a; i++) {
		ans[i] = rand() * 20.0 / RAND_MAX - 10;
	}
	//вычисляем столбец правых частей
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < a; j++) {
			M[i][a] += M[i][j] * ans[j];
		}
	}
	//копируем в матрицы для других алгоритмов
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < a + 1; j++) {
			M_par[i][j] = M[i][j];
			M_for[i][j] = M[i][j];
			M_low[i][j] = M[i][j];
		}
	}
}

void gauss_jord() {
	cout << "Последовательно" << endl;
	double t = omp_get_wtime();
	double m;
	int id;
	double temp;
	double coef;

	for (int k = 0; k < a; k++) {
		m = 0;
		//Находим строку с макс k-ым элементом
		for (int i = k; i < a; i++) {
			if (abs(M[i][k]) > abs(m)) {
				m = M[i][k];
				id = i;
			}
		}
		if (m == 0) continue;
		//Меняем местами строки k и id и делим на m
		for (int j = 0; j < a + 1; j++) {
			temp = M[k][j];
			M[k][j] = M[id][j];
			M[id][j] = temp;
			M[k][j] /= m;
		}
		//Вычитаем из остальных
		for (int i = 0; i < a; i++) {
			if (i == k) continue;
			coef = M[i][k];
			for (int j = 0; j < a + 1; j++) {
				M[i][j] -= M[k][j] * coef;
			}
		}
	}

	cout << "Time: " << omp_get_wtime() - t << endl;
}

void paral_sect_gj() {
	cout << "Параллельно 2 секции" << endl;
	double t = omp_get_wtime();

	int id;
	double m;
	double m_temp = 0, m_temp2 = 0;
	int id1, id2;
	for (int k = 0; k < a; k++)
	{
		//Находим строку с макс k-ым элементом
#pragma omp parallel sections 
		{
#pragma omp section 
			{
				m_temp = 0;
				for (int i = k; i < a; i += 2) {
					if (abs(M[i][k]) > abs(m_temp)) {
						m_temp = M_par[i][k];
						id1 = i;
					}
				}
			}
#pragma omp section 
			{
				m_temp2 = 0;
				for (int i = k + 1; i < a; i += 2) {
					if (abs(M[i][k]) > abs(m_temp2)) {
						m_temp2 = M_par[i][k];
						id2 = i;
					}
				}
			}
		}
		if (abs(m_temp) > abs(m_temp2)) { m = m_temp; id = id1; }
		else { m = m_temp2; id = id2; }
		if (m == 0) continue;

		//Меняем местами строки k и id и делим на m
#pragma omp parallel sections 
		{
#pragma omp section
			{
				double temp;
				for (int j = 0; j < a + 1; j += 2) {
					temp = M_par[k][j];
					M_par[k][j] = M_par[id][j];
					M_par[id][j] = temp;
					M_par[k][j] /= m;
				}
			}
#pragma omp section
			{
				double temp;
				for (int j = 1; j < a + 1; j += 2) {
					temp = M_par[k][j];
					M_par[k][j] = M_par[id][j];
					M_par[id][j] = temp;
					M_par[k][j] /= m;
				}
			}
		}
		//Вычитаем из остальных
#pragma omp parallel sections 
		{
#pragma omp section
			{
				double coef1;
				for (int i = 0; i < a; i += 2) {
					if (i == k) continue;
					coef1 = M_par[i][k];
					for (int j = 0; j < a + 1; j++) {
						M_par[i][j] -= M_par[k][j] * coef1;
					}
				}
			}
#pragma omp section
			{
				double coef2;
				for (int i = 1; i < a; i += 2) {
					if (i == k) continue;
					coef2 = M_par[i][k];
					for (int j = 0; j < a + 1; j++) {
						M_par[i][j] -= M_par[k][j] * coef2;
					}
				}
			}
		}
	}

	cout << "Time: " << omp_get_wtime() - t << endl;
}

void paral_for_gj() {
	cout << "Параллельно for" << endl;
	double t = omp_get_wtime();
	double m;
	int id;
	double temp;
	double coef;

	for (int k = 0; k < a; k++)
	{
		m = 0;
		//Находим строку с макс k-ым элементом
		//Не распараллелить с for?
		for (int i = k; i < a; i++) {
			if (abs(M_for[i][k]) > abs(m)) {
				m = M_for[i][k];
				id = i;
			}
		}
		if (m == 0) continue;
		//Меняем местами строки k и id и делим на m - придется обойтись без temp
#pragma omp parallel for schedule(static)
		for (int j = 0; j < a + 1; j++) {
			/*
			temp = M_for[k][j];
			M_for[k][j] = M_for[id][j];
			M_for[id][j] = temp;
			*/
			if (id != k) {
				//k		id
				//a		b
				M_for[k][j] += M_for[id][j];//a+b	b
				M_for[id][j] -= M_for[k][j];//a+b	-a
				M_for[k][j] += M_for[id][j];//b		-a
				M_for[id][j] *= -1;         //b		a
			}
			M_for[k][j] /= m;
		}
		//Вычитаем из остальных - не сохраняем coef
#pragma omp parallel for schedule(static)
		for (int i = 0; i < a; i++) {
			if (i == k) continue;
			for (int j = 0; j < a + 1; j++) {
				if (j == k) continue;
				M_for[i][j] -= M_for[k][j] * M_for[i][k];
			}
			M_for[i][k] = 0;
		}
	}

	cout << "Time: " << omp_get_wtime() - t << endl;
}


void paral_low_gj() {
	cout << "Параллельно низкого уровня" << endl;
	double t = omp_get_wtime();
	double m;
	int id;

	for (int k = 0; k < a; k++)
	{
		m = 0;
		//Находим строку с макс k-ым элементом
		//Не распараллелить с for?
		for (int i = k; i < a; i++) {
			if (abs(M_low[i][k]) > abs(m)) {
				m = M_low[i][k];
				id = i;
			}
		}
		if (m == 0) continue;
		//Меняем местами строки k и id и делим на m
#pragma omp parallel 
		{
			int thr = omp_get_thread_num();
			int num = omp_get_num_threads();
			double temp;
			for (int j = thr; j < a + 1; j+=num) {
				temp = M_low[k][j];
				M_low[k][j] = M_low[id][j];
				M_low[id][j] = temp;
				M_low[k][j] /= m;
			}
		}
		//Вычитаем из остальных
#pragma omp parallel
		{
			int thr = omp_get_thread_num();
			int num = omp_get_num_threads();
			double coef;
			for (int i = thr; i < a; i+=num) {
				if (i == k) continue;
				coef = M_low[i][k];
				for (int j = 0; j < a + 1; j++) {
					M_low[i][j] -= M_low[k][j] * coef;
				}
			}
		}
	}

	cout << "Time: " << omp_get_wtime() - t << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	//Генерация задачи
	srand(time(NULL));
	generate_sys();

	//Исходная система - для небольших размеров
	if (a < 10) {
		cout << "Исходная система" << endl;
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < a + 1; j++) {
				cout << M[i][j] << "\t";
			}
			cout << endl;
		}
	}

	//Последовательно
	gauss_jord();
	
	//Параллельно 2 секции
	paral_sect_gj();

	//Параллельно for
	paral_for_gj();

	//Параллельно низкого уровня
	paral_low_gj();

	//Проверка для небольших размеров
	/*
	if (a < 10) {
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < a + 1; j++) {
				cout << M[i][j] << "\t";
			}
			cout << endl;
		}
		cout << endl;
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < a + 1; j++) {
				cout << M_par[i][j] << "\t";
			}
			cout << endl;
		}
		cout << endl;
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < a + 1; j++) {
				cout << M_for[i][j] << "\t";
			}
			cout << endl;
		}
		cout << endl;
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < a + 1; j++) {
				cout << M_low[i][j] << "\t";
			}
			cout << endl;
		}
		cout << endl;
	}
	*/

	// все векторы значений
	if (a < 20) {
		cout << "Сгенерированный" << endl;
		for (int i = 0; i < a; i++) {
			cout << ans[i] << "\t";
		}
		cout << endl << "Последовательно" << endl;
		for (int i = 0; i < a; i++) {
			cout << M[i][a] << "\t";
		}
		cout << endl <<  "Параллельно - sections" << endl;
		for (int i = 0; i < a; i++) {
			cout << M_par[i][a] << "\t";
		}
		cout << endl << "Параллельно - for" << endl;
		for (int i = 0; i < a; i++) {
			cout << M_for[i][a] << "\t";
		}
		cout << endl << "Параллельно низкого уровня" << endl;
		for (int i = 0; i < a; i++) {
			cout << M_low[i][a] << "\t";
		}
	}

	return EXIT_SUCCESS;
}
