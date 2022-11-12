#include <iostream>



template <class T>

class Stack {
private:
	class Node_S {

	public:
		Node_S* pNext;
		T data;
		Node_S(T data, Node_S* pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
		}
	};
	Node_S* head;
	unsigned int size;
public:
	Stack() {
		size = 0;
		head = nullptr;
	}
	void clear() {
		Node_S* temp = head;
		while (head != nullptr) {
			temp = head->pNext;
			delete head;
			head = temp;
		}
		size = 0;
	}

	int GetSize() {
		return size;
	}

	void print() {
		if (size == 0) {
			std::cout << 0;
		}
		else {
			Node_S* temp = head;
			for (int i = 0; i < size; i++) {
				std::cout << temp->data << ' ';
				temp = temp->pNext;
			}
			std::cout << std::endl;
		}
	}

	void push(T value) {
		Node_S* temp = new Node_S(value, head);
		head = temp;
		size++;
	}

	void pop() {
		if (size == 0) {
			std::cout << "Steck is empty";
		}
		else {
			Node_S* temp = head;
			head = head->pNext;
			delete temp;
			size--;
		}
	}

	T peak() {
		return head->data;
	}

	bool Empty()
	{
		if (size == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

