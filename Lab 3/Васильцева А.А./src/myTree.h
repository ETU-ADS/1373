#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "myQueue.h"
#include "myStack.h"

enum colorRB { RED, BLACK };

template <class Type>
class binTree {
private:
	struct leaf {
		Type value;
		leaf* left = NULL;
		leaf* right = NULL;
		leaf* parent = NULL;
	};

	leaf* root = NULL;


	int getNum(std::string input_line, int& i) {
		myQueue<char> num_line;
		int num = 0;
		while (input_line[i] != ' ' && input_line[i] != ')') {
			num_line.push(input_line[i]);
			i++;
		}
		while (!num_line.isEmpty()) {
			num *= 10;
			num = (num + int(num_line.pop_front()) - 48);
		}
		return num;
	};

	bool correctInputData(std::string input_line) {
		int open_brack = 0, close_brack = 0;
		myStack<char> child_stack;
		for (int i = 0; i < input_line.size(); i++) {
			if (input_line[i] == '(') {
				open_brack++;
			}
			if (input_line[i] == ')') {
				close_brack++;
			}
			if (!(input_line[i] >= '0' && input_line[i] <= '9' || input_line[i] == ' ' ||
				input_line[i] == '(' || input_line[i] == ')')) {
				std::cout << "\nReadTreeError::unexpectable_symbol\n";
				return false;
			}
			if (i < input_line.size() - 1) {
				if (input_line[i] == '(' && input_line[i + 1] == '(') {
					std::cout << "\nReadTreeError::extra_open_bracket\n";
					return false;
				}
			}
			if (input_line[i] != ')') {
				child_stack.push(input_line[i]);
			}
			else {
				int star = 0;
				while (!child_stack.isEmpty()) {
					if (child_stack.peak() == '(') {
						child_stack.pop();
						child_stack.push('*');
						break;
					}
					else {
						if (child_stack.peak() == '*') {
							star++;
							if (star > 2) {
								std::cout << "\nReadTreeError::not_binary_tree\n\n";
								return false;
							}
						}
						child_stack.pop();
					}
				}
			}
		}
		if (open_brack != close_brack) {
			std::cout << "\nReadTreeError::uncorrect_brackets\n";
			return false;
		}
		return true;
	};

	void in_order(leaf* u) {
		if (u == NULL) { return; }
		in_order(u->left);
		std::cout << u->value << ' ';
		in_order(u->right);
	};

	void in_order_val(leaf* u, myStack<Type>* out) {
		if (u == NULL) { return; }
		in_order_val(u->left, out);
		(*out).push(u->value);;
		in_order_val(u->right, out);
	};

public:

	bool isEmpty() {
		if (root == NULL) return true;
		else return false;
	}

	void readTree() {
		std::ifstream in_file("tree.txt");
		std::string input_line;
		if (in_file.is_open())
		{
			getline(in_file, input_line);
		}
		else {
			std::cout << "\nreadTreeError::open_file_error\n";
		}
		in_file.close();

		if (!correctInputData(input_line)) {
			return;
		}
		int input_lenght = input_line.size();
		leaf* in_tree = new leaf;
		leaf* curr_node = new leaf;
		for (int i = 1; i < input_lenght; i++) {
			if (root == NULL) {
				in_tree->value = getNum(input_line, i);
				root = in_tree;

				//std::cout << "ReadBinTree::root_set: " << in_tree->value << std::endl;
			}
			else {

				if (input_line[i] == '(' && input_line[i + 1] == ')') {
					i += 2;
				}

				// add left node
				if (input_line[i - 3] >= '0' && input_line[i - 3] <= '9'
					&& input_line[i - 2] == ' ' && input_line[i - 1] == '(') {
					in_tree->left = new leaf;
					in_tree->left->value = getNum(input_line, i);
					in_tree->left->parent = in_tree;
					in_tree = in_tree->left;

					//std::cout << "ReadBinTree::left_child_set: " << in_tree->parent->left->value << std::endl;
				}

				// add right node
				if (input_line[i - 3] == ')' && input_line[i - 2] == ' ' && input_line[i - 1] == '(') {
					in_tree->right = new leaf;
					in_tree->right->value = getNum(input_line, i);
					in_tree->right->parent = in_tree;
					in_tree = in_tree->right;

					//std::cout << "ReadBinTree::right_child_set: " << in_tree->parent->right->value << std::endl;
				}
			}

			if (input_line[i] == ')') {
				in_tree = in_tree->parent;
			}
		}
	};

	void in_order() {
		if (root != nullptr) {
			leaf* curr = root;
			in_order(curr);
			std::cout << '\n';
		}
	}

	void in_order_val(myStack<Type>* out) {
		if (root != nullptr) {
			leaf* curr = root;
			in_order_val(curr, out);
			std::cout << '\n';
		}
	}
};


template <class Type>
class rbTree { // название в разработке
private:

	struct leaf {
		Type value;
		colorRB color;
		leaf* left = NULL;
		leaf* right = NULL;
		leaf* parent = NULL;
	};

	leaf* root = NULL;

	void leftRotate(leaf* elem);
	void rightRotate(leaf* elem);

	leaf* findElem(Type elem) {
		leaf* curr = root;
		// found out which curr is elem
		while (curr->value != elem) {
			if (curr->left == NULL && curr->right == NULL) {
				std::cout << "\nError->delete: unexist element\n";
				return 0;
			}
			if (elem < curr->value) {
				curr = curr->left;
			}
			else {
				curr = curr->right;
			}
		}
		return curr;
	};

	void addBalance(leaf* x);
	void deleteBalance(leaf* x);
	void transplant(leaf* x, leaf* y);

	// deep path with recurs
	void in_order(leaf* u) {
		if (u == NULL) { return; }
		in_order(u->left);
		std::cout << u->value << ' ';
		in_order(u->right);
	};
	void post_order(leaf* u) {
		if (u == NULL) { return; }
		post_order(u->left);
		post_order(u->right);
		std::cout << u->value << ' ';
	}

	int getNum(std::string input_line, int& i); // help func for readTree
	bool correctInputData(std::string input_line); // help func for readTree

public:

	void addElem(Type elem);
	void deleteElem(Type elem);

	void breadthFS();
	void pre_order();
	
	// deep path with recurs
	void in_order();
	void post_order();

	// for visual tree
	void textTree(); // tree out
	 
	void readTree(); // tree in (from file)
};

template <class Type>
void rbTree<Type>::leftRotate(leaf* x) {
	leaf* y = x->right;

	x->right = y->left;
	if (y->left != NULL) {
		y->left->parent = x;
	}
	
	y->parent = x->parent;

	if (x->parent == NULL) { // if x was root
		root = y;
	}
	else {
		if (x == x->parent->left) { // if x was left child
			x->parent->left = y;
		}
		else {
			x->parent->right = y; // if x was right child
		}
	}

	y->left = x;
	x->parent = y;
};

template <class Type>
void rbTree<Type>::rightRotate(leaf* x) {
	leaf* y = x->left;

	x->left = y->right;
	if (y->right != NULL) {
		y->right->parent = x;
	}

	y->parent = x->parent;

	if (x->parent == NULL) { // if x was root
		root = y;
	}
	else {
		if (x == x->parent->left) { // if x was left child
			x->parent->left = y;
		}
		else {
			x->parent->right = y; // if x was right child
		}
	}

	y->right = x;
	x->parent = y;
};

template <class Type>
void rbTree<Type>::addElem(Type elem) {

	leaf* x = new leaf;
	x->value = elem;
	x->color = RED;

	leaf* y = root;
	leaf* z = NULL;

	while (y != NULL) {
		z = y;
		if (x->value < y->value) {
			y = y->left;
		}
		else {
			y = y->right;
		}
	}

	x->parent = z;
	if (z != NULL) {
		if (x->value < z->value) {
			z->left = x;
		}
		else {
			z->right = x;
		}
	}
	else {
		root = x;
	}

	addBalance(x);
};

template <class Type>
void rbTree<Type>::addBalance(leaf* x) {

	leaf* dad = x->parent;

	while (x != root && dad->color == RED) {

		leaf* grandad = dad->parent;
		if (dad == grandad->left) {

			leaf* uncle = grandad->right;
			if (uncle != NULL && uncle->color == RED) {

				dad->color = BLACK;
				uncle->color = BLACK;
				grandad->color = RED;
				x = grandad;
				dad = x->parent;
			}
			else
			{
				if (x == dad->right)
				{
					leftRotate(dad);
					leaf* temp = x;
					x = dad; dad = temp;
				}
				rightRotate(grandad);
				grandad->color = RED;
				dad->color = BLACK;
				break;
			}
		}
		else
		{
			leaf* uncle = grandad->left;
			if (uncle != NULL && uncle->color == RED)
			{
				grandad->color = RED;
				dad->color = BLACK;
				uncle->color = BLACK;

				x = grandad;
				dad = x->parent;
			}
			else
			{
				if (x == dad->left)
				{
					rightRotate(dad);
					leaf* temp = x;
					x = dad; dad = temp;
				}
				leftRotate(grandad);
				dad->color = BLACK;
				grandad->color = RED;
				break;
			}
		}
	}
	root->color = BLACK;
};

//template <class Type>
//rbTree<Type>::leaf* rbTree<Type>::findElem(Type elem) {
//	leaf* curr = root;
//	// found out which curr is elem
//	while (curr->value != elem) {
//		if (curr->left == NULL && curr->right == NULL) {
//			std::cout << "\nError->delete: unexist element\n";
//			return 0;
//		}
//		if (elem < curr->value) {
//			curr = curr->left;
//		}
//		else {
//			curr = curr->right;
//		}
//	}
//	return curr;
//};

template <class Type>
void rbTree<Type>::transplant(leaf* x, leaf* y) {
	if (y == NULL) {
		if (x == x->parent->left) {
			x->parent->left = NULL;
		}
		else {
			x->parent->right = NULL;
		}
	}
	else {
		if (x == root) {
			root = y;
			y->parent = NULL;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
			y->parent = x->parent;
		}
		else {
			x->parent->right = y;
			y->parent = x->parent;
		}
	}
};

template <class Type>
void rbTree<Type>::deleteElem(Type elem) {

	leaf* z = findElem(elem);
	if (z == NULL) {
		return;
	}
	leaf* x, *y;
	colorRB y_co = RED;

	if (z->left == NULL) {
		x = z->right;
		transplant(z, z->right);
		delete z;
	}
	else if (z->right == NULL) {
		x = z->left;
		transplant(z, z->left);
		delete z;
	}
	else {
		y = z->right;
		while (y->left != NULL) {
			y = y->left;
		}
		y_co = y->color;
		
		x = y->right;

		if (y->parent == z) {
			if (x != NULL) {
				x->parent = y;
			}
		}
		else {
			transplant(y, y->right);
			
			y->right = z->right;
			y->right->parent = y;
		}

		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
		delete z;
	}

	if (y_co == BLACK && x != NULL) {
		deleteBalance(x);
	}
};

template <class Type>
void rbTree<Type>::deleteBalance(leaf* x) {
	leaf* w;
	while (x != root and x->color == BLACK) {
		if (x == x->parent->left) {
			w = x->parent->right;

			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				leftRotate(x->parent);
				w = x->parent->right;
			}

			if (w->left->color == BLACK and w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rightRotate(w);
					w = x->parent->right;
				}

				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				leftRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
};

template <class Type>
void rbTree<Type>::breadthFS() {
	if (root == NULL) return;
	myQueue<leaf*> q;
	q.push(root);
	leaf* node;
	while (!q.isEmpty()) {
		node = q.pop_front();
		std::cout << node->value << ' ' /*<< node->color << " | "*/;
		if (node->left != NULL) {
			q.push(node->left);
		}
		if (node->right != NULL) {
			q.push(node->right);
		}
	}
	std::cout << '\n';
};

template <class Type>
void rbTree<Type>::pre_order() {
	if (root == NULL) return;
	myStack<leaf*> s;
	leaf* node = root;
	s.push(node);
	while (!s.isEmpty()) {
		node = s.peak();
		s.pop();
		std::cout << node->value << ' ';
		if (node->right != NULL) {
			s.push(node->right);
		}
		if (node->left != NULL) {
			s.push(node->left);
		}
	}
	std::cout << '\n';
};

template <class Type>
void rbTree<Type>::in_order() {
	if (root != nullptr) {
		leaf* curr = root;
		in_order(curr);
		std::cout << '\n';
	}
};

template <class Type>
void rbTree<Type>::post_order() {
	if (root != nullptr) {
		leaf* curr = root;
		post_order(curr);
		std::cout << '\n';
	}
};

template <class Type>
void rbTree<Type>::textTree() {
	if (root == NULL) {
		std::cout << "Tree is clean" << std::endl;
		return;
	}

	myStack<leaf*> s, t;
	leaf* node = root, * brack = new leaf;
	brack->value = ')';
	s.push(brack);
	s.push(node);
	while (!s.isEmpty()) {
		node = s.peak();
		s.pop();

		if (node == root) {
			std::cout << "(" << node->value;
		}
		else {
			std::cout << " (" << node->value;
		}

		if (node->left == NULL && node->right != NULL) {
			std::cout << " ()";
		}

		if (node->right != NULL) {
			s.push(brack);
			s.push(node->right);
		}
		if (node->left != NULL) {
			s.push(brack);
			s.push(node->left);
		}

		if (node->right == NULL && node->left == NULL) {
			while (s.peak()->value == ')' || s.peak()->value == '(') {
				std::cout << char(s.peak()->value);
				s.pop();
				if (s.isEmpty()) {
					std::cout << '\n';
					return;
				}
			}
		}
	}
};