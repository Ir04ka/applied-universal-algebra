#include <iostream>
#include <windows.h>
#include <vector>
#include <set>

using namespace std;

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

    for (int i = 0; i < n; ++i) {
        if (m[i][i] == 0) {
            a.push_back({i + 1, i + 1});
        }
    }

    int q = size(a);

    for (int i = 0; i < q; ++i) {
        a.push_back({a[i].second, a[i].first});
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

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (m[i][j] == 0 && w[i][j] == 1) {
                a.push_back({i + 1, j + 1});
            }
        }
    }

    set<pair<int, int>> rrr(begin(a), end(a));

    bool isFirst = true;
    for (auto [i, j] : rrr) {
        if (!isFirst) {
            cout << ", ";
        }
        cout << "(" << i << ", " << j << ")";
        isFirst = false;
    }

    return 0;
}
