#pragma once
#include <iostream>

class List
{
private:
	class Node
	{
	public:
		Node* ptrNext;
		double data;

		Node(double data = 0, Node* ptrNext = nullptr)
		{
			this->data = data;
			this->ptrNext = ptrNext;
		}
	};

	int size;
	Node* head;

public:
	List();
	~List();

	int find(double value);

	void add(int index, double value);

	void remove(int index);

	int getSize();

	void clear();

	double& operator[](const int index);
};
