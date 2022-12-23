#pragma once
#include"AList.h"

class DoubleArray
{
public:
	DoubleArray(int row, int column);
	~DoubleArray();//dodelat
	ArrayList<int>& operator[](int index);
private:
	ArrayList<int>** arr;
	int row = 0;
	int column = 0;
};

