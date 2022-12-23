#pragma once
#define CAPACITY 2
#include <iostream>


using namespace std;

template<typename T>
class _List {
private:
	struct _Node {
		T val;
		_Node* next;
	};
	_Node* head;
public:

	//Конструкторы
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


	//Перегрузка оператора []
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

	//Вывод списка
	void printList() {
		_Node* temp = head;
		while (temp != nullptr) {
			cout << temp->val << " ";
			temp = temp->next;
		}
	}

	//Вывод значения ноды по индексу
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

	//Размер списка
	int getSize() {
		_Node* temp = this->head;
		int cnt = 0;
		while (temp != nullptr) {
			cnt++;
			temp = temp->next;
		}
		return cnt;
	}

	//Проверка на пустоту
	bool is_empty() {
		if (head == nullptr) { return true; }
		else { return false; }
	}


	//Добавление в конец списка
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
	//создание нового массива после заполнения старого
	void newMas() {
		T* temp = new T[size * capacity];
		for (int i = 0; i < size; i++) {
			temp[i] = mas[i];
		}
		mas = temp;
		realSize = size * capacity;
	}
public:
	//конструктор копирования
	/*_vector(_vector <T>& temp) {
		for (int i = 0; i < temp.getSize(); i++) {
			push(temp[i], i);
		}
		size = temp.getSize();
		capacity = temp.getCapacity();
		realSize = size * capacity;
		
	}*/
	//оператор копирования
	/*_vector operator=(_vector temp) {
		for (int i = 0; i < temp.getSize(); i++) {
			push(temp[i], i);
		}
		size = temp.getSize();
		capacity = temp.getCapacity();
		realSize = size * capacity;
		return *this;
	}*/
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
	//возвращает количество элементов которые может содержать массив без выделения дополнительной памяти
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
		return 0;
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

	//Удаление по индексу
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
	//посмотреть последний элемент без удаления
	L peak() {
		if (arr.getSize() != 0) {
			return arr.getVal(arr.getSize() - 1);
		}

	}

	int getSize() {
		return arr.getSize();
	}

	

	bool is_empty() {
		if (arr.getSize() == 0) {
			return true;
		}
		else { return false; }
	}
};


struct _Pos {
	int start;
	int finish;
};
struct Gallop {
	bool flag;
	int cnt = 0;
};
int GetMinrun(int n);
void TimSort(_vector <int>& mas, int minrun);
void printArr(_vector <int>& mas);
int checkСond(stack<_Pos>& st);
void InsertionSort(_vector <int>& mas, _Pos pos);
void printArrPiece(_vector <int>& mas, _Pos pos);
void Merge(_vector<int>& mas, _Pos pos1, _Pos pos2);
int findMin(_Pos pos1, _Pos pos2);
void checkSt(_vector<int>& mas, stack<_Pos>& st, _Pos& temp1, _Pos& temp2);
void reverseRun(_vector<int>& mas, _Pos pos, int i);
void findRev(_vector<int>& mas, _Pos& pos, int i);