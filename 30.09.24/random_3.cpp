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

void generate_3(auto gen, auto distrib) {
    int x, y;
    char sq[100][100];
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            sq[i][j] = ' ';
        }
    }
    for (int i = 0; i < 200; i++) {
        x = distrib(gen);
        y = distrib(gen);
        sq[x][y] = '*';
    }
    for (int i = 0; i < 100; i++) cout << '-';
    cout << endl;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            cout << sq[i][j];
        }
        cout << '|' << endl;
    }
    for (int i = 0; i < 100; i++) cout << '-';
    cout << endl << endl;
}

void task_3(auto distrib) {

    cout << "minstd_rand" << endl;
    generate_3(gen_minstd, distrib);
    cout << "mt19937" << endl;
    generate_3(gen_mt, distrib);
    cout << "ranlux48" << endl;
    generate_3(gen_ranlux, distrib);
    cout << "knuth_b" << endl;
    generate_3(gen_knuth, distrib);

    cout << "random_device" << endl;
    int x, y;
    char sq[100][100];
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            sq[i][j] = ' ';
        }
    }
    for (int i = 0; i < 200; i++) {
        x = distrib(gen_rd);
        y = distrib(gen_rd);
        sq[x][y] = '*';
    }
    for (int i = 0; i < 100; i++) cout << '-';
    cout << endl;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            cout << sq[i][j];
        }
        cout << '|' << endl;
    }
    for (int i = 0; i < 100; i++) cout << '-';
    cout << endl << endl;
    
}

int main()
{
    setlocale(LC_ALL, "Russian");
    
    int pois_m = 30;
    double norm_m = 60, norm_var = 7.0;
    uniform_int_distribution<int> distrib_uni_3(0, 99);
    poisson_distribution<int> distrib_pois_3(pois_m);
    normal_distribution<double> distrib_norm_3(norm_m, norm_var);

    cout << "Task 3" << endl;
    cout << "Uniform" << endl;

    cout << "Scaled rand" << endl;
    int x, y;
    char sq[100][100];
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            sq[i][j] = ' ';
        }
    }
    for (int i = 0; i < 200; i++) {
        x = scale_rand(0, 99);
        y = scale_rand(0, 99);
        sq[x][y] = '*';
    }
    for (int i = 0; i < 100; i++) cout << '-';
    cout << endl;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            cout << sq[i][j];
        }
        cout << '|' << endl;
    }
    for (int i = 0; i < 100; i++) cout << '-';
    cout << endl << endl;

    cout << "Modulo rand" << endl;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            sq[i][j] = ' ';
        }
    }
    for (int i = 0; i < 200; i++) {
        x = mod_rand(0, 99);
        y = mod_rand(0, 99);
        sq[x][y] = '*';
    }
    for (int i = 0; i < 100; i++) cout << '-';
    cout << endl;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            cout << sq[i][j];
        }
        cout << '|' << endl;
    }
    for (int i = 0; i < 100; i++) cout << '-';
    cout << endl << endl;

    task_3(distrib_uni_3);
    cout << endl << "Normal - " << norm_m << " " << norm_var << endl;
    task_3(distrib_norm_3);
    cout << endl << "Poisson - " << pois_m << endl;
    task_3(distrib_pois_3);
    
	return EXIT_SUCCESS;
}
