#pragma once

template<typename T>
struct Node
{
	Node() {};
	Node(T value, Node<T>* par) {
		data = value;
		parent = par;
		left = nullptr;
		right = nullptr;
	};
	Node(bool Empty) {
		isEmpty = Empty;
	}
	T data;
	bool isEmpty = false;
	bool isVisited = false;
	bool isRed = true;
	bool isPrinted = false;
	Node* left;
	Node* right;
	Node* parent;
};

template<typename T>
class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();
public:
	bool parse(char* str, int strLength);
	void print();
	Node<T>* getRoot();
private:
	void clean(Node<T>* main);
	void print(Node<T>* main, int level);
private:
	Node<T>* root;
};

template<typename T>
class RBTree
{
public:
	RBTree();
	~RBTree();
public:
	void deleteItem(T value);//удаление
	void rightRotate(Node<T>* node);//правый поворот
	void leftRotate(Node<T>* node);//левый поворот
	void transformation(Node<T>* btRoot);//корни rb и bt
	void reverse();//обратный обход
	void forward();//прямой обход
	void central();//центрированный обход
	void inWidth();//обход в ширину.
	Node<T>* insert(T value);//вставка
	Node<T>* find(T value);//поиск
	Node<T>* getRoot();//геттер для корня
private:
	void clearVisits();
	void clearVisits(Node<T>* main);
	void reverse(Node<T>* main);
	void central(Node<T>* main);
	void forward(Node<T>* main);
	void insertElemFromBT(Node<T>* main);
	void balance(Node<T>* inserted);//балансировка удаления
	void balanceZeroBlack(Node<T>* node);//балансировка удаления при чёрной вершине с 0 потомками
	void clean(Node<T>* main);//очистка дерева
	Node<T>* find(T value, Node<T>* main);
	Node<T>* insertVal(T val, Node<T>* main, Node<T>* parent, bool isLeftMode);
private:
	Node<T>* root;
};

