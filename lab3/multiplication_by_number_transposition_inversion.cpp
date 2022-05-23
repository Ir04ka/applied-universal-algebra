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

    cout << "Число, на которое умножается матрица: " << endl;
    int x;
    cin >> x;

    cout << "Введите порядок поля:" << endl;
    int order;
    cin >> order;

    cout << endl << "Результат умножения матрицы на число:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << setw(4) << matrix[i][j] * x % order<< ' ';
        }
        cout << endl;
    }

    vector<vector<int>> matrix_transposed(m, vector<int> (n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j){
            matrix_transposed[i][j] = matrix[j][i];
        }
    }

    cout << endl << "Транспонированная матрица:" << endl;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(4) << matrix_transposed[i][j] % order << ' ';
        }
        cout << endl;
    }


    return 0;
}
