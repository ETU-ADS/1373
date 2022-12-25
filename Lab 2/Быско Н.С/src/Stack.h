#pragma once

template <typename T>
class Stack {
private:
	int size = 0;
	struct Node {
		T element;
		Node* adr = NULL;
	};
	Node* next = NULL;
	Node* current = NULL;
	Node* top = NULL;

public:
	//getting the element at the beginning of the stack without removing it
	T peak() {
		return top->element;
	}
	//operation to remove a new element.
	void pop() {
		current = top;
		top = current->adr;
		delete current;
		size--;
	}
	//inserting a new element
	void push(T element) {
		current = top;
		Node* newStackElement = new Node;
		newStackElement->adr = current;
		newStackElement->element = element;
		top = newStackElement;
		size++;
	}
	//stack destructor
	~Stack() {
		for (int i = 0; i < size; i++) {
			current = top->adr;
			delete top;
			top = current;
		}
	}
	//checking the stack for the presence of elements in it
	bool isEmpty() {
		if (size) {
			return false;
		}
		else {
			return true;
		}
	}
	//get stack size
	int getSize() {
		return size;
	}
};