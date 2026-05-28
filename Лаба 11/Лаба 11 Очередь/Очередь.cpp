#include <iostream>
#include <clocale>
using namespace std;

struct Node {
    int data;
    Node* next = nullptr;
    Node* prev = nullptr;
};

struct Queue {
    Node* head = nullptr;  
    Node* tail = nullptr;          
};

void InitQueue(Queue& queue) {
    queue.head = nullptr;
    queue.tail = nullptr;
}

bool isEmpty(const Queue& queue) {
    return queue.head == nullptr;
}

void Push(Queue& queue, int data) {
    Node* new_node = new Node;
    new_node->data = data;
    if (isEmpty(queue)) {
        queue.head = queue.tail = new_node;
    }
    else {
        queue.tail->next = new_node;
        new_node->prev = queue.tail;
        queue.tail = new_node;
    }
}

bool Delete(Queue& queue) {
    if (isEmpty(queue)) {
        cout << "Очередь пуста!";
        return false;
    }
    Node* temp = queue.head;
    queue.head = queue.head->next;
    if (queue.head) {
        queue.head->prev = nullptr;
    }
    else {
        queue.tail = nullptr;  
    }
    delete temp;
    return true;
}

void PrintQueue(const Queue& queue) {
    Node* current = queue.head;
    cout << "Очередь: " << endl;
    cout << "Начало очереди здесь --> ";
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    Queue Line;
    InitQueue(Line);
    int k, count, count1;
    cout << "Введите количество элементов, которые хотите добавить:  ";
    cin >> count;
    for (int i = 0; i < count; i++) {
        cout << "Введите элемент, который хотите добавить: ";
        cin >> k;
        Push(Line, k);
    }
    char del;
    cout << endl;
    PrintQueue(Line);
    cout << endl << "Хотите ли вы удалить элемент из очереди? (y - да, n - нет): ";
    cin >> del;
    if (del == 'y') {
        cout << "Введите количество элементов, которое хотите удалить: ";
        cin >> count1;
        for (int i = 0; i < count1; i++) {
            Delete(Line);
        }
        cout << endl;
        PrintQueue(Line);
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


