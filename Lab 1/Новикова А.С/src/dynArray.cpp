#include "dynArray.h"

DynArray::DynArray()
{
	size = 1;
	data = new double[size];
}

DynArray::DynArray(int elemAmount)
{
	size = elemAmount;
	data = new double[size];
}

DynArray::~DynArray()
{
	delete[] data;
}

int DynArray::find(double value)
{
	for (int i = 0; i < size; i++) {
		if (data[i] == value)
			return i;
	}

	std::cout << "Not found";
	return -1; 
}

void DynArray::add(int index, double value)
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

double& DynArray::operator[](const int index)
{
	return data[index];
}
