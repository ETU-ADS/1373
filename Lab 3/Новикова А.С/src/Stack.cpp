#include "stack.h"

Stack::Stack(int elemAmount)
{
	size = elemAmount;
	data = new AVLTreeNode * [size];
	top = -1;
}
Stack::~Stack()
{
	delete[] data;
}

AVLTreeNode* Stack::peak()
{
	if (!isEmpty())
		return data[top];

	return nullptr;
}

void Stack::pop()
{
	if (isEmpty())
		std::cout << "The stack is empty! Nothing to pop!";

	else
		top--;

}

void Stack::push(AVLTreeNode* value)
{
	if (top == size - 1)
	{
		AVLTreeNode** temp = new AVLTreeNode * [size + 1];
		for (int i = 0; i < size; i++)
			temp[i] = data[i];

		temp[size] = value;

		size++;

		delete[] * &data;
		data = temp;
	}
	else
		data[++top] = value;
}

bool Stack::isEmpty()
{
	return (top < 0);
}