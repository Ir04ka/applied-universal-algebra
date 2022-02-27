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

    bool q = true;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && m[i][j] == m[j][i] && m[i][j] == 1) {
                q = false;
            }
        }
    }

    if (q) {
        cout << "бинарное отношение ρ является антисимметричным";
    } else {
        cout << "бинарное отношение ρ не является антисимметричным";
    }

    return 0;

}