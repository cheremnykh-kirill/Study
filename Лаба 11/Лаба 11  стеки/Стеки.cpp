#include <iostream>
#include <clocale>
using namespace std;

struct Node {
    int data;
    Node* next = nullptr;
    Node* prev = nullptr;
};

struct Stack {
    Node* head = nullptr;         
};

void InitStack(Stack& stack) {
    stack.head = nullptr;
}

bool IsEmpty(const Stack& stack) {
    return stack.head == nullptr;
}

void Push(Stack& stack, int data) {
    Node* new_node = new Node;
    new_node->data = data;
    if (IsEmpty(stack)) {
        stack.head = new_node;
    }
    else {
        new_node->next = stack.head;
        stack.head->prev = new_node;
        stack.head = new_node;
    }
}

bool Delete(Stack& stack) {
    if (IsEmpty(stack)) {
        cout << "Стек пустой!";
        return false;
    }
    Node* temp = stack.head;
    stack.head = stack.head->next;
    if (stack.head) {
        stack.head->prev = nullptr;
    }
    delete temp;
    return true;
}

void PrintStack(const Stack& stack) {
    Node* current = stack.head;
    cout << "==================================================" << endl;
    cout << "Стек: " << endl;
    while (current) {
        cout << current->data << endl;
        current = current->next;
    }
    cout << "==================================================";
}

int main() {
    setlocale(LC_ALL, "ru");
	Stack Steck;
    InitStack(Steck);
	int k, count, count1;
	cout << "Введите количество элементов, которые хотите добавить:  ";
	cin >> count;
	for (int i = 0; i < count; i++) {
		cout << "Введите элемент, который хотите добавить: ";
		cin >> k;
		Push(Steck, k);
	}
    char del;
	cout << endl;
	PrintStack(Steck);
	cout << endl << "Хотите ли вы удалить элемент из стека? (y - да, n - нет): ";
	cin >> del;
	if (del == 'y') {
		cout << "Введите количество элементов, которое хотите удалить: ";
		cin >> count1;
		for (int i = 0; i < count1; i++) {
            Delete(Steck);
		}
		cout << endl;
		PrintStack(Steck);
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
