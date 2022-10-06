#pragma once

#define CAPACITY 2
#include <iostream>
#include <string>
using namespace std;

enum symbol{num = 1, znak =2, skobka =3, funk = 4};
enum prior { first = 1, second = 2, third = 3, forth = 4, fifth = 5 };

template<typename T>
class _List {
private:
	struct _Node {
		T val;
		_Node* next;
	};
	_Node* head;
public:

	// онструкторы
	_List() {
		head = nullptr;
	}
	_List(int size) {
		head = new _Node;
		head->next = nullptr;
		_Node* temp = head;
		for (int i = 0; i < size - 1; i++) {
			temp->next = new _Node;
			temp = temp->next;

		}
		temp->next = nullptr;
	}
	_List(int size, T data) {
		head = new _Node;
		head->next = nullptr;
		_Node* temp = head;
		for (int i = 0; i < size - 1; i++) {
			temp->next = new _Node;
			temp->val = data;
			temp = temp->next;

		}
		temp->next = nullptr;
		temp->val = data;
	}
	

	//ѕерегрузка оператора []
	_Node* operator[](int index) {
		_Node* temp = head;
		int cnt = 0;
		while (temp != nullptr) {
			if (cnt == index) { return temp; }
			temp = temp->next;
			cnt++;
		}
		
	}

	T getVal(int index) {
		_Node* temp = head;
		int cnt = 0;
		while (temp != nullptr) {
			if (cnt == index) { return temp->val; }
			temp = temp->next;
			cnt++;
		}
	}

	//¬ывод списка
	void printList() {
		_Node* temp = head;
		while (temp != nullptr) {
			cout << temp->val << " ";
			temp = temp->next;
		}
	}

	//¬ывод значени€ ноды по индексу
	void printNode(int index) {
		_Node* temp = this->head;
		int cnt = 0;
		while (temp != nullptr) {
			if (cnt == index) { cout << temp->val; }
			cnt++;
			temp = temp->next;
		}
	}
	//поиск индекса по элементу
	int find(T data) {
		if (is_empty()) {
			cout << "Error: list does not exist";
		}
		else {
			_Node* temp = this->head;
			int cnt = 0;
			while (temp != nullptr) {
				if (temp->val == data) {
					return cnt;
				}
				temp = temp->next;
				cnt++;
			}
			cout << "Error: element not found";
		}
		

	}

	//–азмер списка
	int getSize() {
		_Node* temp = this->head;
		int cnt = 0;
		while (temp != nullptr) {
			cnt++;
			temp = temp->next;
		}
		return cnt;
	}

	//ѕроверка на пустоту
	bool is_empty() {
		if (head == nullptr) { return true; }
		else { return false; }
	}


	//ƒобавление в конец списка
	void push_back(T data) {
		if (is_empty()) {
			head = new _Node;
			head->val = data;
			head->next = nullptr;
		}
		else {
			_Node* temp = head;
			while (temp->next != nullptr) { temp = temp->next; }
			_Node* newNode = new _Node;
			newNode->next = nullptr;
			newNode->val = data;
			temp->next = newNode;
		}

	}
	//добавление в начало списка
	void push_front(T data) {
		if (is_empty()) {
			head = new _Node;
			head->val = data;
			head->next = nullptr;
		}
		else {
			_Node* newNode = new _Node;
			newNode->next = head;
			newNode->val = data;
			head = newNode;
		}
	}
	//добавление по индексу
	void push(int index, T data) {
		if (index >= 0 && index < getSize()) {
			if (index == 0) {
				push_front(data);
			}
			else if (index == getSize() - 1) {
				push_back(data);
			}
			else {
				_Node* temp = head;
				_Node* ptr;
				_Node* newNode = new _Node;
				newNode->next = nullptr;
				newNode->val = data;
				int cnt = 0;
				while (temp != nullptr) {
					if (cnt == index - 1) {
						ptr = temp->next;
						temp->next = newNode;
						newNode->next = ptr;
						return;
					}
					cnt++;
					temp = temp->next;
				}
			}
		}
		else { cout << "Error:out of the list"; }

	}
	//удаление по индексу
	void deleteNode(int index) {
		if (index >= 0 && index < getSize()) {
			if (index == 0) {
				_Node* ptr = head->next;
				delete head;
				head = ptr;
			}
			else if (index == getSize() - 1) {
				int cnt = 0;
				_Node* temp = head;
				while (temp != nullptr) {
					if (cnt == index - 1) {
						_Node* ptr = temp;
						temp = temp->next;
						delete temp;
						ptr->next = nullptr;
						return;
					}
					cnt++;
					temp = temp->next;
				}
			}
			else {
				_Node* temp = head;
				_Node* ptr_priv;
				_Node* ptr_next;
				int cnt = 0;
				while (temp != nullptr) {
					if (cnt == index - 1) {
						ptr_priv = temp;
						temp = temp->next;
						ptr_next = temp->next;
						delete temp;
						ptr_priv->next = ptr_next;
						return;
					}
					cnt++;
					temp = temp->next;
				}

			}
		}
		else { cout << "Error:out of the list"; }
	}

	~_List() {
		int size = getSize();
		for (int i = 0; i < size; i++) {
			deleteNode(0);
		}
	}
};


template <typename T>
class _vector {
private:
	T* mas;
	int size;
	int realSize;
	int capacity;

	//проверка массива на заполнение
	bool checkForCompletion() {
		if (size == realSize) {
			return true;
		}
		else { return false; }
	}
	bool checkForCompletion(int _size) {
		if (_size == realSize) {
			return true;
		}
		else { return false; }
	}
	//создание нового массива после заполнени€ старого
	void newMas() {
		T* temp = new T[size * capacity];
		for (int i = 0; i < size; i++) {
			temp[i] = mas[i];
		}
		mas = temp;
		realSize = size * capacity;
	}
public:
	_vector() {
		size = 0;
		capacity = CAPACITY;
		realSize = capacity;
		mas = new T[capacity];
	}
	_vector(int _size) {
		size = _size;
		capacity = CAPACITY;
		realSize = _size * capacity;
		mas = new T[realSize];

	}
	//возвращает размер массива
	int getSize() { return size; }
	//возвращает количество элементов которые может содержать массив без выделени€ дополнительной пам€ти
	int getCapacity() {
		if (size == 0) { return capacity; }
		else { return realSize; }
	}

	//перегрузка оператора []
	T& operator [](int index) {
		if (index >= 0 && index < size) {
			return mas[index];
		}
	}

	int find(T data) {
		for (int i = 0; i < size; i++) {
			if (mas[i] == data) {
				return i;
			}
			
		}
		cout << "Error:element not found";
	}

	//вставка в конец массива
	void push_back(T temp) {
		if (checkForCompletion()) {
			newMas();
		}
		mas[size] = temp;
		size++;

	}
	//вставка элемента по индексу
	void push(T temp, int index) {
		if (index >= 0 && index < size) {
			int tmp;
			if (checkForCompletion(size + 1)) {
				newMas();
			}
			for (int i = 0; i < size + 1; i++) {
				if (i == index) {
					tmp = mas[i];
					mas[i] = temp;
					i++;
					while (i < size + 1) {
						temp = tmp;
						tmp = mas[i];
						mas[i] = temp;
						i++;
					}
					size++;
					return;
				}
			}
		}
		else {
			cout << "Error::array out of bounds";
		}
	}

	//”даление по индексу
	void erase(int index) {
		if (index >= 0 && index < getSize()) {
			for (int i = index; i < getSize() - 1; i++) {
				mas[i] = mas[i + 1];
			}
			size--;
			realSize = size * capacity;
		}
		else {
			cout << "Error::array out of bounds";
		}

	}

	~_vector() {
		delete mas;
	}
};


template <typename L>
class stack {
private:
	_List<L> arr;
public:
	
	//вытащить элемент из стека с удалением
	L pop() {
		if (arr.getSize() != 0) {
			L temp = arr.getVal(arr.getSize() - 1);
			arr.deleteNode(arr.getSize() - 1);
			return temp;
		}
	}
	
	void push(L data) {
		arr.push_back(data);
	}
	//посмотреть последний элемент без удалени€
	L peak() {
		if (arr.getSize() != 0) {
			return arr.getVal(arr.getSize() - 1);
		}
		
	}

	bool is_empty() {
		if (arr.getSize() == 0) {
			return true;
		}
		else { return false; }
	}
};

