#include <iostream>
#include <clocale>
using namespace std;

int** DeleteElements(int** arr, int& rows, int cols) {
	int new_rows = 0;

	for (int i = 0; i < rows; i++) {
		if ((i+1) % 2 == 1) {
			new_rows++;
		}
	}

	int** new_arr = new int* [new_rows];
	int new_idx = 0;

	for (int i = 0; i < rows; i++) {
		if ((i+1) % 2 == 1) {
			new_arr[new_idx] = new int[cols];
			for (int j = 0; j < cols; j++) {
				new_arr[new_idx][j] = arr[i][j];
			}
			new_idx++;
		}
	}

	for (int i = 0; i < rows; i++) {
		delete[] arr[i];
	}

	delete[] arr;
	rows = new_rows;
	return new_arr;
}

int* DeleteElements(int arr[], int& size) {
	int first = -1, second = -1;

	for (int i = 0; i < size; i++) {
		if (arr[i] == 0) {
			first = i;
			break;
		}
	}

	if (first != -1) {
		for (int i = first + 1; i < size; i++) {
			if (arr[i] == 0) {
				second = i;
				break;
			}
		}
	}

	if (first == -1 || second == -1) {
		cout << "Двух нулей не найдено! Массив остался прежним" << endl;
		return arr; 
	}

	int new_size = size - (second - first - 1);
	int* new_arr = new int[new_size];
	int new_idx = 0;

	for (int i = 0; i <= first; i++) {
		new_arr[new_idx++] = arr[i];
	}

	for (int i = second; i < size; i++) {
		new_arr[new_idx++] = arr[i];
	}

	delete[] arr; 
	size = new_size;
	return new_arr;
}


int main() {
	setlocale(LC_ALL, "ru");
	int n, k;
	cout << "====================Работа с двумерным массивом====================" << endl << endl;
	cout << "Введите количество строк в двумерном массиве: ";
	cin >> n;
	cout << "Введите количество столбцов в двумерном массиве: ";
	cin >> k;
	cout << "Введите ваш двумерный массив: " << endl;
	int** arr2 = new int*[n];

	for (int i = 0; i < n; i++) {
		arr2[i] = new int[k];
		cout << "Введите " << k << " элементов для строки " << i + 1 << ": ";
		for (int j = 0; j < k; j++) {
			cin >> arr2[i][j];
		}
	}

	cout << "Исходный двумерный массив: " << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			cout << arr2[i][j] << "\t";
		}
		cout << endl;
	}

	cout << "Двумерный массив после удаления чётных строк: " << endl;
	arr2 = DeleteElements(arr2, n, k);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			cout << arr2[i][j] << "\t";
		}
		cout << endl;
	}

	cout << "====================================================================" << endl << endl;
	cout << "====================Работа с одномерным массивом====================" << endl << endl;
	int size = 0;
	cout << "Введите размер одномерного массива: ";
	cin >> size;
	int* arr1 = new int[size];
	cout << "Введите свой одномерный массив: ";
	
	for (int i = 0; i < size; i++) {
		cin >> arr1[i];
	}
	
	cout << "Исходный одномерный массив : ";
	
	for (int i = 0; i < size; i++) {
		cout << arr1[i] << " ";
	}

	cout << endl;
	arr1 = DeleteElements(arr1, size);
	cout << "Результат удаления чисел между двумя нолями: " ;
	
	for (int i = 0; i < size; i++) {
		cout << arr1[i] << " ";
	}

	delete[] arr1;
	cout << endl<< endl << "====================================================================";
	
	for (int i = 0; i < n; i++) {
		delete[] arr2[i];
	}

	delete[] arr2;
	return 0;
}