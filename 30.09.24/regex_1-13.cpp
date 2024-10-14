#include <iostream>
#include <cstdlib>
#include <string>
#include <regex>
using namespace std;

bool ex_match(string s, int n) {
    regex patterns[13];
    patterns[0] = regex(".*000.*");
    patterns[1] = regex(".*101.*");
    patterns[2] = regex("(101.*)|(.*101)");
    patterns[3] = regex("[0-9]*1[0-9]*");
    patterns[4] = regex("[02-9]*");
    patterns[5] = regex("(\\d)[0-9]*\\1[0-9]*");
    patterns[6] = regex("(\\d)(?!.*\\1)[0-9]*");
    patterns[7] = regex("(-?[1-9][0-9]*)|0");
    patterns[8] = regex("(-?0[1-7][0-7]*)|(0)");
    patterns[9] = regex("(-?0x[1-9A-F][0-9A-F]*)|(0x0)");
    patterns[10] = regex("(-?(([1-9][0-9]*)|(0[1-7][0-7]*)|(0x[1-9A-F][0-9A-F]*)))|0|0x0");
    patterns[11] = regex("-?(0|([1-9][0-9]*))(\\.[0-9]+)?(e-?[0-9]+)?");
    patterns[12] = regex(".*0(....)*0.*");
    return regex_match(s, patterns[n]);
}

bool ex_search(string s, int n) {
    regex patterns[13];
    patterns[0] = regex("000");
    patterns[1] = regex("101");
    patterns[2] = regex("^(101)|(101)$");
    patterns[3] = regex("^[0-9]*1[0-9]*$");
    patterns[4] = regex("^[02-9]*$");
    patterns[5] = regex("^(\\d)[0-9]*\\1[0-9]*$");
    patterns[6] = regex("^(\\d)(?!.*\\1)[0-9]*$");
    patterns[7] = regex("^(-?[1-9][0-9]*)|0$");
    patterns[8] = regex("^(-?0[1-7][0-7]*)|(0)$");
    patterns[9] = regex("^(-?0x[1-9A-F][0-9A-F]*)|(0x0)$");
    patterns[10] = regex("^(-?(([1-9][0-9]*)|(0[1-7][0-7]*)|(0x[1-9A-F][0-9A-F]*)))|0|0x0$");
    patterns[11] = regex("^-?(0|([1-9][0-9]*))(\\.[0-9]+)?(e-?[0-9]+)?$");
    patterns[12] = regex("0(....)*0");
    return regex_search(s, patterns[n]);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    string s;
    int n;
    cin >> s >> n;
    while (n > 0 && n < 14) {
        cout << boolalpha << ex_match(s, n - 1) << endl;
        cin >> s >> n;
    }
    return EXIT_SUCCESS;
}
