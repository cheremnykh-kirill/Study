#include <iostream>
#include <clocale>
#include <cmath>
using namespace std;
double f(double x) {
    return x - 2 + sin(1 / x);
}
int main() {
    setlocale(LC_ALL, "RU");
    double a, b, x0, x_new, eps;
    bool flag = false;
    int iter = 0;
    int max_iter = 10000;
    cout << "Введите левую границу: ";
    cin >> a;
    cout << "Введите правую границу: ";
    cin >> b;
    cout << "Введите точность вычислений (епсилон): ";
    cin >> eps;
    x0 = (a + b) / 2;
    if (f(a) * f(b) > 0) {
        cout << "На данном интервале корней нет!";
    }
    else {
        while (!flag && iter < max_iter) {
            if (f(a) * f(x0) > 0) {
                a = x0;
            }
            else {
                b = x0;
            }
            x_new = (a + b) / 2;
            if (fabs(x_new - x0) < eps) {
                flag = true;
            }
            x0 = x_new;
            iter++;
        }
        cout << "Корень уравнения = " << x_new << endl;
        cout << "Количество выполненных итераций = " << iter << endl;
    }
    return 0;
}


