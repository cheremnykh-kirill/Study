#include<iostream>
#include<clocale>
using namespace std;


int main() {
    setlocale(LC_ALL, "ru");
    int n, k;
    cout << "Введите количество строк в массиве: ";
    cin >> n;
    cout << "Введите количество слов в строке: ";
    cin >> k;
    char*** arr = new char** [n];
    for (int i = 0; i < n; i++) {
        arr[i] = new char* [k];
        for (int j = 0; j < k; j++) {
            arr[i][j] = new char[100];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cout << "Введите " << i + 1 << " строку " << j + 1 << " слово: ";
            cin >> arr[i][j];
        }
    }
    cout << endl;
    cout << "Исходный массив:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    int position;
    cout << endl << "Введите позицию, куда вставить новую строку (от 1 до " << n + 1 << "): ";
    cin >> position;
    while (position < 1 || position > n + 1) {
        cout << "Ошибка! Введите позицию от 1 до " << n + 1 << ": ";
        cin >> position;
    }
    char*** newarr = new char** [n + 1];
    for (int i = 0; i < n + 1; i++) {
        newarr[i] = new char* [k];
        for (int j = 0; j < k; j++) {
            newarr[i][j] = new char[100];
        }
    }
    for (int i = 0; i < position - 1; i++) {
        for (int j = 0; j < k; j++) {
            int l = 0;
            while (arr[i][j][l] != '\0') {
                newarr[i][j][l] = arr[i][j][l];
                l++;
            }
            newarr[i][j][l] = '\0';
        }
    }
    cout << endl <<"Введите новую строку:" << endl;
    for (int j = 0; j < k; j++) {
        cout << "Слово " << j + 1 << ": ";
        cin >> newarr[position - 1][j];
    }
    for (int i = position - 1; i < n; i++) {
        for (int j = 0; j < k; j++) {
            int l = 0;
            while (arr[i][j][l] != '\0') {
                newarr[i + 1][j][l] = arr[i][j][l];
                l++;
            }
            newarr[i + 1][j][l] = '\0';
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            delete[] arr[i][j];
        }
        delete[] arr[i];
    }
    delete[] arr;
    arr = newarr;
    n = n + 1;
    cout << endl << "Получившийся массив:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            delete[] arr[i][j];
        }
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}