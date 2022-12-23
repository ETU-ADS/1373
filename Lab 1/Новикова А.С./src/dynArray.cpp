#include "dynArray.h"

DynArray::DynArray()
{
	capacity = 1;
	size = 0;
	data = new std::string[capacity];
}

DynArray::DynArray(int elemAmount)
{
	capacity = elemAmount;
	size = 0;
	data = new std::string[capacity];
}

DynArray::~DynArray()
{
	delete[] data;
}

void DynArray::expand()
{
	capacity *= 2;

	std::string* temp = new std::string[capacity];

	for (int i = 0; i < size; i++)
		temp[i] = data[i];

	delete[] data;
	data = temp;

}

int DynArray::find(std::string value)
{
	for (int i = 0; i < size; i++) {
		if (data[i] == value)
			return i;
	}

	std::cout << "Not found";
	return -1; 
}

void DynArray::add(int index, std::string value)
{
	if (index <= size)
	{
		if (index == size)
			pushBack(value);
		else
		{
			if (size >= capacity)
				expand();

			for (int i = 0; i < size - index; i++)
				data[size - i] = data[size - i - 1];

			data[index] = value;
			size++;
		}
	}
	else
		std::cout << "Incorrect index.\n";
}

void DynArray::remove(int index)
{
	if (index >= 0 && index < size)
	{
		if (index == size - 1)
			size--;
		else 
		{
			for (int i = index; i < size; i++)
				data[i] = data[i + 1];

			size--;
		}
	}
	else
		std::cout << "Incorrect index";
}

int DynArray::getSize()
{
	return size;
}

void DynArray::pushBack(std::string value)
{
	if (size >= capacity)
		expand();

	data[size++] = value;
}

std::string& DynArray::operator[](const int index)
{
	if (index >= 0 && index < size)
		return data[index];
}
