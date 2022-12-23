//
// Created by theta-sigma on 11/22/2022.
//

#ifndef SRC_BINARYTREE_H
#define SRC_BINARYTREE_H

#include <iostream>
#include <iomanip>

#include "Stack.h"
// (8 (3 (1) (6 (4) (7))))
// (8 (9 (5)) (1))
// (8 (3 (1) (6 (4) (7))) (10 (14 (13))))
// (8 () (5))

void print(int value);

int get(int value);

struct BtNode {
    int data;
    BtNode *left;
    BtNode *right;
};

class BinaryTree {
public:
    BinaryTree();

    explicit BinaryTree(BtNode *root);

    ~BinaryTree();

    int printDfs();

    int printDfsBraces();

    int parser(const std::string &sss);

    BtNode *getRoot() const;

    void prettyPrint(BtNode *p, int indent = 2);

    void getAllValues(ArrayList<int> &list) const;

private:

    void dfs(BtNode *node) const;

    void dfsBraces(BtNode *node);

    BtNode *root;
};


#endif //SRC_BINARYTREE_H
