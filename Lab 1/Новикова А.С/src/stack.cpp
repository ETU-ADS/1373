#include "stack.h"

Stack::Stack(int elemAmount)
{
	top = -1;
}
Stack::~Stack()
{
	top = 0;
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
	{
		data.pushBack(value);
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
	return (top == data.getSize() - 1);
}