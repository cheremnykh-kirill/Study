#include <iostream>
#include <clocale>
using namespace std;
const int size_arr = 8;
int arr[size_arr][size_arr] = { 0 };
int attempt = 0;
bool first_done = false;

bool check(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (arr[i][col]) return false;
    }

    for (int i = 1; row - i >= 0 && col - i >= 0; i++) {
        if (arr[row - i][col - i]) return false;
    }

    for (int i = 1; row - i >= 0 && col + i < size_arr; i++) {
        if (arr[row - i][col + i]) return false;
    }

    return true;
}


void show() {
    cout << "   a b c d e f g h\n";
    cout << "  +---------------+\n";

    for (int i = 0; i < size_arr; i++) {
        cout << i + 1 << " |";
        for (int j = 0; j < size_arr; j++) {
            cout << (arr[i][j] ? "?" : ".") << " ";
        }
        cout << "|\n";
    }

    cout << "  +---------------+\n";
}

void showStep(int row, int col, const string& action) {
    static int step = 0;
    cout << "\n Шаг " << ++step << ": " << action << " ферзя на "
        << char('a' + col) << row + 1 << "\n";
    show();
}

void game(int row) {
    if (row == size_arr) {
        attempt++;

        if (attempt == 1) {
            cout << "\n ПЕРВАЯ РАССТАНОВКА №1:\n";
            show();
            cout << "--- Продолжаем поиск остальных расстановок ---\n\n";
        }
        else {
            cout << "\nРасстановка №" << attempt << ":\n";
            show();
            cout << endl;
        }
        return;
    }

    for (int col = 0; col < size_arr; col++) {
        if (check(row, col)) {
            arr[row][col] = 1;

            if (attempt == 0) {
                showStep(row, col, "УСТАНОВКА");
            }

            game(row + 1);

            if (attempt == 0 && col < size_arr - 1) {
                cout << "\n Нет решения в этом направлении. Убираем ферзя с "
                    << char('a' + col) << row + 1 << "\n";
                showStep(row, col, "УДАЛЕНИЕ");
            }

            arr[row][col] = 0;
        }
        else {
            if (attempt == 0) {
                cout << "  ? " << char('a' + col) << row + 1 << " - позиция под боем\n";
            }
        }
    }
}

void eightFers() {
    setlocale(LC_ALL, "Russian");
    cout << "=== ЗАДАЧА О 8 ФЕРЗЯХ ===\n";
    cout << "Показываю ПРОЦЕСС поиска первой расстановки:\n\n";

    game(0);

    cout << "\n=== ИТОГ ===\n";
    cout << "Всего найдено расстановок: " << attempt << endl;
}

int main() {
    setlocale(LC_ALL, "Ru");
    eightFers();
}