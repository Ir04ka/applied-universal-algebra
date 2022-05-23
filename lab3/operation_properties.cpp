#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;


bool associative(vector<vector<int>>& cayley_table) {
    for (int x = 0; x < size(cayley_table); ++x) {
        for (int y = 0; y < size(cayley_table); ++y) {
            for (int z = 0; z < size(cayley_table); ++z) {
                if (cayley_table[y][cayley_table[x][z] - 1]
                != cayley_table[cayley_table[y][x] - 1][z]) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool commutativity(vector<vector<int>>& cayley_table) {
    for (int i = 0; i < size(cayley_table); ++i) {
        for (int j = 0; j < size(cayley_table); ++j) {
            if (cayley_table[i][j] != cayley_table[j][i]) {
                return false;
            }
        }
    }
    return true;
}

bool idempotency(vector<vector<int>>& cayley_table) {
    for (int i = 0; i < size(cayley_table); ++i) {
        if (cayley_table[i][i] != i + 1) {
            return false;
        }
    }
    return true;
}

bool invertibility(vector<vector<int>>& cayley_table) {
    for (int i = 0; i < size(cayley_table); ++i) {
        for (int j = 0; j < size(cayley_table); ++j) {
            if (!(cayley_table[i][j] == cayley_table[j][i] && cayley_table[i][j] == 1)){
                return false;
            }
        }
    }
    return true;
}

bool distributivity(vector<vector<int>>& cayley_table) {

    cout << "Другая таблица Кэли:" << endl;
    vector<vector<int>> another_cayley_table(size(cayley_table), vector<int>(size(cayley_table)));
    for (int i = 0; i < size(another_cayley_table); ++i) {
        for (int j = 0; j < size(another_cayley_table); ++j) {
            cin >> another_cayley_table[i][j];
        }
    }

    for (int x = 0; x < size(another_cayley_table); ++x) {
        for (int y = 0; y < size(another_cayley_table); ++y) {
            for (int z = 0; z < size(another_cayley_table); ++z) {
                int p = another_cayley_table[y][z] - 1;
                int q = cayley_table[x][y] - 1;
                int m = cayley_table[x][z] - 1;
                int g = another_cayley_table[y][z] - 1;
                int h = cayley_table[y][x] - 1;
                int u = cayley_table[z][x] - 1;
                if (cayley_table[x][p] != another_cayley_table[q][m] ||
                    cayley_table[g][x] != another_cayley_table[h][u]) {
                    return false;
                }
            }
        }
    }
    return true;
}


int main() {

    SetConsoleOutputCP(CP_UTF8);

    cout << "Количество элементов" << endl;
    int n;
    cin >> n;

    cout << "Таблица Кэли:" << endl;
    vector<vector<int>> cayley_table(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> cayley_table[i][j];
        }
    }

    if (associative(cayley_table)) {
        cout << "Ассоциативность выполянется" << endl;
    } else {
        cout << "Ассоциативность не выполняется" << endl;
    }

    if (commutativity(cayley_table)) {
        cout << "Коммутативность выполянется" << endl;
    } else {
        cout << "Коммутативность не выполняется" << endl;
    }

    if (idempotency(cayley_table)) {
        cout << "Идемпотентность выполняется" << endl;
    } else {
        cout << "Идемпотентность не выполняется" << endl;
    }

    if (invertibility(cayley_table)) {
        cout << "Обратимость выполняется" << endl;
    } else {
        cout << "Обратимость не выполняется" << endl;
    }

    if (distributivity(cayley_table)) {
        cout << "Дистрибутивность выполняется" << endl;
    } else {
        cout << "Дистрибутивность не выполняется" << endl;
    }

    return 0;
}
