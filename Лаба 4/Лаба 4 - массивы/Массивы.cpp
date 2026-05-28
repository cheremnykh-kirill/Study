#include <iostream>
#include <clocale>
#include <cstdlib>
using namespace std;
int main() {
	setlocale(LC_ALL, "RU");
	int n;
	int k;
	int a;
	const int max_size = 100;
	int arr[max_size];
	int ring[max_size];
	cout << "Введите размер вашего массива, не больше 100: ";
	cin >> n;
	cout << endl;
	cout << "Введите начальный индекс k: ";
	cin >> k;
	cout << endl;
	if (n > max_size || n <= 0) {
		cout << "Ошибка! Некорректный размер массива!";
	}
	else {
		cout << "Хотите заполнить массив сами или через rand? (1 - сами, 2 - через rand): ";
		cin >> a;
		cout << endl;
		if (a == 1) {
			cout << "Заполните ваш массив: ";
			for (int i = 0; i < n; i++) {
				cin >> arr[i];
			}
		}
		else if (a == 2) {
			cout << "Ваш массив сгенерируется автоматически" << endl;
			for (int i = 0; i < n; i++) {
				arr[i] = -100 + rand() % 201;
			}
		}
		else if (a != 1 && a != 2) {
			cout << "ОШИБКА!";
			return 1;
		}
		cout << endl;
		cout << "Ваш исходный массив: ";
		for (int i = 0; i < n; i++) {
			cout << arr[i] << ", ";
		}
		cout << endl << endl;
		cout << "Первое кольцо (справа налево, начиная с k = " << k << "): ";
		k = k % n;
		if (k < 0) {
			k += n;
		}
		int ind = 0;
		for (int i = k; i >= 0; i--) {
			ring[ind] = arr[i];
			ind++;
		}
		for (int i = n - 1; i > k; i--) {
			ring[ind] = arr[i];
			ind++;
		}
		for (int i = 0; i < n; i++) {
			cout << ring[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < n; i++) {
			arr[i] = ring[i];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - i - 1; j++) {
				if (arr[j] < arr[j + 1]) {
					int temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}
		cout << endl;
		cout << "Отсортированный массив: ";
		for (int i = 0; i < n; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
		int even = 0;
		for (int i = 0; i < n; i++) {
			if (arr[i] % 2 == 0) {
				arr[even] = arr[i];
				even++;
			}
		}
		n = even;
		cout << endl;
		if (n > 0) {
			k = k % n;
			if (k < 0) {
				k += n;
			}
			cout << "Второе кольцо (после удаления нечетных): ";
			int ind1 = 0;
			for (int i = k; i >= 0; i--) {
				ring[ind1] = arr[i];
				ind1++;
			}
			for (int i = n - 1; i > k; i--) {
				ring[ind1] = arr[i];
				ind1++;
			}
			for (int i = 0; i < n; i++) {
				cout << ring[i] << " ";
			}
			cout << endl;
		}
		else {
			cout << "Массив пуст после удаления нечетных элементов";
		}
	}
	return 0;
}

