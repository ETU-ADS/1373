#pragma once

#include <iostream>

#include "BTree.h"
#include "RBTreeNode.h"

class RBTree {
private:
	int amount = 0;

	RBNode* root = nullptr;
	Array<int> RBTArr;

	//turns
	void leftRotate(RBNode* node) {
		RBNode* parent = node->p;
		if (parent->p)
			if (parent->p->l == parent)
				parent->p->l = node;
			else
				parent->p->r = node;

		node->p = parent->p;

		parent->r = node->l;
		if (node->l)
			node->l->p = parent;
		node->l = parent;
		parent->p = node;
		if (!node->p)
			root = node;
	}
	void rightRotate(RBNode* node) {
		RBNode* parent = node->p;
		if (parent->p) {
			if (parent->p->l == parent)
				parent->p->l = node;
			else
				parent->p->r = node;
		}
		node->p = parent->p;

		parent->l = node->r;
		if (node->r)
			node->r->p = parent;
		node->r = parent;
		parent->p = node;
		if (!node->p)
			root = node;
	}
	//adding
	void insert(int data) {
		RBNode* newNode = new RBNode;
		if (amount == 0) {
			newNode->color = false;
			newNode->data = data;
			root = newNode;
			++amount;
			return;
		}
		else
			newNode->color = true;

		newNode->data = data;
		RBNode* current = root;
		while (current) {
			newNode->p = current;
			if (data >= current->data)
				current = current->r;
			else
				current = current->l;
		}
		if (newNode->p->data > data)
			newNode->p->l = newNode;
		else
			newNode->p->r = newNode;

		insertFixUp(newNode);
		++amount;
	}
	void insert_1(RBNode* p, RBNode* u, bool uColor, RBNode* gp) {
		p->color = false;
		u->color = false;
		if (gp != root) {
			gp->color = true;
			insertFixUp(gp);
		}
	}
	void insert_2(RBNode* p, bool isPLeft, RBNode* gp, bool isGpLeft) {
		if (isGpLeft == isPLeft) {
			p->color = false;
			gp->color = true;
			if (isPLeft)
				rightRotate(p);
			else if (!isPLeft)
				leftRotate(p);
			return;
		}
	}
	void insert_3(RBNode* gp, RBNode* node, bool isGpLeft) {
		gp->color = true;
		node->color = false;
		if (isGpLeft) {
			leftRotate(node);
			rightRotate(node);
		}
		else if (!isGpLeft) {
			rightRotate(node);
			leftRotate(node);
		}
		return;
	}
	void insertFixUp(RBNode* newNode) {
		if (newNode->p->color) {
			RBNode* p = newNode->p, * gp = p->p, * u = gp->r;
			bool isGpLeft = true, isPLeft = true, uColor = false;

			if (gp->r == p) {
				u = gp->l;
				isGpLeft = false;
			}
			if (p->r == newNode)
				isPLeft = false;

			if (u)
				uColor = u->color;

			if ((!gp->color) && p->color && (uColor))
				insert_1(p, u, uColor, gp);
			else if ((!gp->color) && p->color && (!uColor))
				insert_2(p, isPLeft, gp, isGpLeft);
			else if (isGpLeft == !isPLeft)
				insert_3(gp, newNode, isGpLeft);
		}
		return;
	}
	//removal
	RBNode* findNext(RBNode* node) {
		if (node->r) {
			RBNode* current = node->r;
			while (current->l)
				current = current->l;
			return current;
		}
		else
			return node;
	}
	bool remove(RBNode* node) {
		if (amount == 0)
			return false;
		else if (amount == 1) {
			delete node;
			root = nullptr;
			amount--;
			return true;
		}

		bool color = node->color;

		if (node->l && node->r) {
			RBNode* copy = findNext(node);
			node->data = copy->data;
			remove(copy);
		}
		else if (node->l) {
			node->data = node->l->data;
			delete node->l;
			node->l = nullptr;
		}
		else if (node->r) {
			node->data = node->r->data;
			delete node->r;
			node->r = nullptr;
		}
		else {
			if (!color)
				removeFixUp(node);
			if (node->p->l == node)
				node->p->l = nullptr;
			else if (node->p->r == node)
				node->p->r = nullptr;
			delete node;
		}
		amount--;
		return true;
	}
	void remove_1(RBNode* p, RBNode* bro) {
		p->color = false;
		bro->color = true;
	}
	void remove_2(RBNode* bro, RBNode* p, bool isLeftSide, RBNode* cRight, RBNode* cLeft) {
		bro->color = p->color;
		p->color = false;
		if (isLeftSide) {
			cRight->color = false;
			leftRotate(bro);
		}
		else {
			cLeft->color = false;
			rightRotate(bro);
		}
	}
	void remove_3(RBNode* bro, RBNode* cRight, RBNode* cLeft, RBNode* p, bool isLeftSide) {
		bro->color = true;
		if (isLeftSide) {
			cLeft->color = false;
			rightRotate(cLeft);
		}
		else {
			cRight->color = false;
			leftRotate(cRight);
		}

		if (isLeftSide) {
			bro = cLeft;
			cRight = bro->r;
			bro->color = p->color;
			p->color = false;
			cRight->color = false;
			leftRotate(bro);
		}
		else {
			bro = cRight;
			cLeft = bro->l;
			bro->color = p->color;
			p->color = false;
			cLeft->color = false;
			rightRotate(bro);
		}
	}
	void remove_4(RBNode* bro, RBNode* p, RBNode* node) {
		p->color = true;
		bro->color = false;
		removeFixUp(node);
	}
	void remove_5(RBNode* bro, RBNode* p) {
		bro->color = true;
		removeFixUp(p);
	}
	void removeFixUp(RBNode* node, bool fourRemove = true) {
		RBNode* p = node->p, * bro = p->r, * cLeft = nullptr, * cRight = nullptr;
		bool isLeftSide = true;

		if (p->r == node) {
			bro = p->l;
			isLeftSide = false;
		}

		bool cLeftColor = false;

		if (bro->l) {
			cLeft = bro->l;
			cLeftColor = cLeft->color;
		}

		bool cRightColor = false;

		if (bro->r) {
			cRight = bro->r;
			cRightColor = cRight->color;
		}

		if (p->color && !bro->color && !cLeftColor && !cRightColor)
			remove_1(p, bro);
		else if (!bro->color && ((cRightColor) || (!isLeftSide && cLeftColor)))
			remove_2(bro, p, isLeftSide, cRight, cLeft);
		else if (!bro->color && (cLeftColor && !cRightColor || (!isLeftSide && !cLeftColor && cRightColor)))
			remove_3(bro, cRight, cLeft, p, isLeftSide);
		else if ((!p->color && bro->color && !cLeftColor && !cRightColor) && fourRemove)
			remove_4(bro, p, node);
		else if (!p->color && !bro->color && !cLeftColor && !cRightColor)
			remove_5(bro, p);
	}
	//treverses
	//direct traverse
	void preOrder(RBNode* node) {
		if (!node)
			return;
		printNode(node);
		preOrder(node->l);
		preOrder(node->r);

	}
	//centered traverse
	void inOrder(RBNode* node) {
		if (!node)
			return;
		inOrder(node->l);
		printNode(node);
		inOrder(node->r);
	}
	//reverse traverse
	void postOrder(RBNode* node) {
		if (!node)
			return;
		postOrder(node->l);
		postOrder(node->r);
		printNode(node);
	}
	//iterative wide
	void levelOrder(RBNode* node) {
		Array<RBNode*> arr;
		arr.addToTheEnd(node);
		while (arr.getSize() != 0) {
			RBNode* temp = arr[0];
			if (temp) {
				printNode(temp);
				arr.addToTheEnd(temp->l);
				arr.addToTheEnd(temp->r);
			}
			arr.deleteByIndex(0);
		}
	}
	//node output
	void printNode(RBNode* node) {
		if (node) {
			if (node->color == true)
				std::cout << (node->data) << "(r)" << ' ';
			if (node->color == false)
				std::cout << (node->data) << "(b)" << ' ';
		}
	}
	//filling data array
	void fillArr(Node* node) {
		if (node) {
			char* tempChar = node->data;
			int newIntData = 0;

			for (int i = 0; tempChar[i] != '\0'; ++i) {
				newIntData = newIntData * 10 + (tempChar[i] - '0');
			}
			RBTArr.addToTheEnd(newIntData);
			fillArr(node->l);
			fillArr(node->r);
		}
		else {
			return;
		}
	}
	//tree deletion(for destructor)
	void deleteTree(RBNode* node) {
		if (!node)
			return;
		deleteTree(node->l);
		deleteTree(node->r);
		delete node;
	}

public:
	//creating a red-black tree by binary
	void create(BTree* binTree) {
		fillArr(binTree->getRoot());
		for (int i = 0; i < RBTArr.getSize(); ++i) {
			insert(RBTArr[i]);
		}
	}
	//adding an element
	void add(int data) {
		insert(data);
	}
	//deleting an element
	bool del(int data) {
		RBNode* currNode = root;
		bool isFound = false;
		while (currNode) {
			if (data > currNode->data) {
				currNode = currNode->r;
			}
			else if (data < currNode->data) {
				currNode = currNode->l;
			}
			else {
				remove(currNode);
				isFound = true;
				break;
			}
		}
		return isFound;
	}
	//four tree walks
	void traverse() {
		std::cout << "Direct traverse(preOrder): " << std::endl;
		preOrder(root);
		std::cout << std::endl;

		std::cout << "Centered traverse(inOrder):" << std::endl;
		inOrder(root);
		std::cout << std::endl;

		std::cout << "Reverse traverse(postOrder): " << std::endl;
		postOrder(root);
		std::cout << std::endl;

		std::cout << "Iterative wide(levelOrder): " << std::endl;
		levelOrder(root);
		std::cout << std::endl;
	}
	//destructor
	~RBTree() {
		deleteTree(root);
	}
};