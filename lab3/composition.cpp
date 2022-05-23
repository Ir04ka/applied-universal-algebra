#include <iostream>
#include <iomanip>
#include <windows.h>
#include <vector>

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);

    cout << "Размерность матрицы А (n m)" << endl;
    int n, m;
    cin >> n >> m;

    cout << "Матрица А:" << endl;
    vector<vector<int>> matrix_A(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix_A[i][j];
        }
    }

    cout << "Размерность матрицы B (r t)" << endl;
    int r, t;
    cin >> r >> t;

    cout << "Матрица B:" << endl;
    vector<vector<int>> matrix_B(r, vector<int> (t));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < t; ++j) {
            cin >> matrix_B[i][j];
        }
    }

    vector<vector<int>> matrix_C(n, vector<int> (t));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < t; ++j) {
            matrix_C[i][j] = 0;
            for (int w = 0; w < m; ++w) {
                matrix_C[i][j] += matrix_A[i][w] * matrix_B[w][j];
            }
            if (matrix_C[i][j] > 1) {
                matrix_C[i][j] = 1;
            }
        }
    }

    vector<pair<int, int>> result_composition;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < t; ++j) {
            if (matrix_C[i][j]) {
                result_composition.push_back({i + 1, j + 1});
            }
        }
    }

    

    cout << "Результат композиции бинарных отношений: " << endl;
    if (m == r) {
        cout << "[ ";
        for (auto q : result_composition) {
            cout << "(" << q.first << ", " << q.second << ")" << ", ";
        }
        cout << "]" << endl;
    } else {
        cout << "Произведение матриц невозможно" << endl;
    }

    return 0;
}
