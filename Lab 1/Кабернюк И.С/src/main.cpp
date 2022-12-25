#include<iostream>
#include<string>

class Vector {
private:

	unsigned size;
	int* data;
	unsigned all_size;

public:

	Vector() {                                           //standart constructor
		data = nullptr;
		size = 0;
		all_size = 2;
		data = new int[all_size];
	}


	Vector(const unsigned input_size) {                 //create the array of the 'input_size' size
		if (input_size == 0) {
			all_size = 2;
		}
		else {
			all_size = input_size * 1.5;
		}
		data = new int[all_size];

	}

	void push_back(const int last_obj);                 //add the 'last_obj' to the end of the array
	void add(const unsigned position, const int value); //add the 'value' with index 'position' to the array
	void print();                                       //print the array
	void erase(const unsigned position);                //delete the element with index 'position' from the array
	int& find(const unsigned position);                 //get the link to an element with index 'position'
	int get_size();                                     //get the size of the array
	int& operator[](int position);

	~Vector() {                                                   //destructor
		delete[] data;
		data = nullptr;
	}

};

int& Vector::operator[](int position) {
	if (position >= size) {
		std::cout << "Error! Index out of range!";
		std::exit(0);
	}
	else {
		return data[position];
	}
}

void Vector::print() {
	for (int i = 0; i < size; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}


void Vector::push_back(const int last_obj) {
	if (size >= all_size) {
		int* temp = data;
		all_size *= 1.5;
		data = new int[all_size];
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



void Vector::add(const unsigned position, const int value) {
	if (position >= size) {
		std::cout << "The function 'add' was not completed, index out of range." << std::endl;
		std::exit(0);
	}
	else {
		all_size++;
		int* temp = data;
		data = new int[all_size];
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


void Vector::erase(const unsigned position) {
	if (position >= size) {
		std::cout << "The function 'erase' was not completed, index out of range." << std::endl;
		std::exit(0);
	}
	else {
		int* temp = data;
		data = new int[all_size];
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


int& Vector::find(const unsigned position) {
	if (position >= size) {
		std::cout << "The function 'find' was not completed, index out of range." << std::endl;
		std::exit(0);
	}
	else {
		return data[position];
	}
}

int Vector::get_size() {
	return size;
}

/*_______________________________________________________________________________________________________________________________________________*/

class List {
public:
	List() {
		size = 0;
		head = nullptr;
	}


	int GetSize();
	void push_back(const int data);
	int& find(const unsigned position);
	void print();
	void clear();
	void push_front(const int data);
	void add(const unsigned position, const int data);
	void ereas(const unsigned position);
	int& operator[](int position);

	~List() {
		clear();
	}

private:

	class Node {

	public:
		Node* pNext;
		int data;
		Node(int data = 0, Node* pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
		}
	};
	Node* head;
	int size;

};

int& List::operator[](int position) {
	if (position >= size) {
		std::cout << "Error! Index out of range!";
		std::exit(0);
	}
	else {
		return find(position);
	}
}

void List::push_back(int data) {
	if (head == nullptr) {
		head = new Node(data);
	}
	else {
		Node* temp = head;
		while (temp->pNext != nullptr) {
			temp = temp->pNext;
		}
		temp->pNext = new Node(data);
	}
	size++;
}

int List::GetSize() {
	return size;
}

int& List::find(const unsigned position)
{
	if (position >= size) {
		std::cout << "Error! Index out of range!";
		std::exit(0);
	}
	else {
		int count = 0;
		Node* temp = head;
		while (count != position) {
			temp = temp->pNext;
			count++;
		}
		return temp->data;
	}
}

void List::print() {
	Node* temp = head;
	for (int i = 0; i < size; i++) {
		std::cout << temp->data << ' ';
		temp = temp->pNext;
	}
	std::cout << std::endl;
}

void List::clear() {
	Node* temp = head;
	while (head != nullptr) {
		temp = head->pNext;
		delete head;
		head = temp;
	}
	size = 0;
}

void List::push_front(const int data) {
	head = new Node(data, head);
	size++;
}

void List::add(const unsigned position, const int data) {
	if (position == 0) {
		push_front(data);
	}
	else {
		int count = 0;
		Node* prev = head;
		for (int i = 0; i < position - 1; i++) {
			prev = prev->pNext;
		}
		Node* new_element = new Node(data, prev->pNext);
		new_element = prev->pNext;
		size++;
	}
}

void List::ereas(const unsigned position) {
	if (position >= size) {
		std::cout << "Error! Index out of range!";
		std::exit(0);
	}
	else {
		if (position == 0) {
			Node* temp = head;
			head = temp->pNext;
			delete temp;
			size--;
		}
		else {
			int count = 0;
			Node* prev = head;
			for (int i = 0; i < position - 1; i++) {
				prev = prev->pNext;
			}
			Node* temp = prev->pNext;
			prev->pNext = temp->pNext;
			delete temp;
			size--;
		}
	}
}




class Stack {
private:
	class Node_S {

	public:
		Node_S* pNext;
		std::string data;
		Node_S(std::string data = "", Node_S* pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
		}
	};
	Node_S* head;
	int size;
public:
	Stack() {
		size = 0;
		head = nullptr;
	}

	void clear();
	int GetSize();
	void print();
	void push(std::string value);
	void pop();
	std::string peak();


	~Stack() {
		clear();
	}
};


void Stack::clear() {
	Node_S* temp = head;
	while (head != nullptr) {
		temp = head->pNext;
		delete head;
		head = temp;
	}
	size = 0;
}

int Stack::GetSize() {
	return size;
}

void Stack::print() {
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

void Stack::push(std::string value) {
	Node_S* temp = new Node_S(value, head);
	head = temp;
	size++;
}

void Stack::pop() {
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

std::string Stack::peak() {
	return head->data;
}







bool current_bracket(std::string input_str) {

	int count_right_bracket = 0;
	int count_left_bracket = 0;
	for (int i = 0; i < input_str.length(); i++) {

		if (input_str[i] == '(') {
			count_left_bracket++;
		}

		else if (input_str[i] == ')') {
			count_right_bracket++;
		}
	}
	if (count_left_bracket == count_right_bracket) {
		return true;
	}
	else {
		return false;
	}
}


int Priority(std::string operation) {
	if (operation == "+" || operation == "-") {
		return 1;
	}
	else if (operation == "*" || operation == "/") {
		return 2;
	}
	else if (operation == "^") {
		return 3;
	}
	else if (operation == "sin" || operation == "cos") {
		return 4;
	}
}

bool is_digit(std::string number) {
	if (number == "1" || number == "2" || number == "3" || number == "4" || number == "5" || number == "6" || number == "7" ||
		number == "8" || number == "9") {
		return true;
	}
	else {
		return false;
	}
}

bool is_operation(std::string operation) {
	if (operation == "*" || operation == "/" || operation == "+" || operation == "-" || operation == "^" ||
		operation == "sin" || operation == "cos" || operation == "(" || operation == ")") {
		return true;
	}
	else {
		return false;
	}
}

void check_tokens(std::string input_str) {
	std::string output_postfix = "";
	std::string temp = "";
	Stack steck;
	if (!current_bracket(input_str)) {
		std::cout << "Wrong count of brackets" << std::endl;
	}
	else {
		int i = 0;
		for (int i = 0; i <= input_str.length(); i++) {
			if (input_str[i] != ' ') {
				temp += input_str[i];
			}
			else {
				if (is_digit(temp)) {
					output_postfix += (temp + " ");
					temp = "";
				}
				else if (is_operation(temp)) {
					if (temp == "(") {
						steck.push(temp);
						temp = "";
					}
					else if (temp == ")") {
						if (steck.GetSize() != 0) {
							while (steck.peak() != "(") {
								output_postfix += (steck.peak() + " ");
								steck.pop();
							}
							steck.pop();
							temp = "";
						}
						else {
							std::cout << "Attention!! There are error in the recording" << std::endl;
							exit(0);
						}
					}
					else if (is_operation(temp)) {
						if (steck.GetSize() == 0 || steck.peak() == "(") {
							steck.push(temp);
							temp = "";
						}
						else if (Priority(temp) > Priority(steck.peak())) {
							steck.push(temp);
							temp = "";
						}
						else {
							while ((steck.GetSize() != 0) && (Priority(temp) <= Priority(steck.peak())) && (steck.peak() != "(")) {
								output_postfix += (steck.peak() + " ");
								steck.pop();
							}
							steck.push(temp);
							temp = "";
						}
					}
					else {
						std::cout << "Attention!! There are error in the recording" << std::endl;
					}
				}
			}
			if (temp.length() >= 5) {
				std::cout << "Attention!! There are error in the recording" << std::endl;
				exit(0);
			}
		}
		while ((steck.GetSize() != 0) && (steck.peak() != "(")) {
			output_postfix += (steck.peak() + " ");
			steck.pop();
		}
		if (output_postfix == "") {
			std::cout << "Attention!! There are error in the recording" << std::endl;
		}
		else {
			std::cout << "Postfix expression: " << output_postfix;
		}
	}
}




int main() 
{


	std::string input_str;
	std::cout << "Please, enter the infix expression: ";
	getline(std::cin, input_str);
	check_tokens(input_str + " ");

	return 0;
}