#include <iostream>
#include <windows.h>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>

using namespace std;

/*
 4
 1 0 1 0
 1 1 0 0
 0 1 0 1
 0 1 0 1

 */

set<int> inter_set(const set<int>& a, const set<int>& b) {
    vector<int> res;
    set_intersection(begin(a), end(a), begin(b), end(b), back_inserter(res));

    return {begin(res), end(res)};
}

int main() {

    SetConsoleOutputCP(CP_UTF8);

    cout << "Введите количество объектов и количество атрибутов:" << endl;
    int n;
    cin >> n;

    cout << "Введите матрицу:" << endl;
    vector<vector<int>> matrix(n, vector<int>(n));
    vector<set<int>> a(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
            if (matrix[i][j]) {
                a[j].insert(i);
            }
        }
    }

    set<set<int>> inter(begin(a), end(a));

    vector<int> full(n);
    iota(begin(full), end(full), 0);

    inter.insert(set<int>(begin(full), end(full)));
    inter.insert(set<int>());

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            inter.insert(inter_set(a[i], a[j]));
        }
    }

    vector<pair<vector<int>, vector<char>>> ans;

    for (const auto& s : inter) {
        ans.push_back({});
        for (int i = 0; i < n; ++i) {
            if (size(inter_set(s, a[i])) == size(s)) {
                ans.back().second.push_back('a' + i);
            }
        }
        ans.back().first = vector<int>(begin(s), end(s));
    }

    sort(begin(ans), end(ans), [](const auto& lhs, const auto& rhs) {return size(lhs.second) > size(rhs.second);});


    int level = 0;
    int i = 0;

    cout << "Итоговый результат:" << endl;
    for (const auto& [s, names] : ans) {
        cout << "[ ";
        for (auto e : s) {
            cout << e + 1 << ' ';
        }
        cout << "] ";

        cout << "[ ";
        for (auto name : names) {
            cout << name << ' ';
        }
        cout << "] ";

        if (i == 0 || size(ans[i].second) != size(ans[i - 1].second)) {
            ++level;
        }

        cout << "Уровень: " << level << endl;

        ++i;
    }



    return 0;
}
