#include "stack.h"

Stack::Stack(int elemAmount)
{
	size = elemAmount;
	data = new std::string[size];
	top = -1;
}
Stack::~Stack()
{
	delete[] data;
}

std::string Stack::peak()
{
	if (!isEmpty())
		return data[top];

	std::string noPeak = "The stack is empty";
	return noPeak;
}

void Stack::pop()
{
	if (isEmpty())
		std::cout << "The stack is empty! Nothing to pop!";

	else
		top--;

}

void Stack::push(std::string value)
{
	if (isFull())
		std::cout << "The stack is full! Unable to push!";

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