//
// Created by theta-sigma on 11/22/2022.
//

#include "BinaryTree.h"

void print(int value) {
    std::cout << value << " ";
}

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::BinaryTree(BtNode *root) : root(root) {}

int BinaryTree::printDfs() {
    std::cout << root->data << " ";

    dfs(root->left);
    dfs(root->right);

    std::cout << std::endl;

    return 0;
}

int BinaryTree::printDfsBraces() {
    std::cout << "(" << root->data << " ";

    dfsBraces(root->left);

    dfsBraces(root->right);

    std::cout << "\b)" << std::endl;

    return 0;
}

int BinaryTree::parser(const std::string &sss) {
    Stack<BtNode *> stack;

    delete root;
    root = new BtNode();
    BtNode *current = root;

    if (sss[0] == '(') {
        stack.push(current);
    } else {
        return 1;
    }

    bool hasTempNumber = false;
    bool skipLeft = false;

    int integer = 0;
    char sign = 1;
    for (int i = 1; i < sss.length(); i++) {
        if (sss[i] == '-') {
            sign = -1;
        }

        while ('0' <= sss[i] && sss[i] <= '9') {
            hasTempNumber = true;
            integer = integer * 10 + (sss[i] - '0');
            i++;
        }

        if (sss[i] == '(') {
            if (i + 1 < sss.length()) {
                if (sss[i + 1] == ')') {
                    skipLeft = true;
                    i++;
                } else {
                    stack.push(current);
                    if (!skipLeft && current->left == nullptr) {
                        current = current->left = new BtNode();
                    } else if (current->right == nullptr) {
                        current = current->right = new BtNode();
                        skipLeft = false;
                    } else {
                        std::cout << "something strange happened: maybe it's not binary tree..." << std::endl;

                        return 2;
                    }
                }
            } else {
                std::cout << "unmatched ()" << std::endl;
                return 1;
            }
        } else if (sss[i] == ')') {
            if (hasTempNumber) {
                current->data = integer * sign;
                hasTempNumber = false;
                sign = 1;
                integer = 0;
            }
            if (!stack.isEmpty()) {
                current = stack.pop();
            } else {
                std::cout << "unmatched ()" << std::endl;
                return 1;
            }
        } else if (sss[i] == ' ') {
            if (hasTempNumber) {
                current->data = integer * sign;
                hasTempNumber = false;
                sign = 1;
                integer = 0;
            }
        } else if (sss[i] != 13) {
            std::cout << "unknown symbol: " << sss[i] << std::endl << std::endl;;
            return 3;
        }
    }

    return 0;
}

void BinaryTree::dfs(BtNode *node) const {
    if (node == nullptr) {
        return;
    }

    std::cout << node->data << " ";

    dfs(node->left);
    dfs(node->right);
}

void BinaryTree::dfsBraces(BtNode *node) {
    if (node == nullptr) {
        std::cout << "() ";
        return;
    }

    std::cout << "(" << node->data << " ";

    dfsBraces(node->left);

    dfsBraces(node->right);
    std::cout << "\b) ";
}

void clearTreeHelper(BtNode *&pNode) {
    if (pNode != nullptr) {
        clearTreeHelper(pNode->left);
        clearTreeHelper(pNode->right);
        delete pNode;
        pNode = nullptr;
    }
}

BinaryTree::~BinaryTree() {
    clearTreeHelper(root);
}

void BinaryTree::prettyPrint(BtNode *p, int indent) {
    if (p != nullptr) {
        if (p->right) {
            prettyPrint(p->right, indent + 4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->right) std::cout << " /\n" << std::setw(indent) << ' ';
        std::cout << p->data << "\n ";
        if (p->left) {
            std::cout << std::setw(indent) << ' ' << " \\\n";
            prettyPrint(p->left, indent + 4);
        }
    }
    std::cout << std::endl;
}

BtNode *BinaryTree::getRoot() const {
    return root;
}

void BinaryTree::getAllValues(ArrayList<int> &list) const {
    Stack<BtNode *> stack;
    stack.push(root);

    for (int i = 0; !stack.isEmpty(); i++) {
        BtNode *current = stack.pop();

        list.append(current->data);

        if (current->right != nullptr) {
            stack.push(current->right);
        }
        if (current->left != nullptr) {
            stack.push(current->left);
        }
    }
}
