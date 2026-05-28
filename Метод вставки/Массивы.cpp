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
		cout << "Сгенерированный массив: ";
		for (int i = 0; i < n; i++) {
			cout << arr[i] << ", ";
		}
		cout << endl;
		for (int i = 1; i < n; i++) {
			int temp = arr[i];
			cout << "Отсортированная часть: ";
			for (int k = 0; k < i; k++) {
				cout << arr[k] << " ";
			}
			cout << "| Неотсортированная часть: ";
			for (int k = i; k < n; k++) {
				cout << arr[k] << " ";
			}
			cout << endl;
			int j = i - 1;
			bool flag = false;
			while (j >= 0 && !flag) {
				if (arr[j] > temp) {
					arr[j + 1] = arr[j];
					j--;
				}
				else {
					flag = true;
				}
			}
			arr[j + 1] = temp;
		}
		cout << endl;
		cout << "Отсортированный массив: ";
		for (int i = 0; i < n; i++) {
			cout << arr[i] << ", ";
		}
	}
	return 0;
}