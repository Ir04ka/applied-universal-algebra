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
        cout << "отношение не является отношением строгого порядка";
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

        if (!r) {
            cout << "отношение не является отношением строгого порядка";
            return 0;
        } else {
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

            r = true;

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (w[i][j] > m[i][j]) {
                        r = false;
                    }
                }
            }

            if (!r) {
                cout << "отношение не является отношением строгого порядка";
            } else {
                cout << "отношение является отношением строгого порядка";
            }
        }
    }

    return 0;
}