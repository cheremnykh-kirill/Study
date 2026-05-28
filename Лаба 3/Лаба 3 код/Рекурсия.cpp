#include <iostream>
#include <cmath>
#include <clocale>
using namespace std;
double nextTerm(double term, double x, int n) {
    return term * x * x / ((2.0 * n + 2.0) * (2.0 * n + 3.0));
}
double sumFixedN(double x, int max_n, int current_n, double term) {
    if (current_n > max_n) {
        return 0.0;
    }
    return term + sumFixedN(x, max_n, current_n + 1, nextTerm(term, x, current_n));
}
double sumWithEpsilon(double x, double epsilon, int current_n, double term) {
    if (fabs(term) < epsilon) {
        return 0.0;
    }
    return term + sumWithEpsilon(x, epsilon, current_n + 1, nextTerm(term, x, current_n));
}
double f(double x) {
    return (exp(x) - exp(-x)) / 2.0;
}
int main() {
    setlocale(LC_ALL, "RU");
    double a;
    cout << "Введите левую границу диапазона: ";
    cin >> a;      
    double b;
    cout << "Введите правую границу диапазона: ";
    cin >> b;
    int k = 10;          
    int fix_n;    
    cout << "Введите заданное n: ";
    cin >> fix_n;
    double eps = 0.0001; 
    double step = (b - a) / k;
    cout << "Функция: y = (e^x - e^(-x))/2" << endl;
    cout << "Диапазон: x от " << a << " до " << b << " с шагом " << step << endl<< endl;
    cout << "x\t\tТочное\t\tРяд (n= " << fix_n << " )\tРяд(eps)" << endl;
    cout << endl;
    for (int i = 0; i <= k; i++) {
        double x = a + i * step;
        double first_term = x;
        double exact = f(x);
        double sum_n = sumFixedN(x, fix_n - 1, 0, first_term);
        double sum_eps = sumWithEpsilon(x, eps, 0, first_term);
        cout << fixed << x << "\t"
            << exact << "\t"
            << sum_n << "\t"
            << sum_eps << endl;
    }
    return 0;
}