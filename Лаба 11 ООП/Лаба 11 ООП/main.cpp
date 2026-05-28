#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <windows.h>
#include "Pair.h"
using namespace std;

typedef list<double> Ld;

Ld make_list_double(int n) {
    Ld l;
    for (int i = 0; i < n; i++) {
        double a = (double)(rand() % 10001) / 100.0;
        l.push_back(a);
    }
    return l;
}

void print_list_double(Ld& l) {
    Ld::iterator it = l.begin();
    while (it != l.end()) {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}

double srednee_list_double(Ld& l) {
    double s = 0;
    int n = 0;
    Ld::iterator it = l.begin();
    while (it != l.end()) {
        s += *it;
        n++;
        ++it;
    }
    return s / n;
}

void add_to_end_double(Ld& l, double el) {
    l.push_back(el);
}

double sum_minmax_list_double(Ld& l) {
    Ld::iterator it = l.begin();
    double minEl = *it;
    double maxEl = *it;
    ++it;
    while (it != l.end()) {
        if (*it < minEl) minEl = *it;
        if (*it > maxEl) maxEl = *it;
        ++it;
    }
    return minEl + maxEl;
}

void add_sum_minmax_double(Ld& l) {
    double s = sum_minmax_list_double(l);
    Ld::iterator it = l.begin();
    while (it != l.end()) {
        *it = *it + s;
        ++it;
    }
}

void delete_by_range_double(Ld& l, double minVal, double maxVal) {
    Ld::iterator it = l.begin();
    while (it != l.end()) {
        if (*it > minVal && *it < maxVal) {
            it = l.erase(it);
        }
        else {
            ++it;
        }
    }
}

void task1() {
    cout << "\n=== ЗАДАЧА 1 (list<double>) ===" << endl;
    int n;
    cout << "Размер списка: "; cin >> n;
    Ld l = make_list_double(n);
    cout << "Исходный список:" << endl;
    print_list_double(l);

    double avg = srednee_list_double(l);
    cout << "Среднее арифметическое: " << avg << endl;
    add_to_end_double(l, avg);
    cout << "После добавления среднего в конец:" << endl;
    print_list_double(l);

    double minR, maxR;
    cout << "Диапазон для удаления (min max): "; cin >> minR >> maxR;
    delete_by_range_double(l, minR, maxR);
    cout << "После удаления из диапазона:" << endl;
    print_list_double(l);

    cout << "Сумма min+max: " << sum_minmax_list_double(l) << endl;
    add_sum_minmax_double(l);
    cout << "После добавления суммы min+max к каждому:" << endl;
    print_list_double(l);
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

Pair srednee_list_pair(Lp& l) {
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

void add_to_end_pair(Lp& l, Pair el) {
    l.push_back(el);
}

Pair sum_minmax_list_pair(Lp& l) {
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

void add_sum_minmax_pair(Lp& l) {
    Pair s = sum_minmax_list_pair(l);
    Lp::iterator it = l.begin();
    while (it != l.end()) {
        *it = *it + s;
        ++it;
    }
}

void delete_by_range_pair(Lp& l, Pair minVal, Pair maxVal) {
    Lp::iterator it = l.begin();
    while (it != l.end()) {
        if (*it > minVal && *it < maxVal) {
            it = l.erase(it);
        }
        else {
            ++it;
        }
    }
}

void task2() {
    cout << "\n=== ЗАДАЧА 2 (list<Pair>) ===" << endl;
    int n;
    cout << "Размер списка: "; cin >> n;
    Lp l = make_list_pair(n);
    cout << "Исходный список:" << endl;
    print_list_pair(l);

    Pair avg = srednee_list_pair(l);
    cout << "Среднее арифметическое: " << avg << endl;
    add_to_end_pair(l, avg);
    cout << "После добавления среднего в конец:" << endl;
    print_list_pair(l);

    Pair minR, maxR;
    cout << "Диапазон для удаления:" << endl;
    cout << "Мин. ключ: " << endl; cin >> minR;
    cout << "Макс. ключ: " << endl; cin >> maxR;
    delete_by_range_pair(l, minR, maxR);
    cout << "После удаления из диапазона:" << endl;
    print_list_pair(l);

    Pair smm = sum_minmax_list_pair(l);
    cout << "Сумма min+max: " << smm << endl;
    add_sum_minmax_pair(l);
    cout << "После добавления суммы min+max:" << endl;
    print_list_pair(l);
}

template<class T>
class CList {
    list<T> lst;
public:
    CList();
    CList(int n);
    void Print();
    T Srednee();
    void AddToEnd(T el);
    void DeleteByKeyRange(T keyMin, T keyMax);
    T SumMinMax();
    void AddSumMinMax();
};

template<class T>
CList<T>::CList() {}

template<class T>
CList<T>::CList(int n) {
    T a;
    for (int i = 0; i < n; i++) {
        cin >> a;
        lst.push_back(a);
    }
}

template<class T>
void CList<T>::Print() {
    typename list<T>::iterator it = lst.begin();
    while (it != lst.end()) {
        cout << *it << endl;
        ++it;
    }
}

template<class T>
T CList<T>::Srednee() {
    typename list<T>::iterator it = lst.begin();
    T sum = *it;
    int n = 1;
    ++it;
    while (it != lst.end()) {
        sum = sum + *it;
        n++;
        ++it;
    }
    return sum / n;
}

template<class T>
void CList<T>::AddToEnd(T el) {
    lst.push_back(el);
}

template<class T>
void CList<T>::DeleteByKeyRange(T keyMin, T keyMax) {
    typename list<T>::iterator it = lst.begin();
    while (it != lst.end()) {
        if (*it > keyMin && *it < keyMax) {
            it = lst.erase(it);
        }
        else {
            ++it;
        }
    }
}

template<class T>
T CList<T>::SumMinMax() {
    typename list<T>::iterator it = lst.begin();
    T minEl = *it;
    T maxEl = *it;
    ++it;
    while (it != lst.end()) {
        if (*it < minEl) minEl = *it;
        if (*it > maxEl) maxEl = *it;
        ++it;
    }
    return minEl + maxEl;
}

template<class T>
void CList<T>::AddSumMinMax() {
    T s = SumMinMax();
    typename list<T>::iterator it = lst.begin();
    while (it != lst.end()) {
        *it = *it + s;
        ++it;
    }
}

void task3() {
    cout << "\n=== ЗАДАЧА 3 (параметр. класс Список<Pair>) ===" << endl;
    int n;
    cout << "Размер списка: "; cin >> n;
    CList<Pair> cl(n);
    cout << "Исходный список:" << endl;
    cl.Print();

    Pair avg = cl.Srednee();
    cout << "Среднее арифметическое: " << avg << endl;
    cl.AddToEnd(avg);
    cout << "После добавления среднего в конец:" << endl;
    cl.Print();

    Pair minR, maxR;
    cout << "Диапазон для удаления:" << endl;
    cout << "Мин. ключ: " << endl; cin >> minR;
    cout << "Макс. ключ: " << endl; cin >> maxR;
    cl.DeleteByKeyRange(minR, maxR);
    cout << "После удаления из диапазона:" << endl;
    cl.Print();

    Pair smm = cl.SumMinMax();
    cout << "Сумма min+max: " << smm << endl;
    cl.AddSumMinMax();
    cout << "После добавления суммы min+max:" << endl;
    cl.Print();
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

Pair srednee_pq(PQ pq) {
    if (pq.empty()) return Pair();
    Pair sum = pq.top();
    int n = 1;
    pq.pop();
    while (!pq.empty()) {
        sum = sum + pq.top();
        n++;
        pq.pop();
    }
    return sum / n;
}

void add_pq(PQ& pq, Pair el) {
    pq.push(el);
}

Pair sum_minmax_pq(PQ pq) {
    if (pq.empty()) return Pair();
    Pair minEl = pq.top();
    Pair maxEl = pq.top();
    pq.pop();
    while (!pq.empty()) {
        if (pq.top() < minEl) minEl = pq.top();
        if (pq.top() > maxEl) maxEl = pq.top();
        pq.pop();
    }
    return minEl + maxEl;
}

void add_sum_minmax_pq(PQ& pq) {
    Pair s = sum_minmax_pq(pq);
    vector<Pair> temp;
    while (!pq.empty()) {
        temp.push_back(pq.top() + s);
        pq.pop();
    }
    for (int i = 0; i < temp.size(); i++) {
        pq.push(temp[i]);
    }
}

void delete_pq_by_range(PQ& pq, Pair minVal, Pair maxVal) {
    vector<Pair> temp;
    while (!pq.empty()) {
        Pair t = pq.top();
        pq.pop();
        if (t > minVal && t < maxVal) continue;
        temp.push_back(t);
    }
    for (int i = 0; i < temp.size(); i++) {
        pq.push(temp[i]);
    }
}

void task4() {
    cout << "\n=== ЗАДАЧА 4 (priority_queue<Pair>) ===" << endl;
    int n;
    cout << "Размер очереди: "; cin >> n;
    PQ pq = make_pq(n);
    cout << "Исходная очередь:" << endl;
    print_pq(pq);

    Pair avg = srednee_pq(pq);
    cout << "Среднее арифметическое: " << avg << endl;
    add_pq(pq, avg);
    cout << "После добавления среднего:" << endl;
    print_pq(pq);

    Pair minR, maxR;
    cout << "Диапазон для удаления:" << endl;
    cout << "Мин. ключ: " << endl; cin >> minR;
    cout << "Макс. ключ: " << endl; cin >> maxR;
    delete_pq_by_range(pq, minR, maxR);
    cout << "После удаления из диапазона:" << endl;
    print_pq(pq);

    Pair smm = sum_minmax_pq(pq);
    cout << "Сумма min+max: " << smm << endl;
    add_sum_minmax_pq(pq);
    cout << "После добавления суммы min+max:" << endl;
    print_pq(pq);
}

template<class T>
class CPQueue {
    priority_queue<T> pq;
public:
    CPQueue();
    CPQueue(int n);
    void Print();
    T Srednee();
    void AddToEnd(T el);
    void DeleteByKeyRange(T keyMin, T keyMax);
    T SumMinMax();
    void AddSumMinMax();
};

template<class T>
CPQueue<T>::CPQueue() {}

template<class T>
CPQueue<T>::CPQueue(int n) {
    T a;
    for (int i = 0; i < n; i++) {
        cin >> a;
        pq.push(a);
    }
}

template<class T>
void CPQueue<T>::Print() {
    priority_queue<T> temp = pq;
    while (!temp.empty()) {
        cout << temp.top() << endl;
        temp.pop();
    }
}

template<class T>
T CPQueue<T>::Srednee() {
    priority_queue<T> temp = pq;
    if (temp.empty()) return T();
    T sum = temp.top();
    int n = 1;
    temp.pop();
    while (!temp.empty()) {
        sum = sum + temp.top();
        n++;
        temp.pop();
    }
    return sum / n;
}

template<class T>
void CPQueue<T>::AddToEnd(T el) {
    pq.push(el);
}

template<class T>
void CPQueue<T>::DeleteByKeyRange(T keyMin, T keyMax) {
    vector<T> temp;
    while (!pq.empty()) {
        T t = pq.top();
        pq.pop();
        if (t > keyMin && t < keyMax) continue;
        temp.push_back(t);
    }
    for (int i = 0; i < temp.size(); i++) {
        pq.push(temp[i]);
    }
}

template<class T>
T CPQueue<T>::SumMinMax() {
    priority_queue<T> temp = pq;
    if (temp.empty()) return T();
    T minEl = temp.top();
    T maxEl = temp.top();
    temp.pop();
    while (!temp.empty()) {
        if (temp.top() < minEl) minEl = temp.top();
        if (temp.top() > maxEl) maxEl = temp.top();
        temp.pop();
    }
    return minEl + maxEl;
}

template<class T>
void CPQueue<T>::AddSumMinMax() {
    T s = SumMinMax();
    vector<T> temp;
    while (!pq.empty()) {
        temp.push_back(pq.top() + s);
        pq.pop();
    }
    for (int i = 0; i < temp.size(); i++) {
        pq.push(temp[i]);
    }
}

void task5() {
    cout << "\n=== ЗАДАЧА 5 (параметр. класс CPQueue<Pair>) ===" << endl;
    int n;
    cout << "Размер очереди: "; cin >> n;
    CPQueue<Pair> cpq(n);
    cout << "Исходная очередь:" << endl;
    cpq.Print();

    Pair avg = cpq.Srednee();
    cout << "Среднее арифметическое: " << avg << endl;
    cpq.AddToEnd(avg);
    cout << "После добавления среднего:" << endl;
    cpq.Print();

    Pair minR, maxR;
    cout << "Диапазон для удаления:" << endl;
    cout << "Мин. ключ: " << endl; cin >> minR;
    cout << "Макс. ключ: " << endl; cin >> maxR;
    cpq.DeleteByKeyRange(minR, maxR);
    cout << "После удаления из диапазона:" << endl;
    cpq.Print();

    Pair smm = cpq.SumMinMax();
    cout << "Сумма min+max: " << smm << endl;
    cpq.AddSumMinMax();
    cout << "После добавления суммы min+max:" << endl;
    cpq.Print();
}

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(GetTickCount());

    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "   ЛАБОРАТОРНАЯ РАБОТА №11" << endl;
        cout << "========================================" << endl;
        cout << "1. Задача 1 - list<double>" << endl;
        cout << "2. Задача 2 - list<Pair>" << endl;
        cout << "3. Задача 3 - параметр. класс CList<Pair>" << endl;
        cout << "4. Задача 4 - priority_queue<Pair>" << endl;
        cout << "5. Задача 5 - параметр. класс CPQueue<Pair>" << endl;
        cout << "0. Выход" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Ваш выбор: "; cin >> choice;
        switch (choice) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
        case 5: task5(); break;
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