#include "queue.h"
#include <iostream>

Queue::Queue(int elemAmount)
{
	size = elemAmount;
	data = new AVLTreeNode * [size];
	top = -1;
}

Queue::~Queue()
{
	delete[] data;
}

void Queue::pop()
{
	if (isEmpty())
		std::cout << "The queue is empty! Nothing to pop!";

	else
		top--;
}

void Queue::push(AVLTreeNode* value)
{
	if (top == size - 1)
	{
		AVLTreeNode** temp = new AVLTreeNode * [size + 1];
		for (int i = 0; i <= top; i++)
			temp[i] = data[i];

		size++;
		delete[] * &data;
		data = temp;
	}

	for (int i = top + 1; i > 0; --i)
		data[i] = data[i - 1];

	data[0] = value;
	top++;
}

AVLTreeNode* Queue::front()
{
	if (!isEmpty())
		return data[top];

	return nullptr;
}

bool Queue::isEmpty()
{
	return (top < 0);
}

/////////////////

intQueue::intQueue(int elemAmount)
{
	size = elemAmount;
	data = new int[size];
	top = -1;
}
intQueue::~intQueue()
{
	delete[] data;
}

int intQueue::front()
{
	if (!isEmpty())
		return data[top];

	return -1;
}

void intQueue::pop()
{
	if (isEmpty())
		std::cout << "The stack is empty! Nothing to pop!";

	else
		top--;
}

void intQueue::push(int value)
{
	if (top == size - 1)
	{
		int* temp = new int[size + 1];
		for (int i = 0; i <= top; i++)
			temp[i] = data[i];

		size++;
		delete[] * &data;
		data = temp;
	}

	for (int i = top + 1; i > 0; --i)
		data[i] = data[i - 1];

	data[0] = value;
	top++;
}

bool intQueue::isEmpty()
{
	return (top < 0);
}
