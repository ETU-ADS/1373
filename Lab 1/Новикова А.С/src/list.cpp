#include "list.h"

List::List()
{
	size = 0;
	head = nullptr;
}

List::~List()
{
	clear();
}

int List::find(double value)
{
	Node* node = head;
	for (int i = 0; i < size; i++)
	{
		if (node->data == value)
			return i;

		node = node->ptrNext;
	}

	std::cout << "Not found";
	return -1;
}

void List::add(int index, double value)
{
	if (index >= 0)
	{
		if (index == 0)
		{
			head = new Node(value, head);
			size++;
		}
		else
		{
			Node *previous = this->head;

			for (int i = 0; i < index - 1; i++)
				previous = previous->ptrNext;

			Node* newNode = new Node(value, previous->ptrNext);
			previous->ptrNext = newNode;
			size++;
		}
	}
	else
	{
		std::cout << "Incorrect index";
	}
}

void List::remove(int index)
{
	if (index >= 0)
	{
		if (index == 0)
		{
			Node* temp = head;
			head = head->ptrNext;
			delete temp;
		}
		else
		{
			Node* previous = this->head;

			for (int i = 0; i < index - 1; i++)
				previous = previous->ptrNext;

			Node* toRemove = previous->ptrNext;
			previous->ptrNext = toRemove->ptrNext;
			delete toRemove;
		}
		size--;
	}
	else
	{
		std::cout << "Incorrect index";
	}
}

int List::getSize()
{
	return size;
}

void List::clear()
{
	while (size)
	{
		Node* temp = head;
		head = head->ptrNext;
		delete temp;
		size--;
	}
}

double& List::operator[](const int index)
{
	int counter = 0;
	Node* current = this->head;

	while (current != nullptr)
	{
		if (counter == index)
			return current->data;

		current = current->ptrNext;
		counter++;
	}
}