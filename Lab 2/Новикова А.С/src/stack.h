#pragma once
#include <iostream>

struct Run
{
	int start;
	int size;
};

class Stack
{
private:
	Run* data;
	int size;
	int top;

public:

	Stack(int elemAmount);
	~Stack();

	Run peak();

	void pop();

	void push(Run value);

	bool isFull();

	bool isEmpty();

	int getSize();

	void pushBack(Run value);

};
