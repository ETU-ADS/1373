#pragma once
class Vector {
private:

	unsigned size;
	int* data;
	unsigned all_size;

public:

	Vector();
	Vector(const unsigned input_size);
	Vector(const Vector& copy);
	~Vector();

	void push_back(const int last_obj);                 //add the 'last_obj' to the end of the array
	void add(const unsigned position, const int value); //add the 'value' with index 'position' to the array
	void print();                                       //print the array
	void erase(const unsigned position);                //delete the element with index 'position' from the array
	int& find(const unsigned position);                 //get the link to an element with index 'position'
	int get_size();                                     //get the size of the array
	void Delete();
	int& operator[](unsigned int position);


};