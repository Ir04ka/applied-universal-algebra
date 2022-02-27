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

    int q = size(a);

    for (int i = 0; i < q; ++i) {
        a.push_back({a[i].second, a[i].first});
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
