#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>

using namespace std;

/*
 5
 1 0 0 0 0
 0 1 0 1 0
 0 0 1 0 0
 0 1 0 1 0
 0 0 0 0 1
 */

void dfs1(const vector<vector<int>>& graph, vector<bool>& used, vector<int>& order, int v) {
    used[v] = true;
    for (int i = 0; i < size(graph[v]); ++i){
        if (graph[v][i] && !used[i]) {
            dfs1(graph, used, order, i);
        }
    }
    order.push_back(v);
}

void dfs2(const vector<vector<int>>& graph_tr, vector<bool>& used, vector<int>& component, int v) {
    used[v] = true;
    component.push_back(v);
    for (int i = 0; i < size(graph_tr[v]); ++i) {
        if (graph_tr[v][i] && !used[i]) {
            dfs2(graph_tr, used, component, i);
        }
    }
}

int main() {

    SetConsoleOutputCP(CP_UTF8);

    cout << "Введите n:" << endl;
    int n;
    cin >> n;

    cout << "Введите матрицу n*n:" << endl;   
    vector<vector<int>> m(n, vector<int> (n));
    vector<vector<int>> m_tr(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> m[i][j];
            if (m[i][j]) {
                m_tr[j][i] = 1;
            }
        }
    }

    vector<bool> used(n);
    vector<int> order;

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs1(m, used, order, i);
        }
    }

    used.assign(n, false);
    vector<int> result;

    for (int i = n - 1; i >= 0; --i) {
        if (!used[i]) {
            vector<int> component;
            dfs2(m_tr, used, component, i);
            result.push_back(component[0] + 1);
        }
    }

    sort(begin(result), end(result));

    cout << "Представители фактор-множества:" << endl;
    for (int element : result) {
        cout << element << ' ';
    }
    cout << endl;

    return 0;
}