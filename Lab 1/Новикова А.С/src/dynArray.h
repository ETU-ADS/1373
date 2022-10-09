#pragma once
#include <iostream>

class DynArray
{
private:
	int size;
	double* data;

public:
	DynArray();
	DynArray(int elemAmount);
	~DynArray();

	int find(double value); //найти индекс по значению

	void add(int index, double value); //добавить элемент

	void remove(int index); // удалить элемент из списка по индексу

	double& operator[](const int index);
};
