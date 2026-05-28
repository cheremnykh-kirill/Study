#include <iostream>
#include <clocale>
#include <cmath>
#include <cstdarg>
using namespace std;


double FindLength(double x1, double y1, double x2, double y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}


double Square(double x1, double y1, double x2, double y2, double x3, double y3) {
	double a = FindLength(x1, y1, x2, y2);
	double b = FindLength(x2, y2, x3, y3);
	double c = FindLength(x3, y3, x1, y1);
	double p = (a + b + c) / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}


double Square1(int count, ...) {
	va_list args;
	va_start(args, count);
	double* x = new double[count];
	double* y = new double[count];
	for (int i = 0; i < count; i++) {
		x[i] = va_arg(args, double);
		y[i] = va_arg(args, double);
	}
	va_end(args);
	double max_d = 0;
	int d_start = 0;
	int d_end = 0;

	for (int i = 0; i < count; i++) {
		for (int j = i + 1; j < count; j++) {
			if (abs(i - j) > 1 && abs(i - j) < count - 1) {
				double d = FindLength(x[i], y[i], x[j], y[j]);
				if (d > max_d) {
					max_d = d;
					d_start = i;
					d_end = j;
				}
			}
		}
	}
	int third = -1;
	for (int i = 0; i < count; i++) {
		if (i != d_start && i != d_end) {
			third = i;
			break;
		}
	}
	double area = Square(x[d_start], y[d_start], x[d_end], y[d_end], x[third], y[third]);
	delete[] x;
	delete[] y;
	return area;
}


int main() {
	setlocale(LC_ALL, "ru");
	cout << "==========================================Проверка функции FindLength==========================================" << endl << endl;
	int x1, y1, x2, y2;
	cout << "Введите координаты точек: " << endl << "x1: ";
	cin >> x1;
	cout << "y1: ";
	cin >> y1;
	cout << "x2: ";
	cin >> x2;
	cout << "y2: ";
	cin >> y2;
	double length = FindLength(x1, y1, x2, y2);
	cout << "Длина стороны между (" << x1 << ", " << y1 << ") и (" << x2 << ", " << y2 << ") = " << length << endl<<endl;
	cout << "============================================Проверка функции Square============================================" << endl << endl;
	cout << "Введите координаты вершин треугольника: " << endl << "x1: ";
	int x3, y3, x4, y4, x5, y5;
	cin >> x3;
	cout << "y1: ";
	cin >> y3;
	cout << "x2: ";
	cin >> x4;
	cout << "y2: ";
	cin >> y4; 
	cout << "x3: ";
	cin >> x5;
	cout << "y3: ";
	cin >> y5;
	double s = Square(x3, y3, x4, y4, x5, y5);
	cout << "Площадь треугольника с вашими вершинами = " << s << endl << endl;
	cout << "============================================Проверка функции Square1===========================================" << endl << endl;
	int n;
	cout << "Введите количество углов многоугольника: " << endl;
	cin >> n;
	if (n <= 2 || n >= 9) {
		if (n <= 2) {
			cout << "Ошибка! У многоугольника минимум 3 вершины!";
		}
		else {
			cout << "Количество вершин большое! Я пока не придумал, как реализовать такой размер!";
		}
	}
	else {
		cout << "Введите координаты вершин многоугольника: " << endl;
		if (n == 3) {
			double x1, y1, x2, y2, x3, y3;
			cout << "Вершина 1 - x: ";
			cin >> x1;
			cout << "Вершина 1 - y: ";
			cin >> y1;
			cout << "Вершина 2 - x: ";
			cin >> x2;
			cout << "Вершина 2 - y: ";
			cin >> y2;
			cout << "Вершина 3 - x: ";
			cin >> x3;
			cout << "Вершина 3 - y: ";
			cin >> y3;

			double area = Square1(3, x1, y1, x2, y2, x3, y3);
			cout << "Площадь треугольника с наибольшей диагональю = " << area << endl;
		}
		else if (n == 4) {
			double x1, y1, x2, y2, x3, y3, x4, y4;
			cout << "Вершина 1 - x: ";
			cin >> x1;
			cout << "Вершина 1 - y: ";
			cin >> y1;
			cout << "Вершина 2 - x: ";
			cin >> x2;
			cout << "Вершина 2 - y: ";
			cin >> y2;
			cout << "Вершина 3 - x: ";
			cin >> x3;
			cout << "Вершина 3 - y: ";
			cin >> y3;
			cout << "Вершина 4 - x: ";
			cin >> x4;
			cout << "Вершина 4 - y: ";
			cin >> y4;

			double area = Square1(4, x1, y1, x2, y2, x3, y3, x4, y4);
			cout << "Площадь треугольника с наибольшей диагональю = " << area << endl;
		}
		else if (n == 5) {
			double x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;
			cout << "Вершина 1 - x: ";
			cin >> x1;
			cout << "Вершина 1 - y: ";
			cin >> y1;
			cout << "Вершина 2 - x: ";
			cin >> x2;
			cout << "Вершина 2 - y: ";
			cin >> y2;
			cout << "Вершина 3 - x: ";
			cin >> x3;
			cout << "Вершина 3 - y: ";
			cin >> y3;
			cout << "Вершина 4 - x: ";
			cin >> x4;
			cout << "Вершина 4 - y: ";
			cin >> y4;
			cout << "Вершина 5 - x: ";
			cin >> x5;
			cout << "Вершина 5 - y: ";
			cin >> y5;

			double area = Square1(5, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);
			cout << "Площадь треугольника с наибольшей диагональю = " << area << endl;
		}
		else if (n == 6) {
			double x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6;
			cout << "Вершина 1 - x: ";
			cin >> x1;
			cout << "Вершина 1 - y: ";
			cin >> y1;
			cout << "Вершина 2 - x: ";
			cin >> x2;
			cout << "Вершина 2 - y: ";
			cin >> y2;
			cout << "Вершина 3 - x: ";
			cin >> x3;
			cout << "Вершина 3 - y: ";
			cin >> y3;
			cout << "Вершина 4 - x: ";
			cin >> x4;
			cout << "Вершина 4 - y: ";
			cin >> y4;
			cout << "Вершина 5 - x: ";
			cin >> x5;
			cout << "Вершина 5 - y: ";
			cin >> y5;
			cout << "Вершина 6 - х: ";
			cin >> x6;
			cout << "Вершина 6 - y: ";
			cin >> y6;

			double area = Square1(5, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6);
			cout << "Площадь треугольника с наибольшей диагональю = " << area << endl;
		}
		else if (n == 7) {
			double x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7;
			cout << "Вершина 1 - x: ";
			cin >> x1;
			cout << "Вершина 1 - y: ";
			cin >> y1;
			cout << "Вершина 2 - x: ";
			cin >> x2;
			cout << "Вершина 2 - y: ";
			cin >> y2;
			cout << "Вершина 3 - x: ";
			cin >> x3;
			cout << "Вершина 3 - y: ";
			cin >> y3;
			cout << "Вершина 4 - x: ";
			cin >> x4;
			cout << "Вершина 4 - y: ";
			cin >> y4;
			cout << "Вершина 5 - x: ";
			cin >> x5;
			cout << "Вершина 5 - y: ";
			cin >> y5;
			cout << "Вершина 6 - х: ";
			cin >> x6;
			cout << "Вершина 6 - y: ";
			cin >> y6;
			cout << "Вершина 7 - х: ";
			cin >> x7;
			cout << "Вершина 7 - y: ";
			cin >> y7;

			double area = Square1(5, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7);
			cout << "Площадь треугольника с наибольшей диагональю = " << area << endl;
		}
		else if (n == 8) {
			double x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8;
			cout << "Вершина 1 - x: ";
			cin >> x1;
			cout << "Вершина 1 - y: ";
			cin >> y1;
			cout << "Вершина 2 - x: ";
			cin >> x2;
			cout << "Вершина 2 - y: ";
			cin >> y2;
			cout << "Вершина 3 - x: ";
			cin >> x3;
			cout << "Вершина 3 - y: ";
			cin >> y3;
			cout << "Вершина 4 - x: ";
			cin >> x4;
			cout << "Вершина 4 - y: ";
			cin >> y4;
			cout << "Вершина 5 - x: ";
			cin >> x5;
			cout << "Вершина 5 - y: ";
			cin >> y5;
			cout << "Вершина 6 - х: ";
			cin >> x6;
			cout << "Вершина 6 - y: ";
			cin >> y6;
			cout << "Вершина 7 - х: ";
			cin >> x7;
			cout << "Вершина 7 - y: ";
			cin >> y7;
			cout << "Вершина 8 - х: ";
			cin >> x8;
			cout << "Вершина 8 - y: ";
			cin >> y8;


			double area = Square1(5, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7);
			cout << "Площадь треугольника с наибольшей диагональю = " << area << endl;
			}
	}
	return 0;
}
