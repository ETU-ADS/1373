#pragma once
template<typename T>
class MyList {
public:
	MyList() {
		size = 0;
		head = nullptr;
	}
	~MyList() {
		clear();
	}
	T& operator[] (const int ind) {
		int counter = 0;
		Node<T>* cur = this->head;
		while (cur != nullptr) {
			if (counter == ind) {
				return cur->data;
			}
			cur = cur->adrNext;
			counter++;
		}
	}
	void push_back(T data) {
		if (head == nullptr) {
			head = new Node<T>(data);
		}
		else {
			Node<T>* cur = this->head;
			while (cur->adrNext != nullptr) {
				cur = cur->adrNext;
			}
			cur->adrNext = new Node<T>(data);
		}
		size++;
	}
	int getsize() {
		return size;
	}

	void push_front(T data) {
		head = new Node<T>(data, head);
		size++;
	}
	void insert(T data, int ind) {
		if (ind == 0) {
			push_front(data);
		}
		else {
			Node<T>* tmp = this->head;
			for (int i = 0; i < ind - 1; i++) {
				tmp = tmp->adrNext;
			}
			Node<T>* newNode = new Node<T>(data, tmp->adrNext);
			tmp->adrNext = newNode;
			size++;
		}
	}
	void deletebyind(int ind) {
		if (ind == 0) {
			Node<T>* tmp = head;
			head = head->adrNext;
			delete tmp;
			size--;
		}
		else {
			Node <T>* tmp = this->head;
			for (int i = 0; i < ind - 1; i++) {
				tmp = tmp->adrNext;
			}
			Node <T>* todelete = tmp->adrNext;
			tmp->adrNext = todelete->adrNext;
			delete todelete;
			size--;
		}
	}
	void clear() {
		while (size) {
			Node<T>* tmp = head;
			head = head->adrNext;
			delete tmp;
			size--;
		}
	}
	T find(int val) {
		Node<T>* tmp = head;
		int counter = 0;
		while ((tmp != nullptr) && (val != tmp->data)) {
			tmp = tmp->adrNext;
			counter++;
		}
		return counter;
	}

	bool isEmpty() {
		return head == nullptr;
	}

private:
	template<typename T>
	class Node {
	public:
		Node* adrNext;
		T data;
		Node(T data = T(), Node* adrNext = nullptr) {
			this->data = data;
			this->adrNext = adrNext;
		}
	};
	Node<T>* head;
	int size;
};