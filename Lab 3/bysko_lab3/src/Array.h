#pragma once

template <typename T>
class Array
{
private:
	T* arr = NULL;
	int cap = 1;
	int size = 0;
	//array resizing
	void resize() {
		cap = int(cap * 2);
		T* newArr = new T[cap];

		for (int i = 0; i < size; i++) {
			newArr[i] = arr[i];
		}

		delete[] arr;
		arr = newArr;
	}

public:
	//default constructor
	Array() {
	}
	//constructor for an array of a specific size
	Array(unsigned int N) {
		arr = new T[N];
		size = N;
		cap = N;
	}
	//element search by value
	int findByValue(T value) {
		for (int i = 0; i < size; i++) {
			if (value == arr[i]) {
				return i;
			}
		}
	}
	//added element by index
	void addByIndex(unsigned int index, T element) {
		if (size == cap) {
			resize();
		}

		for (unsigned int i = 0; i < size - index; i++) {
			arr[size - i] = arr[size - i - 1];
		}
		arr[index] = element;
		size++;
	}
	//operator overload[]
	T& operator[](unsigned int index) {
		return arr[index];
	}
	//adding an element to the end of an array
	void addToTheEnd(T value) {
		if (size == cap || size == 0) {
			resize();
		}

		arr[size] = value;
		size++;
	}
	//deleting an element by index
	void deleteByIndex(unsigned int index) {
		for (int i = index; i < size - 1; i++) {
			arr[i] = arr[i + 1];
		}
		arr[size - 1] = 0;
		size--;
	}
	//getting the size of an array
	int getSize() {
		return size;
	}
	//filling an array with random numbers
	void random(int N) {
		for (int i = 0; i < N; i++) {
			addToTheEnd(rand() % 1000 - 50);
		}
	}
	//output array to console
	void print() {
		for (int i = 0; i < size; i++) {
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}
	//destructor
	~Array() {
		delete[]arr;
	}
};