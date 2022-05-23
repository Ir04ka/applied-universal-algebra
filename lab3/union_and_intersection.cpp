#include <iostream>
#include <iomanip>
#include <windows.h>
#include <vector>

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);

    cout << "Размерность матриц А и B (n m)" << endl;
    int n, m;
    cin >> n >> m;

    cout << "Матрица А:" << endl;
    vector<vector<int>> matrix_A(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix_A[i][j];
        }
    }

    cout << "Матрица B:" << endl;
    vector<vector<int>> matrix_B(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix_B[i][j];
        }
    }

    vector<pair<int, int>> result_union;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix_A[i][j] || matrix_B[i][j]) {
                result_union.push_back({i + 1, j + 1});
            }
        }
    }

    vector<pair<int, int>> result_intersection;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix_A[i][j] && matrix_B[i][j]) {
                result_intersection.push_back({i + 1, j + 1});
            }
        }
    }

    cout << "Результат объединения бинарных отношений: " << endl;
    cout << "[ ";
    for (auto q : result_union) {
        cout << "(" << q.first << ", " << q.second << ")" << ", ";
    }
    cout << "]" << endl;

    cout << "Результат пересечения бинарных отношений: " << endl;
    cout << "[ ";
    for (auto q : result_intersection) {
        cout << "(" << q.first << ", " << q.second << ")" << ", ";
    }
    cout << "]" << endl;

    return 0;
}
