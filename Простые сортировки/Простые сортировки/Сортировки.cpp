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
        cout << "  (Обозначения: [x] - сравниваемый, (x) - опорный)" << endl;
    }
}

void printSeparator() { // Функция для вывода разделителя
    cout << "--------------------------------------------------" << endl;
}

int* inputArray(int& size) { // Функция для ввода массива
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

// а) Быстрая сортировка
int partition(int arr[], int low, int high, int size) {
    int pivot = arr[high];
    int i = low - 1;
    cout << "\nШаг: разделение массива" << endl;
    cout << "Опорный элемент: " << pivot << " (индекс " << high << ")" << endl;
    cout << "Диапазон: от индекса " << low << " до " << high << endl;
    printArray(arr, size, -1, -1, high, "Текущий массив:");
    for (int j = low; j < high; j++) {
        cout << "\nСравниваем arr[" << j << "] = " << arr[j] << " с опорным " << pivot << endl;
        printArray(arr, size, j, -1, high);
        if (arr[j] <= pivot) {
            i++;
            if (i != j) {
                cout << "  " << arr[j] << " <= " << pivot << ", меняем местами arr[" << i << "]=" << arr[i] << " и arr[" << j << "]=" << arr[j] << endl;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                printArray(arr, size, i, j, high, "  После обмена:");
            }
            else {
                cout << "  " << arr[j] << " <= " << pivot << ", элемент остается на месте" << endl;
            }
        }
        else {
            cout << "  " << arr[j] << " > " << pivot << ", оставляем на месте" << endl;
        }
    }
    if (i + 1 != high) {
        cout << "\nПомещаем опорный элемент на правильную позицию:" << endl;
        cout << "Меняем arr[" << i + 1 << "]=" << arr[i + 1] << " и arr[" << high << "]=" << arr[high] << endl;
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        printArray(arr, size, i + 1, -1, i + 1, "После размещения опорного элемента:");
    }
    cout << "\nРезультат разделения:" << endl;
    cout << "Элемент " << pivot << " теперь на позиции " << i + 1 << endl;
    cout << "Слева - элементы <= " << pivot << ", справа - элементы >= " << pivot << endl;
    printArray(arr, size, -1, -1, i + 1);
    printSeparator();
    return i + 1;
}

void quickSort(int arr[], int low, int high, int size) {
    if (low < high) {
        cout << "\n========================================" << endl;
        cout << "Вызов быстрой сортировки" << endl;
        cout << "Сортируем подмассив с индексами [" << low << ".." << high << "]" << endl;
        cout << "========================================" << endl;
        int pi = partition(arr, low, high, size);
        cout << "\nРекурсивно сортируем левую часть [" << low << ".." << pi - 1 << "]" << endl;
        quickSort(arr, low, pi - 1, size);
        cout << "\nРекурсивно сортируем правую часть [" << pi + 1 << ".." << high << "]" << endl;
        quickSort(arr, pi + 1, high, size);
    }
}

void quickSortDemo() {
    cout << "\nБыстрая сортировка" << endl;
    cout << "=================================" << endl;
    int size;
    int* A = inputArray(size);
    cout << "\nИсходный массив:" << endl;
    printArray(A, size);
    cout << "\nОписание алгоритма:" << endl;
    cout << "1. Выбираем опорный элемент (последний в подмассиве)" << endl;
    cout << "2. Разделяем массив: слева - меньшие элементы, справа - большие" << endl;
    cout << "3. Рекурсивно применяем алгоритм к левой и правой частям" << endl;
    printSeparator();
    quickSort(A, 0, size - 1, size);
    cout << "\n========================================" << endl;
    cout << "Сортировка окончена!" << endl;
    cout << "========================================" << endl;
    cout << "Отсортированный массив:" << endl;
    printArray(A, size);
    delete[] A;
}

// б) Сортировка подсчётом
void countingSortDemo() {
    cout << "\nСортировка подсчётом" << endl;
    cout << "======================================" << endl;
    int size;
    int* A = inputArray(size);
    cout << "\nИсходный массив:" << endl;
    printArray(A, size);
    cout << "\nШаг 1: Находим минимальный и максимальный элементы" << endl;
    int max = A[0], min = A[0];
    for (int i = 1; i < size; i++) {
        if (A[i] > max) max = A[i];
        if (A[i] < min) min = A[i];
    }
    cout << "min = " << min << ", max = " << max << endl;
    cout << "\nШаг 2: Вычисляем размер вспомогательного массива" << endl;
    int countSize = max - min + 1;
    cout << "size = max - min + 1 = " << max << " - " << min << " + 1 = " << countSize << endl;
    cout << "\nШаг 3: Создаём массив B для подсчёта частот" << endl;
    int* B = new int[countSize];
    for (int i = 0; i < countSize; i++) {
        B[i] = 0;
    }
    cout << "Подсчитываем количество вхождений каждого значения:" << endl;
    for (int i = 0; i < size; i++) {
        int index = A[i] - min;
        B[index]++;
        cout << "  Встретили " << A[i] << " -> B[" << index << "] = " << B[index] << endl;
    }
    cout << "\nМассив частот B: [";
    for (int i = 0; i < countSize; i++) {
        cout << B[i];
        if (i < countSize - 1) cout << ", ";
    }
    cout << "]" << endl;
    printSeparator();
    cout << "\nШаг 4: Заполняем исходный массив в соответствии с частотами" << endl;
    int index = 0;
    for (int i = 0; i < countSize; i++) {
        if (B[i] > 0) {
            cout << "Значение " << (i + min) << " встречается " << B[i] << " раз(а)" << endl;
            for (int j = 0; j < B[i]; j++) {
                A[index] = i + min;
                index++;
                cout << "  A[" << index - 1 << "] = " << (i + min) << " -> ";
                printArray(A, size);
            }
        }
    }
    delete[] B;
    cout << "\n========================================" << endl;
    cout << "Сортировка окончкна!" << endl;
    cout << "========================================" << endl;
    cout << "Отсортированный массив:" << endl;
    printArray(A, size);

    delete[] A;
}

// в) Ссортировка слиянием
void merge(int arr[], int left, int mid, int right, int size) {
    cout << "\nСлияние подмассивов [" << left << ".." << mid << "] и [" << mid + 1 << ".." << right << "]" << endl;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    cout << "Левый подмассив: [";
    for (int i = 0; i < n1; i++) {
        cout << L[i];
        if (i < n1 - 1) cout << ", ";
    }
    cout << "]" << endl;
    cout << "Правый подмассив: [";
    for (int j = 0; j < n2; j++) {
        cout << R[j];
        if (j < n2 - 1) cout << ", ";
    }
    cout << "]" << endl;
    int i = 0, j = 0, k = left;
    cout << "\nПроцесс слияния:" << endl;
    while (i < n1 && j < n2) {
        cout << "Сравниваем L[" << i << "]=" << L[i] << " и R[" << j << "]=" << R[j] << " -> ";
        if (L[i] <= R[j]) {
            cout << "берём " << L[i] << " из левого подмассива" << endl;
            arr[k] = L[i];
            i++;
        }
        else {
            cout << "берём " << R[j] << " из правого подмассива" << endl;
            arr[k] = R[j];
            j++;
        }
        k++;
        printArray(arr, size);
    }
    while (i < n1) {
        cout << "Добавляем оставшийся элемент " << L[i] << " из левого подмассива" << endl;
        arr[k] = L[i];
        i++;
        k++;
        printArray(arr, size);
    }
    while (j < n2) {
        cout << "Добавляем оставшийся элемент " << R[j] << " из правого подмассива" << endl;
        arr[k] = R[j];
        j++;
        k++;
        printArray(arr, size);
    }
    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right, int size) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        cout << "\n========================================" << endl;
        cout << "Делим массив [" << left << ".." << right << "]" << endl;
        cout << "Середина: индекс " << mid << endl;
        cout << "Левая часть: [" << left << ".." << mid << "]" << endl;
        cout << "Правая часть: [" << mid + 1 << ".." << right << "]" << endl;
        cout << "========================================" << endl;
        mergeSort(arr, left, mid, size);
        mergeSort(arr, mid + 1, right, size);
        merge(arr, left, mid, right, size);
    }
}

void mergeSortDemo() {
    cout << "\nСортировка слиянием" << endl;
    cout << "=================================" << endl;
    int size;
    int* A = inputArray(size);
    cout << "\nИсходный массив:" << endl;
    printArray(A, size);
    cout << "\nОписание алгоритма:" << endl;
    cout << "1. Рекурсивно делим массив пополам, пока не останутся единичные элементы" << endl;
    cout << "2. Сливаем отсортированные подмассивы в правильном порядке" << endl;
    printSeparator();
    mergeSort(A, 0, size - 1, size);
    cout << "\n========================================" << endl;
    cout << "Сортировка окончена!" << endl;
    cout << "========================================" << endl;
    cout << "Отсортированный массив:" << endl;
    printArray(A, size);
    delete[] A;
}

// г) Блочная сортировка
void bucketSortDemo() {
    cout << "\nБлочная сортировка" << endl;
    cout << "=================================" << endl;
    int size;
    int* A = inputArray(size);
    cout << "\nИсходный массив:" << endl;
    printArray(A, size);
    cout << "\nШаг 1: Находим максимальный и минимальный элементы" << endl;
    int max = A[0], min = A[0];
    for (int i = 1; i < size; i++) {
        if (A[i] > max) max = A[i];
        if (A[i] < min) min = A[i];
    }
    cout << "min = " << min << ", max = " << max << endl;
    int bucketCount;  // Количество блоков
    cout << "\nВведите количество блоков (рекомендуется 3-5): ";
    cin >> bucketCount;
    if (bucketCount <= 0) bucketCount = 3;
    cout << "\nШаг 2: Создаём " << bucketCount << " блоков" << endl;
    // Создаём блоки как динамические массивы
    int** buckets = new int* [bucketCount];
    int* bucketSizes = new int[bucketCount];
    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = new int[size];
        bucketSizes[i] = 0;
    }
    cout << "\nШаг 3: Распределяем элементы по блокам" << endl;
    int range = max - min + 1;
    for (int i = 0; i < size; i++) {
        int bucketIndex = ((A[i] - min) * bucketCount) / range;
        if (bucketIndex >= bucketCount) bucketIndex = bucketCount - 1;
        buckets[bucketIndex][bucketSizes[bucketIndex]] = A[i];
        bucketSizes[bucketIndex]++;
        cout << "Элемент " << A[i] << " -> блок " << bucketIndex << endl;
    }
    cout << "\nСодержимое блоков:" << endl;
    for (int i = 0; i < bucketCount; i++) {
        cout << "Блок " << i << ": [";
        for (int j = 0; j < bucketSizes[i]; j++) {
            cout << buckets[i][j];
            if (j < bucketSizes[i] - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    printSeparator();
    cout << "\nШаг 4: Сортируем каждый блок (сортировка вставками)" << endl;
    for (int b = 0; b < bucketCount; b++) {
        if (bucketSizes[b] > 0) {
            cout << "Сортируем блок " << b << ":" << endl;
            // Сортировка вставками для блока
            for (int i = 1; i < bucketSizes[b]; i++) {
                int key = buckets[b][i];
                int j = i - 1;
                while (j >= 0 && buckets[b][j] > key) {
                    buckets[b][j + 1] = buckets[b][j];
                    j--;
                }
                buckets[b][j + 1] = key;
            }
            cout << "  Отсортированный блок " << b << ": [";
            for (int j = 0; j < bucketSizes[b]; j++) {
                cout << buckets[b][j];
                if (j < bucketSizes[b] - 1) cout << ", ";
            }
            cout << "]" << endl;
        }
    }
    cout << "\nШаг 5: Объединяем блоки в отсортированный массив" << endl;
    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 0; j < bucketSizes[i]; j++) {
            A[index] = buckets[i][j];
            index++;
            cout << "Добавляем " << buckets[i][j] << " из блока " << i << " -> ";
            printArray(A, size);
        }
    }
    for (int i = 0; i < bucketCount; i++) {
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucketSizes;
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
        cout << "     МЕНЮ БЫСТРЫХ МЕТОДОВ СОРТИРОВКИ" << endl;
        cout << "========================================" << endl;
        cout << "1. Быстрая сортировка" << endl;
        cout << "2. Сортировка подсчётом" << endl;
        cout << "3. Сортировка слиянием" << endl;
        cout << "4. Блочная сортировка" << endl;
        cout << "0. Выход из программы" << endl;
        cout << "========================================" << endl;
        cout << "Ваш выбор: ";
        cin >> choose;
        switch (choose) {
        case 1:
            quickSortDemo();
            break;
        case 2:
            countingSortDemo();
            break;
        case 3:
            mergeSortDemo();
            break;
        case 4:
            bucketSortDemo();
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