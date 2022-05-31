#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <iomanip>
#include <windows.h>

using namespace std;

vector<vector<int>> multy_matrix(const vector<vector<int>>& sets, const vector<vector<int>>& result, int n) {
    vector <vector <int>> temp_result(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (sets[i][k] == 1 && result[k][j] == 1) {
                    temp_result[i][j] = 1;
                    break;
                }
                else temp_result[i][j] = 0;
            }
        }
    }
    return temp_result;
}

set<vector<vector<int>>> insert_matrix(set<vector<vector<int>>> sets, int n) {
    for (auto& sets1 : sets)
        for (auto& sets2 : sets) {
            sets.insert(multy_matrix(sets1, sets2, n));
        }
    return sets;
}

int main() {

    SetConsoleOutputCP(CP_UTF8);

    int m;
    cout << "Количество матриц в порождающем множестве: " << endl;
    cin >> m;

    int n;
    cout << "Размер матриц: " << endl;
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n));
    map<char, vector<vector<int>>> in_matrix;
    map<vector<vector<int>>, char> out_matrix;

    set<vector<vector<int>>> sets;
    int q = 0;
    for (int i = 1; i <= m; i++) {
        cout << "Матрица " << char(65 + q) << ":" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; j++)
                cin >> matrix[i][j];
        }
        sets.insert(matrix);
        in_matrix.insert({char(65 + q), matrix});
        out_matrix.insert({matrix, char(65 + q++)});
    }

    set<vector<vector<int>>> group;
    group = sets;
    int count = 0;
    while (true) {
        for (auto& i: sets) {
            for (auto& j : sets) {
                vector<vector<int>> new_matrix = multy_matrix(i, j, n);

                if (!group.count(new_matrix)) {
                     in_matrix.insert({char(65 + q + count), new_matrix});
                     out_matrix.insert({new_matrix, char(65 + q + count++)});
                    group.insert(new_matrix);
                }
            }
        }

        if (group == sets) {

            group = sets;
            sets = insert_matrix(sets, n);

            cout << endl << "Итоговая полугруппа:" << endl;
            for (const vector<vector<int>>& temp_result : sets) {
                cout << out_matrix[temp_result];
                for (int i = 0; i < size(temp_result); ++i) {
                    cout << endl;
                    for (int j = 0; j < size(temp_result); ++j)
                        cout << temp_result[i][j] << ' ';
                }
                cout << endl;
            }

            cout << endl << "Таблица Кэли: " << endl << ' ';
            for (int i = 0; i < size(out_matrix); ++i){
                cout << setw(4) << char(65 + i);
            }

            cout << endl;

            for (int i = 0; i < size(out_matrix); ++i) {
                cout << char(65 + i) << setw(4);
                for (int j = 0; j < size(out_matrix); ++j){
                    cout << setw(4) << out_matrix[multy_matrix(in_matrix[char(65 + i)], in_matrix[char(65 + j)], n)];
                }
                cout << endl;
            }
            return 0;

        } else {
            sets = group;
        }
    }

    return 0;
}
