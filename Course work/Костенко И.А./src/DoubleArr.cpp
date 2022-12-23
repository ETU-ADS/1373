#include "DoubleArr.h"

DoubleArray::DoubleArray(int row, int column)
{
	this->row = row;
	this->column = column;
	arr = new ArrayList<int>*[row];
	for (int i = 0; i < row; i++)
	{
		arr[i] = new ArrayList<int>(column);
	}
}

DoubleArray::~DoubleArray()
{
	for (int i = 0; i < row; i++)
	{
		arr[i]->~ArrayList();
	}
	delete arr;
}

ArrayList<int>& DoubleArray::operator[](int index)
{
	ArrayList<int>& p = *(arr[index]);
	return p;
}
