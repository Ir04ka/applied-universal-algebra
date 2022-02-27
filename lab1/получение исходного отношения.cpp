#include <iostream>
#include <windows.h>
#include <vector>

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

    for (int i = 0; i < size(a); ++i) {
        if (i > 0) {
            cout << ", ";
        }
        cout << "(" << a[i].first << ", " << a[i].second << ")";
    }

    return 0;
}
