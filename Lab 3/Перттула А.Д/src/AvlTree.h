//
// Created by theta-sigma on 11/23/2022.
//

#ifndef SRC_AVLTREE_H
#define SRC_AVLTREE_H

#include <iostream>
#include <iomanip>
#include "BinaryTree.h"

struct AvlNode {
    AvlNode() : value(0), left(nullptr), right(nullptr), parent(nullptr), height(1) {};

    int value;
    AvlNode *left;
    AvlNode *right;
    AvlNode *parent;
    int height;
};

class AvlTree {
public:
    AvlTree() : root(nullptr) {}

    virtual ~AvlTree();

    explicit AvlTree(const BinaryTree &bt);

    explicit AvlTree(AvlNode *p) : root(p) {}

    AvlNode *find(int value);

    AvlNode *shadowFind(int value);

    AvlNode * rightRotate(AvlNode *pivot);

    AvlNode * leftRotate(AvlNode *pivot);

    void insert(int value);

    static AvlNode *treeMinimum(AvlNode *node);

    static AvlNode *treeMaximum(AvlNode *node);

    static AvlNode *findSuccessor(AvlNode *node);

    void remove(int value);

    void prettyPrint(AvlNode *p, int indent = 2);

    AvlNode *getRoot();

    void bfs();

    void preorder();

    void inorder();

    void postorder();

private:

    static int getBalance(AvlNode *node);

    static int getHeight(AvlNode *node);

    static int max(int a, int b);

    AvlNode *root;
};


#endif //SRC_AVLTREE_H
