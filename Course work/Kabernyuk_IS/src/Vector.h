#include <iostream>

template <class T>

class Vector {
private:

	unsigned size;
	T* data;
	unsigned all_size;

public:

	Vector()
	{
		data = nullptr;
		size = 0;
		all_size = 50;
		data = new T[all_size];
	}
	Vector(const unsigned input_size) 
	{
		if (input_size == 0) {
			all_size = 2;
		}
		else {
			all_size = input_size * 1.5;
		}
		data = new T[all_size];
	}
	Vector(const T& copy)
		: size(copy.size), data(new T[copy.size])
	{
		std::copy(copy.data, copy.data + copy.size, data);
	}
	~Vector()
	{
		delete[] data;
	}

	void push_back(const T last_obj)
	{
		if (size >= all_size) {
			T* temp = data;
			all_size *= 1.5;
			data = new T[all_size];
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
	void add(const unsigned position, const T value) 
	{
		if (position >= size) {
			std::cout << "The function 'add' was not completed, index out of range." << std::endl;
			std::exit(0);
		}
		else {
			all_size++;
			T* temp = data;
			data = new T[all_size];
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
	void print()                                    
	{
		for (int i = 0; i < size; i++) {
			std::cout << data[i] << " ";
		}
		std::cout << std::endl;
	}
	void erase(const unsigned position)
	{
		if (position >= size) {
			std::cout << "The function 'erase' was not completed, index out of range." << std::endl;
			std::exit(0);
		}
		else {
			int* temp = data;
			data = new T[all_size];
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
	T& find(const unsigned position)
	{
		if (position >= size) {
			std::cout << "The function 'find' was not completed, index out of range." << std::endl;
			std::exit(0);
		}
		else {
			return data[position];
		}
	}
	int get_size()
	{
		return size;
	}
	T& operator[](unsigned int position)
	{
		return data[position];
	}


};