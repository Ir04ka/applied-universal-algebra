#include <iostream>
#include <windows.h>
#include <vector>
#include <set>

using namespace std;

bool reflexivity(vector<vector<int>>& m) {

    int q = 0;

    for (int i = 0; i < size(m); ++i) {
        if (m[i][i] == 1) {
            ++q;
        }
    }

    return q == size(m);
}

bool antireflexivity(vector<vector<int>>& m) {

    int q = 0;

    for (int i = 0; i < size(m); ++i) {
        if (m[i][i] == 0) {
            ++q;
        }
    }

    return q == size(m);
}

bool symmetry(vector<vector<int>>& m) {

    bool q = true;

    for (int i = 0; i < size(m); ++i) {
        for (int j = 0; j < size(m); ++j) {
            if (i != j && m[i][j] != m[j][i]) {
                q = false;
            }
        }
    }

    return q;
}

bool antisymmetry(vector<vector<int>>& m) {

    bool q = true;

    for (int i = 0; i < size(m); ++i) {
        for (int j = 0; j < size(m); ++j) {
            if (i != j && m[i][j] == m[j][i] && m[i][j] == 1) {
                q = false;
            }
        }
    }

    return q;
}

bool transitivity(vector<vector<int>>& m) {

    vector<vector<int>> w(size(m), vector<int> (size(m)));

    for (int i = 0; i < size(m); ++i) {
        for (int j = 0; j < size(m); ++j) {
            w[i][j] = 0;
        }
    }

    for (int i = 0; i < size(m); ++i) {
        for (int l = 0; l < size(m); ++l) {
            int s = 0;
            for (int j = 0; j < size(m); ++j) {
                s += m[i][j] * m[j][l];
            }
            w[i][l] += s;
            if (w[i][l] > 1) {
                w[i][l] = 1;
            }
        }
    }

    bool q = true;

    for (int i = 0; i < size(m); ++i) {
        for (int j = 0; j < size(m); ++j) {
            if (w[i][j] > m[i][j]) {
                q = false;
            }
        }
    }

    return q;

}

void original_closure(vector<vector<int>>& m) {

    vector<pair<int, int>> a;

    for (int i = 0; i < size(m); ++i) {
        for (int j = 0; j < size(m); ++j) {
            if (m[i][j] == 1) {
                a.push_back({i + 1, j + 1});
            }
        }
    }

    for (int i = 0; i < size(a); ++i) {
        if (i > 0) {
            cout << ", ";
        }
        cout << "(" << a[i].first << ", " << a[i].second << ")";
    }
}

void reflexive_closure(vector<vector<int>>& m) {

    vector<pair<int, int>> a;

    for (int i = 0; i < size(m); ++i) {
        for (int j = 0; j < size(m); ++j) {
            if (m[i][j] == 1) {
                a.push_back({i + 1, j + 1});
            }
        }
    }

    for (int i = 0; i < size(m); ++i) {
        if (m[i][i] == 0) {
            a.push_back({i + 1, i + 1});
        }
    }

    for (int i = 0; i < size(a); ++i) {
        if (i > 0) {
            cout << ", ";
        }
        cout << "(" << a[i].first << ", " << a[i].second << ")";
    }
}

void symmetric_closure(vector<vector<int>>& m) {

    vector<pair<int, int>> a;

    for (int i = 0; i < size(m); ++i) {
        for (int j = 0; j < size(m); ++j) {
            if (m[i][j] == 1) {
                a.push_back({i + 1, j + 1});
            }
        }
    }

    int q = size(a);

    for (int i = 0; i < q; ++i) {
        a.push_back({a[i].second, a[i].first});
    }

    set<pair<int, int>> rrr(begin(a), end(a));

    bool isFirst = true;
    for (auto [i, j] : rrr) {
        if (!isFirst) {
            cout << ", ";
        }
        cout << "(" << i << ", " << j << ")";
        isFirst = false;
    }
}


void transitive_closure(vector<vector<int>>& m) {

    vector<pair<int, int>> a;

    for (int i = 0; i < size(m); ++i) {
        for (int j = 0; j < size(m); ++j) {
            if (m[i][j] == 1) {
                a.push_back({i + 1, j + 1});
            }
        }
    }

    vector<vector<int>> w(size(m), vector<int> (size(m)));

    for (int i = 0; i < size(m); ++i) {
        for (int j = 0; j < size(m); ++j) {
            w[i][j] = 0;
        }
    }

    for (int i = 0; i < size(m); ++i) {
        for (int l = 0; l < size(m); ++l) {
            int s = 0;
            for (int j = 0; j < size(m); ++j) {
                s += m[i][j] * m[j][l];
            }
            w[i][l] += s;
            if (w[i][l] > 1) {
                w[i][l] = 1;
            }
        }
    }

    vector<vector<int>> copy_m(size(m), vector<int> (size(m)));

    for (int i = 0; i < size(m); ++i) {
        for (int j = 0; j < size(m); ++j) {
            copy_m[i][j] = m[i][j];
        }

    }

    while (!transitivity(m)) {
        for (int i = 0; i < size(m); ++i) {
            for (int j = 0; j < size(m); ++j) {
                if (m[i][j] == 0 && w[i][j] == 1) {
                    a.push_back({i + 1, j + 1});
                    m[i][j] = 1;
                }
            }
        }
        if (!transitivity(m)) {
            for (int i = 0; i < size(m); ++i) {
                for (int l = 0; l < size(m); ++l) {
                    int s = 0;
                    for (int j = 0; j < size(m); ++j) {
                        s += m[i][j] * copy_m[j][l];
                    }
                    w[i][l] += s;
                    if (w[i][l] > 1) {
                        w[i][l] = 1;
                    }
                }
            }
        }
    }

    for (int i = 0; i < size(a); ++i) {
        if (i > 0) {
            cout << ", ";
        }
        cout << "(" << a[i].first << ", " << a[i].second << ")";
    }
}

void equivalent_closure(vector<vector<int>>& m) {

    vector<pair<int, int>> a;

    for (int i = 0; i < size(m); ++i) {
        for (int j = 0; j < size(m); ++j) {
            if (m[i][j] == 1) {
                a.push_back({i + 1, j + 1});
            }
        }
    }

    int q = size(a);

    for (int i = 0; i < q; ++i) {
        a.push_back({a[i].second, a[i].first});
    }

    vector<vector<int>> w(size(m), vector<int> (size(m)));

    for (int i = 0; i < size(m); ++i) {
        for (int j = 0; j < size(m); ++j) {
            w[i][j] = 0;
        }
    }

    for (int i = 0; i < size(m); ++i) {
        for (int l = 0; l < size(m); ++l) {
            int s = 0;
            for (int j = 0; j < size(m); ++j) {
                s += m[i][j] * m[j][l];
            }
            w[i][l] += s;
            if (w[i][l] > 1) {
                w[i][l] = 1;
            }
        }
    }

    for (int i = 0; i < size(m); ++i) {
        for (int j = 0; j < size(m); ++j) {
            if (m[i][j] == 0 && w[i][j] == 1) {
                a.push_back({i + 1, j + 1});
            }
        }
    }

    set<pair<int, int>> rrr(begin(a), end(a));

    bool isFirst = true;
    for (auto [i, j] : rrr) {
        if (!isFirst) {
            cout << ", ";
        }
        cout << "(" << i << ", " << j << ")";
        isFirst = false;
    }

}


int main() {

    SetConsoleOutputCP(CP_UTF8);

    int n;
    cin >> n;
    vector<vector<int>> m(n, vector<int> (n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> m[i][j];
        }
    }

    if (reflexivity(m)) {
        cout << "бинарное отношение ρ является рефлексивным" << endl;
    } else {
        cout << "бинарное отношение ρ не является рефлексивным" << endl;
    }

    if (antireflexivity(m)) {
        cout << "бинарное отношение ρ является антирефлексивным" << endl;
    } else {
        cout << "бинарное отношение ρ не является антирефлексивным" << endl;
    }

    if (symmetry(m)) {
        cout << "бинарное отношение ρ является симметричным" << endl;
    } else {
        cout << "бинарное отношение ρ не является симметричным" << endl;
    }

    if (antisymmetry(m)) {
        cout << "бинарное отношение ρ является антисимметричным" << endl;
    } else {
        cout << "бинарное отношение ρ не является антисимметричным" << endl;
    }

    if (transitivity(m)) {
        cout << "бинарное отношение ρ является транзитивным" << endl;
    } else {
        cout << "бинарное отношение ρ не является транзитивным" << endl;
    }

    cout << endl;

    if (reflexivity(m) && transitivity(m)) {
        cout << "отношение является отношением квазипорядка" << endl;
    } else {
        cout << "отношение не является отношением квазипорядка" << endl;
    }

    if (reflexivity(m) && symmetry(m) && transitivity(m)) {
        cout << "отношение является отношением эквивалентности" << endl;
    } else {
        cout << "отношение не является отношением эквивалентности" << endl;
    }

    if (reflexivity(m) && antisymmetry(m) && transitivity(m)) {
        cout << "отношение является отношением частичного порядка" << endl;
    } else {
        cout << "отношение не является отношением частичного порядка" << endl;
    }

    if (antireflexivity(m) && antisymmetry(m) && transitivity(m)) {
        cout << "отношение является отношением строгого порядка" << endl;
    } else {
        cout << "отношение не является отношением строгого порядка" << endl;
    }

    if (antireflexivity(m) && antisymmetry(m)) {
        cout << "отношение является отношением доминирования" << endl;
    } else {
        cout << "отношение не является отношением доминирования" << endl;
    }

    cout << endl << "Исходное замыкание: " << endl;
    original_closure(m);

    cout << endl << "Рефлексивное замыкание: " << endl;
    reflexive_closure(m);

    cout << endl << "Симметричное замыкание: " << endl;
    symmetric_closure(m);

    cout << endl << "Транзитивное замыкание: " << endl;
    transitive_closure(m);

    cout << endl << "Эквивалентное замыкание: " << endl;
    equivalent_closure(m);

    return 0;
}