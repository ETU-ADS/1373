#include "wiseTreesFunctions.h"
#include "stackFunctions.h"
#include"listFunctions.h"
#include "taskFunctions.h"
#include <iostream>
#include <cstdlib>
using namespace std;

/*int convertingCharToInt(char string)
{
	switch (string)
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	}
}*/

bool dataVerification(char* string, int length)
{
	if (length <= 0)
	{
		cout << "Error. Incorrect length of string" << endl;
		return false;
	}
	int leftBrackets = 0, rightBrackets = 0;
	for (int i = 0; i < length ; i++)
	{
		if (string[i] == '(' && string[i - 1] == '(')
		{
			cout << "Error. Incorrect input of structures enclosed in square brackets: an empty node cannot have descendants";
			return false;
		}
		if (string[i] == '(')
			leftBrackets++;
		if (string[i] == ')')
			rightBrackets++;
	}
	if (leftBrackets != rightBrackets)
	{
		cout << "Error. Incorrect entry of bracketed structures: unequal number of opening and closing brackets" << endl;
		return false;
	}
	return true;
}

void parsing(char* string, int length, bool resultOfChecking, int*& array, int& countOfElements)
{
	if (resultOfChecking)
	{
		BinaryTree Tree = BinaryTree();
		binaryNode* root = Tree.rootAddressGetter();
		binaryNode* treeItem = new binaryNode();
		char number[10];
		bool isLongNumber = false;
		int index = 0;
		int numberOfDigits = 0;
		for (int i = 0; i < length; i++)
		{
			if (string[i] != ')' && string[i] != '(' && root == nullptr)
			{
				while (string[i] != '(' && string[i] != ')')
				{
					number[index] = string[i];
					index++;
					i++;
				}
				index = 0;
				Tree.createRoot(atoi(number), 0);
				countOfElements++;
				root = Tree.rootAddressGetter();
				treeItem = root;
				for (int a = 0; a < 10; a++)
				{
					number[a] = '\0';
				}
			}
			if (string[i - 1] == '(' && root!=nullptr)
			{

				while (string[i] != '(' && string[i] != ')')
				{
					number[index] = string[i];
					index++;
					i++;
					isLongNumber = true;
				}
				if (isLongNumber) 
				{
					i--;
					isLongNumber = false;
				}
				index = 0;
				if (treeItem->leftChild == nullptr)
				{
					if (string[i] == ')')
					{
						Tree.insertLeft(treeItem, 0, 1);
						countOfElements++;
					}
					else
					{
						Tree.insertLeft(treeItem, atoi(number), 0);
						countOfElements++;
					}
					treeItem = treeItem->leftChild;
				}
				else
				{
					if (string[i] == ')')
					{
						Tree.insertRight(treeItem, 0, 1);
						countOfElements++;
					}
					else
					{
						Tree.insertRight(treeItem, atoi(number), 0);
						countOfElements++;

					}
					treeItem = treeItem->rightChild;
				}
				for (int a = 0; a < 10; a++)
				{
					number[a] = '\0';
				}
			}
			if (string[i - 1] == ')' && treeItem->parent != nullptr)
				treeItem = treeItem->parent;
		}
		int* arr = new int[countOfElements];
		array = arr;
		int i = 0;
		Tree.passingTree(root, arr,i);
		Tree.deleteTree(root);
	}
}