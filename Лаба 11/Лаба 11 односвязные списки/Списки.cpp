#include <iostream>
#include <clocale>
using namespace std;

struct Node {
	int data;
	Node* pointer_to_next_node = nullptr;
};
struct List {
	Node* head_node = nullptr;
};

void PrintList(const List& list) {
	Node* current_node = list.head_node;
	cout << "Ваш итоговый список: ";
	while (current_node != nullptr) {     
		cout << current_node->data << " ";  
		current_node = current_node->pointer_to_next_node;  
	}
	cout << endl;  
}


void PushBack(List& list, const int& data) {
	Node* new_node = new Node;
	new_node->data = data;
	if (list.head_node == nullptr) {
		list.head_node = new_node;

	}
	else {
		Node* current_node = list.head_node;
		while (current_node->pointer_to_next_node != nullptr) {
			current_node = current_node->pointer_to_next_node;
		}
		current_node->pointer_to_next_node = new_node;
	}
}

void PushHead(List& list, const int& data) {
	Node* new_node = new Node;
	new_node->data = data;
	new_node->pointer_to_next_node = list.head_node;
	list.head_node = new_node;
}

bool PushAtIndex(List& list, const int& data, int index) {
	Node* new_node = new Node;
	new_node->data = data;
	if (index < 0) {
		cout << "Ошибка! Индекс не может быть меньше 0!";
		return false;
	}
	if (index == 0) {
		PushHead(list, data);
		return true;
	}
	Node* current_node = list.head_node;
	int current_idx = 0;
	while (current_node != nullptr && current_idx < index - 1) {
		current_node = current_node->pointer_to_next_node;
		current_idx++;
	}
	if (current_node == nullptr) {
		return false;
	}
	new_node->pointer_to_next_node = current_node->pointer_to_next_node;
	current_node->pointer_to_next_node = new_node;
}

bool DeleteFromBack(List& list) {
	if (list.head_node == nullptr) {
		cout << "Список пуст!";
		return false;
	}
	if (list.head_node->pointer_to_next_node == nullptr) {
		delete list.head_node;
		list.head_node = nullptr;
		cout << "Удалён единственный элемент списка!";
		return true;
	}
	Node* current_node = list.head_node;
	while (current_node->pointer_to_next_node->pointer_to_next_node != nullptr) {
		current_node = current_node->pointer_to_next_node;
	}
	Node* temp = current_node->pointer_to_next_node;
	current_node->pointer_to_next_node = nullptr;
	delete temp;
	cout << "Удален конечный элемент из списка: ";
	return true;
}

bool DeleteFromHead(List& list) {
	if (list.head_node == nullptr) {
		cout << "Список пуст!";
		return false;
	}
	Node* temp = list.head_node;
	list.head_node = list.head_node->pointer_to_next_node;
	delete temp;
	return true;
}

bool DeleteAtIndex(List& list, int index) {
	if (list.head_node == nullptr) {
		cout << "Список пуст!";
		return false;
	}
	if (index < 0) {
		cout << "Ошибка! Индекс не может быть меньше 0";
	}
	if (index == 0) {
		return DeleteFromHead(list);
	}
	Node* current_node = list.head_node;
	int current_index = 0;
	while (current_node != nullptr && current_index < index - 1) {
		current_node = current_node->pointer_to_next_node;
		current_index++;
	}
	if (current_node == nullptr || current_node->pointer_to_next_node == nullptr) {
		return false;
	}
	Node* temp = current_node->pointer_to_next_node;
	current_node->pointer_to_next_node = temp->pointer_to_next_node;
	delete temp;
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
	cout << endl << "Хотите ли вы удалить элементы из списка? (y - да, n - нет): ";
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