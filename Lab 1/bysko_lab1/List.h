#pragma once
#include "Node.h"

template <typename T>
class List {
private:
	int ListSize;		//list size
	Node <T>* ListHead;	//pointer to the beginning of the list

public:
	//list constructor
	List() {
		ListSize = 0;
		ListHead = nullptr;
	}

	//list destructor
	~List() {
		while (ListSize) {
			Node<T>* temp = ListHead;
			ListHead = ListHead->pNext;
			delete temp;
			ListSize--;
		}
	}

	//add by index function
	void insert(T data, int index) {
		if (index == 0) {
			push_front(data);
		}
		else {
			Node<T>* previous = this->head;
			for (int i = 0; i < (index - 1); i++)
			{
				previous = previous->pNext;
			}
			Node<T>* newNode = new Node<T>(data, previous->pNext);
			previous->pNext = newNode;
			ListSize++;
		}
	}

	//delete function by index
	void remove(int index) {
		if (index == 0)
		{
			pop_front();
		}
		else
		{
			Node<T>* previous = this->head;
			for (int i = 0; i < index - 1; i++)
			{
				previous = previous->pNext;
			}
			Node<T>* toDelete = previous->pNext;
			previous->pNext = toDelete->pNext;
			delete toDelete;
			ListSize--;
		}
	}

	//element index lookup function
	int find(const T data) {
		Node<T>* node = this->head;
		int n = GetSize();
		for (int i = 0; i < n; i++) {
			if (node->data == data) {
				return i + 1;
			}
			node = node->pNext;
		}
		return 0;
	}

	//element search function by index
	const T& getElement(int index) {
		int counter = 0;
		Node<T>* current = this->head;
		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->data;
			}
			current = current->pNext;
			counter++;
		}
	}

	//adding an element to the beginning of the list
	void push_front(T data) {
		ListHead = new Node<T>(data, ListHead);
		ListSize++;
	}

	//adding an element to the end of a list
	void push_back(T data) {
		if (ListHead == nullptr)
		{
			ListHead = new Node<T>(data);
		}
		else
		{
			Node<T>* current = this->ListHead;
			while (current->pNext != nullptr)
			{
				current = current->pNext;
			}
			current->pNext = new Node<T>(data);
		}
		ListSize++;
	}

	//removing the first element in the list
	void pop_front()
	{
		Node<T>* temp = ListHead;
		ListHead = ListHead->pNext;
		delete temp;
		ListSize--;
	}

	//get the number of elements in a list
	int GetSize() {
		return ListSize;
	}
};