#pragma once
#include <cstring>

struct LinkedList
{
	int information;
	LinkedList* address;
};
class LinkList
{
private:
	LinkedList* head;
	LinkedList* current;
public:
	LinkedList* indexAccess(int index);
	int indexByValue(int value);
	void addingByIndex(int index, int value);
	void deleteByIndex(int index);
};



class DynamicArray
{
private:
	int* dArray;
	unsigned numberOfElemets;
public:
	int indexAccess(int index);
	int indexByValue(int value);
	void addingByIndex(int index, int value);
	void deleteByIndex(int index);
};



struct Stack
{
	Stack* address;
	std::string data;
};
class StackClass
{
private:
	Stack* current;
	int quantity;
public:
	StackClass();
	~StackClass();
	std::string pop();
	void push(std::string value);
	std::string peek();
	void deleteElement();
};