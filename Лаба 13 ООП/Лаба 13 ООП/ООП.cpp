#include <iostream>
#include <list>
#include <queue>
#include <map>
#include <algorithm>
#include <functional>
#include <windows.h>
#include "Pair.h"
using namespace std;

Pair s; 
Pair sumMinMax; 

struct Greater_s {
    bool operator()(Pair t) {
        return t > s;
    }
};

struct Equal_s {
    bool operator()(Pair t) {
        return t == s;
    }
};

struct InRange {
    Pair minVal, maxVal;
    InRange(Pair min, Pair max) : minVal(min), maxVal(max) {}
    bool operator()(Pair t) {
        return t > minVal && t < maxVal;
    }
};

struct Comp_greater {
    bool operator()(Pair a, Pair b) {
        return a > b;
    }
};

void del_func(Pair& t) {
    t = t / s;
}

void add_sumMinMax(Pair& t) {
    t = t + sumMinMax;
}

typedef list<Pair> Lp;

Lp make_list_pair(int n) {
    Lp l;
    for (int i = 0; i < n; i++) {
        Pair p;
        p.set_first(rand() % 100);
        p.set_second((double)(rand() % 10000) / 100.0);
        l.push_back(p);
    }
    return l;
}

void print_list_pair(Lp& l) {
    Lp::iterator it = l.begin();
    while (it != l.end()) {
        cout << *it << endl;
        ++it;
    }
}

Pair srednee_list(Lp& l) {
    Lp::iterator it = l.begin();
    Pair sum = *it;
    int n = 1;
    ++it;
    while (it != l.end()) {
        sum = sum + *it;
        n++;
        ++it;
    }
    return sum / n;
}

Pair sum_minmax_list(Lp& l) {
    Lp::iterator it = l.begin();
    Pair minEl = *it;
    Pair maxEl = *it;
    ++it;
    while (it != l.end()) {
        if (*it < minEl) minEl = *it;
        if (*it > maxEl) maxEl = *it;
        ++it;
    }
    return minEl + maxEl;
}

void task1() {
    cout << "\n=== ЗАДАЧА 1 (list<Pair>) ===" << endl;
    int n;
    cout << "Размер списка: "; cin >> n;
    Lp l = make_list_pair(n);
    cout << "Исходный список:" << endl;
    print_list_pair(l);

    Pair avg = srednee_list(l);
    cout << "\nСреднее арифметическое: " << avg << endl;
    l.push_back(avg);
    cout << "После добавления среднего в конец:" << endl;
    print_list_pair(l);

    sumMinMax = sum_minmax_list(l);
    s = avg;
    cout << "\nСумма min+max: " << sumMinMax << endl;
    replace_if(l.begin(), l.end(), Greater_s(), sumMinMax);
    cout << "После замены элементов > среднего на сумму min+max:" << endl;
    print_list_pair(l);

    Pair minR, maxR;
    cout << "\nДиапазон для удаления:" << endl;
    cout << "Мин. ключ: " << endl; cin >> minR;
    cout << "Макс. ключ: " << endl; cin >> maxR;
    l.remove_if(InRange(minR, maxR));
    cout << "После удаления элементов из диапазона:" << endl;
    print_list_pair(l);

    cout << "\nСортировка по возрастанию:" << endl;
    l.sort();
    print_list_pair(l);
    cout << "Сортировка по убыванию:" << endl;
    l.sort(Comp_greater());
    print_list_pair(l);

    cout << "\nВведите ключ для поиска:" << endl;
    cin >> s;
    Lp::iterator it = find_if(l.begin(), l.end(), Equal_s());
    if (it != l.end()) {
        cout << "Найден элемент: " << *it << endl;
    }
    else {
        cout << "Элемент не найден." << endl;
    }
    cout << "Количество элементов с таким ключом: " << count_if(l.begin(), l.end(), Equal_s()) << endl;

    sumMinMax = sum_minmax_list(l);
    cout << "\nСумма min+max: " << sumMinMax << endl;
    for_each(l.begin(), l.end(), add_sumMinMax);
    cout << "После добавления суммы min+max к каждому:" << endl;
    print_list_pair(l);
}

typedef priority_queue<Pair> PQ;

void print_pq(PQ pq) {
    while (!pq.empty()) {
        cout << pq.top() << endl;
        pq.pop();
    }
}

PQ make_pq(int n) {
    PQ pq;
    for (int i = 0; i < n; i++) {
        Pair p;
        p.set_first(rand() % 100);
        p.set_second((double)(rand() % 10000) / 100.0);
        pq.push(p);
    }
    return pq;
}

void pq_to_vector(PQ& pq, vector<Pair>& v) {
    while (!pq.empty()) {
        v.push_back(pq.top());
        pq.pop();
    }
}

void vector_to_pq(vector<Pair>& v, PQ& pq) {
    for (int i = 0; i < v.size(); i++) {
        pq.push(v[i]);
    }
}

Pair srednee_vector(vector<Pair>& v) {
    Pair sum = v[0];
    for (int i = 1; i < v.size(); i++) {
        sum = sum + v[i];
    }
    return sum / (int)v.size();
}

Pair sum_minmax_vector(vector<Pair>& v) {
    Pair minEl = v[0];
    Pair maxEl = v[0];
    for (int i = 1; i < v.size(); i++) {
        if (v[i] < minEl) minEl = v[i];
        if (v[i] > maxEl) maxEl = v[i];
    }
    return minEl + maxEl;
}

void task2() {
    cout << "\n=== ЗАДАЧА 2 (priority_queue<Pair>) ===" << endl;
    int n;
    cout << "Размер очереди: "; cin >> n;
    PQ pq = make_pq(n);
    cout << "Исходная очередь:" << endl;
    print_pq(pq);

    pq = make_pq(n);

    vector<Pair> v;
    pq_to_vector(pq, v);

    Pair avg = srednee_vector(v);
    cout << "\nСреднее арифметическое: " << avg << endl;
    v.push_back(avg);
    cout << "После добавления среднего в конец:" << endl;
    for (int i = 0; i < v.size(); i++) cout << v[i] << endl;

    sumMinMax = sum_minmax_vector(v);
    s = avg;
    cout << "\nСумма min+max: " << sumMinMax << endl;
    replace_if(v.begin(), v.end(), Greater_s(), sumMinMax);
    cout << "После замены элементов > среднего на сумму min+max:" << endl;
    for (int i = 0; i < v.size(); i++) cout << v[i] << endl;

    Pair minR, maxR;
    cout << "\nДиапазон для удаления:" << endl;
    cout << "Мин. ключ: " << endl; cin >> minR;
    cout << "Макс. ключ: " << endl; cin >> maxR;
    InRange rangePred(minR, maxR);
    v.erase(remove_if(v.begin(), v.end(), rangePred), v.end());
    cout << "После удаления из диапазона:" << endl;
    for (int i = 0; i < v.size(); i++) cout << v[i] << endl;

    cout << "\nСортировка по возрастанию:" << endl;
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) cout << v[i] << endl;
    cout << "Сортировка по убыванию:" << endl;
    sort(v.begin(), v.end(), Comp_greater());
    for (int i = 0; i < v.size(); i++) cout << v[i] << endl;

    cout << "\nВведите ключ для поиска:" << endl;
    cin >> s;
    vector<Pair>::iterator it = find_if(v.begin(), v.end(), Equal_s());
    if (it != v.end()) {
        cout << "Найден элемент: " << *it << endl;
    }
    else {
        cout << "Элемент не найден." << endl;
    }
    cout << "Количество: " << count_if(v.begin(), v.end(), Equal_s()) << endl;

    sumMinMax = sum_minmax_vector(v);
    cout << "\nСумма min+max: " << sumMinMax << endl;
    for_each(v.begin(), v.end(), add_sumMinMax);
    cout << "После добавления суммы min+max к каждому:" << endl;
    for (int i = 0; i < v.size(); i++) cout << v[i] << endl;
}

typedef map<int, Pair> TMap;

TMap make_map(int n) {
    TMap m;
    for (int i = 0; i < n; i++) {
        Pair p;
        p.set_first(rand() % 100);
        p.set_second((double)(rand() % 10000) / 100.0);
        m.insert(make_pair(i, p));
    }
    return m;
}

void print_map(TMap& m) {
    for (int i = 0; i < m.size(); i++) {
        cout << i << " - " << m[i] << endl;
    }
}

Pair srednee_map(TMap& m) {
    Pair sum = m[0];
    for (int i = 1; i < m.size(); i++) {
        sum = sum + m[i];
    }
    return sum / (int)m.size();
}

Pair sum_minmax_map(TMap& m) {
    Pair minEl = m[0];
    Pair maxEl = m[0];
    for (int i = 1; i < m.size(); i++) {
        if (m[i] < minEl) minEl = m[i];
        if (m[i] > maxEl) maxEl = m[i];
    }
    return minEl + maxEl;
}

void task3() {
    cout << "\n=== ЗАДАЧА 3 (map<int, Pair>) ===" << endl;
    int n;
    cout << "Размер словаря: "; cin >> n;
    TMap m = make_map(n);
    cout << "Исходный словарь:" << endl;
    print_map(m);

    Pair avg = srednee_map(m);
    cout << "\nСреднее арифметическое: " << avg << endl;
    m.insert(make_pair(m.size(), avg));
    cout << "После добавления среднего:" << endl;
    print_map(m);

    sumMinMax = sum_minmax_map(m);
    s = avg;
    cout << "\nСумма min+max: " << sumMinMax << endl;
    for (int i = 0; i < m.size(); i++) {
        if (m[i] > s) m[i] = sumMinMax;
    }
    cout << "После замены элементов > среднего:" << endl;
    print_map(m);

    Pair minR, maxR;
    cout << "\nДиапазон для удаления:" << endl;
    cout << "Мин. ключ: " << endl; cin >> minR;
    cout << "Макс. ключ: " << endl; cin >> maxR;
    TMap::iterator it = m.begin();
    while (it != m.end()) {
        if (it->second > minR && it->second < maxR) {
            m.erase(it++);
        }
        else {
            ++it;
        }
    }
    cout << "После удаления из диапазона:" << endl;
    print_map(m);

    cout << "\nСловарь уже отсортирован по ключу (по возрастанию):" << endl;
    print_map(m);

    cout << "\nВведите ключ для поиска значения:" << endl;
    cin >> s;
    bool found = false;
    for (int i = 0; i < m.size(); i++) {
        if (m[i] == s) {
            cout << "Найден элемент с ключом " << i << ": " << m[i] << endl;
            found = true;
        }
    }
    if (!found) cout << "Элемент не найден." << endl;

    // Задание 7
    sumMinMax = sum_minmax_map(m);
    cout << "\nСумма min+max: " << sumMinMax << endl;
    for (int i = 0; i < m.size(); i++) {
        m[i] = m[i] + sumMinMax;
    }
    cout << "После добавления суммы min+max к каждому:" << endl;
    print_map(m);
}

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(GetTickCount());

    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "   ЛАБОРАТОРНАЯ РАБОТА №13" << endl;
        cout << "========================================" << endl;
        cout << "1. Задача 1 - list<Pair>" << endl;
        cout << "2. Задача 2 - priority_queue<Pair>" << endl;
        cout << "3. Задача 3 - map<int, Pair>" << endl;
        cout << "0. Выход" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Ваш выбор: "; cin >> choice;

        switch (choice) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 0: cout << "До свидания!" << endl; break;
        default: cout << "Неверный выбор!" << endl;
        }

        if (choice != 0) {
            cout << "\nНажмите Enter...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 0);

    return 0;
}