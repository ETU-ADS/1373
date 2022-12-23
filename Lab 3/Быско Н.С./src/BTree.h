#pragma once

#include <iostream>

#include "Array.h"
#include "Stack.h"
#include "BTreeNode.h"

class BTree {
private:
	Node* root = nullptr;

	int bracketsCount = 0;
	int H = 0;
	int amount = 0;
	//array for storing tree nodes
	Array<Node*> BTArr;
	//checking if a tree is binary
	int isBTree(int start, int end, Array<char>& brackets) {
		int countOpen = 0, countClose = 0, max = 0, newStart = start + 1;
		if ((start == end) || (start == end - 1))
			return 0;
		for (int i = start + 1; i <= end - 1; ++i) {
			if (brackets[i] == '(')
				++countOpen;
			else if (brackets[i] == ')')
				--countOpen;
			if (countOpen == 0) {
				++countClose;
				int count = isBTree(newStart, i, brackets);
				newStart = i + 1;
				if (count > 2)
					std::cout << "A node in your tree has more than two children" << std::endl;
			}
		}
		return countClose;
	}
	//symmetrical bypass
	void inOrderPrint(Node* node) {
		if (node) {
			inOrderPrint(node->l);
			if (node)
				std::cout << (node->data);
			else
				std::cout << "-";
			std::cout << ' ';
			inOrderPrint(node->r);
		}
		else {
			return;
		}
	}

public:
	//creating a tree from strings
	bool createBTree(char* userArr) {
		int maxH = 0;
		bool null = false, addR = false, end = false;

		Node* previous = root;

		Array<char> bracketsArr;

		int count = 0;

		for (int i = 0; !end; ++i) {
			switch (userArr[i])
			{
			case '(': {
				bracketsCount++;
				bracketsArr.addToTheEnd('(');
				if (userArr[i + 1] == ')')
					null = true;
				else {
					++maxH;
					if (maxH > H)
						H = maxH;
					null = false;
				}
				break;
			}
			case ' ': {
				break;
			}
			case ')': {
				--bracketsCount;
				bracketsArr.addToTheEnd(')');
				if (userArr[i + 1] != ')')
					addR = !addR;
				if (!null) {
					maxH--;
					previous = previous->p;
				}
				break;
			}
			case '\0': {
				end = true;
				break;
			}
			default: {
				int j = 0;
				char* temp = new char[8];

				while (userArr[i] != '(' && userArr[i] != ')' && userArr[i] != ' ') {
					if (j < 8) {
						temp[j] = userArr[i];
						i++;
						j++;
					}
					else {
						std::cout << "Too big number." << std::endl;
						return false;
					}
				}

				while (j < 8) {
					temp[j] = '\0';
					j++;
				}

				Node* tempNode = new Node;
				tempNode->data = temp;

				if (amount == 0) {
					root = tempNode;
					root->p = root;
				}
				else if (amount == 1) {
					root->l = tempNode;
					tempNode->p = root;
					previous = tempNode;
				}
				else if (!addR) {
					previous->l = tempNode;
					tempNode->p = previous;
					previous = tempNode;
				}
				else if (addR) {
					previous->r = tempNode;
					tempNode->p = previous;
					previous = tempNode;
					addR = false;
				}
				amount++;
				i--;
				break;
			}
			}
		}

		if (bracketsCount != 0) {
			std::cout << "Invalid brackets." << std::endl;
			return false;
		}

		int firsrB = 0, lastB = bracketsArr.getSize() - 1;

		isBTree(firsrB, lastB, bracketsArr);

		Array<Node*> tempArray;
		if (root) 
			tempArray.addToTheEnd(root);
		while (tempArray.getSize() != 0) {
			BTArr.addToTheEnd(tempArray[0]);
			if (tempArray[0]) {
				if (tempArray[0]->l) 
					tempArray.addToTheEnd(tempArray[0]->l);
				else 
					tempArray.addToTheEnd(nullptr);

				if (tempArray[0]->r) 
					tempArray.addToTheEnd(tempArray[0]->r);
				else 
					tempArray.addToTheEnd(nullptr);
			}
			tempArray.deleteByIndex(0);
		}

		return true;
	}
	//symmetrical bypass
	void inOrderPrint() {
		std::cout << "Centered traverse(inOrder):" << std::endl;
		inOrderPrint(root);
		std::cout << std::endl;
	}
	//function to get the root
	Node* getRoot() {
		return root;
	}
	//destructor
	~BTree() {
		for (int i = 0; i < BTArr.getSize(); ++i) {
			if (BTArr[i]) {
				delete[](BTArr[i]->data);
				delete BTArr[i];
			}
		}
	}
};