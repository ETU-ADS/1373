#pragma once

#include <iostream>

template<typename T>
class Stack {
private:
	struct Node
	{
		T value;
		Node* next;
	};

	Node* head = (0, nullptr);
public:
	Stack() {
	}
	Stack(const int count) {
		if (count <= 0)
			return;

		head = new Node;
		head->next = nullptr;

		if (count == 1) {
			head->next = nullptr;
			return;
		}
		if (count == 2) {
			Node* current = new Node;
			head->next = current;
			return;
		}

		Node* current = new Node;
		current->next = nullptr;
		head->next = current;

		for (int i = 0; i < count - 2; i++) {
			Node* next = new Node;
			current->next = next;
			current = next;
			current->next = nullptr;
		}
	}
	void push(T element) {
		Node* newNode = new Node;
		newNode->next = nullptr;
		newNode->value = element;
		newNode->next = head;
		head = newNode;
	}
	T pop() {
		if (isEmpty())
			return 0;
		return head->field;
	}
	T peak() {
		if (isEmpty())
			return 0;
		return head->field;
	}
	bool isEmpty() {
		if (head == nullptr)
			return true;
		return false;
	}
	void print() {
		if (head == nullptr) {
			return;
		}

		Node* element = head;

		while (element->next != nullptr) {
			std::cout << element->value;
			element = element->next;
		}
		std::cout << element->value;
	}
	~Stack() {
		if (head == nullptr) {
			return;
		}

		Node* current = head, * next = current->next;

		while (next != nullptr) {
			delete current;
			current = next;
			next = next->next;
		}
		delete current;
		head = nullptr;
	}
};