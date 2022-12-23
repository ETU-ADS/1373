#pragma once

template <typename T>
class Arr {
private:
	int arrSize;		//array size
	int arrCapacity;	//array capacity
	T* arr;				//pointer to array
public:
	//array constructor
	Arr(int capacity) {
		arrSize = 0;
		arrCapacity = capacity;
		if (capacity != 0) {
			arr = new T[capacity];
		}
		else {
			arr = 0;
		}
	}

	//array destructor
	~Arr() {
		if (arr) {
			delete[] arr;
		}
	}

	//access element by index
	const T& getElement(int index) {
		if ((arrSize - 1) < index) {
			return -1;
		}
		return arr[index];
	}

	//find index by value
	int findValue(const T& value) {
		for (int i = 0; i < arrSize; i++) {
			if (arr[i] == value) {
				return i;
			}
		}
	}

	//deleting an element by index
	void Delete(const int index) {
		if (index == (arrSize - 1)) {
			arrSize--;
		}
		else if (index < (arrSize - 1)) {
			for (int i = index; i < (arrSize - 1); i++) {
				arr[i] = arr[i + 1];
			}
		}
		arrSize--;
	}

	//adding element by index
	void Insert(int index, const T value) {
		if (arrSize == arrCapacity) {
			resize();
		}

		if (index >= arrSize) {
			arr[arrSize] = value;
		}
		else if (index < arrSize) {
			for (int i = arrSize - 1; i >= index; i--) {
				arr[i + 1] = arr[i];
			}
			arr[index] = value;
			arrSize++;
		}
	}

	//array capacity change
	void resize() {
		T* tempArr = new T[arrCapacity];
		for (int i = 0; i < arrSize; i++) {
			tempArr[i] = arr[i];
		}
		delete[]arr;
		arrCapacity *= 2;
		arr = new T[arrCapacity];
		for (int i = 0; i < arrSize; i++) {
			arr[i] = tempArr[i];
		}
		delete[] tempArr;
	}

	//a function that returns the size of an array
	int size() const {
		return arrSize;
	}
};