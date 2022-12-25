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
	void forward();
	Node<T>* getRoot();
private:
	void forward(Node<T>* main);
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
	void deleteItem(T value);
	void rightRotate(Node<T>* node);
	void leftRotate(Node<T>* node);
	void transformation(Node<T>* btRoot);//корни rb и bt
	void reverse();
	void forward();
	void central();
	void print();
	void inWidth();//обход в ширину.
	Node<T>* insert(T value);
	Node<T>* find(T value);
	Node<T>* getRoot();
private:
	void print(Node<T>* main, int level);
	void clearVisits();
	void clearVisits(Node<T>* main);
	void reverse(Node<T>* main);
	void central(Node<T>* main);
	void forward(Node<T>* main);
	void insertElemFromBT(Node<T>* main);
	void balance(Node<T>* inserted);
	void balanceZeroBlack(Node<T>* node);
	void clean(Node<T>* main);
	void forwardRedCheck();
	Node<T>* forwardRedCheck(Node<T>* main);
	Node<T>* find(T value, Node<T>* main);
	Node<T>* insertVal(T val, Node<T>* main, Node<T>* parent, bool isLeftMode);
private:
	Node<T>* root;
};

