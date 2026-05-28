#include <iostream>
#include <clocale>
using namespace std;
void han(int n, int start, int point, int temp, int& moveCount)
{
    if (n <= 0)
        return;
    han(n - 1, start, temp, point, moveCount);
    moveCount++;
    cout << moveCount << ".  Диск " << n << ": " << start << " -> " << point << endl;
    han(n - 1, temp, point, start, moveCount);
}
int main()
{
    setlocale(LC_ALL, "RU");
    int n;
    cout << "Введите количество дисков: ";
    cin >> n;
    cout << "Последовательность перемещений: " << endl; 
    cout << "=================================" << endl;
    int moveCount = 0;
    han(n, 1, 3, 2, moveCount);
    cout << "=================================" << endl;
    cout << "Всего ходов: " << moveCount << endl;
    return 0;
}