#include <iostream>
#include "definitions.h"



LinkedList* LinkList::indexAccess(int index)
{
	if (index == 0)
	{
		std::cout << current->information << std::endl;
		return current;
	}

	while (index != 0)
	{
		current = current->address;
		--index;
	}
	std::cout << current->information << std::endl;
	return current;

}

int LinkList::indexByValue(int value)
{
	int index = 0;
	while (index != -1)
	{
		if (value == current->information)
		{
			return index;
		}
		else
		{
			++index;
			current = current->address;
		}

		if (current == NULL)
			return -1;
	}
}

void LinkList::addingByIndex(int index, int value)
{
	LinkedList* newObj = new LinkedList;
	if (index == 0)
		current = newObj;
	else
	{
		int counter = 0;
		while ((counter - 1) != index)
		{
			current = current->address;
			++counter;
		}
		newObj->address = current->address;
		current->address = newObj;
	}
}

void LinkList::deleteByIndex(int index)
{
	LinkedList* next;
	LinkedList* deleting;
	int counter = 0;
	while (index != (counter - 1))
	{
		current = current->address;
		++counter;
	}
	deleting = current->address;
	current->address = deleting->address;
	delete deleting;
}



int DynamicArray::indexAccess(int index)
{
	if (index >= numberOfElemets)
	{
		std::cout << "error";
		return -1;
	}
	return dArray[index];
}

int DynamicArray::indexByValue(int value)
{
	while (numberOfElemets != -1)
	{
		if (dArray[numberOfElemets - 1] == value)
			return numberOfElemets;
		else
			--numberOfElemets;
	}
	std::cout << "error";
	return -1;
}

void DynamicArray::addingByIndex(int index, int value)
{
	++numberOfElemets;
	if (index > numberOfElemets)
		std::cout << "error";
	int* array1 = new int[numberOfElemets + 1];
	for (int i = 0; i < index; i++)
	{
		array1[i] = dArray[i];
	}
	for (int i = (index + 1); i < numberOfElemets; i++)
	{
		array1[i] = dArray[i];
	}
	array1[index] = value;
	delete[] dArray;
	dArray = array1;
}

void DynamicArray::deleteByIndex(int index)
{
	if (index > numberOfElemets)
		std::cout << "error";
	for (int i = index; i < numberOfElemets; i++)
	{
		dArray[i] = dArray[i + 1];
	}
	--numberOfElemets;
}

StackClass::~StackClass()
{
	while (current != NULL)
	{
		Stack* temp;
		temp = current->address;
		delete current;
		current = temp;
	}
}

StackClass::StackClass()
{
	Stack *current = new Stack;
	current = NULL;
	quantity = -1;
}

std::string StackClass::pop()
{

		Stack* temp;
		std::string temporary;
		--quantity;
		temp = current->address;
		temporary = current->data;
		delete current;
		current = temp;
		return temporary;
}

void StackClass::push(std::string value)
{
		++quantity;
		Stack* newElement = new Stack;
		newElement->address = current;
		current = newElement;
		current->data = value;

}

std::string StackClass::peek()
{
	if (quantity == -1)
	{
		return "0";
	}
	else
		return current->data;
}

void StackClass::deleteElement()
{
	--quantity;
	Stack* temp;
	temp = current->address;
	delete current;
	current = temp;
}