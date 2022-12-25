#pragma once
#include <string>

struct AVLTreeNode
{
	int value;
	AVLTreeNode* right;
	AVLTreeNode* left;
	int height;

};

class AVLTree
{
private:

	AVLTreeNode* head;

	void deleteNode(AVLTreeNode* node);
	AVLTreeNode* insert(int data, AVLTreeNode* node);
	AVLTreeNode* rightRotation(AVLTreeNode* node);
	AVLTreeNode* leftRotation(AVLTreeNode* node);
	AVLTreeNode* doubleRightRotation(AVLTreeNode* node);
	AVLTreeNode* doubleLeftRotation(AVLTreeNode* node);
	AVLTreeNode* toBalance(AVLTreeNode* node);
	AVLTreeNode* getMin(AVLTreeNode* node);
	AVLTreeNode* remove(int data, AVLTreeNode* node);
	AVLTreeNode* find(int data, AVLTreeNode* node);
	int getHeight(AVLTreeNode* node);
	int getBalance(AVLTreeNode* node);
	void preorderDFS(AVLTreeNode* node);
	void inorderDFS(AVLTreeNode* node);
	void postorderDFS(AVLTreeNode* node);
	void BFS(AVLTreeNode* node);
	void print(AVLTreeNode* node, std::string str, bool flag);


public:
	AVLTree();
	~AVLTree();
	void clear();
	void insert(int data);
	void remove(int data);
	void find(int data);
	void inorderDFS();
	void preorderDFS();
	void postorderDFS();
	void BFS();
	void print();
};
