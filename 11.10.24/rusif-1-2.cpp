#include <iostream>
#include <cstdlib>
#include <string>
#include <fcntl.h>
#include <io.h>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    //1
    double m;
    wchar_t a, b;
    wcin >> m >> a >> b;
    switch (a) {
    case L'к':
        m *= 1e3;
        break;
    case L'ц':
        m *= 1e5;
        break;
    case L'т':
        m *= 1e6;
        break;
    }
    switch (b) {
    case L'к':
        m /= 1e3;
        break;
    case L'ц':
        m /= 1e5;
        break;
    case L'т':
        m /= 1e6;
        break;
    }
    wcout << m << endl;

    //2
    wstring day;
    wcin >> day;
    wstring names[7][2] = { {L"Понедельник", L"Monday"},
                            {L"Вторник", L"Tuesday"},
                            {L"Среда", L"Wednesday"},
                            {L"Четверг", L"Thursday"},
                            {L"Пятница", L"Friday"},
                            {L"Суббота", L"Saturday"},
                            {L"Воскресенье", L"Sunday"}};
    for (int i = 0; i < 7; i++) {
        if (day == names[i][0]) wcout << names[i][1] << endl;
        else if (day == names[i][1]) wcout << names[i][0] << endl;
    }

	return EXIT_SUCCESS;
}
