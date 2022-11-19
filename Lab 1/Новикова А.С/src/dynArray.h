#pragma once
#include <iostream>
#include <string>

class DynArray
{
private:
	int size;
	std::string* data;

public:
	DynArray();
	DynArray(int elemAmount);
	~DynArray();

	int find(std::string value); //найти индекс по значению

	void add(int index, std::string value); //добавить элемент

	void remove(int index); // удалить элемент из списка по индексу

	int getSize();

	void pushBack(std::string value);

	std::string& operator[](const int index);
};
