#pragma once

#include "Array.h"

class DoubleArray {
private:
	Array<int>** array;
	int row = 0;
	int column = 0;

public:
	DoubleArray(int row, int column) {
		this->row = row;
		this->column = column;

		array = new Array<int>*[row];

		for (int i = 0; i < row; i++)
			array[i] = new Array<int>(column);
	}
	~DoubleArray() {
		for (int i = 0; i < row; i++)
			array[i]->~Array();
		delete array;
	}
	Array<int>& operator[](int index) {
		Array<int>& p = *(array[index]);
		return p;
	}
};