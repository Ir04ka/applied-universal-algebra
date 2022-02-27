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

    int w[n][n];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            w[i][j] = 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int l = 0; l < n; ++l) {
            int s = 0;
            for (int j = 0; j < n; ++j) {
                s += m[i][j] * m[j][l];
            }
            w[i][l] += s;
            if (w[i][l] > 1) {
                w[i][l] = 1;
            }
        }
    }

    bool q = true;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (w[i][j] > m[i][j]) {
                q = false;
            }
        }
    }
    
    if (!q) {
        cout << "бинарное отношение ρ не является транзитивным";
    } else {
        cout << "бинарное отношение ρ является транзитивным";
    }

    return 0;

}