#include <iostream>
#include <clocale>
using namespace std;

struct Node {
	int data;
	Node* prev = nullptr;
	Node* next = nullptr;
};

struct List {
	Node* head = nullptr;
	Node* tail = nullptr;
};

void PrintList(const List& list) {
    Node* current_node = list.head;
    cout << "Список: ";
    while (current_node != nullptr) {
        cout << current_node->data << " ";
        current_node = current_node->next;
    }
    cout << endl;
}

void PushBack(List& list, int data) {
    Node* new_node = new Node;
    new_node->data = data;
    if (list.head == nullptr) {
        list.head = list.tail = new_node;
    }
    else {
        list.tail->next = new_node;
        new_node->prev = list.tail;
        list.tail = new_node;
    }
}

void PushHead(List& list, int data) {
    Node* new_node = new Node;
    new_node->data = data;
    if (list.head == nullptr) {
        list.head = list.tail = new_node;
    }
    else {
        new_node->next = list.head;
        list.head->prev = new_node;
        list.head = new_node;
    }
}

bool PushAtIndex(List& list, int data, int index) {
    if (index < 0) {
        cout << "Ошибка! Индекс не может быть меньше 0!";
        return false;
    }
    if (index == 0) {
        PushHead(list, data);
        return true;
    }
    Node* current = list.head;
    int current_index = 0;
    while (current != nullptr && current_index < index) {
        current = current->next;
        current_index++;
    }
    if (current == nullptr) {
        PushBack(list, data); 
        return true;
    }
    Node* new_node = new Node;
    new_node->data = data;
    new_node->next = current;
    new_node->prev = current->prev;
    current->prev->next = new_node;
    current->prev = new_node;
    return true;
}

bool DeleteFromBack(List& list) {
    if (list.tail == nullptr) {
        return false;
    }
    Node* temp = list.tail;
    if (list.head == list.tail) {
        list.head = list.tail = nullptr;
    }
    else {
        list.tail = list.tail->prev;
        list.tail->next = nullptr;
    }
    delete temp;
    return true;
}

bool DeleteFromHead(List& list) {
    if (list.head == nullptr) {
        return false;
    }
    Node* temp = list.head;
    if (list.head == list.tail) {
        list.head = list.tail = nullptr;
    }
    else {
        list.head = list.head->next;
        list.head->prev = nullptr;
    }
    delete temp;
    return true;
}

bool DeleteAtIndex(List& list, int index) {
    if (list.head == nullptr) {
        return false;
    }
    if (index < 0) {
        cout << "Ошибка! Индекс не может быть меньше 0!";
    }
    if (index == 0) {
        return DeleteFromHead(list);
    }
    Node* current = list.head;
    int current_index = 0;
    while (current != nullptr && current_index < index) {
        current = current->next;
        current_index++;
    }
    if (current == nullptr) {
        return false;
    }
    if (current == list.tail) {
        return DeleteFromBack(list);
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    return true;
}

int main() {
    setlocale(LC_ALL, "ru");
    List Spisok;
    int choose, k, count, count1;
    cout << "Введите количество элементов, которые хотите добавить:  ";
    cin >> count;
    for (int i = 0; i < count; i++) {
        cout << "Куда вы хотите добавить элемент?" << endl << "В начало - введите 1" << endl << "В конец - введите 2" << endl << "По индексу - введите 3" << endl;
        cout << "Введите: ";
        cin >> choose;
        while (choose != 1 && choose != 2 && choose != 3) {
            cout << "Ошибка, такое действие не обнаружено!" << endl;
            cout << "Введите действие заново: ";
            cin >> choose;
        }
        cout << "Введите элемент, который хотите добавить: ";
        cin >> k;
        switch (choose) {
        case 1:
            PushHead(Spisok, k);
            break;
        case 2:
            PushBack(Spisok, k);
            break;
        case 3:
            int idx;
            cout << "Введите индекс, по которому хотите добавить элемент: ";
            cin >> idx;
            PushAtIndex(Spisok, k, idx);
            break;
        default:
            cout << "Такого варианта нет!";
            break;
        }
    }
    char del;
    int choose1;
    cout << endl;
    PrintList(Spisok);
    cout << endl << "Хотите ли вы удалить элемент из списка? (y - да, n - нет): ";
    cin >> del;
    if (del == 'y') {
        cout << "Введите количество элементов, которое хотите удалить: ";
        cin >> count1;
        for (int i = 0; i < count1; i++) {
            cout << "Откуда вы хотите удалить элемент?" << endl << "Из начала - введите 1" << endl << "Из конца - введите 2" << endl << "По индексу - введите 3" << endl;
            cout << "Введите: ";
            cin >> choose1;
            while (choose1 != 1 && choose1 != 2 && choose1 != 3) {
                cout << "Ошибка, такое действие не обнаружено!" << endl;
                cout << "Введите действие заново: ";
                cin >> choose1;
            }
            switch (choose1) {
            case 1:
                DeleteFromHead(Spisok);
                break;
            case 2:
                DeleteFromBack(Spisok);
                break;
            case 3:
                int idx;
                cout << "Введите индекс, по которому хотите удалить элемент: ";
                cin >> idx;
                DeleteAtIndex(Spisok, idx);
                break;
            default:
                cout << "Такого варианта нет!";
                break;
            }
            cout << endl;
            PrintList(Spisok);
        }
    }
    else if (del == 'n') {
        cout << "Работа завершена!" << endl;
        return 1;
    }
    else {
        cout << "Такого варианта ответа нет!";
    }
    return 0;
}

