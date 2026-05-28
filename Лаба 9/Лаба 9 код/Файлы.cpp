#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
using namespace std;


int main() {
    setlocale(LC_ALL, "ru");
    ifstream in("file1.txt");
    ofstream out("file2.txt");
    if (!in.is_open() || !out.is_open()) {
        cout << "Не удалось открыть файл" << endl;
        return 1;
    }
    string str;
    int max = 0;        
    int best_line = 0;        
    int word_pos = 0;      
    int line_num = 0;       
    while (getline(in, str)) {
        line_num++;
        string words[100];
        string word;
        int word_count = 0;
        for (int i = 0; i <= str.length(); i++) {
            if (i == str.length() || str[i] == ' ') {
                if (!word.empty()) {
                    words[word_count] = word;
                    word_count++;
                    word = "";
                }
            }
            else {
                word += str[i];
            }
        }
        bool duplicates = false;
        for (int i = 0; i < word_count; i++) {
            for (int j = i + 1; j < word_count; j++) {
                if (words[i] == words[j]) {
                    duplicates = true;
                    break;
                }
            }
            if (duplicates) {
                break;
            }
        }
        if (duplicates) {
            out << str << endl;
        }
        for (int i = 0; i < word_count; i++) {
            int digit = 0;
            for (int j = 0; j < words[i].length(); j++) {
                if (words[i][j] >= '0' && words[i][j] <= '9') {
                    digit++;
                }
            }

            if (digit > max) {
                max = digit;
                best_line = line_num;
                word_pos = i + 1; // Так как нам нужен номер, а не индекс
            }
        }
    }
    in.close();
    out.close();
    cout << "Строка, в которой находится слово: " << best_line << endl;
    cout << "Номер слова в строке: " << word_pos << endl;
    if (max > 0) {
        cout << "Количество цифр в слове: " << max << endl;
    }
    else {
        cout << "В файле нет слов, содержащих цифры." << endl;
    }
    return 0;
}