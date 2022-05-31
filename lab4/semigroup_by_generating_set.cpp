#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <iomanip>
#include <windows.h>

using namespace std;

set<string> set_of_R;
map<string, string> R;
set<string> S_cur, S, copy_S;
int maximum = 0;
string cur_word;
vector<vector<string>> cayley_table;


vector<string> split(string word) {
    vector <string> splited_word;

    for (int i = 0; i < size(word); ++i) {
        splited_word.push_back(word.substr(i, 1));
    }

    return(splited_word);
}


bool comp(string A, string B) {
    return (size(A) < size(B)) || (size(A) == size(B) && A < B);
}


void new_element(string word, bool flag = false, int row = 0, int size = -1) {
    if (set_of_R.find(word) != end(set_of_R) && !flag)
        return;

    vector<string> temp_word = split(word);

    int substr = 2;
    while (substr <= maximum) {
        for (int i = temp_word.size() - 1; i >= 0; --i) {
            if (substr > word.size() || substr > i + 1)
                break;

            string part = "";

            for (int j = i; j > i - substr; --j) {
                part = temp_word[j] + part;
            }

            if (R.find(part) != end(R)) {
                cur_word = "";
                vector<string> temp_part = split(R[part]);

                if (!flag) {
                    for (int q = 0; q < i - substr; ++q) {
                        cur_word = cur_word + temp_word[q];
                    }
                } else {
                    for (int q = 0; q < i - substr + 1; ++q) {
                        cur_word = cur_word + temp_word[q];
                    }
                }

                cur_word = cur_word + R[part];

                for (int q = i + 1; q < temp_word.size(); ++q) {
                    cur_word = cur_word + temp_word[q];
                }

                if (cur_word.size() < word.size() && !flag) {
                    set_of_R.insert(word);
                    set_of_R.insert(cur_word);
                    return;
                } else if (set_of_R.find(cur_word) != set_of_R.end() && !flag) {
                    return;
                } else if (flag && copy_S.find(cur_word) != copy_S.end()) {
                    if (cayley_table[row].size() < size) {
                        cayley_table[row].push_back(cur_word);
                    }
                    return;
                } else {
                    int check = cayley_table[row].size();
                    new_element(cur_word, flag, row, size);
                    if (flag && cayley_table[row].size() > check) {
                        return;
                    }
                }
            }

            if (set_of_R.find(word) != end(set_of_R) && !flag) {
                return;
            }

            if (flag && copy_S.find(word) != end(copy_S)) {
                if (cayley_table[row].size() <= size)
                    cayley_table[row].push_back(word);
                return;
            }
        }

        ++substr;
    }

    if (cur_word.size() == word.size() && cur_word < word && set_of_R.find(word) == set_of_R.end() && set_of_R.find(cur_word) == set_of_R.end()) {
        S.insert(cur_word);
        set_of_R.insert(word);
        set_of_R.insert(cur_word);
    } else {
        S.insert(word);
        set_of_R.insert(word);
        set_of_R.insert(cur_word);
    }
}

int main() {

    SetConsoleOutputCP(CP_UTF8);

    int n;
    cout << "Количество букв в множестве: " << endl;
    cin >> n;

    set<string> A;
    cout << "Алфавит: " << endl;
    for (int i = 0; i < n; ++i) {
        string a;
        cin >> a;
        A.insert(a);
        S.insert(a);
        set_of_R.insert(a);
    }

    int m;
    cout << "Количество определяющих отношений: " << endl;
    cin >> m;

    cout << "Oпределяющие отношения: " << endl;
    for (int i = 0; i < m; ++i) {
        string r1, r2;
        cin >> r1 >> r2;

        if (size(r1) > maximum)
            maximum = size(r1);
        if (r2.size() > maximum)
            maximum = size(r2);

        if (size(r1) < size(r2))
            R[r2] = r1;
        else if (size(r1) > size(r2))
            R[r1] = r2;
        else {
            if (r1 < r2)
                R[r2] = r1;
            else
                R[r1] = r2;
        }
    }

    int count = 1;
    S_cur = A;
    while (!empty(S_cur)) {
        ++count;

        for (string s : S_cur) {
            for (string letter : A) {
                new_element(s + letter);
            }
        }

        S_cur.clear();
        for (auto s : S) {
            if (size(s) == count) {
                S_cur.insert(s);
            }
        }

    }

    vector<string> halfgroup;
    for (string s : S) {
        halfgroup.push_back(s);
    }
    sort(begin(halfgroup), end(halfgroup), comp);

    cout << " Полугруппа: {";
    for (int i = 0; i < size(halfgroup); ++i) {
        if (i == size(halfgroup) - 1) {
            cout << halfgroup[i] << "}" << endl;
        } else {
            cout << halfgroup[i] << " ";
        }
    }

    cayley_table.resize(size(halfgroup));
    copy_S = S;
    for (int i = 0; i < size(halfgroup); ++i) {
        for (int j = 0; j < size(halfgroup); ++j) {
            new_element(halfgroup[i] + halfgroup[j], true, i, size(halfgroup));
        }
    }

    cout << endl << "Таблица Кэли: " << endl;
    cout << "    ";
    for (int i = 0; i < size(halfgroup); ++i){
        cout << setw(5) << halfgroup[i];
    }
    cout << endl;
    for (int i = 0; i < size(halfgroup); ++i) {
        cout << setw(5) << halfgroup[i] << setw(5);
        for (int j = 0; j < size(halfgroup); ++j) {
            cout << cayley_table[i][j] << setw(5);
        }
        cout << endl;
    }

    cout << endl;

    return 0;
}

