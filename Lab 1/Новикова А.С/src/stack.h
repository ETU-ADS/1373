#pragma once
#include <iostream>
#include <string>

class Stack
{
private:
	int size;
	int top;
	std::string* data;

public:

	Stack(int elemAmount);
	~Stack();

	std::string peak();

	void pop();

	void push(std::string value);

	bool isFull();

	bool isEmpty();
};