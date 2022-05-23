#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <set>


using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);

    cout << "Введите число x:" << endl;
    int x;
    cin >> x;
    vector<int> divisor_set;

    for (int i = 1; i <= x; ++i) {
        if (x % i == 0) {
            divisor_set.push_back(i);
        }
    }

    cout << "Множество делителей x:" << endl;
    for (int element : divisor_set) {
        cout << element << ' ';
    }

    cout << endl << "Наименьший и наибольший элементы: " << endl;
    for (int element : divisor_set) {
        if (element == 1 || element == x) {
            if (element == 1) {
                cout << element << " - наименьший элемент" << endl;
            } else {
                cout << element << " - наибольший элемент" << endl;
            }
        }
    }

    auto iter_first = begin(divisor_set);
    divisor_set.erase(iter_first);
    divisor_set.pop_back();

    int q = x;
    int w = 2;
    vector<int> simple_divisors;

    while (q != 1) {
        if (q % w == 0) {
            simple_divisors.push_back(w);
            q = q / w;
        } else ++w;
    }

    if (!empty(simple_divisors)) {

        set<int> minimal_elements(begin(simple_divisors), end(simple_divisors));

        cout << "Минимальные элементы:" << endl;
        for (int element : minimal_elements) {
            cout << element << ' ';
        }
        cout << endl;

    } else {
        cout << "Минимальный элемент - 1" << endl;
    }

    if (!empty(simple_divisors)) {

        set<int> maximum_elements;
        for (int i = 0; i < size(simple_divisors); ++i) {
            maximum_elements.emplace(x / simple_divisors[i]);
        }

        cout << "Максимальные элементы:" << endl;
        for (int element : maximum_elements) {
            cout << element << ' ';
        }
        cout << endl;

    } else {
        cout << "Максимальный элемент -" << x;
    }

    return 0;
}