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
        if (m[i][i] == 0) {
            ++q;
        }
    }

    if (q != n) {
        cout << "отношение не является отношением доминирования";
        return 0;
    } else {

        bool r = true;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && m[i][j] == m[j][i] && m[i][j] == 1) {
                    r = false;
                }
            }
        }

        if (r) {
            cout << "отношение является отношением доминирования";
        } else {
            cout << "отношение не является отношением доминирования";
        }

        return 0;

    }
}
