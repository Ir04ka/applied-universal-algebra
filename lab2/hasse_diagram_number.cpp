#include <iostream>
#include <windows.h>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void dfs(int x, int cur_level, map<int, bool>& used, map<int, int>& levels, map<int, set<int>>& connect) {
    used[x] = true;
    levels[x] = cur_level;

    for (int d = 1; d <= x; ++d) {

        if (x % d == 0) {
            if (!used[x / d]) {
                connect[x].insert(x / d);
                dfs(x / d, cur_level + 1, used, levels, connect);
            } else if (levels[x / d] == cur_level + 1) {
                connect[x].insert(x / d);
            }
        }
    }
}

int main() {

    SetConsoleOutputCP(CP_UTF8);

    cout << "Введите число x:" << endl;
    int x;
    cin >> x;

    map<int, bool> used;
    map<int, int> levels;
    map<int, set<int>> connect;

    dfs(x, 0, used, levels, connect);

    vector<pair<int, int>> res(begin(levels), end(levels));

    sort(begin(res), end(res), [](const pair<int, int>& lhs, const pair<int, int>& rhs) {
        return lhs.second < rhs.second
               || lhs.second == rhs.second && lhs.first < rhs.first;
    });

    cout << "Диаграмма Хассе:" << endl;
    for (auto [k, v] : res) {
        cout << "Число: " << k << ' ' << "Уровень: " << v << ' ';
        cout << "Связано с: ";
        for (auto to : connect[k]) {
            cout << to << ' ';
        }
        cout << endl;
    }

}