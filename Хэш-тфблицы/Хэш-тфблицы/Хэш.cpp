#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

const double A = 0.6180339887;
const int DEFAULT_TABLE_SIZE = 40;
const int MAX_NAME_LENGTH = 50;

struct Record {
    char fio[50];
    char birthDate[11];
    char passportNumber[15];
    bool isDeleted;
    int next;
};

struct ListNode {
    Record data;
    ListNode* next;
    ListNode* prev;
};

struct HashNode {
    Record data;
    HashNode* next;
    bool isOccupied;
};

void printSeparator() {
    cout << "--------------------------------------------------" << endl;
}

void printRecord(const Record& rec) {
    cout << "ФИО: " << rec.fio << endl;
    cout << "Дата рождения: " << rec.birthDate << endl;
    cout << "Номер паспорта: " << rec.passportNumber << endl;
    if (rec.isDeleted) {
        cout << "(ЗАПИСЬ УДАЛЕНА)" << endl;
    }
}

Record inputRecord() {
    Record rec;
    rec.isDeleted = false;
    cout << "Введите ФИО: ";
    cin.ignore();
    cin.getline(rec.fio, 50);
    cout << "Введите дату рождения (ДД.ММ.ГГГГ): ";
    cin.getline(rec.birthDate, 11);
    cout << "Введите номер паспорта: ";
    cin.getline(rec.passportNumber, 15);
    return rec;
}

// Генерация случайной записи
Record generateRandomRecord() {
    Record rec;
    rec.isDeleted = false;

    // Случайное ФИО
    const char* surnames[] = { "Иванов", "Петров", "Сидоров", "Смирнов", "Кузнецов",
                              "Попов", "Васильев", "Михайлов", "Новиков", "Федоров" };
    const char* names[] = { "Иван", "Петр", "Александр", "Сергей", "Дмитрий",
                           "Андрей", "Алексей", "Максим", "Евгений", "Денис" };
    const char* patronymics[] = { "Иванович", "Петрович", "Александрович", "Сергеевич",
                                 "Дмитриевич", "Андреевич", "Алексеевич", "Максимович",
                                 "Евгеньевич", "Денисович" };

    int sId = rand() % 10;
    int nId = rand() % 10;
    int pId = rand() % 10;

    // Формируем ФИО через snprintf для безопасности
    snprintf(rec.fio, 50, "%s %s %s", surnames[sId], names[nId], patronymics[pId]);

    // Случайная дата рождения (1960-2010)
    int day = 1 + rand() % 28;
    int month = 1 + rand() % 12;
    int year = 1960 + rand() % 50;
    snprintf(rec.birthDate, 11, "%02d.%02d.%04d", day, month, year);

    // Случайный номер паспорта
    snprintf(rec.passportNumber, 15, "%02d %02d %06d",
        rand() % 100, rand() % 100, rand() % 1000000);

    return rec;
}

int dateToNumber(const char* date) {
    int result = 0;
    for (int i = 0; i < 10; i++) {
        if (date[i] != '.') {
            result = result * 10 + (date[i] - '0');
        }
    }
    return result;
}

int hashFunction(const char* key, int M) {
    int k = dateToNumber(key);
    double temp = k * A;
    double fractionalPart = temp - floor(temp);
    int hash = (int)(M * fractionalPart);
    return hash;
}

ListNode* addToListBegin(ListNode* head, Record rec) {
    ListNode* newNode = new ListNode;
    newNode->data = rec;
    newNode->next = head;
    newNode->prev = NULL;
    if (head != NULL) {
        head->prev = newNode;
    }
    return newNode;
}

ListNode* addToListEnd(ListNode* head, Record rec) {
    ListNode* newNode = new ListNode;
    newNode->data = rec;
    newNode->next = NULL;

    if (head == NULL) {
        newNode->prev = NULL;
        return newNode;
    }

    ListNode* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
    return head;
}

ListNode* addToListAtPosition(ListNode* head, Record rec, int position) {
    ListNode* newNode = new ListNode;
    newNode->data = rec;

    if (position == 0 || head == NULL) {
        newNode->next = head;
        newNode->prev = NULL;
        if (head != NULL) {
            head->prev = newNode;
        }
        return newNode;
    }

    ListNode* current = head;
    int currentPos = 0;
    while (current->next != NULL && currentPos < position - 1) {
        current = current->next;
        currentPos++;
    }

    newNode->next = current->next;
    newNode->prev = current;
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    current->next = newNode;
    return head;
}

int deleteByKey(ListNode* head, const char* key) {
    int count = 0;
    ListNode* current = head;
    while (current != NULL) {
        if (strcmp(current->data.birthDate, key) == 0 && !current->data.isDeleted) {
            current->data.isDeleted = true;
            count++;
        }
        current = current->next;
    }
    return count;
}

ListNode* deleteByPosition(ListNode* head, int position) {
    if (head == NULL) return NULL;

    ListNode* current = head;
    int currentPos = 0;
    while (current != NULL && currentPos < position) {
        current = current->next;
        currentPos++;
    }
    if (current == NULL) return head;

    current->data.isDeleted = true;
    return head;
}

ListNode* restoreLastDeleted(ListNode* head) {
    ListNode* lastDeleted = NULL;
    ListNode* current = head;
    while (current != NULL) {
        if (current->data.isDeleted) {
            lastDeleted = current;
        }
        current = current->next;
    }
    if (lastDeleted != NULL) {
        lastDeleted->data.isDeleted = false;
        cout << "Восстановлена запись: " << endl;
        printRecord(lastDeleted->data);
    }
    else {
        cout << "Нет удаленных записей для восстановления." << endl;
    }
    return head;
}

void editByKey(ListNode* head, const char* key) {
    ListNode* current = head;
    bool found = false;
    while (current != NULL) {
        if (strcmp(current->data.birthDate, key) == 0 && !current->data.isDeleted) {
            found = true;
            cout << "Найдена запись:" << endl;
            printRecord(current->data);
            cout << "\nВведите новые данные:" << endl;
            current->data = inputRecord();
        }
        current = current->next;
    }
    if (!found) {
        cout << "Запись с ключом " << key << " не найдена." << endl;
    }
}

void editByPosition(ListNode* head, int position) {
    ListNode* current = head;
    int currentPos = 0;
    while (current != NULL && currentPos < position) {
        current = current->next;
        currentPos++;
    }
    if (current != NULL && !current->data.isDeleted) {
        cout << "Найдена запись:" << endl;
        printRecord(current->data);
        cout << "\nВведите новые данные:" << endl;
        current->data = inputRecord();
    }
    else {
        cout << "Запись на позиции " << position << " не найдена." << endl;
    }
}

void printList(ListNode* head) {
    if (head == NULL) {
        cout << "Список пуст." << endl;
        return;
    }

    ListNode* current = head;
    int index = 0;
    int activeCount = 0;
    while (current != NULL) {
        cout << "\nЗапись #" << index << ":" << endl;
        printRecord(current->data);
        if (!current->data.isDeleted) activeCount++;
        current = current->next;
        index++;
    }
    cout << "\nВсего записей: " << index << " (активных: " << activeCount << ")" << endl;
}

int countRecords(ListNode* head) {
    int count = 0;
    ListNode* current = head;
    while (current != NULL) {
        if (!current->data.isDeleted) {
            count++;
        }
        current = current->next;
    }
    return count;
}

int countDeleted(ListNode* head) {
    int count = 0;
    ListNode* current = head;
    while (current != NULL) {
        if (current->data.isDeleted) {
            count++;
        }
        current = current->next;
    }
    return count;
}

void clearList(ListNode* head) {
    while (head != NULL) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void saveToFile(ListNode* head, const char* filename) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    ListNode* current = head;
    int count = 0;
    while (current != NULL) {
        file.write((char*)&current->data, sizeof(Record));
        current = current->next;
        count++;
    }

    file.close();
    cout << "Данные сохранены в файл " << filename << " (записей: " << count << ")" << endl;
}

ListNode* loadFromFile(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Файл не найден. Будет создан новый список." << endl;
        return NULL;
    }

    // Проверяем размер файла
    file.seekg(0, ios::end);
    int fileSize = file.tellg();
    file.seekg(0, ios::beg);

    if (fileSize == 0) {
        cout << "Файл пуст. Будет создан новый список." << endl;
        file.close();
        return NULL;
    }

    // Проверяем, что размер файла кратен размеру записи
    if (fileSize % sizeof(Record) != 0) {
        cout << "Ошибка: файл повреждён (неверный формат)." << endl;
        file.close();
        return NULL;
    }

    ListNode* head = NULL;
    Record rec;
    int count = 0;

    while (file.read((char*)&rec, sizeof(Record))) {
        head = addToListEnd(head, rec);
        count++;
    }

    file.close();
    cout << "Данные загружены из файла " << filename << " (записей: " << count << ")" << endl;
    return head;
}

HashNode** createHashTable(int size) {
    HashNode** table = new HashNode * [size];
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
    return table;
}

void insertToHashTable(HashNode** table, int tableSize, Record rec, int& collisions) {
    if (rec.isDeleted) return;

    int index = hashFunction(rec.birthDate, tableSize);

    HashNode* newNode = new HashNode;
    newNode->data = rec;
    newNode->next = NULL;
    newNode->isOccupied = true;

    if (table[index] == NULL) {
        table[index] = newNode;
    }
    else {
        collisions++;
        HashNode* current = table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

HashNode** buildHashTable(ListNode* head, int tableSize, int& collisions) {
    HashNode** table = createHashTable(tableSize);
    collisions = 0;

    ListNode* current = head;
    while (current != NULL) {
        insertToHashTable(table, tableSize, current->data, collisions);
        current = current->next;
    }

    return table;
}

HashNode* searchInHashTable(HashNode** table, int tableSize, const char* key, int& comparisons) {
    int index = hashFunction(key, tableSize);
    comparisons = 0;

    if (table[index] == NULL) {
        return NULL;
    }

    HashNode* current = table[index];
    while (current != NULL) {
        comparisons++;
        if (strcmp(current->data.birthDate, key) == 0 && !current->data.isDeleted) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void printHashTable(HashNode** table, int tableSize) {
    cout << "\nХеш-таблица (размер " << tableSize << "):" << endl;
    printSeparator();

    for (int i = 0; i < tableSize; i++) {
        cout << "Индекс " << i << ": ";
        if (table[i] == NULL) {
            cout << "пусто" << endl;
        }
        else {
            HashNode* current = table[i];
            int count = 0;
            while (current != NULL) {
                if (count > 0) cout << " -> ";
                cout << current->data.birthDate;
                current = current->next;
                count++;
            }
            cout << " (элементов: " << count << ")" << endl;
        }
    }
}

void clearHashTable(HashNode** table, int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        HashNode* current = table[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}

void demonstrateHashSearch(ListNode* head) {
    cout << "\nПОИСК В ХЕШ-ТАБЛИЦЕ" << endl;
    cout << "=====================" << endl;

    int tableSize;
    cout << "Введите размер хеш-таблицы (40, 75 или 90): ";
    cin >> tableSize;

    int collisions;
    HashNode** table = buildHashTable(head, tableSize, collisions);

    cout << "\nХеш-таблица построена." << endl;
    cout << "Количество коллизий: " << collisions << endl;
    printHashTable(table, tableSize);

    cout << "\nВведите дату рождения для поиска (ДД.ММ.ГГГГ): ";
    char key[11];
    cin.ignore();
    cin.getline(key, 11);

    int comparisons;
    HashNode* result = searchInHashTable(table, tableSize, key, comparisons);

    if (result != NULL) {
        cout << "\nЗапись найдена за " << comparisons << " сравнений:" << endl;
        printRecord(result->data);
    }
    else {
        cout << "\nЗапись с ключом " << key << " не найдена." << endl;
        cout << "Выполнено сравнений: " << comparisons << endl;
    }

    clearHashTable(table, tableSize);
}

void demonstrateCollisions(ListNode* head) {
    cout << "\nПОДСЧЕТ КОЛЛИЗИЙ ПРИ РАЗНЫХ РАЗМЕРАХ ТАБЛИЦЫ" << endl;
    cout << "=============================================" << endl;

    int sizes[] = { 40, 75, 90 };
    int numSizes = 3;

    for (int i = 0; i < numSizes; i++) {
        int collisions;
        HashNode** table = buildHashTable(head, sizes[i], collisions);

        cout << "\nРазмер таблицы: " << sizes[i] << endl;
        cout << "Количество коллизий: " << collisions << endl;

        int emptyCells = 0;
        int maxChainLength = 0;
        for (int j = 0; j < sizes[i]; j++) {
            if (table[j] == NULL) {
                emptyCells++;
            }
            else {
                int chainLength = 0;
                HashNode* current = table[j];
                while (current != NULL) {
                    chainLength++;
                    current = current->next;
                }
                if (chainLength > maxChainLength) {
                    maxChainLength = chainLength;
                }
            }
        }

        cout << "Пустых ячеек: " << emptyCells << endl;
        cout << "Максимальная длина цепочки: " << maxChainLength << endl;
        cout << "Коэффициент заполнения: " << (double)(sizes[i] - emptyCells) / sizes[i] << endl;

        clearHashTable(table, sizes[i]);
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    ListNode* dataList = NULL;
    const char* filename = "hash_data.bin";
    int choose;

    do {
        cout << "\n========================================" << endl;
        cout << "  МЕНЮ - ХЕШ-ТАБЛИЦЫ" << endl;
        cout << "========================================" << endl;
        cout << "1. Загрузить данные из файла" << endl;
        cout << "2. Сгенерировать 100 случайных записей" << endl;
        cout << "3. Добавить запись" << endl;
        cout << "  3.1 - в начало" << endl;
        cout << "  3.2 - в конец" << endl;
        cout << "  3.3 - на заданную позицию" << endl;
        cout << "4. Удалить запись" << endl;
        cout << "  4.1 - по ключу (дате рождения)" << endl;
        cout << "  4.2 - по номеру" << endl;
        cout << "5. Восстановить последнюю удаленную запись" << endl;
        cout << "6. Корректировка записи" << endl;
        cout << "  6.1 - по ключу (дате рождения)" << endl;
        cout << "  6.2 - по номеру" << endl;
        cout << "7. Показать все записи" << endl;
        cout << "8. Поиск в хеш-таблице" << endl;
        cout << "9. Подсчет коллизий" << endl;
        cout << "10. Сохранить изменения в файл" << endl;
        cout << "0. Выход" << endl;
        cout << "========================================" << endl;
        cout << "Ваш выбор: ";
        cin >> choose;

        switch (choose) {
        case 1:
            clearList(dataList);
            dataList = loadFromFile(filename);
            if (dataList != NULL) {
                cout << "Загружено активных записей: " << countRecords(dataList) << endl;
            }
            break;

        case 2: {
            cout << "\nГенерация 100 случайных записей..." << endl;
            for (int i = 0; i < 100; i++) {
                Record rec = generateRandomRecord();
                dataList = addToListEnd(dataList, rec);
            }
            cout << "Сгенерировано 100 записей." << endl;
            break;
        }

        case 3: {
            cout << "\nДобавление записи:" << endl;
            cout << "1 - в начало, 2 - в конец, 3 - на позицию: ";
            int subChoice;
            cin >> subChoice;
            Record rec = inputRecord();
            switch (subChoice) {
            case 1:
                dataList = addToListBegin(dataList, rec);
                break;
            case 2:
                dataList = addToListEnd(dataList, rec);
                break;
            case 3: {
                int pos;
                cout << "Введите позицию (начиная с 0): ";
                cin >> pos;
                dataList = addToListAtPosition(dataList, rec, pos);
                break;
            }
            }
            cout << "Запись добавлена." << endl;
            break;
        }
        case 4: {
            cout << "\nУдаление записи:" << endl;
            cout << "1 - по ключу, 2 - по номеру: ";
            int subChoice;
            cin >> subChoice;
            switch (subChoice) {
            case 1: {
                char key[11];
                cout << "Введите дату рождения (ДД.ММ.ГГГГ): ";
                cin.ignore();
                cin.getline(key, 11);
                int deleted = deleteByKey(dataList, key);
                cout << "Удалено записей: " << deleted << endl;
                break;
            }
            case 2: {
                int pos;
                cout << "Введите номер записи: ";
                cin >> pos;
                dataList = deleteByPosition(dataList, pos);
                cout << "Запись помечена как удаленная." << endl;
                break;
            }
            }
            break;
        }
        case 5:
            dataList = restoreLastDeleted(dataList);
            break;
        case 6: {
            cout << "\nКорректировка записи:" << endl;
            cout << "1 - по ключу, 2 - по номеру: ";
            int subChoice;
            cin >> subChoice;
            switch (subChoice) {
            case 1: {
                char key[11];
                cout << "Введите дату рождения (ДД.ММ.ГГГГ): ";
                cin.ignore();
                cin.getline(key, 11);
                editByKey(dataList, key);
                break;
            }
            case 2: {
                int pos;
                cout << "Введите номер записи: ";
                cin >> pos;
                editByPosition(dataList, pos);
                break;
            }
            }
            break;
        }
        case 7:
            printList(dataList);
            break;
        case 8:
            demonstrateHashSearch(dataList);
            break;
        case 9:
            demonstrateCollisions(dataList);
            break;
        case 10:
            saveToFile(dataList, filename);
            break;
        case 0:
            cout << "\nСохранить изменения перед выходом? (1-да, 0-нет): ";
            int saveChoice;
            cin >> saveChoice;
            if (saveChoice == 1) {
                saveToFile(dataList, filename);
            }
            clearList(dataList);
            cout << "До свидания!" << endl;
            break;
        default:
            cout << "Неверный выбор!" << endl;
        }
        if (choose != 0) {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
    } while (choose != 0);
    return 0;
}