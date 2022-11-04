#include <iostream>
#include "DynamicArray.h"

using namespace std;


DynamicArray::DynamicArray() {
	size = 0;
	capacity = 0;
	data = nullptr;
}

DynamicArray::DynamicArray(int newsize) {
	size = newsize;
	capacity = size * 2;
	if (size != 0) {
		data = new int[capacity];
	}
	else {
		data = nullptr;
	}
}

DynamicArray::DynamicArray(const DynamicArray& other) {
	data = new int[other.size];
	for (int i = 0; i < other.size; i++) {
		data[i] = other.data[i];
	}
	size = other.size;
	capacity = other.capacity;
}
DynamicArray::~DynamicArray() {
	delete[] data;
}

void DynamicArray::PushBack(int val) {
	if (size == 0) {
		size++;
		capacity = size * 2;
		data = new int[capacity];
		data[0] = val;
	}
	else {
		if (size < capacity) {
			data[size] = val;
			size++;
		}
		else {
			capacity = size * 2;
			int* new_data = data;
			data = new int[capacity];
			for (int i = 0; i < size; i++) {
				data[i] = new_data[i];
			}
			data[size] = val;
			size++;
			delete[] new_data;
		}
	}
}

int DynamicArray::GetSize() {
	return size;
}

void DynamicArray::insert(int val, int ind) {
	if (ind == size) {
		PushBack(val);
	}
	else {
		if (ind < size) {
			if (size < capacity) {
				int* new_data = data;
				data = new int[capacity];
				for (int i = 0; i < size; i++) {
					data[i] = new_data[i];
				}
				data[ind] = val;
				size++;
				for (int i = ind + 1; i < size; i++) {
					data[i] = new_data[i - 1];
				}
				delete[] new_data;
			}

			else {
				capacity = size * 2;
				int* new_data = data;
				data = new int[capacity];
				for (int i = 0; i < size; i++) {
					data[i] = new_data[i];
				}
				data[ind] = val;
				size++;
				for (int i = ind + 1; i < size; i++) {
					data[i] = new_data[i - 1];
				}
				delete[] new_data;
			}
		}
	}

}

void DynamicArray::DeleteByInd(int ind) {
	if (ind < size) {
		int* new_data = data;
		data = new int[capacity];
		for (int i = 0; i < size; i++) {
			data[i] = new_data[i];
		}
		for (int i = ind + 1; i < size; i++) {
			data[i - 1] = new_data[i];
		}
		size--;
		delete[] new_data;
	}
}

void DynamicArray::PrintDynamicArray() {
	for (int i = 0; i < size; i++) {
		cout << data[i] << " ";
	}
}

int& DynamicArray::operator[](int ind) {
	if (ind >= size) {
		cout << "Error" << endl;
	}
	return data[ind];
}

int DynamicArray::find(int val) {
	int counter = 0;
	while ((counter < size) && (val != data[counter])) {
		counter++;
	}
	return counter;
}
void DynamicArray::operator =(const DynamicArray& other) {
	data = new int[other.size];
	for (int i = 0; i < other.size; i++) {
		data[i] = other.data[i];
	}
	size = other.size;
	capacity = other.capacity;
}