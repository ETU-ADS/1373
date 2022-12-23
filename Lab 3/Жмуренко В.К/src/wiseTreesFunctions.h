#pragma once

struct binaryNode // Структура элемента бинарного дерева
{
	binaryNode() {};
	binaryNode(int data, binaryNode* par)
	{
		Inf = data;
		parent = par;
		leftChild = nullptr;
		rightChild = nullptr;
	}

	int Inf;
	binaryNode* leftChild, * rightChild, *parent; // Каждый узел хранит указатели на детей и родителя
};

class BinaryTree
{
	binaryNode* ourTree; // Адрес главного корня дерева
public:

	BinaryTree(); // Конструктор

	void createNode(int data, binaryNode*& Node, binaryNode* par, bool isEmpty);		// Функция создания элемента дерева
	void createRoot(int data, bool isEmpty);							// Функция создания изначального корня дерева
	binaryNode* rootAddressGetter();					// Получение адреса изначального корня дерева
	void insertLeft(binaryNode* parent, int data, bool isEmpty);		// Функция добавления левого элемента дерева
	void insertRight(binaryNode* parent, int data, bool isEmpty);		// Функция добавления правого элемента дерева
	void passingTree(binaryNode* ourTree, int *& arr, int& point);				// Функция центрированного обхода дерева
	void deleteTree(binaryNode*& ourTree);				// Функция высвобождения памяти дерева
};

struct AVLnode
{
	int Inf;
	AVLnode* leftChild, * rightChild, * parent; // Каждый узел хранит указатели на детей и родителя
	int balance; // баланс элемента
};

class AVLTree
{
	AVLnode* ourTree; // Адрес главного корня дерева
public:
	
	AVLTree(); // Конструктор
	int balance(AVLnode*& Node); // Вспомогательная функция для высчитывания баланса
	int balanceDifference(AVLnode*& Node); // Вспомогательная функция для понимания, какое дерево слишком "тяжелое"
	void correctingNodeBalance(AVLnode*& Node); // Функция вызова центрированного обхода
	void balancingTree(AVLnode*& Node);  // Функция балансировки дерева
	AVLnode* insert(int data, AVLnode*& Node); // Функция создания элемента дерева
	AVLnode* singleLeftRotate(AVLnode*& Node); // Левый поворот
	AVLnode* singleRightRotate(AVLnode*& Node); // Правый поворот
	AVLnode* findMin(AVLnode*& Node); // Функция поиска элемента АВЛ-дерева с минимальным значением данных
	AVLnode* findMax(AVLnode*& Node); // Функция поиска элемента АВЛ-дерева с максимальным значением данных
	AVLnode* findForData(int data, AVLnode*& Node); // Функция поиска элемента АВЛ-дерева по значению данных
	AVLnode* deleteTreeElement(int data, AVLnode*& Node); // Функция удаления элемента по значению
	void deleteTree(AVLnode*& ourTree);	// Функция высвобождения памяти дерева
	void balanceChangingTree(AVLnode*& Node);
	void insert(int data); // Функция вызова создания элемента дерева
	void deleteTreeElement(int data); // Функция удаления элемента дерева
	void straightPassing(); // Функция прямого обхода дерева через итерации
	void centralPassing(AVLnode*& Node); // Функция центрированного обхода через рекурсию
	void reversePassing(AVLnode*& Node); // Функция обратного обхода через рекурсию
	void widePassing(); // Функция обхода в ширину через очередь
	void centralPassing(); // Функция вызова центрированного обхода
	void reversePassing(); // Функция вызова обратного обхода
};