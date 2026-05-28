#include <iostream>
#include <cmath>
#include <clocale>
using namespace std;
double f(double x) {
    return x - 2 + sin(1 / x);
}
double df(double x) {
    return 1 - (cos(1 / x) / (x * x));
}
int main() {
    setlocale(LC_ALL, "RU");
    double a, b, eps, lam, x0, x_new;
    bool flag = false;
    int iter = 0;
    int max_iter = 10000;
    cout << "Введите левую границу: ";
    cin >> a;
    cout << "Введите правую границу: ";
    cin >> b;
    cout << "Введите точность для нахождения корня (эпсилон): ";
    cin >> eps;
    x0 = (a + b) / 2;
    if (f(a) * f(b) > 0) {
        cout << "На данном интервале нет корней!";
    }
    else {
        double i1 = df(a);
        double i2 = df(b);
        double i3 = df((a + b) / 2);
        double M = i1;
        double m = i1;
        if (i2 < m) {
            m = i2;
        }
        if (i3 < m) {
            m = i3;
        }
        if (i2 > M) {
            M = i2;
        }
        if (i3 > M) {
            M = i3;
        }
        if ((M > 0 && m > 0) || (M < 0 && m < 0)) {
            lam = 2 / (M + m);
        }
        else {
            lam = -1 / (fabs(m) + fabs(M));
        }
        cout << "Лямбда равна: " << lam << endl;
        while (!flag && iter < max_iter) {
            x_new = x0 - lam * f(x0);
            if (fabs(x_new - x0) < eps) {
                flag = true;
            }
            x0 = x_new;
            iter++;
        }
        cout << "Искомый корень уравнения = " << x_new << endl;
        cout << "Количество выполненных итераций для нахождения корня = " << iter;
    }
    return 0;
}
