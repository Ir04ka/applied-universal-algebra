#include <iostream>
#include <windows.h>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

/*
8
1 1 1 1 1 1 1 1
0 1 0 0 1 1 0 1
0 0 1 0 1 0 1 1
0 0 0 1 0 1 1 1
0 0 0 0 1 0 0 1
0 0 0 0 0 1 0 1
0 0 0 0 0 0 1 1
0 0 0 0 0 0 0 1

9
1 0 1 0 1 1 1 1 1
0 1 1 0 0 1 1 0 1
0 0 1 0 0 1 1 0 1
0 0 0 1 1 0 1 1 1
0 0 0 0 1 0 1 1 1
0 0 0 0 0 1 1 0 1
0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 1 1 1
0 0 0 0 0 0 0 0 1
*/

vector<int> get_min_matrix(const vector<vector<int>>& matrix, const set<int>& elements) {
    vector<int> minimal;

    for (int i = 0; i < size(matrix); ++i) {
        bool flag = true;

        for (int j = 0; j < size(matrix); ++j)
            if (matrix[j][i] && i != j) {
                flag = false;
                break;
            }

        if (flag && elements.count(i)) {
            minimal.push_back(i);
        }
    }

    return minimal;
}

void remove_min_elements(set<int>& elements, const vector<int>& minimal) {
   for (auto elem : minimal) {
       elements.erase(elem);
   }
}

void clean_rows(vector<vector<int>>& matrix, const vector<int>& minimal)
{
    for (int min : minimal)
        matrix[min].assign(size(matrix), 0);
}

void get_hasse_connections_matrix(const vector<vector<int>>& matrix,
                                  const vector<int>& p_level,
                                  const vector<int>& n_level,
                                  vector<vector<pair<int, int>>>& levels_connections) {

    vector<pair<int, int>> level_connections;

    for (int p_level_element : p_level) {
        for (int n_level_element: n_level) {
            if (matrix[p_level_element][n_level_element] == 1) {
                level_connections.push_back({p_level_element + 1, n_level_element + 1});
            }
        }
    }
    levels_connections.push_back(level_connections);
}

void levels_and_connections (vector<vector<int>> hasse_levels, vector<vector<pair<int, int>>> hasse_level_connections) {

    cout << "Диаграмма Хассе по уровням:" << endl;

    for (int i = size(hasse_levels) - 1; i >= 0; --i) {
        for (int j = 0; j < hasse_levels[i].size (); ++j) {
            cout << hasse_levels[i][j] + 1 << " ";
        }
        cout << endl;
    }

    cout << "Связи в диаграмме Хассе:" << endl;

    for (int i = hasse_level_connections.size () - 1; i >= 0; --i) {
        for (int j = 0; j < size(hasse_level_connections[i]); ++j) {
            auto level_element = hasse_level_connections[i][j];

            cout << "( " << level_element.first << " связан с " << level_element.second << ")" << (j == size(hasse_level_connections[i]) - 1 ? "." : ", ");
        }
        cout << endl;
    }
}

int main() {

    SetConsoleOutputCP(CP_UTF8);

    cout << "Введите n:" << endl;
    int n;
    cin >> n;

    cout << "Введите матрицу n*n:" << endl;
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    vector<vector<int>> original_matrix = matrix;

    set<int> elements;
    for (int i = 0; i < size(matrix); ++i) {
        elements.insert(i);
    }

    vector<vector<int>> hasse_levels;

    while (!empty(elements)) {
        vector<int> minimal = get_min_matrix(matrix, elements);
        hasse_levels.push_back(minimal);
        remove_min_elements(elements, minimal);
        clean_rows(matrix, minimal);
    }

    vector<vector<pair<int, int>>> hasse_level_connections;
    for (int i = 0; i < size(hasse_levels) - 1; ++i) {
        get_hasse_connections_matrix(original_matrix, hasse_levels[i], hasse_levels[i + 1], hasse_level_connections);
    }

    levels_and_connections(hasse_levels, hasse_level_connections);

    return 0;
}
