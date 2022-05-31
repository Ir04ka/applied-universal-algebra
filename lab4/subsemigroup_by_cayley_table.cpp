#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

bool check_associativity(const vector<pair<int, int>>& result, const vector<pair<int, int>>& prov) {

    if (size(result) != size(prov)) {
        return true;
    }

    int count_elements = 0;
    for (auto& [first, junk1] : result) {
        for (auto& [second, junk2] : prov) {
            if (first == second) {
                ++count_elements;
            }
        }
    }

    return size(result) != count_elements;
}

auto unite(const vector<pair<int, int>>& result, const vector<pair<int, int>>& resSt) {
    vector<pair<int, int>> temp_res(result);

    for (int i = 0; i < size(resSt); ++i) {
        int count_elements = count_if(begin(temp_res), end(temp_res), [&resSt, i](auto element) {
            return resSt[i].first == element.first && resSt[i].second == element.second;
        });

        if (count_elements == 0) {
            temp_res.push_back(resSt[i]);
        }
    }

    return temp_res;
}

vector<pair<int, int>> subpool_group(vector<vector<int>>& cayley_table, vector<pair<int, int>>& subset, vector<int>& half_group) {
    vector<pair<int, int>> res = subset;
    vector<pair<int, int>> check;

    while (true) {
        vector<pair<int, int>> temp;
        for (int i = 0; i < size(subset); ++i) {
            for (int j = 0; j < size(res); ++j) {
                int element = cayley_table[subset[i].second][res[j].second];

                temp.push_back({element, find(begin(half_group), end(half_group), element) - begin(half_group)});
            }
        }

        check = res;
        res = unite(res, temp);

        if (!check_associativity(res, check)) {
            break;
        }
    }

    return res;
}

int main() {

    SetConsoleOutputCP(CP_UTF8);

    int n;
    cout << "Количество элементов в полугруппе:" << endl;
    cin >> n;

    vector<int> half_group(n);
    int element;
    cout << "элементы полугруппы:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> element;
        half_group[i] = element;
    }

    vector<vector<int>> cayley_table(n, vector<int>(n));
    cout << "Таблица Кэли:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> cayley_table[i][j];
        }
    }

    cout << "Kоличество элементов в подмножестве: " << endl;
    int m;
    cin >> m;

    vector<pair<int, int>> subset;
    cout << "Элементы подмножества: " << endl;
    for (int i = 0; i < m; ++i) {
        int element;
        cin >> element;
        subset.push_back({element, find(begin(half_group), end(half_group), element) - begin(half_group)});
    }

    vector<pair<int, int>> result;
    result = subpool_group(cayley_table, subset, half_group);
    sort(begin(result), end(result));

    cout << "Подполугруппа: ";
    bool is_first = true;
    cout << "{";
    for (auto [first, junk] : result) {
        cout << (is_first ? "" : ", ") << first;
        is_first = false;
    }
    cout << "}" << endl;

    return 0;
}
