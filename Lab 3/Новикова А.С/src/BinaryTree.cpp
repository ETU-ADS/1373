#include "binaryTree.h"
#include <iostream>

BinaryTreeNode::BinaryTreeNode(int data, BinaryTreeNode* left, BinaryTreeNode* right)
{
	value = data;
	left = left;
	right = right;
}

BinaryTree::BinaryTree()
{
	head = nullptr;
}

BinaryTree::~BinaryTree()
{
	clear();
}

BinaryTreeNode* BinaryTree::getRoot()
{
	return head;
}

void BinaryTree::insert(int data)
{
	if (head == nullptr)
		head = new BinaryTreeNode(data);
	else
	{
		BinaryTreeNode* current = head;

		while (true)
		{
			if (data < current->value)
			{
				if (current->left == nullptr)
				{
					current->left = new BinaryTreeNode(data);
					break;
				}
				else
					current = current->left;
			}
			else if (data > current->value)
			{
				if (current->right == nullptr)
				{
					current->right = new BinaryTreeNode(data);
					break;
				}
				else
					current = current->right;
			}
			else
				break;
		}
	}
}
void BinaryTree::clear()
{
	deleteNode(head);
	head = nullptr;
}

void BinaryTree::deleteNode(BinaryTreeNode* node)
{
	if (node != nullptr)
	{
		deleteNode(node->left);
		deleteNode(node->right);
		delete node;
	}
}

void BinaryTree::parcing(BinaryTreeNode** node, std::string str, bool& flag)
{
	if (str != "()")
	{
		*node = new BinaryTreeNode(0);

		int i = 1;
		char ch[10] = {};
		int index = 0;

		while (str[i] != '(' && str[i] != ' ' && str[i] != ')' && str[i] != '\0')
		{
			ch[index] = str[i];
			i++;
			index++;
		}
		int num = atoi(ch);

		for (int i = 0; i < 10; i++)
			ch[i] = '\0';

		(*node)->value = num;

		while (str[i] != ')' && str[i] != '\0' && str[i] != '(')
			i++;
		while (str[i] != ')' && str[i] != '\0' && str[i] != '(')
			i++;
		if (str[i] != ')')
		{
			std::string left, right;
			int sum = 0;
			while (str[i] != '(') i++;
			left += str[i];
			sum++;
			i++;
			while (sum != 0) {
				if (str[i] == '(')
					sum++;
				if (str[i] == ')')
					sum--;
				left += str[i];
				i++;
			}
			parcing(&(*node)->left, left, flag);

			while (str[i] != '(' && str[i] != ')')
				i++;

			if (str[i] != ')') {
				right += str[i];
				sum++;
				i++;
				while (sum != 0)
				{
					if (str[i] == '(')
						sum++;
					if (str[i] == ')')
						sum--;
					right += str[i];
					i++;
				}
				parcing(&(*node)->right, right, flag);
			}
			while (str[i] != '(' && str[i] != ')' && str[i] != '\0')
				i++;

			if (str[i] == '(') {
				flag = 1;
			}
		}
	}
}

void BinaryTree::parcing(std::string str)
{
	int brLeft = 0;
	int brRight = 0;

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
			brLeft++;
		if (str[i] == ')')
			brRight++;
	}
	if (brLeft != brRight)
	{
		std::cout << "Invalid input! Unequal number of brackets!" << std::endl;
		return;
	}

	bool flag = 0;
	parcing(&head, str, flag);

	if (flag == 1)
	{
		std::cout << "Invalid input! The tree is not binary!" << std::endl;
		clear();
	}

}

void BinaryTree::createAVL(AVLTree* tree, BinaryTreeNode* node)
{
	tree->insert(node->value);
	if (node->left != nullptr || node->right != nullptr)
	{
		if (node->left != nullptr)
			createAVL(tree, node->left);
		if (node->right != nullptr)
			createAVL(tree, node->right);
	}
}

void BinaryTree::print(BinaryTreeNode* node, std::string str, bool flag)
{
	if (node != nullptr)
	{
		std::cout << str;
		if (flag)
		{
			std::cout << "R---";
			str += "     ";
		}
		else
		{
			std::cout << "L---";
			str += "|   ";
		}

		std::cout << node->value << std::endl;

		print(node->left, str, false);
		print(node->right, str, true);
	}
}


void BinaryTree::print()
{
	print(head, "", true);
}


std::ostream& print(std::ostream& ostr, BinaryTreeNode* node)
{
	if (node != nullptr)
	{
		print(ostr, node->left);
		std::cout << ' ' << node->value;
		print(ostr, node->right);
	}
	return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const BinaryTree& node)
{
	return print(ostr, node.head);
}