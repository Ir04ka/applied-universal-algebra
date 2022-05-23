#include <iostream>
#include <iomanip>
#include <windows.h>
#include <vector>

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);

    cout << "Размерность матрицы (n m):" << endl;
    int n, m;
    cin >> n >> m;

    cout << "Матрица: " << endl;
    vector<vector<int>> matrix(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
        }
    }

    vector<vector<int>> matrix_transposed(m, vector<int> (n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j){
            matrix_transposed[i][j] = matrix[j][i];
        }
    }

    vector<pair<int, int>> result_additions;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!matrix[i][j]) {
                result_additions.push_back({i + 1, j + 1});
            }
        }
    }

    vector<pair<int, int>> result_reversal;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if(matrix_transposed[i][j]){
                result_reversal.push_back({i + 1, j + 1});
            }
        }
    }

    cout << "Результат дополнения бинарного отношения: " << endl;
    cout << "[ ";
    for (auto q : result_additions) {
        cout << "(" << q.first << ", " << q.second << ")" << ", ";
    }
    cout << "]" << endl;

    cout << "Результат обращения бинарного отношения: " << endl;
    cout << "[ ";
    for (auto q : result_reversal) {
        cout << "(" << q.first << ", " << q.second << ")" << ", ";
    }
    cout << "]" << endl;

    return 0;
}
