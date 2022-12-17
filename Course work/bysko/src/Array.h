#pragma once

#include <iostream>

#include "Edge.h"

template<typename T>
class Array {
private:
	T* array = nullptr;
	int lastIndex = 0, size = 0;

	void resize() {
		if (lastIndex == size) {
			int previousSize = size;
			size = size * 2;
			T* newArray = new T[size];
			for (int i = 0; i < previousSize; i++)
				newArray[i] = array[i];
			delete[] array;
			array = newArray;
		}
	}
public:
	Array() {
		array = new T[10];
		size = 10;
	}
	Array(int N) {
		if (typeid(T).name() == typeid(EDGE).name()) {
			array = new T[N];
			size = N;
		}
		if (typeid(T).name() == typeid(Array<int>).name()) {
			array = new T(N * 2);
			for (int i = 0; i < N; i++)
				array[i] = (N * 2);
			size = N * 2;
		}
		else
		{
			array = new T[N];
			size = N;
		}
	}
	void addToTheEnd(T value) {
		resize();
		array[lastIndex] = value;
		lastIndex++;
	}
	void deleteByIndex(int index) {
		for (int i = index; i < lastIndex; i++)
			array[i] = array[i + 1];
		array[lastIndex - 1] = -1;
		lastIndex--;
	}
	T findByValue(T value) {
		for (int i = 0; i < lastIndex; i++) {
			if (array[i] == value)
				return i;
		}
		return -1;
	}
	T& operator[](int index) {
		if (index < size)
			return array[index];
		else
			throw;
	}
	void insertionSort(int left, int right) {
		if (typeid(EDGE).name() == typeid(T).name()) {
			for (int i = left + 1; i <= right; i++) {
				EDGE current = array[i];
				int previous = i - 1;
				while (previous >= left && array[previous].weight > current.weight) {
					array[previous + 1] = array[previous];
					previous--;
				}
				array[previous + 1] = current;
			}
		}
	}
	int getSize() {
		return lastIndex;
	}
	void print() {
		for (int i = 0; i < lastIndex; i++)
			std::cout << array[i] << ' ';
	}
	~Array() {
		delete[] array;
	}
};