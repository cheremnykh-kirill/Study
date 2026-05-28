#include <iostream>
#include <clocale>
#include <string>
#include <windows.h>
using namespace std;

void linear_search() {
    const int size = 10;
    int arr[size];
    int c = 10, z, count = 0, ind;
    cout << "\nПОИСК ЭЛЕМЕНТА ЛИНЕЙНЫМ МЕТОДОМ" << "\n-----------------" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Введите очередной элемент массива (осталось " << c << "): ";
        c--;
        cin >> arr[i];
    }

    cout << endl << "Ваш массив: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    cout << "Введите z - элемент, который необходимо найти в массиве: ";
    cin >> z;
    for (int i = 0; i < size; i++) {
        if (arr[i] == z) {
            count++;
            if (count == 1) {
                ind = i;
            }
        }
    }
    if (count == 0) {
        cout << "Не найдено элементов, равных z";
        return;
    }

    cout << endl << "Результаты поиска:" << "\n------------------";
    cout << endl << "Количество элементов в массиве, равных z: " << count;
    cout << endl << "Индекс первого встретившегося элемента, равного z: " << ind;
    cout << endl << "Номер первого встретившегося элемента, равного z: " << ind + 1 << endl;
}

void binary_search() {
    setlocale(LC_ALL, "RU");
    const int size = 10;
    int arr[size];
    int c = 10, z, count = 0, ind;
    cout << "\nПОИСК ЭЛЕМЕНТА БИНАРНЫМ МЕТОДОМ (требует отсортированный массив)" << "\n-----------------" << endl;

    for (int i = 0; i < size; i++) {
        cout << "Введите очередной элемент массива (осталось " << c << "): ";
        c--;
        cin >> arr[i];
    }

    cout << endl << "Ваш массив: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    for (int i = 1; i < size; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;

    }

    cout << "\nОтсортированный массив: { ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "}";

    cout << "\n\nВведите z - элемент, который необходимо найти в массиве: ";
    cin >> z;
    if (z == arr[size / 2]) {
        cout << "Элемент найден";
    }
    if (z < arr[size / 2]) {

    }
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == z) {
            count++;
            ind = mid;

            int temp = mid - 1;
            while (temp >= 0 && arr[temp] == z) {
                count++;
                ind = temp;
                temp--;
            }
            temp = mid + 1;
            while (temp < size && arr[temp] == z) {
                count++;
                temp++;
            }

            break;
        }
        else if (arr[mid] < z) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (count == 0) {
        cout << "Не найдено элементов, равных z" << endl;
        return;
    }

    cout << endl << "Результаты поиска:" << "\n------------------";
    cout << endl << "Количество элементов в массиве, равных z: " << count;
    cout << endl << "Индекс первого встретившегося элемента, равного z: " << ind;
    cout << endl << "Номер первого встретившегося элемента, равного z: " << ind + 1 << endl;
}

void interpol_search() {
    setlocale(LC_ALL, "RU");
    int first, step, z, count = 0, ind;
    const int size = 10;
    int arr[size];
    cout << "\nПОИСК ЭЛЕМЕНТА ИНТЕРПОЛЯЦИОННЫМ МЕТОДОМ (требует отсортированный и равномерный массив)"
        << "\n-----------------" << "\nМассив состоит из 10 элементов" << endl;

    cout << "Введите первый элемент массива: ";
    cin >> first;
    cout << "Введите шаг: ";
    cin >> step;

    arr[0] = first;
    for (int i = 1; i < size; i++) {
        arr[i] = arr[i - 1] + step;
    }

    cout << "Ваш массив: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    cout << "\n\nВведите z - элемент, который необходимо найти в массиве: ";
    cin >> z;

    int left = 0;
    int right = size - 1;

    bool ascending = (step > 0);

    while (left <= right &&
        ((ascending && z >= arr[left] && z <= arr[right]) ||
            (!ascending && z <= arr[left] && z >= arr[right]))) {

        if (arr[right] == arr[left]) {
            if (arr[left] == z) {
                count = right - left + 1;
                ind = left;
            }
            break;
        }

        int pos = left + ((z - arr[left]) * (right - left)) / (arr[right] - arr[left]);

        if (pos < left || pos > right) {
            break;
        }

        if (arr[pos] == z) {
            count++;
            ind = pos;

            int temp = pos - 1;
            while (temp >= 0 && arr[temp] == z) {
                count++;
                ind = temp;
                temp--;
            }
            temp = pos + 1;
            while (temp < size && arr[temp] == z) {
                count++;
                temp++;
            }

            break;
        }
        else if ((ascending && arr[pos] < z) || (!ascending && arr[pos] > z)) {
            left = pos + 1;
        }
        else {
            right = pos - 1;
        }
    }

    if (count == 0) {
        cout << "Элемент " << z << " не найден в массиве" << endl;
    }
    else {
        cout << endl << "Результаты поиска:" << endl;
        cout << "Количество элементов, равных " << z << ": " << count << endl;
        cout << "Индекс первого вхождения: " << ind << endl;
        cout << "Порядковый номер первого вхождения: " << ind + 1 << endl;
    }
}

void substring_search() {
    setlocale(LC_ALL, "RU");
    string text, pattern;

    cout << "\nПРЯМОЙ ПОИСК ПОДСТРОКИ В СТРОКЕ" << "\n-----------------" << endl;

    cout << "Введите текст: ";
    cin.ignore();
    getline(cin, text);

    cout << "Введите подстроку для поиска: ";
    getline(cin, pattern);

    int n = text.length();
    int m = pattern.length();
    int count = 0;
    int firstPos = -1;

    cout << "\nТекст: \"" << text << "\"" << endl;
    cout << "Образец: \"" << pattern << "\"" << endl;

    if (m > n) {
        cout << "Ошибка: подстрока длиннее текста!" << endl;
        return;
    }

    if (m == 0) {
        cout << "Подстрока не может быть пустой!" << endl;
        return;
    }

    for (int i = 0; i <= n - m; i++) {
        bool found = true;

        for (int j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }

        if (found) {
            count++;
            if (firstPos == -1) {
                firstPos = i;
            }
        }
    }

    cout << "\n-----------------" << endl;
    cout << "РЕЗУЛЬТАТЫ ПОИСКА:" << endl;

    if (count == 0) {
        cout << "Подстрока \"" << pattern << "\" не найдена в тексте" << endl;
    }
    else {
        cout << "Найдено вхождений: " << count << endl;

        cout << "\nВизуализация первого вхождения:" << endl;
        cout << "Текст:     " << text << endl;
        cout << "Позиция:   ";
        for (int i = 0; i < firstPos; i++) cout << " ";
        cout << "^" << endl;
        cout << "Образец:   ";
        for (int i = 0; i < firstPos; i++) cout << " ";
        cout << pattern << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choose;
    char again;
    do {
        cout << "========================================" << endl;
        cout << "     МЕНЮ ПОИСКОВЫХ АЛГОРИТМОВ" << endl;
        cout << "========================================" << endl;
        cout << "1. Линейный поиск" << endl;
        cout << "2. Бинарный поиск (требует сортировку)" << endl;
        cout << "3. Интерполяционный поиск (требует сортировку и равномерность)" << endl;
        cout << "4. Поиск подстроки в строке" << endl;
        cout << "0. Выход из программы" << endl;
        cout << "========================================" << endl;
        cout << "Ваш выбор : ";
        cin >> choose;

        switch (choose) {
        case 1:
            linear_search();
            break;
        case 2:
            binary_search();
            break;
        case 3:
            interpol_search();
            break;
        case 4:
            substring_search();
            break;
        case 0:
            cout << "\nСпасибо за использование программы!" << endl;
            cout << "До свидания!" << endl;
            return 0;
        default:
            cout << "\nОшибка: такого варианта нет!" << endl;
            break;
        }

        cout << "\n========================================" << endl;
        cout << "Желаете выполнить другой поиск? (y/n): ";
        cin >> again;
        cout << "========================================" << endl;

        cin.ignore();

    } while (again == 'y' || again == 'Y');

    cout << "\nСпасибо за использование программы!" << endl;
    cout << "До свидания!" << endl;

    return 0;
}