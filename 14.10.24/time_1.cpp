#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    t += 3600 * 3;
    int h, m, s;
    while (true) {
        cout << '\r';
        s = t % 60;
        m = (t / 60) % 60;
        h = (t / 3600) % 24;
        (h < 10 ? cout << '0' << h << ':' : cout << h << ':');
        (m < 10 ? cout << '0' << m << ':' : cout << m << ':');
        (s < 10 ? cout << '0' << s : cout << s);
        t++;
        std::this_thread::sleep_for(995ms);
    }
    return EXIT_SUCCESS;
}
