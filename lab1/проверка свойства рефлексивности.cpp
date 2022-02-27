#include <iostream>
#include <windows.h>

using namespace std;

int main(){

    SetConsoleOutputCP(CP_UTF8);

    int n;
    cin >> n;
    int m[n][n];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> m[i][j];
        }
    }

    int q = 0;

    for (int i = 0; i < n; ++i) {
        if (m[i][i] == 1) {
            ++q;
        }
    }

    if (q == n) {
        cout << "бинарное отношение ρ является рефлексивным";
    } else {
        cout << "бинарное отношение ρ не является рефлексивным";
    }

    return 0;

}