#include <iostream>
#include <cstdlib>
#include <string>
#include <random>
using namespace std;

//Task 1 and its part of task 4
minstd_rand gen_minstd;
mt19937 gen_mt;
ranlux48 gen_ranlux;
knuth_b gen_knuth;
random_device gen_rd;

int scale_rand(int a, int b) {
    return (int)(rand() / (1.0 + RAND_MAX) * (b - a + 1)) + a;
}

int mod_rand(int a, int b) {
    return rand() % (b - a + 1) + a;
}

void generate_1(auto gen, auto distrib) {
    int k;
    double disp = 0;
    double count[101] = { 0 };
    int max_val = 0;
    for (int i = 0; i < 1000000; i++) {
        k = distrib(gen);
        count[k]++;
    }

    for (int i = 0; i < 101; i++) {
        count[i] *= 100.0 / 1000000;
        disp += (count[i] - 100.0 / 101) * (count[i] - 100.0 / 101);
        count[i] = round(count[i] * 100);
        max_val = max_val < count[i] ? count[i] : max_val;
    }

    disp /= 100;
    cout << "Дисперсия отклонений: " << disp << endl;

    for (int i = max_val; i > 0; i--) {
        for (int j = 0; j < 101; j++) {
            count[j] >= i ? cout << '*' : cout << ' ';
        }
        cout << endl;
    }
    for (int j = 0; j < 101; j++) {
        cout << '-';
    }
    cout << endl;
}

void task_1(auto distrib) {

    int k;
    double disp = 0;
    double count[101] = { 0 };
    int max_val = 0;

    cout << "minstd_rand" << endl;
    generate_1(gen_minstd, distrib);
    cout << "mt19937" << endl;
    generate_1(gen_mt, distrib);
    cout << "ranlux48" << endl;
    generate_1(gen_ranlux, distrib);
    cout << "knuth_b" << endl;
    generate_1(gen_knuth, distrib);
    cout << "random_device" << endl;

    for (int i = 0; i < 1000000; i++) {
        k = distrib(gen_rd);
        count[k]++;
    }
    for (int i = 0; i < 101; i++) {
        count[i] *= 100.0 / 1000000;
        disp += (count[i] - 100.0 / 101) * (count[i] - 100.0 / 101);
        count[i] = round(count[i] * 100);
        max_val = max_val < count[i] ? count[i] : max_val;
    }

    disp /= 100;
    cout << "Дисперсия отклонений: " << disp << endl;

    for (int i = max_val; i > 0; i--) {
        for (int j = 0; j < 101; j++) {
            count[j] >= i ? cout << '*' : cout << ' ';
        }
        cout << endl;
    }
    for (int j = 0; j < 101; j++) {
        cout << '-';
    }
    cout << endl;
}
 
int main()
{
    setlocale(LC_ALL, "Russian");

    //task 1
    cout << "Task 1 - uniform distribution" << endl;
    int k;
    double disp = 0;
    double count[101] = { 0 };
    int max_val = 0;

    cout << "Scaled rand" << endl;

    for (int i = 0; i < 1000000; i++) {
        k = scale_rand(0, 100);
        count[k]++;
    }
    for (int i = 0; i < 101; i++) {
        count[i] *= 100.0 / 1000000;
        disp += (count[i] - 100.0 / 101) * (count[i] - 100.0 / 101);
        count[i] = round(count[i] * 100);
        max_val = max_val < count[i] ? count[i] : max_val;
    }

    disp /= 100;
    cout << "Дисперсия отклонений: " << disp << endl;

    for (int i = max_val; i > 0; i--) {
        for (int j = 0; j < 101; j++) {
            count[j] >= i ? cout << '*' : cout << ' ';
        }
        cout << endl;
    }

    for (int j = 0; j < 101; j++) {
        cout << '-';
    }
    cout << endl;


    for (int i = 0; i < 101; i++) {
        count[i] = 0;
    }
    disp = 0;


    cout << "Modulo rand" << endl;

    for (int i = 0; i < 1000000; i++) {
        k = mod_rand(0, 100);
        count[k]++;
    }
    for (int i = 0; i < 101; i++) {
        count[i] *= 100.0 / 1000000;
        disp += (count[i] - 100.0 / 101) * (count[i] - 100.0 / 101);
        count[i] = round(count[i] * 100);
        max_val = max_val < count[i] ? count[i] : max_val;
    }
    disp /= 100;
    cout << "Дисперсия отклонений: " << disp << endl;

    for (int i = max_val; i > 0; i--) {
        for (int j = 0; j < 101; j++) {
            count[j] >= i ? cout << '*' : cout << ' ';
        }
        cout << endl;
    }
    for (int j = 0; j < 101; j++) {
        cout << '-';
    }
    cout << endl;

    for (int i = 0; i < 101; i++) {
        count[i] = 0;
    }
    disp = 0;

    int pois_m = 30;
    double norm_m = 60;
    double norm_var = 7.0;
    uniform_int_distribution<int> distrib_uni_1(0, 100);
    normal_distribution<double> distrib_norm_1(norm_m, norm_var);
    poisson_distribution<int> distrib_pois_1(pois_m);

    task_1(distrib_uni_1);
    cout << "Normal distribution: " << norm_m << " " << norm_var << endl;
    task_1(distrib_norm_1);
    cout << "Poisson distribution: " << pois_m << endl;
    task_1(distrib_pois_1);
	return EXIT_SUCCESS;
}
