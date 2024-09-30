#include <iostream>
#include <cstdlib>
#include <string>
#include <random>
using namespace std;

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

void generate_2(auto gen, auto distrib) {
    int k;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            k = distrib(gen_rd);
            if (k == 0) cout << " "; else cout << '*';
        }
        cout << endl;
    }
    for (int j = 0; j < 101; j++) {
        cout << '-';
    }
    cout << endl << endl;
}

void task_2(auto distrib) {

    cout << "minstd_rand" << endl;
    generate_2(gen_minstd, distrib);
    cout << "mt19937" << endl;
    generate_2(gen_mt, distrib);
    cout << "ranlux48" << endl;
    generate_2(gen_ranlux, distrib);
    cout << "knuth_b" << endl;
    generate_2(gen_knuth, distrib);
    cout << "random_device" << endl;

    int k;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            k = distrib(gen_rd);
            if (k == 0) cout << " "; else cout << '*';
        }
        cout << endl;
    }
    for (int j = 0; j < 101; j++) {
        cout << '-';
    }
    cout << endl << endl; 
}

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "Uniform distribution" << endl;
    int k;
    cout << "Scaled rand" << endl;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            k = scale_rand(0, 1);
            if (k == 0) cout << " "; else cout << '*';
        }
        cout << endl;
    }
    for(int j = 0; j < 101; j++) {
        cout << '-';
    }
    cout << endl << endl;

    cout << "Modulo rand" << endl;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            k = mod_rand(0, 1);
            if (k == 0) cout << " "; else cout << '*';
        }
        cout << endl;
    }
    for (int j = 0; j < 101; j++) {
        cout << '-';
    }
    cout << endl << endl;

    double norm_var = 1.0;
    uniform_int_distribution distrib_uni_2(0, 1);
    normal_distribution distrib_norm_2(0.0, norm_var);
    poisson_distribution distrib_pois_2(1);
    task_2(distrib_uni_2);
    cout << "Normal distribution: 0 " << norm_var  << endl;
    task_2(distrib_norm_2);
    cout << "Poisson distribution: 1" << endl;
    task_2(distrib_pois_2);
	return EXIT_SUCCESS;
}
