#pragma once

template <typename T>
class Stack {
private:
	std::string* stackPtr; //stack pointer
	int size;			   //maximum number of elements on the stack
	int top;			   //number of the current stack element

public:
	//stack constructor
	Stack(int maxSize) {
		size = maxSize;
		stackPtr = new std::string[size];
		top = 0;
	}

	//stack destructor
	~Stack() {
		delete[] stackPtr;
	}

	//function to add an element to the stack
	void push(std::string value) {

		if (top == size - 1) {
			resize();
		}
		stackPtr[++top] = value;
	}

	//function to remove an element from the stack
	std::string pop() {

		return stackPtr[top--];
	}

	//stack top value function without popping it
	std::string peek() {

		return stackPtr[top];
	}

	//function to change the stack size
	void resize() {
		std::string* temp = new std::string[size];

		for (int i = 0; i < size; i++) {
			temp[i] = stackPtr[i];
		}
		delete[]stackPtr;

		int tempSize = size;

		size *= 2;

		stackPtr = new std::string[size];

		for (int i = 0; i < tempSize; i++) {
			stackPtr[i] = temp[i];
		}
		delete[]temp;
	}

	//stack empty check
	bool empty()
	{
		if (top == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}
};