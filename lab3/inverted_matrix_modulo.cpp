#include <iostream>
#include <iomanip>
#include <windows.h>
#include <vector>
#include <cmath>

using namespace std;

int Get_minor(vector<vector<int>>& matrix,vector<vector<int>>& matrix_alg, int x, int y, int size) {
    int xCount = 0;
    int yCount = 0;

    for (int i = 0; i < size; ++i) {
        if (i != x) {
            yCount = 0;
            for (int j = 0; j < size; ++j) {
                if (j != y) {
                    matrix_alg[xCount][yCount] = matrix[i][j];
                    ++yCount;
                }
            } ++xCount;
        }
    }
    return 0;
}

int Find_determinant (vector<vector<int>>& matrix, int size) {
    if (size == 1) {
        return matrix[0][0];
    } else {

        int det = 0;
        vector<vector<int>> minor(size - 1, vector<int> (size - 1));
        for (int i = 0; i < size; ++i) {
            Get_minor(matrix, minor, 0, i, size);
            det += pow(-1, i) * matrix[0][i] * Find_determinant(minor, size - 1);
        }

        return det;
    }

}


void Find_alg_dop(vector<vector<int>>& matrix, int size, vector<vector<int>>& matrix_alg) {
    int det = Find_determinant(matrix, size);
    if (det > 0) {
        det = -1;
    } else {
        det = 1;
    }

    vector<vector<int>> minor(size - 1, vector<int> (size - 1));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Get_minor(matrix, minor, i, j, size);
            if ((i + j) % 2 == 0) {
                matrix_alg[i][j] = -det * Find_determinant(minor, size - 1);
            } else {
                matrix_alg[i][j] = det * Find_determinant(minor, size - 1);
            }
        }
    }
}

void gcdExtended (int a, int b, int& x, int& y)
{
    if (a == 0) { x = 0; y = 1; return; }

    int x_1, y_1;
    gcdExtended (b % a, a, x_1, y_1);

    x = y_1 - (b / a) * x_1;
    y = x_1;

    return;
}

int main() {

    SetConsoleOutputCP(CP_UTF8);

    cout << "Размерность матрицы для обращения (n): " << endl;
    int n;
    cin >> n;

    cout << "Матрица для обращения: " << endl;
    vector<vector<int>> matrix(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    int det = Find_determinant(matrix, n);
    int det_inverse = 0;
    int rrr = 0;

    if (det % order == 0) {
        cout << "Матрица является вырожденной" << endl;
        return 0;
    }

    vector<vector<int>> alg_dop(n, vector<int> (n));
    Find_alg_dop(matrix, n, alg_dop);

    vector<vector<int>> alg_dop_transposed(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            alg_dop_transposed[i][j] = alg_dop[j][i];
        }
    }

    cout << "Введите порядок поля:" << endl;
    int order;
    cin >> order;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            alg_dop_transposed[i][j] = alg_dop_transposed[i][j] % order;
        }
    }

    gcdExtended (abs(det), order, det_inverse, rrr);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            alg_dop_transposed[i][j] = alg_dop_transposed[i][j] * det_inverse;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (alg_dop_transposed[i][j] >= 0) {
                alg_dop_transposed[i][j] = alg_dop_transposed[i][j] % order;
            } else {
                alg_dop_transposed[i][j] = (alg_dop_transposed[i][j] % order) + order;
            }
        }
    }

    cout << "ОБращенная матрица по модулю " << order << " : " << endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << alg_dop_transposed[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}