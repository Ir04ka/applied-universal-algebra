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

    cout << "Введите порядок поля:" << endl;
    int order;
    cin >> order;

    vector<vector<int>> matrix_C(n, vector<int> (m));

    if (n != r || m != t) {
        cout << "Сложение матриц невозможно" << endl;
    } else {
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < m; ++j) {
                matrix_C[i][j] = matrix_A[i][j] + matrix_B[i][j];
            }
        }

        cout << "Результат сложения матриц А и B:" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << setw(4) << matrix_C[i][j] % order << ' ';
            }
            cout << endl;
        }

    }

    vector<vector<int>> matrix_D(n, vector<int> (t));

    if (m == r) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < t; ++j) {
                matrix_D[i][j] = 0;
                for (int q = 0; q < r; ++q) {
                    matrix_D[i][j] += matrix_A[i][q] * matrix_B[q][j];
                }
            }
        }
        cout << "Результат умножения матриц A и В: " << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < t; ++j) {
                cout << setw(4) << matrix_D[i][j] % order << ' ';
            }
            cout << endl;
        }
    } else {
        cout << "Умножение матриц невозможно" << endl;
    }

    return 0;
}

