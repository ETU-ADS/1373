#pragma once

class DynamicArray {
public:
	int size;
	int capacity;
	int* data;

	DynamicArray();

	DynamicArray(int newsize);

	DynamicArray(const DynamicArray& other);

	~DynamicArray();

	void PushBack(int val);

	int GetSize();

	void insert(int val, int ind);

	void DeleteByInd(int ind);

	void PrintDynamicArray();

	int& operator[](int ind);

	void operator = (const DynamicArray& other);

	int find(int val);
};