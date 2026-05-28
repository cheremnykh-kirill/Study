#include <iostream>
#include <clocale>
#include <string>
#include <windows.h>
using namespace std;

// Функция для вывода массива
void printArray(int arr[], int size, int highlight1 = -1, int highlight2 = -1, int pivot = -1, const string& message = "") {
    if (!message.empty()) {
        cout << message << endl;
    }
    cout << "Массив: [";
    for (int i = 0; i < size; i++) {
        if (i == highlight1 || i == highlight2) {
            cout << "[" << arr[i] << "]";
        }
        else if (i == pivot) {
            cout << "(" << arr[i] << ")";
        }
        else {
            cout << arr[i];
        }

        if (i < size - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    if (highlight1 != -1 || highlight2 != -1 || pivot != -1) {
        cout << "  (Обозначения: [x] - сравниваемый/выделенный, (x) - опорный)" << endl;
    }
}

// Функция для вывода разделителя
void printSeparator() {
    cout << "--------------------------------------------------" << endl;
}

// Функция для ввода массива
int* inputArray(int& size) {
    cout << "Введите размер массива: ";
    cin >> size;
    while (size <= 0) {
        cout << "Размер должен быть положительным! Введите заново: ";
        cin >> size;
    }
    int* arr = new int[size];
    cout << "Введите " << size << " элементов массива:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "arr[" << i << "] = ";
        cin >> arr[i];
    }
    return arr;
}

// а) Сортировка Шелла
void shellSortDemo() {
    cout << "\nСортировка Шелла" << endl;
    cout << "===============================" << endl;
    int size;
    int* A = inputArray(size);
    cout << "\nИсходный массив:" << endl;
    printArray(A, size);
    cout << "\nОписание алгоритма:" << endl;
    cout << "1. Выбираем начальный шаг (step)" << endl;
    cout << "2. Разбиваем массив на подсписки с этим шагом" << endl;
    cout << "3. Сортируем каждый подсписок методом вставки" << endl;
    cout << "4. Уменьшаем шаг и повторяем, пока шаг не станет равным 1" << endl;
    printSeparator();
    // Вычисляем начальный шаг (последовательность Кнута: h = 3*h + 1)
    int step = 1;
    while (step < size / 3) {
        step = 3 * step + 1;
    }
    cout << "\nНачальный шаг: " << step << endl;
    int iteration = 1;
    while (step > 0) {
        cout << "\n========================================" << endl;
        cout << "Итерация " << iteration << " (шаг = " << step << ")" << endl;
        cout << "========================================" << endl;
        // Показываем подсписки
        cout << "\nПодсписки с шагом " << step << ":" << endl;
        for (int start = 0; start < step; start++) {
            cout << "  Список " << start << ": [";
            bool first = true;
            for (int i = start; i < size; i += step) {
                if (!first) cout << ", ";
                cout << A[i];
                first = false;
            }
            cout << "]" << endl;
        }
        // Сортировка вставками для каждого подсписка
        for (int start = 0; start < step; start++) {
            cout << "\nСортируем список " << start << " методом вставки:" << endl;
            for (int i = start + step; i < size; i += step) {
                int key = A[i];
                int j = i - step;
                cout << "  Вставляем элемент " << key << " (индекс " << i << "):" << endl;
                printArray(A, size, i, -1, -1, "  Текущий массив:");
                while (j >= start && A[j] > key) {
                    cout << "    " << A[j] << " > " << key << ", сдвигаем " << A[j] << " вправо" << endl;
                    A[j + step] = A[j];
                    j -= step;
                    printArray(A, size, j + step, i, -1, "    После сдвига:");
                }
                A[j + step] = key;
                cout << "    Вставили " << key << " на позицию " << j + step << endl;
                printArray(A, size, j + step, -1, -1, "    После вставки:");
            }
        }
        cout << "\nМассив после итерации с шагом " << step << ":" << endl;
        printArray(A, size);
        printSeparator();
        // Уменьшаем шаг
        step = (step - 1) / 3;
        iteration++;
    }
    cout << "\n========================================" << endl;
    cout << "Сортировка окончена!" << endl;
    cout << "========================================" << endl;
    cout << "Отсортированный массив:" << endl;
    printArray(A, size);
    delete[] A;
}

// б) Сортировка Хоара
int hoarePartition(int arr[], int low, int high, int size) {
    int pivot = arr[(low + high) / 2];
    int i = low - 1;
    int j = high + 1;
    cout << "\nШаг: разделение Хоара" << endl;
    cout << "Опорный элемент: " << pivot << " (в середине)" << endl;
    cout << "Диапазон: от индекса " << low << " до " << high << endl;
    printArray(arr, size, -1, -1, (low + high) / 2, "Текущий массив:");
    while (true) {
        do { // Двигаем i вправо, пока элемент меньше опорного
            i++;
            cout << "\nДвигаем i: arr[" << i << "] = " << arr[i];
            if (arr[i] < pivot) {
                cout << " < " << pivot << ", продолжаем" << endl;
            }
            else {
                cout << " >= " << pivot << ", останавливаемся" << endl;
            }
            printArray(arr, size, i, -1, (low + high) / 2);
        } while (arr[i] < pivot);
        do { // Двигаем j влево, пока элемент больше опорного
            j--;
            cout << "\nДвигаем j: arr[" << j << "] = " << arr[j];
            if (arr[j] > pivot) {
                cout << " > " << pivot << ", продолжаем" << endl;
            }
            else {
                cout << " <= " << pivot << ", останавливаемся" << endl;
            }
            printArray(arr, size, -1, j, (low + high) / 2);
        } while (arr[j] > pivot);
        if (i >= j) {
            cout << "\ni (" << i << ") >= j (" << j << "), разделение завершено" << endl;
            cout << "Точка разделения: " << j << endl;
            return j;
        }
        // Меняем местами arr[i] и arr[j]
        cout << "\nМеняем местами arr[" << i << "]=" << arr[i] << " и arr[" << j << "]=" << arr[j] << endl;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        printArray(arr, size, i, j, (low + high) / 2, "После обмена:");
    }
}

void hoareQuickSort(int arr[], int low, int high, int size) {
    if (low < high) {
        cout << "\n========================================" << endl;
        cout << "Вызов сортировки Хоара" << endl;
        cout << "Сортируем подмассив с индексами [" << low << ".." << high << "]" << endl;
        cout << "========================================" << endl;
        int pi = hoarePartition(arr, low, high, size);
        cout << "\nРекурсивно сортируем левую часть [" << low << ".." << pi << "]" << endl;
        hoareQuickSort(arr, low, pi, size);
        cout << "\nРекурсивно сортируем правую часть [" << pi + 1 << ".." << high << "]" << endl;
        hoareQuickSort(arr, pi + 1, high, size);
    }
}

void hoareSortDemo() {
    cout << "\nСортировка Хоара" << endl;
    cout << "=================================================" << endl;
    int size;
    int* A = inputArray(size);
    cout << "\nИсходный массив:" << endl;
    printArray(A, size);
    cout << "\nОписание алгоритма:" << endl;
    cout << "1. Выбираем опорный элемент в середине массива" << endl;
    cout << "2. Двигаем i слева направо, пока элемент < опорного" << endl;
    cout << "3. Двигаем j справа налево, пока элемент > опорного" << endl;
    cout << "4. Если i <= j, меняем элементы местами" << endl;
    cout << "5. Повторяем рекурсивно для полученных частей" << endl;
    printSeparator();
    hoareQuickSort(A, 0, size - 1, size);
    cout << "\n========================================" << endl;
    cout << "Сортировка окончена!" << endl;
    cout << "========================================" << endl;
    cout << "Отсортированный массив:" << endl;
    printArray(A, size);
    delete[] A;
}

// в) Сортировка Лмута
int lomutoPartition(int arr[], int low, int high, int size) {
    int pivot = arr[high];
    int i = low - 1;
    cout << "\nШаг: разделение Ломуто" << endl;
    cout << "Опорный элемент: " << pivot << " (последний, индекс " << high << ")" << endl;
    cout << "Диапазон: от индекса " << low << " до " << high << endl;
    printArray(arr, size, -1, -1, high, "Текущий массив:");
    for (int j = low; j < high; j++) {
        cout << "\nСравниваем arr[" << j << "] = " << arr[j] << " с опорным " << pivot << endl;
        printArray(arr, size, j, -1, high);
        if (arr[j] < pivot) {
            i++;
            if (i != j) {
                cout << "  " << arr[j] << " < " << pivot << ", меняем местами arr[" << i << "]=" << arr[i] << " и arr[" << j << "]=" << arr[j] << endl;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                printArray(arr, size, i, j, high, "  После обмена:");
            }
            else {
                cout << "  " << arr[j] << " < " << pivot << ", элемент остается на месте" << endl;
            }
        }
        else {
            cout << "  " << arr[j] << " >= " << pivot << ", оставляем справа" << endl;
        }
    }
    if (i + 1 != high) { // Помещаем опорный элемент на правильную позицию
        cout << "\nПомещаем опорный элемент на позицию " << i + 1 << ":" << endl;
        cout << "Меняем arr[" << i + 1 << "]=" << arr[i + 1] << " и arr[" << high << "]=" << arr[high] << endl;
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        printArray(arr, size, i + 1, -1, i + 1, "После размещения опорного элемента:");
    }
    cout << "\nРезультат разделения:" << endl;
    cout << "Элемент " << pivot << " теперь на позиции " << i + 1 << endl;
    cout << "Слева - элементы < " << pivot << ", справа - элементы >= " << pivot << endl;
    printArray(arr, size, -1, -1, i + 1);
    printSeparator();
    return i + 1;
}

void lomutoQuickSort(int arr[], int low, int high, int size) {
    if (low < high) {
        cout << "\n========================================" << endl;
        cout << "Вызов сортировки Ломута" << endl;
        cout << "Сортируем подмассив с индексами [" << low << ".." << high << "]" << endl;
        cout << "========================================" << endl;
        int pi = lomutoPartition(arr, low, high, size);
        cout << "\nРекурсивно сортируем левую часть [" << low << ".." << pi - 1 << "]" << endl;
        lomutoQuickSort(arr, low, pi - 1, size);
        cout << "\nРекурсивно сортируем правую часть [" << pi + 1 << ".." << high << "]" << endl;
        lomutoQuickSort(arr, pi + 1, high, size);
    }
}

void lomutoSortDemo() {
    cout << "\nСортировка Ломута" << endl;
    cout << "===================================================" << endl;
    int size;
    int* A;
    A = inputArray(size);
    cout << "\nИсходный массив:" << endl;
    printArray(A, size);
    cout << "\nОписание алгоритма:" << endl;
    cout << "1. Выбираем опорный элемент (последний в подмассиве)" << endl;
    cout << "2. Все элементы < опорного размещаем слева" << endl;
    cout << "3. Все элементы >= опорного остаются справа" << endl;
    cout << "4. Помещаем опорный элемент между частями" << endl;
    cout << "5. Рекурсивно повторяем для левой и правой частей" << endl;
    printSeparator();
    lomutoQuickSort(A, 0, size - 1, size);
    cout << "\n========================================" << endl;
    cout << "Сортировка окончена!" << endl;
    cout << "========================================" << endl;
    cout << "Отсортированный массив:" << endl;
    printArray(A, size);
    delete[] A;
}

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choose;
    char again;
    do {
        cout << "\n========================================" << endl;
        cout << "    МЕНЮ СЛОЖНЫХ МЕТОДОВ СОРТИРОВКИ" << endl;
        cout << "========================================" << endl;
        cout << "1. Сортировка Шелла" << endl;
        cout << "2. Сортировка Хоара" << endl;
        cout << "3. Сортировка Ломуто" << endl;
        cout << "0. Выход из программы" << endl;
        cout << "========================================" << endl;
        cout << "Ваш выбор: ";
        cin >> choose;
        switch (choose) {
        case 1:
            shellSortDemo();
            break;
        case 2:
            hoareSortDemo();
            break;
        case 3:
            lomutoSortDemo();
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
        cout << "Желаете выполнить другую сортировку? (y/n): ";
        cin >> again;
        cout << "========================================" << endl;
        cin.ignore();

    } while (again == 'y' || again == 'Y');

    cout << "\nСпасибо за использование программы!" << endl;
    cout << "До свидания!" << endl;
    return 0;
}