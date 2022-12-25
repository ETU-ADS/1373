#pragma once
#define CAPACITY 2

#include <iostream>
#include <fstream>
#include <string>
using namespace std;



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

	void SortMas() {
		int temp;
		for (int i = 1, j; i < size; i++) {
			j = i;
			while (j > 0 && mas[j] < mas[j - 1]) {
				temp = mas[j];
				mas[j] = mas[j - 1];
				mas[j - 1] = temp;
				j--;
			}

		}
	}

	~_vector() {
		delete mas;
	}
};


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

template <typename L>
class queue {
private:
	_List<L> arr;
public:
	//вытащить элемент из очереди с удалением
	L pop() {
		if (arr.getSize() != 0) {
			L temp = arr.getVal(0);
			arr.deleteNode(0);
			return temp;
		}
	}

	void push(L data) {
		arr.push_back(data);
	}
	//посмотреть первый элемент без удаления
	L peak() {
		if (arr.getSize() != 0) {
			return arr.getVal(0);
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



class _Tree {
private:
	struct TreeNode {
		int key;
		TreeNode* left;
		TreeNode* right;
		TreeNode* parent;
	};
	TreeNode* root;

	bool checkTree(string temp) {
		//проверка корректности ввода данных
		for (unsigned int i = 0; i < temp.length(); i++) {
			if ((int(temp[i]) < 48 || int(temp[i]) > 57)
				&& temp[i] != ' ' && temp[i] != '('
				&& temp[i] != ')'  && temp[i]!='-') {
				cout << "Error: Invalid character" << endl;
				return false;
			}
		}

		stack<char> arr;
		//проверка правильности раставления скобок
		for (unsigned int i = 0; i < temp.length(); i++) {
			if (temp[i] == '(') {
				arr.push(temp[i]);
			}
			else if (temp[i] == ')') {
				if (arr.is_empty()) { 
					cout << "Error: extra close bracket" << endl;
					return false; 
				}
				else {
					arr.pop();
				}
			}
		}
		
		if(!arr.is_empty()){
			cout << "Error: extra open bracket"<<endl;
			return false;
		}

		//проверка на то, является ли дерево бинарным
		int cnt = 0;
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i] != ')') {
				arr.push(temp[i]);
			}
			else {
				cnt = 0;
				while (!arr.is_empty()) {
					if (arr.peak() == '(') {
						arr.pop();
						arr.push('*');
						break;
					}
					else {
						if (arr.peak() == '*') {
							cnt++;
							if (cnt > 2) {
								cout << "\nError: This is not a binary tree"<<endl;
								return false;
							}
						}
						arr.pop();
					}
				}
			}
		}

		//проверка на расположение символа "-"
		for (int i = 1; i < temp.size()-1; i++) {
			if (i == temp.size() - 2) {
				if (temp[temp.size() - 1] == '-') {
					cout << "\nError: Incorrect data entry." << endl;
					return false;
				}
			}
			if (temp[i] == '-') {
				if (temp[i - 1] != '(' || temp[i + 1] < '1' || temp[i + 1] > '9') {
					cout << "\nError: Incorrect data entry." << endl;
					return false;
				}
			}
		}

		return true;

	}

public:
	_Tree() {
		root = nullptr;
	}

	TreeNode*& getRoot() { return root; }
	int getKey() { return root->key; }

	
	//парсинг бинарного дерева из файла
	void ReadTreeFromFile() {
		string temp;
		ifstream f("tree.txt");
		if (f.is_open()) {
			while (!f.eof()) {
				getline(f, temp);
			}
		}
		f.close();

		cout << temp;
		//если дерево не бинарное, завершаем программу
		if (checkTree(temp)) {
			cout << "\nTrue" << endl;
		}
		else {
			//cout << "\nError: This is not a tree!\n" << endl;
			exit(0);
		}
		//если дерево в файле бинарное, создаем соответсвующее бинарное дерево
		CreateTree(temp);
	}

	//метод создания бинарного дереваы
	void CreateTree(string temp) {
		bool flag = true; //flag = false в случае, когда у узла нет левого потомка
		root = new TreeNode;
		root->left = nullptr;
		root->right = nullptr;
		root->parent = nullptr;
		TreeNode* t = root;
		bool sign = true;
		int k = 0;
		
		for (int i = 1, j = 1; i < temp.length(); i++) {
			if (int(temp[i]) >= 48 && int(temp[i]) <= 57 || temp[i-1]=='-') {

				if (temp[i - 1] == '('||temp[i - 2] == '(' && temp[i - 1] == '-') {
					
					if (int(temp[i]) >= 48 && int(temp[i]) <= 57) {
						if (temp[i - 1] == '-') {
							sign = false;
						}
						//если встречаем цифру, вычисляем ключ
						for (j = i; temp[j] != ' ' && temp[j] != ')'; j++) {
							k = k * 10 + int(temp[j]) - 48;
							/*if (temp[j + 1] != ' ') {
								i = j;
							}*/

						}
						//если ключ отрицательный, меняем знак вычисленному
						if (!sign) {
							k *=-1;
						}
					}
					
					
				}
				//добавление значения ключа корню дерева
				if (i == 1 || i==2 && !sign) {
					t->key = k;
					k = 0;
					sign = true;
					i = j;
				}
				else {
					if (temp[i - 2] == ' ' && temp[i - 1] == '(' ||
						temp[i - 3] == ' ' && temp[i - 2] == '(' && temp[i-1]=='-') {
						//добавление левого потомка
						if (t->left == nullptr  && flag == true) {
							t->left = new TreeNode;
							t->left->parent = t;
							t = t->left;
							t->key = k;
							k = 0;
							sign = true;
							t->left = nullptr;
							t->right = nullptr;
							i = j;
						}
						//добавление правого потомка
						else if (t->right == nullptr) {
							t->right = new TreeNode;
							t->right->parent = t;
							t = t->right;
							t->key = k;
							k = 0;
							sign = true;
							t->right = nullptr;
							t->left = nullptr;
							flag = true;
							i = j;
						}
					}

				}

			}
			//возвращение в родителя после создания потомка
			if (temp[i] == ')') {
				if (temp[i - 1] == '(') { flag = false; }
				if (t->parent != nullptr && temp[i - 1] != '(') {
					t = t->parent;
					k = 0;
					sign = true;
				}
				
				
			}
		}
	}

	
	//рекурсивный прямой обход в глубину
	void Print(TreeNode *t) {
		if (t == nullptr) {
			return;
		}
		cout << t->key << " ";
		Print(t->left);
		Print(t->right);
	}

	//удаление бинарного дерева
	void deleteTree(TreeNode*& t) {
		if (t == nullptr) {
			return;
		}
		deleteTree(t->left);
		deleteTree(t->right);
		delete t;
		t = nullptr;
	}

	//преобразование дерева в целочисленный массив
	void InVector(TreeNode*& t, _vector <int> &arr) {
		if (t == nullptr) {
			return;
		}
		arr.push_back(t->key);
		InVector(t->left, arr);
		InVector(t->right, arr);
	}

	~_Tree() {
		deleteTree(root);
	}
	
};


class AVLTree {
private:
	struct AVLTreeNode {
		int key;
		AVLTreeNode *left;
		AVLTreeNode *right;
		AVLTreeNode *parent;
		int hg;

		AVLTreeNode() {
			left = nullptr;
			right = nullptr;
			parent = nullptr;
			hg = 1;
			key = 0;
		}

		AVLTreeNode( int k) {
			key = k;
			left = nullptr;
			right = nullptr;
			parent = nullptr;
			hg = 1;
		}

	};

	AVLTreeNode* root;


	//поиск минимального элемента
	AVLTreeNode* findMin(AVLTreeNode*& t) {
		return t->left ? findMin(t->left) : t;
	}
	//удаление минимального элемента
	AVLTreeNode* DelMin(AVLTreeNode* t) {
		if (t->left == nullptr) {
			return t->right;
		}
		t->left = DelMin(t->left);
		return balance(t);
	}

	//удаление по ключу
	AVLTreeNode* Del(AVLTreeNode* t, int k) {
		if (k == root->key) {
			AVLTreeNode* L = t->left;
			AVLTreeNode* R = t->right;
			delete t;
			if (R == nullptr) {
				return L;
			}
			AVLTreeNode* min = findMin(R);
			min->right = DelMin(R);
			min->left = L;
			root = min;
			return balance(min);
		}
		else {
			if (t == nullptr) {
				return 0;
			}
			if (k < t->key) {
				t->left = Del(t->left, k);
			}
			else if (k > t->key) {
				t->right = Del(t->right, k);
			}
			else {
				AVLTreeNode* L = t->left;
				AVLTreeNode* R = t->right;
				delete t;
				if (R == nullptr) {
					return L;
				}
				AVLTreeNode* min = findMin(R);
				min->right = DelMin(R);
				min->left = L;
				return balance(min);
			}
		}


		return balance(t);
	}

	//высота поддерева
	int getHg(AVLTreeNode*& t) {
		return t ? t->hg : 0;
	}

	//разница высот поддеревьев узла
	int blFactor(AVLTreeNode*& t) {
		return getHg(t->right) - getHg(t->left);
	}

	//считаем высоту поддерева
	void fixHg(AVLTreeNode*& t) {
		int hgL = getHg(t->left);
		int hgR = getHg(t->right);
		t->hg = (hgL > hgR ? hgL : hgR) + 1;
	}

	//правый поворот
	AVLTreeNode* RightRotate(AVLTreeNode*& t) {
		AVLTreeNode* temp = t->left;
		temp->parent = t->parent;
		t->left = temp->right;
		temp->right = t;
		t->parent = temp;
		fixHg(t);
		fixHg(temp);
		return temp;

		

	}

	//левый поворот
	AVLTreeNode* LeftRotate(AVLTreeNode*& t) {
		AVLTreeNode* temp = t->right;
		temp->parent = t->parent;
		t->right = temp->left;
		temp->left = t;
		t->parent = temp;
		fixHg(t);
		fixHg(temp);
		return temp;

	
	}

	//балансировка дерева
	AVLTreeNode* balance(AVLTreeNode *t) {
		fixHg(t);
		if (blFactor(t) == 2) {
			if (blFactor(t->right) < 0) {
				t->right = RightRotate(t->right);
			}
			return LeftRotate(t);
		}
		if (blFactor(t) == -2) {
			if (blFactor(t->left) > 0) {
				t->left = LeftRotate(t->left);
			}
			return RightRotate(t);
		}
		return t;
	}

	//добавление элемента
	AVLTreeNode* push(AVLTreeNode*& t, int k) {
		if (!t) {
			AVLTreeNode* temp = new AVLTreeNode(k);
			temp->parent = t;
			return temp;
		}
		if (k < t->key) {
			t->left = push(t->left, k);
			if (t->left->parent == nullptr) {
				t->left->parent = t;
			}

		}
		else {
			t->right = push(t->right, k);
			if (t->right->parent == nullptr) {
				t->right->parent = t;
			}
			
		}
		return balance(t);
	}
	//печатаем дерево	
	void Print(AVLTreeNode*& t) {
		if (t == nullptr) {
			return;
		}
		cout << t->key << " ";
		Print(t->left);
		Print(t->right);
	}


	
	//поиск элемента по ключу
	AVLTreeNode* find(AVLTreeNode*t, int k) {
		if (t != nullptr) {
			if (t->key == k) {
				return t;
			}
			else {
				if (k < t->key) {
					find(t->left, k);
				}
				else if (k > t->key) {
					find(t->right, k);
				}
			}
		}
		else {
			return 0;
		}
	}

public:

	AVLTree() {
		root = nullptr;
	}

	
	//создание дерева из обычного
	void CreateTree(_Tree *t) {
		_vector <int> temp;
		t->InVector(t->getRoot(), temp);
		temp.SortMas();
		root = new AVLTreeNode(temp[0]);
		
		for (int i = 1; i < temp.getSize(); i++) {
			root = push(root, temp[i]);
		}
		
		
	}


	
	//добавление элемента
	void push(int k) {
		root = push(root, k);
	}
	//печатаем дерево
	void print() {
		Print(root);
	}

	void printNode(AVLTreeNode* t) {
		if (t != nullptr) {
			cout << t->key<<" ";
		}
		else {
			cout << "Element not exist!" << endl;
		}
		
	}
	
	//удаление по ключу
	void remote(int k) {
		Del(root, k);
	}

	//поиск по ключу
	AVLTreeNode* find(int k) {
		return find(root, k);
	}

	//обход в глубину (прямой)
	void itPreOrder() {
		AVLTreeNode* t = root;
		stack<AVLTreeNode*> st;
		st.push(t);
		while (!st.is_empty()) {
			t = st.pop();
			printNode(t);
			if (t->right != nullptr) {
				st.push(t->right);
			}
			if (t->left != nullptr) {
				st.push(t->left);
			}
		}
	}

	//обход в глубину (обратный)
	void itPostOrder() {
		AVLTreeNode* t = root;
		AVLTreeNode* lastNode = nullptr;
		AVLTreeNode* peekNode = nullptr;
		stack<AVLTreeNode*> st;
		while (!st.is_empty() || t != nullptr) {
			if (t != nullptr) {
				st.push(t);
				t = t->left;
			}
			else {
				peekNode = st.peak();
				if (peekNode->right != nullptr && lastNode != peekNode->right) {
					t = peekNode->right;
				}
				else {
					printNode(peekNode);
					lastNode = st.pop();
				}
			}
		}
	}

	//обход в глубину (центрированный)
	void itInOrder() {
		AVLTreeNode* t = root;
		stack<AVLTreeNode*> st;
		while (!st.is_empty() || t != nullptr) {
			if (t != nullptr) {
				st.push(t);
				t = t->left;
			}
			else {
				t = st.pop();
				printNode(t);
				t = t->right;
			}
		}
	}

	//обход в ширину 
	void levelOrder() {
		AVLTreeNode* t = root;
		queue<AVLTreeNode*> q;
		q.push(root);
		while (!q.is_empty()) {
			t = q.pop();
			printNode(t);
			if (t->left != nullptr) {
				q.push(t->left);
			}
			if (t->right != nullptr) {
				q.push(t->right);
			}
		}
	}
};

enum menu {
	Push = 1, Delete = 2, Preorder = 3, Inorder = 4, Postorder = 5, Levelorder = 6, Exit = 7
};
void printMenu();
void Menu(AVLTree& al, int k);
