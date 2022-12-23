#pragma once

template<class T>
class Stack {
	T* data;
	int size, ind;
public:
	Stack(int num) {
		size = num;
		data = new T[size];
		ind = 0;
	}

	~Stack() {
		delete[] data;
	}

	void push(T val) {
		if (ind == size - 1) {
			T* new_data = new T[size];
			for (int i = 0; i < size; i++)
				new_data[i] = data[i];
			delete[] data;
			int new_size = size;
			size *= 2;
			data = new T[size];
			for (int i = 0; i < new_size; i++)
				data[i] = new_data[i];
			delete[] new_data;
		}
		data[++ind] = val;
	}

	T pop() {
		return data[ind--];
	}

	T peak() {
		return data[ind];
	}

	bool isEmpty() {
		return ind == 0;
	}
};