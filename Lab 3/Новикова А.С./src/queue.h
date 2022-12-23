#pragma once
#include "AVLTree.h"

class Queue
{
private:
	AVLTreeNode** data;
	int top;
	int size;

public:

	Queue(int elemAmount);
	~Queue();

	void pop();

	void push(AVLTreeNode* value);

	AVLTreeNode* front();

	bool isEmpty();
};


class intQueue
{
private:
	int* data;
	int size;
	int top;

public:
	intQueue(int elemAmount);
	~intQueue();

	int front();

	void pop();

	void push(int value);

	bool isEmpty();
};