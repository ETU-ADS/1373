#pragma once
#include <iostream>

using namespace std;

template <typename T>
class DynamicArray {
public:
	int size;
	int capacity;
	T* data;

	DynamicArray() {
		size = 0;
		capacity = 0;
		data = nullptr;
	}

	DynamicArray(int newsize) {
		size = newsize;
		capacity = size * 2;
		if (size != 0) {
			data = new T[capacity];
		}
		else {
			data = nullptr;
		}
	}

	~DynamicArray() {
		delete[] data;
	}

	DynamicArray(const DynamicArray& other) {
		data = new T[other.size];
		for (int i = 0; i < other.size; i++) {
			data[i] = other.data[i];
		}
		size = other.size;
		capacity = other.capacity;
	}

	void PushBack(T val) {
		if (size == 0) {
			size++;
			capacity = size * 2;
			data = new T[capacity];
			data[0] = val;
		}
		else {
			if (size < capacity) {
				data[size] = val;
				size++;
			}
			else {
				capacity = size * 2;
				T* new_data = data;
				data = new T[capacity];
				for (int i = 0; i < size; i++) {
					data[i] = new_data[i];
				}
				data[size] = val;
				size++;
				delete[] new_data;
			}
		}
	}

	int GetSize() {
		return size;
	}

	void insert(T val, int ind) {
		if (ind == size) {
			PushBack(val);
		}
		else {
			if (ind < size) {
				if (size < capacity) {
					T* new_data = data;
					data = new T[capacity];
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
					T* new_data = data;
					data = new T[capacity];
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

	void DeleteByInd(int ind) {
		if (ind < size) {
			T* new_data = data;
			data = new T[capacity];
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

	void PrintDynamicArray() {
		for (int i = 0; i < size; i++) {
			cout << data[i] << " ";
		}
	}

	T& operator[](int ind) {
		if (ind > size) {
			cout << "Error" << endl;
		}
		return data[ind];
	}

	int find(T val) {
		int counter = 0;
		while ((counter < size) && (val != data[counter])) {
			counter++;
		}
		return counter;
	}
};