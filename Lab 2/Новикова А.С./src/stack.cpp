#include "stack.h"

Stack::Stack(int elemAmount)
{
	size = elemAmount;
	data = new Run[size];
	top = -1;
}
Stack::~Stack()
{
	delete[] data;
}

Run Stack::peak()
{
	return data[top];
}

void Stack::pop()
{
	if (isEmpty())
		std::cout << "The stack is empty! Nothing to pop!";

	else
		top--;

}

void Stack::push(Run value)
{
	if (isFull())
	{
		pushBack(value);
		top++;
	}

	else
		data[++top] = value;
}

bool Stack::isEmpty()
{
	return (top < 0);
}

bool Stack::isFull()
{
	return (top == size - 1);
}

int Stack::getSize()
{
	return top;
}

void Stack::pushBack(Run value)
{
	Run* temp = new Run[size + 1];
	for (int i = 0; i < size; i++)
		temp[i] = data[i];

	temp[size++] = value;

	delete[] * &data;
	data = temp;
}