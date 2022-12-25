#pragma once
#include "stack.h"
#include "queue.h"
#include "AVLTree.h"
#include <string>

class BinaryTreeNode
{
public:

	int value;
	BinaryTreeNode* left;
	BinaryTreeNode* right;

	BinaryTreeNode(int data, BinaryTreeNode* left = nullptr, BinaryTreeNode* right = nullptr);
};

class BinaryTree
{
private:
	BinaryTreeNode* head;
	std::ostream& print(std::ostream& ostr, BinaryTreeNode* node);
	void deleteNode(BinaryTreeNode* node);
	void parcing(BinaryTreeNode** node, std::string str, bool& flag);
	void print(BinaryTreeNode* node, std::string str, bool flag);

public:

	BinaryTree();
	~BinaryTree();
	void parcing(std::string str);
	BinaryTreeNode* getRoot();
	void insert(int data);
	void clear();
	void createAVL(AVLTree* tree, BinaryTreeNode* node);
	void print();
	friend std::ostream& operator<<(std::ostream& ostr, const BinaryTree& node);
};
