#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

bool transitivity(vector<vector<int>>& m) {

    vector<vector<int>> w(size(m), vector<int> (size(m)));

    for (int i = 0; i < size(m); ++i) {
        for (int j = 0; j < size(m); ++j) {
            w[i][j] = 0;
        }
    }

    for (int i = 0; i < size(m); ++i) {
        for (int l = 0; l < size(m); ++l) {
            int s = 0;
            for (int j = 0; j < size(m); ++j) {
                s += m[i][j] * m[j][l];
            }
            w[i][l] += s;
            if (w[i][l] > 1) {
                w[i][l] = 1;
            }
        }
    }

    bool q = true;

    for (int i = 0; i < size(m); ++i) {
        for (int j = 0; j < size(m); ++j) {
            if (w[i][j] > m[i][j]) {
                q = false;
            }
        }
    }

    return q;

}

int main(){

    SetConsoleOutputCP(CP_UTF8);

    int n;
    cin >> n;
    vector<vector<int>> m(n, vector<int> (n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> m[i][j];
        }
    }

    vector<pair<int, int>> a;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (m[i][j] == 1) {
                a.push_back({i + 1, j + 1});
            }
        }
    }

    vector<vector<int>> w(n, vector<int> (n));

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

    vector<vector<int>> copy_m(size(m), vector<int> (size(m)));

    for (int i = 0; i < size(m); ++i) {
        for (int j = 0; j < size(m); ++j) {
            copy_m[i][j] = m[i][j];
        }

    }

    while (!transitivity(copy_m)) {
        for (int i = 0; i < size(m); ++i) {
            for (int j = 0; j < size(m); ++j) {
                if (copy_m[i][j] == 0 && w[i][j] == 1) {
                    a.push_back({i + 1, j + 1});
                    copy_m[i][j] = 1;
                }
            }
        }
        if (!transitivity(copy_m)) {
            for (int i = 0; i < size(m); ++i) {
                for (int l = 0; l < size(m); ++l) {
                    int s = 0;
                    for (int j = 0; j < size(m); ++j) {
                        s += copy_m[i][j] * m[j][l];
                    }
                    w[i][l] += s;
                    if (w[i][l] > 1) {
                        w[i][l] = 1;
                    }
                }
            }
        }
    }

    for (int i = 0; i < size(a); ++i) {
        if (i > 0) {
            cout << ", ";
        }
        cout << "(" << a[i].first << ", " << a[i].second << ")";
    }

    return 0;
}
