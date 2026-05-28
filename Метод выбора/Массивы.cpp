#include <iostream>
#include <clocale>
#include <cstdlib>
using namespace std;
int main() {
	setlocale(LC_ALL, "RU");
	const int max_size = 100;
	int n;
	cout << "Введите размер вашего массива, он должен быть не больше " << max_size << ": ";
	cin >> n;
	if (n > max_size || n <= 0) {
		cout << "Ошибка! Некорректный размер массива!";
	}
	else {
		cout << "Введите ваш массив: ";
		int arr[max_size];
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}
		cout << "Искомый массив: ";
		for (int i = 0; i < n; i++) {
			cout << arr[i] << ", ";
		}
		cout << endl << endl;
		for (int i = 0; i < n; i++) {
			cout << "Шаг " << i + 1 << endl;
			int min = i;
			cout << "Отсортированная часть:  ";
			for (int k = 0; k < i; k++) {
				cout << arr[k] << " ";
			}
			cout << " |  Неотсортированная часть:  ";
			for (int k = i; k < n; k++) {
				cout << arr[k] << " ";
			}
			cout << endl;
			for (int j = i + 1; j < n; j++) {
				if (arr[j] < arr[min]) {
					min = j;
				}
			}
			cout << "Минимальный элемент на этом шаге: " << arr[min] << endl;
			if (min != i) {
				int temp = arr[i];
				arr[i] = arr[min];
				arr[min] = temp;
			}
		}
		cout << endl;
		cout << "Отсортированный массив: ";
		for (int i = 0; i < n; i++) {
			cout << arr[i] << ", ";
		}
	}
	return 0;
}

