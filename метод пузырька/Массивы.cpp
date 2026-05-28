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
			cout << "Отсортированная часть: ";
			for (int k = 0; k < i; k++) {
				cout << arr[k] << " ";
			}
			cout << "| Неотсортированная часть: ";
			for (int k = i; k < n; k++) {
				cout << arr[k] << " ";
			}
			cout << endl;
			bool flag = false;
			for (int j = 0; j < n - i - 1; j++) {
				cout << "Сравниваем " << arr[j] << " и " << arr[j + 1] << endl;
				if (arr[j] > arr[j + 1]) {
					int temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
					flag = true;
					cout << "Меняем местами " << arr[j] << " и " << arr[j + 1] << endl;
				}
				if (!flag) {
					cout << "Обменов не было. " << arr[j] << " переносим в отсортированную часть" << endl;
				}
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