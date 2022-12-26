#include <iostream>
#include <fstream>
#include <string>
#include "Stack.h"
#include "Queue.h"

int Max(int a, int b)
{
	if (a >= b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

Stack<int> temp;

class Tree
{
public:
	Tree();
	~Tree();
	
	void DestroyTree();
	void PreorderPrint();
	void ParseTree(std::string parse_string);

private:
	class Node
	{
	public:
		int data;
		Node* left;
		Node* right;
		Node(int data = 0, Node* left = nullptr, Node* right = nullptr) {
			this->data = data;
			this->left = left;
			this->right = right;
		}
	};
	void ParseTree(std::string str, Node*& root);
	void DestroyTree(Node *leaf);
	void PreorderPrint(Node* leaf);
	Node* root;
};



void Tree::ParseTree(std::string str, Node*& root)
{
	if (str != "()") {
		root = new Node;
		int i = 1;
		while (str[i] == ' ')i++;
		if (str[i] != ')') {
			int new_data = str[i] - '0';
			i++;
			while (str[i] != '(' && str[i] != ' ' && str[i] != ')' && str[i] != '\0') {
				new_data *= 10;
				new_data += str[i] - '0';
				i++;
			}
			(root)->data = new_data;
			while (str[i] != ')' && str[i] != '\0' && str[i] != '(') {
				i++;
			}
			if (str[i] != ')') {
				string left, right;
				int sum = 0;
				while (str[i] != '(') i++;
				left += str[i];
				sum++;
				i++;
				while (sum != 0) {
					if (str[i] == '(')sum++;
					if (str[i] == ')')sum--;
					left += str[i];
					i++;
				}
				ParseTree(left, root->left);

				while (str[i] != '(' && str[i] != ')') {
					i++;
				}
				if (str[i] != ')') {
					right += str[i];
					sum++;
					i++;
					while (sum != 0) {
						if (str[i] == '(')sum++;
						if (str[i] == ')')sum--;
						right += str[i];
						i++;
					}
					ParseTree(right, root->right);
				}
				while (str[i] != '(' && str[i] != ')' && str[i] != '\0') {
					i++;
				}
				if (str[i] == '(') {
					std::cout << "EROOR, isnot binary tree";
					exit(0);
				}
			}
		}
	}
}


void Tree::ParseTree(std::string str)
{
	bool flag = 0;
	ParseTree(str, root);
	int num_op = 0;
	int num_cl = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '(') {
			num_op++;
		}
		if (str[i] == ')') {
			num_cl++;
		}
	}
	if (num_op != num_cl) {
		cout << "Error! Wrong brackets!\n";
		exit(0);
	}
}




Tree::Tree()
{
	root = NULL;
}

Tree::~Tree()
{
	DestroyTree();
}

void Tree::DestroyTree(Node *leaf)
{
	if (leaf != NULL)
	{
		DestroyTree(leaf->left);
		DestroyTree(leaf->right);
		delete leaf;
		leaf = NULL;
	}
}

void Tree::DestroyTree()
{
	DestroyTree(root);
}


void Tree::PreorderPrint() {
	PreorderPrint(root);
	std::cout << "\n";
}

void Tree::PreorderPrint(Node* leaf) {
	if (leaf != NULL) {
		temp.push(leaf->data);
		std::cout << leaf->data << ", ";
		PreorderPrint(leaf->left);
		PreorderPrint(leaf->right);
	}
}







class AVLTree
{
private:
	class Node
	{
	public:
		int data;
		Node* left;
		Node* right;
		int balance;
	};
	int HeightTree(Node* root);
	void BalanceValue(Node*& root);
	void RightTurn(Node*& root);
	void LeftTurn(Node*& root);
	void Insert(Node*& root, int value);
	void DestroyAVLTree(Node** root);
	void Output(Node* root);
	Node* MinValueNode(Node* node);
	void DeleteNode(Node*& root, int value);
	void Preorder(Node* root);
	void Inorder(Node* root);
	void Postorder(Node* root);
	void Widthorder(Node* root);
	int balanceFactor(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		else {
			return HeightTree(node->right) - HeightTree(node->left);
		}
	}


	Node* root;
public:
	AVLTree();
	~AVLTree();
	void Insert(int value);
	void DestroyAVLTree();
	void FromTreeToAVL(Tree& tree);
	void Output();
	void DeleteNode(int value);
	void Preorder();
	void Inorder();
	void Postorder();
	void Widthorder();
	

};

AVLTree::AVLTree()
{
	root = NULL;
}

AVLTree::~AVLTree()
{
	DestroyAVLTree(&root);
}


int AVLTree::HeightTree(Node* root)
{
	if (root == NULL)
	{
		return 0;
	}
	int left_height = HeightTree(root->left);
	int right_height = HeightTree(root->right);
	if (left_height > right_height)
	{
		return ++left_height;
	}
	else
	{
		return ++right_height;
	}

}

void AVLTree::BalanceValue(Node*& root)
{
	if (root != NULL)
	{
		root->balance = HeightTree(root->right) - HeightTree(root->left);
	}
}

void AVLTree::RightTurn(Node*& root)
{
	Node* left_child;
	Node* left_right_child;

	left_child = root->left;
	left_right_child = left_child->right;

	left_child->right = root;
	root->left = left_right_child;
	root = left_child;
	BalanceValue(root->right);
	BalanceValue(root);
}

void AVLTree::LeftTurn(Node*& root)
{
	Node* right_child;
	Node* right_left_child;

	right_child = root->right;
	right_left_child = right_child->left;

	right_child->left = root;
	root->right = right_left_child;
	root = right_child;
	BalanceValue(root->left);
	BalanceValue(root);
}

void AVLTree::Insert(Node*& root, int value)
{
	if (root == NULL)
	{
		root = new Node;
		root->data = value;
		root->left = NULL;
		root->right = NULL;
		root->balance = 0;

		if (balanceFactor(root) > 1)
		{
			if (balanceFactor(root->right) < 0)
			{
				RightTurn(root->right);
			}
			LeftTurn(root);
		}
		if (balanceFactor(root) < -1)
		{
			if (balanceFactor(root->left) > 0)
			{
				LeftTurn(root->left);
			}
			RightTurn(root);
		}
	}
	else
	{

		if (value > root->data)
		{
			Insert(root->right, value);
			if (balanceFactor(root) > 1)
			{
				if (balanceFactor(root->right) < 0)
				{
					RightTurn(root->right);
				}
				LeftTurn(root);
			}
			if (balanceFactor(root) < -1)
			{
				if (balanceFactor(root->left) > 0)
				{
					LeftTurn(root->left);
				}
				RightTurn(root);
			}
		}
		else
		{
			Insert(root->left, value);
			if (balanceFactor(root) > 1)
			{
				if (balanceFactor(root->right) < 0)
				{
					RightTurn(root->right);
				}
				LeftTurn(root);
			}
			if (balanceFactor(root) < -1)
			{
				if (balanceFactor(root->left) > 0)
				{
					LeftTurn(root->left);
				}
				RightTurn(root);
			}
		}
		BalanceValue(root);
	}
}

void AVLTree::Insert(int value)
{
	Insert(root, value);
}

void AVLTree::DestroyAVLTree(Node** root)
{
	if ((*root) != NULL)
	{
		DestroyAVLTree(&(*root)->left);
		DestroyAVLTree(&(*root)->right);
		delete *root;
		*root = NULL;
	}
}

void AVLTree::FromTreeToAVL(Tree& tree)
{
	int size = temp.GetSize();
	for (int i = 0; i < size; i++)
	{
		Insert(temp.peak());
		temp.pop();

	}
}



AVLTree::Node* AVLTree::MinValueNode(Node* node)
{
	Node* current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}


void AVLTree::DeleteNode(int value)
{
	DeleteNode(root, value);
}

void AVLTree::DeleteNode(Node*& root, int value)
{
	if (root == NULL)
	{
		return ;
	}
	if (value < root->data)
	{
		DeleteNode(root->left, value);
	}
	else if (value > root->data)
	{
		DeleteNode(root->right, value);
	}
	else
	{
		if ((root->left == NULL) || (root->right == NULL))
		{
			Node* temp = root->left ? root->left : root->right;
 
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else  
				*root = *temp; 
			delete temp;
			temp = NULL;
		}
		else
		{
			Node* temp = MinValueNode(root->left);

			root->data = temp->data;

			DeleteNode(root->left, temp->data);
		}
	}
	if (root == NULL)
	{
		return ;
	}

	BalanceValue(root);
	BalanceValue(root->left);
	BalanceValue(root->right);

	if (balanceFactor(root) > 1)
	{
		if (balanceFactor(root->right) < 0)
		{
			RightTurn(root->right);
		}
		LeftTurn(root);
	}
	if (balanceFactor(root) < -1)
	{
		if (balanceFactor(root->left) > 0)
		{
			LeftTurn(root->left);
		}
		RightTurn(root);
	}
	
}



void AVLTree::Preorder(Node* root)
{
	std::cout << "Preorder:" << std::endl;
	Stack <Node*> iter_stack;
	while ((iter_stack.GetSize() != 0) || (root != NULL))
	{
		if (iter_stack.GetSize() != 0)
		{
			root = iter_stack.peak();
			iter_stack.pop();
		}
		while (root != NULL)
		{
			std::cout << root->data << " ";
			if (root->right != NULL)
			{
				iter_stack.push(root->right);
			}
			root = root->left;
		}
	}
}

void AVLTree::Preorder()
{
	Preorder(root);
}


void AVLTree::Inorder(Node* root)
{
	std::cout << "Inorder:" << std::endl;
	Stack <Node*> iter_stack;
	while ((iter_stack.GetSize() != 0) || (root != NULL))
	{
		if (iter_stack.GetSize() != 0) 
		{
			root = iter_stack.peak();
			iter_stack.pop();
			std::cout << root->data << " ";
			if (root->right != NULL)
			{
				root = root->right;
			}
			else
			{
				root = NULL;
			}
		}
		while (root != NULL)
		{
			iter_stack.push(root);
			root = root->left;
		}
	}
}

void AVLTree::Inorder()
{
	Inorder(root);
}


void AVLTree::Postorder(Node* root)
{
	std::cout << "Postorder:" << std::endl;
	Stack <Node*> iter_stack;
	while ((iter_stack.GetSize() != 0) || (root != NULL))
	{
		if (iter_stack.GetSize() != 0)
		{
			root = iter_stack.peak();
			iter_stack.pop();
			if ((iter_stack.GetSize() != 0) && (root->right == iter_stack.peak()))
			{
				root = iter_stack.peak();
				iter_stack.pop();
			}
			else
			{
				std::cout << root->data << " ";
				root = NULL;
			}
		}
		while(root != NULL)
		{
			iter_stack.push(root);
			if (root->right != NULL)
			{
				iter_stack.push(root->right);
				iter_stack.push(root);
			}
			root = root->left;
		}
	}
}

void AVLTree::Postorder()
{
	Postorder(root);
}


void AVLTree::Widthorder(Node* root)
{
	std::cout << "Widthorder:" << std::endl;
	Queue<Node*> queue(1000);
	do
	{
		std::cout << root->data << " ";
		if (root->left != NULL)
		{
			queue.Push(root->left);
		}
		if (root->right != NULL)
		{
			queue.Push(root->right);
		}
		if (!queue.isEmpty())
		{
			root = queue.Pop();
		}
	} while (!queue.isEmpty());
	std::cout << root->data;
}

void AVLTree::Widthorder()
{
	Widthorder(root);
}


int main()
{
	std::string parse_string;
	std::ifstream fin("1.TXT");
	if (fin.is_open())
	{
		getline(fin, parse_string);
		std::cout << parse_string << std::endl;
	}
	fin.close();
	Tree b;
	b.ParseTree(parse_string);
	b.PreorderPrint();
	AVLTree a;
	a.FromTreeToAVL(b);

	for (int i = 16; i < 25; i++)
	{
		a.Insert(i);
	}

	a.Inorder();
	std::cout << std::endl;
	a.Postorder();
	std::cout << std::endl;
	a.Preorder();
	std::cout << std::endl;
	a.Widthorder();
	std::cout << std::endl;



	return 0;
}