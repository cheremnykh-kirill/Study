#include <iostream>
#include <set>
#include <windows.h>
#include "Pair.h"
using namespace std;

typedef multiset<double> MSd;

MSd make_multiset_double(int n) {
    MSd ms;
    for (int i = 0; i < n; i++) {
        double a = (double)(rand() % 10001) / 100.0;
        ms.insert(a);
    }
    return ms;
}

void print_multiset_double(MSd& ms) {
    MSd::iterator it = ms.begin();
    while (it != ms.end()) {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}

double srednee_multiset_double(MSd& ms) {
    double s = 0;
    int n = 0;
    MSd::iterator it = ms.begin();
    while (it != ms.end()) {
        s += *it;
        n++;
        ++it;
    }
    return s / n;
}

void add_to_end_double(MSd& ms, double el) {
    ms.insert(el);
}

double sum_minmax_multiset_double(MSd& ms) {
    MSd::iterator it = ms.begin();
    double minEl = *it;
    double maxEl = *it;
    ++it;
    while (it != ms.end()) {
        if (*it < minEl) minEl = *it;
        if (*it > maxEl) maxEl = *it;
        ++it;
    }
    return minEl + maxEl;
}

void add_sum_minmax_double(MSd& ms) {
    double s = sum_minmax_multiset_double(ms);
    double* temp = new double[ms.size()];
    int idx = 0;
    MSd::iterator it = ms.begin();
    while (it != ms.end()) {
        temp[idx++] = *it + s;
        ++it;
    }
    ms.clear();
    for (int i = 0; i < idx; i++) {
        ms.insert(temp[i]);
    }
    delete[] temp;
}

void delete_by_range_double(MSd& ms, double minVal, double maxVal) {
    double* temp = new double[ms.size()];
    int idx = 0;
    MSd::iterator it = ms.begin();
    while (it != ms.end()) {
        if (*it > minVal && *it < maxVal) {
            ++it;
            continue;
        }
        temp[idx++] = *it;
        ++it;
    }
    ms.clear();
    for (int i = 0; i < idx; i++) {
        ms.insert(temp[i]);
    }
    delete[] temp;
}

void task1() {
    cout << "\n=== ЗАДАЧА 1 (multiset<double>) ===" << endl;
    int n;
    cout << "Размер контейнера: "; cin >> n;
    MSd ms = make_multiset_double(n);
    cout << "Исходный multiset:" << endl;
    print_multiset_double(ms);

    double avg = srednee_multiset_double(ms);
    cout << "Среднее арифметическое: " << avg << endl;
    add_to_end_double(ms, avg);
    cout << "После добавления среднего:" << endl;
    print_multiset_double(ms);

    double minR, maxR;
    cout << "Диапазон для удаления (min max): "; cin >> minR >> maxR;
    delete_by_range_double(ms, minR, maxR);
    cout << "После удаления из диапазона:" << endl;
    print_multiset_double(ms);

    cout << "Сумма min+max: " << sum_minmax_multiset_double(ms) << endl;
    add_sum_minmax_double(ms);
    cout << "После добавления суммы min+max:" << endl;
    print_multiset_double(ms);
}

typedef multiset<Pair> MSp;

MSp make_multiset_pair(int n) {
    MSp ms;
    for (int i = 0; i < n; i++) {
        Pair p;
        p.set_first(rand() % 100);
        p.set_second((double)(rand() % 10000) / 100.0);
        ms.insert(p);
    }
    return ms;
}

void print_multiset_pair(MSp& ms) {
    MSp::iterator it = ms.begin();
    while (it != ms.end()) {
        cout << *it << endl;
        ++it;
    }
}

Pair srednee_multiset_pair(MSp& ms) {
    MSp::iterator it = ms.begin();
    Pair sum = *it;
    int n = 1;
    ++it;
    while (it != ms.end()) {
        sum = sum + *it;
        n++;
        ++it;
    }
    return sum / n;
}

void add_to_end_pair(MSp& ms, Pair el) {
    ms.insert(el);
}

Pair sum_minmax_multiset_pair(MSp& ms) {
    MSp::iterator it = ms.begin();
    Pair minEl = *it;
    Pair maxEl = *it;
    ++it;
    while (it != ms.end()) {
        if (*it < minEl) minEl = *it;
        if (*it > maxEl) maxEl = *it;
        ++it;
    }
    return minEl + maxEl;
}

void add_sum_minmax_pair(MSp& ms) {
    Pair s = sum_minmax_multiset_pair(ms);
    int sz = ms.size();
    Pair* temp = new Pair[sz];
    int idx = 0;
    MSp::iterator it = ms.begin();
    while (it != ms.end()) {
        temp[idx++] = *it + s;
        ++it;
    }
    ms.clear();
    for (int i = 0; i < idx; i++) {
        ms.insert(temp[i]);
    }
    delete[] temp;
}

void delete_by_range_pair(MSp& ms, Pair minVal, Pair maxVal) {
    int sz = ms.size();
    Pair* temp = new Pair[sz];
    int idx = 0;
    MSp::iterator it = ms.begin();
    while (it != ms.end()) {
        if (*it > minVal && *it < maxVal) {
            ++it;
            continue;
        }
        temp[idx++] = *it;
        ++it;
    }
    ms.clear();
    for (int i = 0; i < idx; i++) {
        ms.insert(temp[i]);
    }
    delete[] temp;
}

void task2() {
    cout << "\n=== ЗАДАЧА 2 (multiset<Pair>) ===" << endl;
    int n;
    cout << "Размер контейнера: "; cin >> n;
    MSp ms = make_multiset_pair(n);
    cout << "Исходный multiset:" << endl;
    print_multiset_pair(ms);

    Pair avg = srednee_multiset_pair(ms);
    cout << "Среднее арифметическое: " << avg << endl;
    add_to_end_pair(ms, avg);
    cout << "После добавления среднего:" << endl;
    print_multiset_pair(ms);

    Pair minR, maxR;
    cout << "Диапазон для удаления:" << endl;
    cout << "Мин. ключ: " << endl; cin >> minR;
    cout << "Макс. ключ: " << endl; cin >> maxR;
    delete_by_range_pair(ms, minR, maxR);
    cout << "После удаления из диапазона:" << endl;
    print_multiset_pair(ms);

    Pair smm = sum_minmax_multiset_pair(ms);
    cout << "Сумма min+max: " << smm << endl;
    add_sum_minmax_pair(ms);
    cout << "После добавления суммы min+max:" << endl;
    print_multiset_pair(ms);
}

template<class T>
class CList {
    multiset<T> ms;
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
        ms.insert(a);
    }
}

template<class T>
void CList<T>::Print() {
    typename multiset<T>::iterator it = ms.begin();
    while (it != ms.end()) {
        cout << *it << endl;
        ++it;
    }
}

template<class T>
T CList<T>::Srednee() {
    typename multiset<T>::iterator it = ms.begin();
    T sum = *it;
    int n = 1;
    ++it;
    while (it != ms.end()) {
        sum = sum + *it;
        n++;
        ++it;
    }
    return sum / n;
}

template<class T>
void CList<T>::AddToEnd(T el) {
    ms.insert(el);
}

template<class T>
void CList<T>::DeleteByKeyRange(T keyMin, T keyMax) {
    int sz = ms.size();
    T* temp = new T[sz];
    int idx = 0;
    typename multiset<T>::iterator it = ms.begin();
    while (it != ms.end()) {
        if (*it > keyMin && *it < keyMax) {
            ++it;
            continue;
        }
        temp[idx++] = *it;
        ++it;
    }
    ms.clear();
    for (int i = 0; i < idx; i++) {
        ms.insert(temp[i]);
    }
    delete[] temp;
}

template<class T>
T CList<T>::SumMinMax() {
    typename multiset<T>::iterator it = ms.begin();
    T minEl = *it;
    T maxEl = *it;
    ++it;
    while (it != ms.end()) {
        if (*it < minEl) minEl = *it;
        if (*it > maxEl) maxEl = *it;
        ++it;
    }
    return minEl + maxEl;
}

template<class T>
void CList<T>::AddSumMinMax() {
    T s = SumMinMax();
    int sz = ms.size();
    T* temp = new T[sz];
    int idx = 0;
    typename multiset<T>::iterator it = ms.begin();
    while (it != ms.end()) {
        temp[idx++] = *it + s;
        ++it;
    }
    ms.clear();
    for (int i = 0; i < idx; i++) {
        ms.insert(temp[i]);
    }
    delete[] temp;
}

void task3() {
    cout << "\n=== ЗАДАЧА 3 (параметр. класс CList<Pair> на multiset) ===" << endl;
    int n;
    cout << "Размер контейнера: "; cin >> n;
    CList<Pair> cl(n);
    cout << "Исходный контейнер:" << endl;
    cl.Print();

    Pair avg = cl.Srednee();
    cout << "Среднее арифметическое: " << avg << endl;
    cl.AddToEnd(avg);
    cout << "После добавления среднего:" << endl;
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

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(GetTickCount());

    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "   ЛАБОРАТОРНАЯ РАБОТА №12 " << endl;
        cout << "========================================" << endl;
        cout << "1. Задача 1 - multiset<double>" << endl;
        cout << "2. Задача 2 - multiset<Pair>" << endl;
        cout << "3. Задача 3 - параметр. класс CList<Pair>" << endl;
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