#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    using clock = std::chrono::system_clock;
    time_t start = clock::to_time_t(clock::now());
    start += 3600 * 3;
    int h, m, s;
    while (true) {
        s = start % 60;
        m = (start / 60) % 60;
        h = (start / 3600) % 24;
        (h < 10 ? cout << '0' << h << ':' : cout << h << ':');
        (m < 10 ? cout << '0' << m << ':' : cout << m << ':');
        (s < 10 ? cout << '0' << s : cout << s);
        cout << endl;
        start++;
        std::this_thread::sleep_for(990ms);
    }
    return EXIT_SUCCESS;
}
