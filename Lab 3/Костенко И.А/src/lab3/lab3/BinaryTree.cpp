#include "BinaryTree.h"
#include <cassert>
#include <iostream>
using namespace std;
template<typename T>
bool BinaryTree<T>::parse(char* str, int strLength)
{
	if (strLength <= 0)
	{
		cout << "Внимание, строка имеет длину <= 0" << endl;
		return false;
	}
	int leftBrackets = 0, rightBrackets = 0;
	for (int i = 0; i < strLength - 1; i++)
	{
		if (str[i] == '(' && str[i-1] == '(')
		{
			cout << "Ошибка! Неверная запись скобчатых структур:у пустого узла потомков быть не может";
			return false;
		}
		if (str[i] == '(')
			leftBrackets++;
		if (str[i] == ')')
			rightBrackets++;
	}
	if (leftBrackets != rightBrackets)
	{
		cout << "Ошибка! Неверная запись скобчатых структур: неравное количество открывающих и закрывающих скобок" << endl;
		return false;
	}
	char val[12];
	short index = 0;
	bool isLongNumber = false;
	Node<T>* item = new Node<T>();
	for (int i = 0; i < strLength; i++)
	{
		if (str[i] != ')' && str[i] != '(')
			if (root == nullptr)
			{
				while (str[i] != ')' && str[i] != '(')
				{
					val[index] = str[i];
					index++;
					i++;
					isLongNumber = true;
				}
				if (isLongNumber) {
					i--;
					isLongNumber = false;
				}
				index = 0;
				root = new Node<T>();
				root->data = atoi(val);//convert char[] into int.
				for (int i = 0; i < 12; i++)
				{
					val[i] = '\0';
				}
				root->left = nullptr;
				root->left = nullptr;
				root->parent = nullptr;
				item = root;
				continue;
			}
		Node<T>* buffer = item;
		if (str[i - 1] == ')' && item->parent != nullptr)
			item = item->parent;
		if (str[i - 1] == '(')
		{
			while (str[i] != ')' && str[i] != '(')
			{
				val[index] = str[i];
				index++;
				i++;
				isLongNumber = true;
			}
			if (isLongNumber) {
				i--;
				isLongNumber = false;
			}
			index = 0;
			if (item->left == nullptr)
			{
				item->left = new Node<T>();
				item = item->left;
				item->left = nullptr;
				item->right = nullptr;
				item->parent = buffer;
				if (str[i] == ')')
					item->isEmpty = true;
				else
					item->data = atoi(val);
			}
			else
			{
				item->right = new Node<T>();
				item = item->right;
				item->data = atoi(val);
				item->left = nullptr;
				item->right = nullptr;
				item->parent = buffer;
			}
			for (int i = 0; i < 12; i++)
			{
				val[i] = '\0';
			}
		}
	}
	return true;
}

template<typename T>
void BinaryTree<T>::print()
{
	print(root, 0);
}

template<typename T>
BinaryTree<T>::BinaryTree()
{
	root = nullptr;
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
	clean(root);
}

template<typename T>
Node<T>* BinaryTree<T>::getRoot()
{
	return root;
}

template<typename T>
void BinaryTree<T>::clean(Node<T>* main)
{
	if (main == nullptr)
		return;
	if (main->left != nullptr && main->left->isEmpty == false && main->left->isVisited == false)
		clean(main->left);
	else
	{
		if (main->right != nullptr && main->right->isEmpty == false && main->right->isVisited == false)
		{
			clean(main->right);
		}
		else
		{
			main->isVisited = true;
			Node<T>* parent = main->parent;
			delete main;
			clean(parent);
		}
	}
}

template<typename T>
void BinaryTree<T>::print(Node<T>* main, int level)
{
	if (main != nullptr && main->isEmpty == false)
	{
		print(main->right, level + 1);
		for (int i = 0; i < level; i++)
			cout << "   ";
		cout << main->data << endl;
		print(main->left, level + 1);
	}
}