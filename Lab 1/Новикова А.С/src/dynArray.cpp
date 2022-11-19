#include "dynArray.h"

DynArray::DynArray()
{
	size = 1;
	data = new std::string[size];
}

DynArray::DynArray(int elemAmount)
{
	size = elemAmount;
	data = new std::string[size];
}

DynArray::~DynArray()
{
	delete[] data;
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
	if (index >= 0)
	{
		if (index < size) 
			data[index] = value;
	}
	else
	{
		std::cout << "Incorrect index";
	}
}

void DynArray::remove(int index)
{
	if (index >= 0)
	{
		if (index == size - 1)
		{
			size--;
		}
		else if (index < size - 1)
		{
			for (int i = index; i < size - 1; i++)
				data[i] = data[i + 1];

			size--;
		}
		else
		{
			std::cout << "Nothing to remove";
		}
	}
	else
	{
		std::cout << "Incorrect index";
	}
}

int DynArray::getSize()
{
	return size;
}

void DynArray::pushBack(std::string value)
{
	std::string* temp = new std::string[size + 1];
	for (int i = 0; i < size; i++)
		temp[i] = data[i];

	temp[size++] = value;

	delete[] *&data;
	data = temp;
}

std::string& DynArray::operator[](const int index)
{
	return data[index];
}
