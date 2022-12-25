#include <iostream>
#include "Vector.h"


	Vector::Vector() {                                           //standart constructor
		data = nullptr;
		size = 0;
		all_size = 2;
		data = new int[all_size];
	}


	Vector::Vector(const unsigned input_size) {                 //create the array of the 'input_size' size
		if (input_size == 0) {
			all_size = 2;
		}
		else {
			all_size = input_size * 1.5;
		}
		data = new int[all_size];

	}

	Vector::Vector(const Vector& copy)
		: size(copy.size), data(new int[copy.size])
	{		std::copy(copy.data, copy.data + copy.size, data);
	}


	Vector::~Vector() {                                                   //destructor
		delete[] data;
		data = nullptr;
	}

int& Vector::operator[](unsigned int position) {
		return data[position];
}

void Vector::print() {
	for (int i = 0; i < size; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}


void Vector::push_back(const int last_obj) {
	if (size >= all_size) {
		int* temp = data;
		all_size *= 1.5;
		data = new int[all_size];
		for (int i = 0; i < size; i++) {
			data[i] = temp[i];
		}
		data[size] = last_obj;
		size++;
		delete[] temp;
		temp = nullptr;
	}
	else {
		data[size] = last_obj;
		size++;
	}
}



void Vector::add(const unsigned position, const int value) {
	if (position >= size) {
		std::cout << "The function 'add' was not completed, index out of range." << std::endl;
		std::exit(0);
	}
	else {
		all_size++;
		int* temp = data;
		data = new int[all_size];
		for (int i = 0; i < position; i++) {
			data[i] = temp[i];
		}
		data[position] = value;
		size++;
		for (int i = position + 1; i < size; i++) {
			data[i] = temp[i - 1];
		}
		delete[] temp;
		temp = nullptr;
	}
}


void Vector::erase(const unsigned position) {
	if (position >= size) {
		std::cout << "The function 'erase' was not completed, index out of range." << std::endl;
		std::exit(0);
	}
	else {
		int* temp = data;
		data = new int[all_size];
		for (int i = 0; i < position; i++) {
			data[i] = temp[i];
		}
		size--;
		for (int i = position; i < size; i++) {
			data[i] = temp[i + 1];
		}
		delete[] temp;
		temp = nullptr;
	}
}

void Vector::Delete() {
	delete[] data;
	data = nullptr;
	size = 0;
	all_size = 2;
	data = new int[all_size];
}


int& Vector::find(const unsigned position) {
	if (position >= size) {
		std::cout << "The function 'find' was not completed, index out of range." << std::endl;
		std::exit(0);
	}
	else {
		return data[position];
	}
}

int Vector::get_size() {
	return size;
}