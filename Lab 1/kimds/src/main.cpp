#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
class dynamic_array {
public:
	int size;
	int capacity;
	int* data;
	dynamic_array() {
		size = 0;
		capacity = 0;
		data = nullptr;
	}
	dynamic_array(int newsize) {
		size = newsize;
		capacity = size * 2;
		if (size != 0) {
			data = new int[capacity];
		}
		else {
			data = nullptr;
		}
	}

	~dynamic_array() {
		delete[] data;
	}
	dynamic_array(const dynamic_array& other) {
		data = new int[other.size];
		for (int i = 0; i < other.size; i++) {
			data[i] = other.data[i];
		}
		size = other.size;
		capacity = other.capacity;
	}

	void push_back(int val) {
		if (size == 0) {
			size++;
			capacity = size * 2;
			data = new int[capacity];
			data[0] = val;
		}
		else {
			if (size > capacity) {
				capacity = size * 2;
				int* new_data = data;
				data = new int[capacity];
				for (int i = 0;i < size; i++) {
					data[i] = new_data[i];
				}
				data[size] = val;
				size++;
				delete[] new_data;
			}
			else {
				data[size] = val;
				size++;
			}
		}
	}
	int getsize() {
		return size;
	}
	void insert(int val, int ind) {
		if (ind == size) {
			push_back(val);
		}
		else {
			if (ind < size) {
				if (size > capacity) {
					capacity = size * 2;
					int* new_data = data;
					data = new int[capacity];
					for (int i = 0; i < size; i++) {
						data[i] = new_data[i];
					}
					data[ind] = val;
					size++;
					for (int i = ind; i < size; i++) {
						data[i + 1] = new_data[i];
					}
					delete[] new_data;
				}

				else {
					int* new_data = data;
					data = new int[capacity];
					for (int i = 0; i < size; i++) {
						data[i] = new_data[i];
					}
					data[ind] = val;
					size++;
					for (int i = ind; i < size; i++) {
						data[i + 1] = new_data[i];
					}
					delete[] new_data;
				}
			}
		}

	}
	void deletebyind(int ind) {
		if (ind < size) {
			int* new_data = data;
			data = new int[capacity];
			for (int i = 0; i < size; i++) {
				data[i] = new_data[i];
			}
			for (int i = ind + 1; i < size;i++) {
				data[i - 1] = new_data[i];
			}
			size--;
			delete[] new_data;
		}
	}
	void print_dynamic_array() {
		for (int i = 0;i < size; i++) {
			cout << data[i] << " ";
		}
	}
	int& operator[](int ind) {
		if (ind >= size) {
			cout << "Error" << endl;
		}
		return data[ind];
	}
	int find(int val) {
		int counter = 0;
		while ((counter < size) && (val != data[counter])) {
			counter++;
		}
		return counter;
	}
};
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
class Stack {
	string* data;
	int size, ind;
public:
	Stack(int num) {
		size = num;
		data = new string[size];
		ind = 0;
	}
	~Stack() {
		delete[] data;
	}
	void push(string val) {
		if (ind == size - 1) {
			string* new_data = new string[size];
			for (int i = 0;i < size;i++)
				new_data[i] = data[i];
			delete[] data;
			int new_size = size;
			size *= 2;
			data = new string[size];
			for (int i = 0;i < new_size;i++)
				data[i] = new_data[i];
			delete[] new_data;
		}
		data[++ind] = val;
	}
	string pop() {
		return data[ind--];
	}
	string peak() {
		return data[ind];
	}
	bool is_empty() {
		return ind == 0;
	}
};
int Rang(string act) {
	if (act == "sin" || act == "cos")
		return 4;
	if (act == "^")
		return 3;
	if (act == "*" || act == "/")
		return 2;
	if (act == "+" || act == "-")
		return 1;
	else return 0;
}

string sort(string line) {
	Stack stack(10);
	string conclusion = "", str = "";
	int l_bracket = 0, r_bracket = 0;
	line += " ";
	for (int i = 0;i < line.length();i++) {
		if (line[i] != ' ') {
			str += line[i];
		}
		else if (str > "0" && str <= "9") {
			conclusion += (str + " ");
			str = "";
		}
		else if (str == "sin" || str == "cos" || str == "^" || str == "*" || str == "/" || str == "+" || str == "-") {
			if ((Rang(str) > Rang(stack.peak())) && (!stack.is_empty())) {
				stack.push(str);
				str = "";
			}
			else {
				while ((Rang(str) <= Rang(stack.peak())) && (!stack.is_empty())) {
					conclusion += (stack.pop() + " ");
				}
				stack.push(str);
				str = "";
			}
		}
		else if (str == "(") {
			stack.push(str);
			str = "";
			l_bracket++;
		}
		else if (str == ")") {
			r_bracket++;
			if (l_bracket < r_bracket) {
				cout << "Count of left bracket is not equal count of right bracket" << endl;
				return"";
			}
			while (stack.peak() != "(") {
				conclusion += (stack.pop() + " ");
			}
			stack.pop();
			str = "";
		}
		else {
			cout << str << " is not token" << endl;
			return "";
		}
	}
	if (l_bracket > r_bracket) {
		cout << "Count of left bracket is not equal count of right bracket" << endl;
		return"";
	}
	while (!stack.is_empty()) {
		conclusion += (stack.pop() + " ");
	}
	return conclusion;
}
int main()
{
	string str;
	getline(cin, str);
	cout << sort(str) << endl;
}