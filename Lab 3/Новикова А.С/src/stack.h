#pragma once

#include <iostream>
#include "AVLTree.h"

class Stack
{
private:
	AVLTreeNode** data;
	int size;
	int top;

public:

	Stack(int elemAmount);
	~Stack();

	AVLTreeNode* peak();

	void pop();

	void push(AVLTreeNode* value);

	bool isEmpty();

};
