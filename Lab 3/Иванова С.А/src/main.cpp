#include <iostream>
#include <string>
#include "Tree.h"
#include <fstream>

using namespace std;

class AVLtree {
	struct Node {
		int key = 0;
		Node* left = nullptr;
		Node* right = nullptr;
		unsigned char height = 0;
	};

	Node* root;

	unsigned char height(Node* node) {
		return node ? node->height : 0;
	}

	int balanceFactor(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		else {
			return height(node->right) - height(node->left);
		}
	}

	void fixHeight(Node* node) {
		unsigned char hLeft = height(node->left);
		unsigned char hRight = height(node->right);
		node->height = (hLeft > hRight ? hLeft : hRight) + 1;
	}

	Node* rotateRight(Node* node) {
		Node* son = node->left;
		node->left = son->right;
		son->right = node;
		fixHeight(node);
		fixHeight(son);
		return son;
	}

	Node* rotateLeft(Node* node) {
		Node* son = node->right;
		node->right = son->left;
		son->left = node;
		fixHeight(node);
		fixHeight(son);
		return son;
	}

	Node* balance(Node* node) {
		fixHeight(node);
		if (balanceFactor(node) == -2) {
			if (balanceFactor(node->left) > 0) {
				node->left = rotateLeft(node->left);
			}
			return rotateRight(node);
		}
		if (balanceFactor(node) == 2) {
			if (balanceFactor(node->right) < 0) {
				node->right = rotateRight(node->right);
			}
			return rotateLeft(node);
		}
		return node;
	}
	//добавление
	Node* insert(Node* node, int data) {
		if (node == nullptr) {
			node = new Node;
			node->key = data;
			node->left = nullptr;
			node->right = nullptr;
			node->height = 0;
		}
		else if (data < node->key) {
			node->left = insert(node->left, data);
		}
		else {
			node->right = insert(node->right, data);
		}
		fixHeight(node);
		return balance(node);
	}
	//поиск
	Node* findMin(Node* node) {
		if (node == nullptr) {
			return nullptr;
		}
		else {
			return node->left ? findMin(node->left) : node;
		}
	}
	//удаление
	Node* remove(Node* node, int data) {
		Node* tmp;
		if (node == nullptr) {
			return nullptr;
		}
		else if (data < node->key) {
			node->left = remove(node->left, data);
		}
		else if (data > node->key) {
			node->right = remove(node->right, data);
		}
		else if (node->left && node->right) {
			tmp = findMin(node->right);
			node->key = tmp->key;
			node->right = remove(node->right, node->key);
		}
		else {
			tmp = node;
			if (node->left == nullptr)
			{
				node = node->right;
			}
			else if (node->right == nullptr)
			{
				node = node->left;
			}
			delete tmp;
		}
		if (node == nullptr) {
			return node;
		}
		return balance(node);
	}

	Node* find(Node* node, int data) {
		if (node == nullptr || node->key == data) {
			return node;
		}
		else if (data < node->key) {
			return find(node->left, data);
		}
		else {
			return find(node->right, data);
		}
	}
	//Прямой обход
	void preOrder(Node* root) {
		if (root == NULL) {
			return;
		}
		cout << root->key << " ";
		preOrder(root->left);
		preOrder(root->right);
	}
	//Симметричный обход
	void inOrder(Node* root) {
		if (root == NULL) {
			return;
		}
		inOrder(root->left);
		cout << root->key << " ";
		inOrder(root->right);
	}
	//Обратный обход
	void postOrder(Node* root) {
		if (root == NULL) {
			return;
		}
		postOrder(root->left);
		postOrder(root->right);
		cout << root->key << " ";
	}

	//Обход в ширину
	void bfsOrder(Node* root) {
		MyList<Node*> node;
		MyList<int> key;
		key.push_back(root->key);
		if (root->left) {
			node.push_back(root->left);
		}
		node.push_back(root->right);
		while (!node.isEmpty()) {
			int i = 0;
			while (i < node.getsize()) {
				if (node[i]) {
					key.push_back(node[i]->key);
					node.insert(node[i]->right, i + 1);
					node[i] = node[i]->left;
					i += 2;
				}
				else {
					node.deletebyind(i);
				}
			}
		}
		for (int i = 0; i < key.getsize(); i++) {
			cout << key[i] << " ";
		}
	}

	void printTreeHelp(Node* node) {
		cout << node->key;
		if (node->left != nullptr || node->right != nullptr) {
			cout << "(";
			if (node->left != nullptr) {
				printTreeHelp(node->left);
			}
			cout << ")(";
			if (node->right != nullptr) {
				printTreeHelp(node->right);
			}
			cout << ")";
		}
	}

public:
	AVLtree() {
		root = nullptr;
	}

	void insert(int data) {
		root = insert(root, data);
	}

	void remove(int data) {
		root = remove(root, data);
	}

	void search(int data) {
		if (find(root, data) == nullptr) {
			cout << "There is no Node with this key " << endl;
		}
		else {
			cout << "Node with such key found " << endl;
		}
	}

	void printTree() {
		if (root != nullptr) {
			cout << "(";
			printTreeHelp(root);
			cout << ")";
		}
		else cout << "Tree is empty" << endl;;
	}

	void PreOrder() {
		preOrder(root);
	}

	void InOrder() {
		inOrder(root);
	}

	void PostOrder() {
		postOrder(root);
	}

	void BFSOrder() {
		bfsOrder(root);
	}
};

class BinaryTree {
private:
	struct Node {
		int key = 0;
		Node* left = nullptr;
		Node* right = nullptr;
	};
	Node* root;

	void deleteTreeHelp(Node* node) {
		if (node->left != nullptr) {
			deleteTreeHelp(node->left);
		}
		if (node->right != nullptr) {
			deleteTreeHelp(node->right);
		}
		delete node;
	}
	void printTreeHelp(Node* node) {
		cout << node->key;
		if (node->left != nullptr || node->right != nullptr) {
			cout << "(";
			if (node->left != nullptr) {
				printTreeHelp(node->left);
			}
			cout << ")(";
			if (node->right != nullptr) {
				printTreeHelp(node->right);
			}
			cout << ")";
		}
	}

	void readTreeHelp(Node** node, string str, bool& flag) {
		if (str != "()") {
			*node = new Node;
			int i = 1;
			while (str[i] == ' ') {
				i++;
			}
			if (str[i] != ')') {
				int new_data = str[i] - '0';
				i++;
				while (str[i] != '(' && str[i] != ' ' && str[i] != ')' && str[i] != '\0') {
					new_data *= 10;
					new_data += str[i] - '0';
					i++;
				}
				(*node)->key = new_data;
				while (str[i] != ')' && str[i] != '\0' && str[i] != '(') {
					i++;
				}
				if (str[i] != ')') {
					string left, right;
					int sumBrackets = 0;
					while (str[i] != '(') i++;
					left += str[i];
					sumBrackets++;
					i++;
					while (sumBrackets != 0) {
						if (str[i] == '(')sumBrackets++;
						if (str[i] == ')')sumBrackets--;
						left += str[i];
						i++;
					}
					readTreeHelp(&(*node)->left, left, flag);

					while (str[i] != '(' && str[i] != ')') {
						i++;
					}
					if (str[i] != ')') {
						right += str[i];
						sumBrackets++;
						i++;
						while (sumBrackets != 0) {
							if (str[i] == '(')sumBrackets++;
							if (str[i] == ')')sumBrackets--;
							right += str[i];
							i++;
						}
						readTreeHelp(&(*node)->right, right, flag);
					}
					while (str[i] != '(' && str[i] != ')' && str[i] != '\0') {
						i++;
					}
					if (str[i] == '(') {
						flag = 1;
					}
				}
			}
		}
	}

	void createAVLtreeHelp(Node* node, AVLtree& tree) {
		tree.insert(node->key);
		if (node->left != nullptr || node->right != nullptr) {
			if (node->left != nullptr) {
				createAVLtreeHelp(node->left, tree);
			}
			if (node->right != nullptr) {
				createAVLtreeHelp(node->right, tree);
			}
		}
	}

	void inOrder(Node* root) {
		if (root == NULL) {
			return;
		}
		inOrder(root->left);
		cout << root->key << " ";
		inOrder(root->right);
	}

public:
	BinaryTree() {
		root = nullptr;
	}

	BinaryTree(int newKey) {
		root = new Node;
		root->key = newKey;
	}

	~BinaryTree() {
		if (root != nullptr) {
			deleteTreeHelp(root);
			root = nullptr;
		}
	}

	void readTree(string str) {
		bool flag = 0;
		readTreeHelp(&root, str, flag);
		int leftBracket = 0;
		int rightBracket = 0;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '(') {
				leftBracket++;
			}
			if (str[i] == ')') {
				rightBracket++;
			}
		}
		if (leftBracket != rightBracket) {
			cout << "Count of left bracket is not equal count of right bracket" << endl;
			deleteTree();
		}
		else if (flag == 1) {
			cout << "This tree is not binary" << endl;;
			deleteTree();
		}
	}

	void deleteTree() {
		if (root != nullptr) {
			deleteTreeHelp(root);
			root = nullptr;
		}
		else {
			cout << "Tree is empty" << endl;
		}
	}

	void printTree() {
		if (root != nullptr) {
			cout << "(";
			printTreeHelp(root);
			cout << ")";
		}
		else cout << "Tree is empty";
	}

	void createAVLtree(AVLtree& tree) {
		if (root != nullptr) {
			createAVLtreeHelp(root, tree);
		}
	}

	void InOrder() {
		inOrder(root);
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	string str;
	ifstream in("file.txt");
	if (in.is_open()) {
		while (getline(in, str)) {
			std::cout << str << std::endl;
		}
	}
	in.close();
	BinaryTree binTree;
	binTree.readTree(str);
	binTree.printTree();
	cout << " - binary tree";
	cout << endl;
	binTree.InOrder();
	cout << " - inorder binary tree";
	cout << endl;
	AVLtree tree;
	binTree.createAVLtree(tree);
	tree.printTree();
	cout << " - AVL tree" << endl;
	int a;
	while (true) {
		cout << "\nВыберете,пожалуйста,опцию:\n1.Вставка элемента\n2.Удаление элемента\n3.Поиск элемента\n4.Прямой обход\n5.Симметричный обход\n6.Обратный обход\n7.Обход в ширину\n8.Выход\n\n";
		cin >> a;
		switch (a) {
		case 1: {
			cout << "Enter element: ";
			cin >> a;
			tree.insert(a);
			tree.printTree();
			cout << endl;
			break;
		}
		case 2: {
			cout << "Enter element: ";
			cin >> a;
			tree.remove(a);
			tree.printTree();
			cout << endl;
			break;
		}
		case 3: {
			cout << "Enter element: ";
			cin >> a;
			tree.search(a);
			tree.printTree();
			cout << endl;
			break;
		}
		case 4: {
			tree.PreOrder();
			cout << endl;
			break;

		}
		case 5: {
			tree.InOrder();
			cout << endl;
			break;
		}
		case 6: {
			tree.PostOrder();
			cout << endl;
			break;
		}
		case 7: {
			tree.BFSOrder();
			cout << endl;
			break;
		}
		case 8: {
			return 0;
			break;
		}
		default: {
			cout << "You entered the wrong number" << endl;
			break;
		}
		}
	}
}