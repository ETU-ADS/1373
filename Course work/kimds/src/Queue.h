#pragma once

template <typename T>
class Queue {
	T* data;
	int top;
	int size;
public:
	Queue(int newSize) {
		data = new T[newSize];
		top = -1;
		size = newSize;
	}
	~Queue() {
		delete[] data;
	}
	void push(T val) {
		if (size - 1 == top) {
			T* newData = new T[size];
			for (int i = 0; i <= top; i++){
				newData[i]=data[i];
			}
			delete[] data;
		}
		for (int i = top + 1; i > 0; i--) {
			data[i]=data[i-1];
		}
		data[0]=val;
		top++;
	}

	bool empty() {
		return top == -1;
	}

	T pop() {
		return data[top--];
	}
};