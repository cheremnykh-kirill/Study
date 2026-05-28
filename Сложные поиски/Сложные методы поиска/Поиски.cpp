#include <iostream>
#include <clocale>
#include <string>
#include <windows.h>
using namespace std;


// Визуализация
// text - исходная строка, pattern - подстрока (образец)
// shift - сдвиг образца от начала строки
// compare_pos - позиция в подстроке, где проходит сравнение
void visualize_comparison(const string& text, const string& pattern, int shift, int compare_pos = -1) {
    int n = text.length();
    int m = pattern.length();
    cout << "Текст:     " << text << endl;
    cout << "Образец:   ";
    for (int i = 0; i < shift; i++) {
        cout << " ";
    }
    cout << pattern << endl;
    // Показываем позицию сравнения, если она указана
    if (compare_pos >= 0 && shift + compare_pos < n && compare_pos < m) {
        cout << "Сравнение: ";
        for (int i = 0; i < shift + compare_pos; i++) {
            cout << " ";
        }
        if (shift + compare_pos < n) {
            if (text[shift + compare_pos] == pattern[compare_pos]) {
                cout << "=";
            }
            else {
                cout << "!";
            }
        }
        cout << endl;
    }
    cout << "--------------------------------------------------" << endl;
}

// Алгоритм Бойера-Мура 
void boyer_moore_search() {
    setlocale(LC_ALL, "RU");
    string text, pattern;
    cout << "\nАлгоритм Бойера-Мура" << "\n-----------------" << endl;
    cout << "Введите текст: ";
    cin.ignore();
    getline(cin, text);
    cout << "Введите образец для поиска: ";
    getline(cin, pattern);
    int n = text.length();
    int m = pattern.length();
    if (m == 0 || m > n) {
        cout << "Ошибка: некорректная длина образца!" << endl;
        return;
    }
    // Таблица сдвигов для "Плохого символа"
    int badchar[256];
    for (int i = 0; i < 256; i++) {
        badchar[i] = m;
    }
    for (int i = 0; i < m - 1; i++) {
        badchar[(unsigned char)pattern[i]] = m - 1 - i;
    }
    // Таблица сдвигов "хорошего суффикса"
    int* goodsuffix = new int[m + 1];
    int* border = new int[m + 1];
    for (int i = 0; i <= m; i++) {
        goodsuffix[i] = 0;
        border[i] = 0;
    }
    // Вычисление границ суффиксов
    int i = m, j = m + 1;
    border[i] = j;
    while (i > 0) {
        while (j <= m && pattern[i - 1] != pattern[j - 1]) {
            if (goodsuffix[j] == 0)
                goodsuffix[j] = j - i;
            j = border[j];
        }
        i--; j--;
        border[i] = j;
    }
    j = border[0];
    for (i = 0; i <= m; i++) {
        if (goodsuffix[i] == 0)
            goodsuffix[i] = j;
        if (i == j)
            j = border[j];
    }
    cout << "\n--- Начало поиска ---" << endl;
    int count = 0, firstPos = -1;
    int s = 0;
    while (s <= n - m) {
        int j = m - 1;
        // Визуализация начальной позиции
        visualize_comparison(text, pattern, s, j);
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }
        if (j < 0) {
            count++;
            if (firstPos == -1) firstPos = s;
            cout << ">>> Найдено совпадение на позиции " << s << " <<<" << endl;
            s += (s + m < n) ? goodsuffix[0] : 1;
        }
        else {
            // Проверка границ перед вычислением сдвига
            if (s + j < n) {
                int bc_shift = badchar[(unsigned char)text[s + j]] - (m - 1 - j);
                if (bc_shift < 1) bc_shift = 1;
                int gs_shift = goodsuffix[j + 1];
                if (gs_shift < 1) gs_shift = 1;
                int shift = max(bc_shift, gs_shift);
                cout << "Несовпадение на символе '" << text[s + j] << "'. ";
                cout << "Сдвиг: " << shift << endl;
                s += shift;
            }
            else {
                break;
            }
        }
    }
    delete[] goodsuffix;
    delete[] border;
    cout << "\n-----------------" << endl;
    cout << "Результаты поиска:" << endl;
    if (count == 0)
        cout << "Образец \"" << pattern << "\" не найден в тексте." << endl;
    else {
        cout << "Найдено вхождений: " << count << endl;
        cout << "Первое вхождение на позиции: " << firstPos << endl;
    }
}
// Алгоритм Бойера-Мура-Хорспула
void boyer_moore_horspool_search() {
    setlocale(LC_ALL, "RU");
    string text, pattern;
    cout << "\nАлгоритм Бойера-Мура-Хорспула" << "\n-----------------" << endl;
    cout << "Введите текст: ";
    cin.ignore();
    getline(cin, text);
    cout << "Введите образец для поиска: ";
    getline(cin, pattern);
    int n = text.length();
    int m = pattern.length();
    if (m == 0 || m > n) {
        cout << "Ошибка: некорректная длина образца!" << endl;
        return;
    }
    // Таблица смещений
    int shift[256];
    for (int i = 0; i < 256; i++)
        shift[i] = m;
    for (int i = 0; i < m - 1; i++)
        shift[(unsigned char)pattern[i]] = m - 1 - i;
    cout << "\n--- Начало поиска ---" << endl;
    int count = 0, firstPos = -1;
    int s = 0;
    while (s <= n - m) {
        // Визуализация текущего окна
        visualize_comparison(text, pattern, s, m - 1);
        // Проверка совпадения с конца
        bool match = true;
        for (int j = m - 1; j >= 0; j--) {
            if (s + j >= n || pattern[j] != text[s + j]) {
                match = false;
                break;
            }
        }
        if (match) {
            count++;
            if (firstPos == -1) firstPos = s;
            cout << ">>> НАЙДЕНО СОВПАДЕНИЕ на позиции " << s << " <<<" << endl;
            s++;
        }
        else {
            if (s + m - 1 < n) {
                char last_char = text[s + m - 1];
                int sh = shift[(unsigned char)last_char];
                if (sh < 1) sh = 1;
                cout << "Несовпадение. Последний символ окна: '" << last_char << "', сдвиг: " << sh << endl;
                s += sh;
            }
            else {
                break;
            }
        }
    }
    cout << "\n-----------------" << endl;
    cout << "Результаты поиска:" << endl;
    if (count == 0)
        cout << "Образец \"" << pattern << "\" не найден в тексте." << endl;
    else {
        cout << "Найдено вхождений: " << count << endl;
        cout << "Первое вхождение на позиции: " << firstPos << endl;
    }
}

// Алгоритм Кнута-Морриса-Пратта
void knut_morris_pratt_search() {
    setlocale(LC_ALL, "RU");
    string text, pattern;
    cout << "\nАлгоритм Кнута-Морриса-Пратта" << "\n-----------------" << endl;
    cout << "Введите текст: ";
    cin.ignore();
    getline(cin, text);
    cout << "Введите образец для поиска: ";
    getline(cin, pattern);
    int n = text.length();
    int m = pattern.length();
    if (m == 0 || m > n) {
        cout << "Ошибка: некорректная длина образца!" << endl;
        return;
    }
    // Вычисление префикс-функции
    int* pi = new int[m];
    pi[0] = 0;
    int j = 0;
    cout << "\nВычисление префикс-функции для образца \"" << pattern << "\":" << endl;
    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j])
            j = pi[j - 1];
        if (pattern[i] == pattern[j])
            j++;
        pi[i] = j;
        cout << "pi[" << i << "] (" << pattern[i] << ") = " << pi[i] << endl;
    }
    cout << "\n--- Начало поиска ---" << endl;
    int count = 0, firstPos = -1;
    j = 0;
    for (int i = 0; i < n; i++) {
        // Визуализация с проверкой границ
        cout << "Текст:     " << text << endl;
        cout << "Образец:   ";
        int shift = i - j;
        if (shift >= 0) {
            for (int k = 0; k < shift; k++) cout << " ";
            cout << pattern << endl;
        }
        else {
            cout << pattern << endl;
        }
        cout << "Сравнение: ";
        for (int k = 0; k < i; k++) cout << " ";
        cout << "^ (текст[" << i << "]='" << text[i] << "'";
        if (j < m) {
            cout << ", образец[" << j << "]='" << pattern[j] << "'";
        }
        cout << ")" << endl;
        cout << "--------------------------------------------------" << endl;
        while (j > 0 && text[i] != pattern[j]) {
            cout << "Несовпадение! Сдвиг по префикс-функции: pi[" << j - 1 << "]=" << pi[j - 1] << endl;
            j = pi[j - 1];
        }
        if (j < m && text[i] == pattern[j]) {
            cout << "Совпадение!" << endl;
            j++;
        }
        if (j == m) {
            count++;
            int pos = i - m + 1;
            if (firstPos == -1) firstPos = pos;
            cout << ">>> НАЙДЕНО СОВПАДЕНИЕ на позиции " << pos << " <<<" << endl;
            j = pi[j - 1];
        }
    }
    delete[] pi;
    cout << "\n-----------------" << endl;
    cout << "Результаты поиска:" << endl;
    if (count == 0)
        cout << "Образец \"" << pattern << "\" не найден в тексте." << endl;
    else {
        cout << "Найдено вхождений: " << count << endl;
        cout << "Первое вхождение на позиции: " << firstPos << endl;
    }
}


int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choose;
    char again;
    do {
        cout << "\n========================================" << endl;
        cout << "     МЕНЮ СЛОЖНЫХ ПОИСКОВ ПОДСТРОКИ" << endl;
        cout << "========================================" << endl;
        cout << "1. Алгоритм Бойера-Мура" << endl;
        cout << "2. Алгоритм Бойера-Мура-Хорспула" << endl;
        cout << "3. Алгоритм Кнута-Морриса-Пратта" << endl;
        cout << "0. Выход из программы" << endl;
        cout << "========================================" << endl;
        cout << "Ваш выбор : ";
        cin >> choose;

        switch (choose) {
        case 1:
            boyer_moore_search();
            break;
        case 2:
            boyer_moore_horspool_search();
            break;
        case 3:
            knut_morris_pratt_search();
            break;
        case 0:
            cout << "\nСпасибо за использование программы!" << endl;
            cout << "До свидания!" << endl;
            return 0;
        default:
            cout << "\nОшибка: такого варианта нет!" << endl;
            break;
        }

        cout << "\n========================================" << endl;
        cout << "Желаете выполнить другой поиск? (y/n): ";
        cin >> again;
        cout << "========================================" << endl;
        cin.ignore();

    } while (again == 'y' || again == 'Y');
    cout << "\nСпасибо за использование программы!" << endl;
    cout << "До свидания!" << endl;
    return 0;
}