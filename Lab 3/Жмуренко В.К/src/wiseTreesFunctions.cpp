#include "listFunctions.h"
#include "stackFunctions.h"
#include "queue.h"
#include "wiseTreesFunctions.h"
#include<iostream>
using namespace std;

BinaryTree::BinaryTree()	// Конструктор
{
	ourTree = nullptr;
}

void BinaryTree::createNode(int data, binaryNode*& Node, binaryNode* par, bool isEmpty)	// Функция создания элемента дерева
{
	Node = new binaryNode;
	if (isEmpty == false)
		Node->Inf = data;
	else
		Node->Inf = 0;
	Node->leftChild = nullptr;
	Node->rightChild = nullptr;
	Node->parent = par;
}

void BinaryTree::createRoot(int data, bool isEmpty)	// Функция создания изначального корня дерева
{
	createNode(data, ourTree, nullptr, isEmpty);
}


binaryNode* BinaryTree::rootAddressGetter()		// Получение адреса изначального корня дерева
{
	return(ourTree);
}

void BinaryTree::insertLeft(binaryNode* parent, int data, bool isEmpty)		// Функция добавления левого элемента дерева
{
	createNode(data, parent->leftChild, parent, isEmpty);
}

void BinaryTree::insertRight(binaryNode* parent, int data, bool isEmpty)		// Функция добавления правого элемента дерева
{
	createNode(data, parent->rightChild, parent, isEmpty);
}

void BinaryTree::passingTree(binaryNode* ourTree, int *& arr, int& point)              //Функция центрированного обхода дерева
{
	if (ourTree != nullptr)               //Пока не встретится пустое звено
	{
		passingTree(ourTree->leftChild, arr, point);               //Рекурсивная функция для вывода левого поддерева
		cout << ourTree->Inf << '\t';
		arr[point] = ourTree->Inf;
		point++;
		passingTree(ourTree->rightChild, arr, point);               //Рекурсивная функци для вывода правого поддерева
	}
}

void BinaryTree::deleteTree(binaryNode*& ourTree)		// Функция высвобождения памяти дерева
{
	if (ourTree->leftChild)
		deleteTree(ourTree->leftChild);
	if (ourTree->rightChild)
		deleteTree(ourTree->rightChild);
	delete ourTree;
}

AVLTree::AVLTree()		// Конструктор
{
	ourTree = nullptr;
}

int AVLTree::balance(AVLnode*& Node) // Height
{
	return (Node ? Node->balance : 0);
}

int AVLTree::balanceDifference(AVLnode*& Node) // balance Factor
{
	return(balance(Node->rightChild) - balance(Node->leftChild));
}

void AVLTree::correctingNodeBalance(AVLnode*& Node) // Correcting Height   balance - высота
{
	int left = balance(Node->leftChild);
	int right= balance(Node->rightChild);;
	Node->balance =(right > left ? right : left) + 1;
}

void AVLTree::balancingTree(AVLnode*& Node)
{
	correctingNodeBalance(Node);
	if (Node->balance >= 2)
	{
		if (balanceDifference(Node) >= 2)
		{
			if (balanceDifference(Node->rightChild) < 0)
				Node->rightChild = singleRightRotate(Node->rightChild);
			Node = singleLeftRotate(Node);
		}
		if (balanceDifference(Node) <= -2)
		{
			if (balanceDifference(Node->leftChild) > 0)
				Node->leftChild = singleLeftRotate(Node->leftChild);
			Node=singleRightRotate(Node);
		}
	}
}

AVLnode* AVLTree::insert(int data, AVLnode*& Node)
{
	if (Node == nullptr)
	{
		Node = new AVLnode;
		Node->Inf = data;
		Node->balance = 0;
		Node->leftChild = nullptr;
		Node->rightChild = nullptr;
	}
	else
	{
		if (data < Node->Inf)
			insert(data, Node->leftChild);	// Добавляем в левое поддерево
		else
			insert(data, Node->rightChild);		// Добавляем в правое поддерево
	}
	balancingTree(Node);
	return Node;
}

AVLnode* AVLTree::singleLeftRotate(AVLnode*& Node) // Одиночный левый поворот
{
		AVLnode* item = Node->rightChild;
		Node->rightChild = item->leftChild;
		item->leftChild = Node;
		correctingNodeBalance(Node);
		correctingNodeBalance(item);
		return item;
}

AVLnode* AVLTree::singleRightRotate(AVLnode*& Node) // Одиночный правый поворот
{
		AVLnode* item = Node->leftChild;
		Node->leftChild = item->rightChild;
		item->rightChild = Node;
		correctingNodeBalance(Node);
		correctingNodeBalance(item);
		return item;
}

AVLnode* AVLTree::findMin(AVLnode*& Node) // Функция поиска элемента АВЛ-дерева с минимальным значением данных
{
	if (Node == nullptr)
		return nullptr;
	else
	{
		if (Node->leftChild == nullptr)
			return Node;
		else
			return findMin(Node->leftChild);
	}
}

AVLnode* AVLTree::findMax(AVLnode*& Node) // Функция поиска элемента АВЛ-дерева с максимальным значением данных
{
	if (Node == nullptr)
		return nullptr;
	else
	{
		if (Node->rightChild == nullptr)
			return Node;
		else
			return findMin(Node->rightChild);
	}
}

AVLnode* AVLTree::findForData(int data, AVLnode*& Node) // Функция поиска элемента АВЛ-дерева по значению данных
{
	if (Node == nullptr)
	{
		cout << endl << "Error.This value is not contained in our tree";
		return Node;
	}
	else if (Node->Inf == data)
		return Node;
	else if (data < Node->Inf)
		return findForData(data, Node->leftChild);
	else
		return findForData(data, Node->rightChild);
}
AVLnode* AVLTree::deleteTreeElement(int data, AVLnode*& Node)
{
	AVLnode* minItem;
	if (Node == nullptr)	//	Не нашли нужный элемент
	{
		cout << endl << "Error. This value is not contained in our tree";
		return nullptr;
	}

	//	Проводим поиск элемента
	else if (data < Node->Inf)
		Node->leftChild = deleteTreeElement(data, Node->leftChild);
	else if (data > Node->Inf)
		Node->rightChild = deleteTreeElement(data, Node->rightChild);

	// Элемент был найден

	else 
	{
		if (Node->leftChild && Node->rightChild)	// Имеет двух потомков
		{
			minItem = findMin(Node->rightChild);
			Node->Inf = minItem->Inf;
			Node->rightChild = deleteTreeElement(Node->Inf, Node->rightChild);
			balancingTree(Node);
			return Node;
		}
		else	// Имеет одного или ноль потомков
		{
			minItem = Node;
			if (Node->leftChild == nullptr)
				Node = Node->rightChild;
			else if (Node->rightChild == nullptr)
				Node = Node->leftChild;
			delete minItem;
		}
		if (Node == nullptr)
			return Node;
		balancingTree(Node);
		return Node;
	}
	balancingTree(Node);
	return Node;
}

void AVLTree::insert(int data)
{
	ourTree = insert(data, ourTree);
	balancingTree(ourTree);
}

void AVLTree::deleteTreeElement(int data)
{
	ourTree = deleteTreeElement(data, ourTree);
}

void AVLTree::deleteTree(AVLnode*& Node)		// Функция высвобождения памяти дерева
{
	if (Node->leftChild)
		deleteTree(Node->leftChild);
	if (Node->rightChild)
		deleteTree(Node->rightChild);
	delete Node;
}

void AVLTree::balanceChangingTree(AVLnode*& Node)		// Функция высвобождения памяти дерева
{
	if (Node->leftChild)
		balanceChangingTree(Node->leftChild);
	if (Node->rightChild)
		balanceChangingTree(Node->rightChild);
	correctingNodeBalance(Node->rightChild);;
}

void AVLTree::straightPassing()
{
	List OurList = List();
	Stack OurStack;
	AVLnode* buffer;
	box* listBeggining = OurStack.push(OurList);
	listBeggining->FirstInf = ourTree;
	while (OurStack.isNotEmpty(OurList))
	{
		listBeggining = OurList.addressGetter();
		buffer = listBeggining->FirstInf;
		cout << buffer->Inf << '\t';
		OurStack.pop(OurList);
		if (buffer->rightChild!=nullptr)
		{
			listBeggining = OurStack.push(OurList);
			listBeggining->FirstInf = buffer->rightChild;
		}
		if (buffer->leftChild != nullptr)
		{
			listBeggining = OurStack.push(OurList);
			listBeggining->FirstInf = buffer->leftChild;
		}
	}
}

void AVLTree::centralPassing(AVLnode*& Node)
{
	if (Node != nullptr)
	{
		centralPassing(Node->leftChild);               //Рекурсивная функция для вывода левого поддерева
		cout << Node->Inf << '\t';
		centralPassing(Node->rightChild);               //Рекурсивная функци для вывода правого поддерева
	}
}

void AVLTree::reversePassing(AVLnode*& Node)
{
	if (Node != nullptr)
	{
		reversePassing(Node->leftChild);               //Рекурсивная функция для вывода левого поддерева
		reversePassing(Node->rightChild);               //Рекурсивная функци для вывода правого поддерева
		cout << Node->Inf << '\t';
	}
}

void AVLTree::widePassing()
{
	Queue ourQueue = Queue(15);
	AVLnode* buffer;
	ourQueue.push(ourTree);
	while (ourQueue.isNotEmpty())
	{
		buffer = ourQueue.peak();
		cout << buffer->Inf << '\t';
		ourQueue.pop();
		if (buffer->leftChild != nullptr)
			ourQueue.push(buffer->leftChild);
		if (buffer->rightChild != nullptr)
			ourQueue.push(buffer->rightChild);
	}
}

void AVLTree::centralPassing()
{
	centralPassing(ourTree);
}
void AVLTree::reversePassing()
{
	reversePassing(ourTree);
}