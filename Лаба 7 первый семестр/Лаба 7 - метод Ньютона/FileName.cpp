#include <iostream>
#include <clocale>
#include <cmath>
using namespace std;
double f(double x) {
    return x - 2 + sin(1 / x);
}
double df(double x) {
    return 1 - cos(1 / x) / (x * x);
}
double ddf(double x) {
    return  (2 * x * cos(1 / x) - sin(1 / x)) / (x * x * x * x);
}
int main() {
    setlocale(LC_ALL, "RU");
    double a, b, eps, x0, x_new;
    int iter = 0;
    bool flag = false;
    int max_iter = 10000;
    cout << "Введите левую границу интервала: ";
    cin >> a;
    cout << "Введите правую границу интервала: ";
    cin >> b;
    cout << "Введите заданную точность (епсилон): ";
    cin >> eps;
    if (f(a) * f(b) > 0) {
        cout << "На данном интервале корня нет!";
    }
    else {
        if (f(a) * ddf(a) > 0) {
            x0 = a;
        }
        else if (f(b) * ddf(b) > 0) {
            x0 = b;
        }
        else {
            x0 = (a + b) / 2;
        }
        while (!flag && iter < max_iter) {
            if (fabs(df(x0)) == 0) {
                cout << "Производная равна нулю!" << endl;
                flag = true;
            }
            else {
                x_new = x0 - (f(x0) / df(x0));
                if (fabs(x_new - x0) < eps) {
                    flag = true;
                }
                x0 = x_new;
                iter++;
            }
        }
        cout << "Количество совершённых итераций: " << iter << endl;
        cout << "Искомый корень: " << x_new << endl;
    }
    return 0;
}


