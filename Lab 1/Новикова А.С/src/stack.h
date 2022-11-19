#pragma once
#include <iostream>
#include "dynArray.h"

class Stack
{
private:
	DynArray data;
	int top;

public:

	Stack(int elemAmount);
	~Stack();

	std::string peak();

	void pop();

	void push(std::string value);

	bool isFull();

	bool isEmpty();

};