#include <iostream>
#include <clocale>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;
struct Student {
    char surname[50];
    char name[50];
    char patronymic[50];
    char birthDate[11];     // ДД.ММ.ГГГГ
    char address[200];
    float rating;
};
void CreateFile(const char* filename) {
    ofstream file(filename, ios::binary | ios::out);
    if (!file) {
        cout << "Ошибка! Не удалось создать файл!" << endl;
        return;
    }
    int n;
    cout << "Введите количество студентов: ";
    cin >> n;
    cin.ignore();
    Student s;
    for (int i = 0; i < n; i++) {
        cout << "Студент номер " << i + 1 << endl;
        cout << "Фамилия: ";
        cin.getline(s.surname, 50);
        cout << "Имя: ";
        cin.getline(s.name, 50);
        cout << "Отчество: ";
        cin.getline(s.patronymic, 50);
        cout << "Дата рождения (ДД.ММ.ГГГГ): ";
        cin.getline(s.birthDate, 11);
        cout << "Домашний адрес: ";
        cin.getline(s.address, 100);
        cout << "Рейтинг: ";
        cin >> s.rating;
        cin.ignore();
        file.write((char*)&s, sizeof(Student));
    }
    file.close();
    cout << "Файл успешно создан!" << endl;
}
void PrintFile(const char* filename) {
    ifstream file(filename, ios::binary | ios::in);
    if (!file) {
        cout << "Ошибка! Не удалось открыть файл!" << endl;
        return;
    }
    Student s;
    int count = 0;
    cout << "Содержимое файла: " << endl;
    while (file.read((char*)&s, sizeof(Student))) {
        count++;
        cout << "Запись номер: " << count << endl;
        cout << "ФИО: " << s.surname << " " << s.name << " " << s.patronymic << endl;
        cout << "Дата рождения: " << s.birthDate << endl;
        cout << "Адрес: " << s.address << endl;
        cout << "Рейтинг: " << s.rating << endl;
    }
    if (count == 0) {
        cout << "Файл пуст!" << endl;
    }
    file.close();
}
void DeleteDuplicates(const char* filename) {
    ifstream file(filename, ios::binary | ios::in);
    if (!file) {
        cout << "Ошибка! Не удалось открыть файл!" << endl;
        return;
    }
    file.seekg(0, ios::end);
    int size = file.tellg();
    int count = size / sizeof(Student);
    file.seekg(0, ios::beg);
    if (count == 0) {
        cout << "Файл пуст!" << endl;
        file.close();
        return;
    }
    Student* students = new Student[count];
    for (int i = 0; i < count; i++) {
        file.read((char*)&students[i], sizeof(Student));
    }
    file.close();
    bool* Delete = new bool[count];
    for (int i = 0; i < count; i++) {
        Delete[i] = false;
    }
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(students[i].birthDate, students[j].birthDate) == 0) {
                Delete[i] = true;
                Delete[j] = true;
            }
        }
    }
    int new_count = 0;
    for (int i = 0; i < count; i++) {
        if (!Delete[i]) {
            new_count++;
        }
    }
    if (new_count == count) {
        cout << "Совпадающих дат рождения не найдено!" << endl;
        delete[] students;
        delete[] Delete;
        return;
    }
    ofstream outFile(filename, ios::binary | ios::out | ios::trunc);
    if (!outFile) {
        cout << "Ошибка при записи в файл!" << endl;
        delete[] students;
        delete[] Delete;
        return;
    }
    for (int i = 0; i < count; i++) {
        if (!Delete[i]) {
            outFile.write((char*)&students[i], sizeof(Student));
        }
    }
    outFile.close();
    delete[] students;
    delete[] Delete;
    cout << "Удалены записи с совпадающими датами рождения!" << endl;
}
void AddBeforeSurname(const char* filename) {
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "Ошибка! Не удалось открыть файл!" << endl;
        return;
    }
    file.seekg(0, ios::end);
    int size = file.tellg();
    int count = size / sizeof(Student);
    file.seekg(0, ios::beg);
    if (count == 0) {
        cout << "Файл пуст!" << endl;
        file.close();
        return;
    }
    Student* students = new Student[count];
    for (int i = 0; i < count; i++) {
        file.read((char*)&students[i], sizeof(Student));
    }
    char TargetSurname[50];
    cout << "Введите фамилию, перед которой нужно добавить запись: ";
    cin.ignore(); 
    cin.getline(TargetSurname, 50);
    int position = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].surname, TargetSurname) == 0) {
            position = i;
            break;
        }
    }
    if (position == -1) {
        cout << "Студент с фамилией " << TargetSurname << " не найден!" << endl;
        delete[] students;
        file.close();
        return;
    }
    cout << "Найдена запись на позиции " << position + 1 << endl;
    Student newStudent;
    cout << "Введите данные нового студента: " << endl;
    cout << "Фамилия: ";
    cin.getline(newStudent.surname, 50);
    cout << "Имя: ";
    cin.getline(newStudent.name, 50);
    cout << "Отчество: ";
    cin.getline(newStudent.patronymic, 50);
    cout << "Дата рождения (ДД.ММ.ГГГГ): ";
    cin.getline(newStudent.birthDate, 11);
    cout << "Адрес: ";
    cin.getline(newStudent.address, 100);
    cout << "Рейтинг: ";
    cin >> newStudent.rating;
    Student* newStudents = new Student[count + 1];
    for (int i = 0; i < position; i++) {
        newStudents[i] = students[i];
    }
    newStudents[position] = newStudent;
    for (int i = position; i < count; i++) {
        newStudents[i + 1] = students[i];
    }
    file.close();
    ofstream outFile(filename, ios::binary | ios::out | ios::trunc);
    if (!outFile) {
        cout << "Ошибка при записи в файл!" << endl;
        delete[] students;
        delete[] newStudents;
        return;
    }
    for (int i = 0; i < count + 1; i++) {
        outFile.write((char*)&newStudents[i], sizeof(Student));
    }
    outFile.close();
    delete[] students;
    delete[] newStudents;
    cout << "Новый студент успешно добавлен перед записью с фамилией " << TargetSurname << "!" << endl;
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");
    const char* filename = "students.dat";
    int choice;
    do {
        cout << "====================================================Меню====================================================" << endl;
        cout << "1. Создать файл и ввести студентов" << endl;
        cout << "2. Просмотреть содержимое файла" << endl;
        cout << "3. Удалить записи с совпадающими датами рождения" << endl;
        cout << "4. Добавить запись перед заданной фамилией" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            CreateFile(filename);
            break;
        case 2:
            PrintFile(filename);
            break;
        case 3:
            DeleteDuplicates(filename);
            break;
        case 4:
            AddBeforeSurname(filename);
            break;
        case 0:
            cout << "Программа завершена." << endl;
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }
    } while (choice != 0);
    return 0;
}