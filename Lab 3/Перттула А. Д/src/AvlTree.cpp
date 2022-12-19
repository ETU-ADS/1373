//
// Created by theta-sigma on 11/23/2022.
//

#include "AvlTree.h"
#include "Stack.h"
#include "Queue.h"

AvlNode *AvlTree::find(int value) {
    AvlNode *current = root;
    while (current != nullptr && current->value != value) {
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return current;
}

AvlNode *AvlTree::shadowFind(int value) {
    AvlNode *prev = nullptr;
    AvlNode *current = root;
    while (current != nullptr && current->value != value) {
        prev = current;
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (current == nullptr) {
        current = prev;
    }

    return current;
}

AvlNode *AvlTree::rightRotate(AvlNode *pivot) {
    AvlNode *y = pivot->left;
    pivot->left = y->right;

    if (y->right != nullptr) {
        y->right->parent = pivot;
    }

    y->parent = pivot->parent;

    if (pivot->parent == nullptr) {
        root = y;
    } else if (pivot == pivot->parent->right) {
        pivot->parent->right = y;
    } else {
        pivot->parent->left = y;
    }

    y->right = pivot;
    pivot->parent = y;

    pivot->height -= 2;

    return y;
}

AvlNode *AvlTree::leftRotate(AvlNode *pivot) {
    AvlNode *y = pivot->right;
    pivot->right = y->left;

    if (y->left != nullptr) {
        y->left->parent = pivot;
    }

    y->parent = pivot->parent;

    if (pivot->parent == nullptr) {
        root = y;
    } else if (pivot == pivot->parent->left) {
        pivot->parent->left = y;
    } else {
        pivot->parent->right = y;
    }

    y->left = pivot;
    pivot->parent = y;

    pivot->height -= 2;

    return y;
}

void AvlTree::insert(int value) {
    AvlNode *current = shadowFind(value);

    if (current != nullptr) {
        if (value != current->value) { // появился новый узел
            if (value < current->value) {
                current->left = new AvlNode();
                current->left->value = value;
                current->left->parent = current;
            } else if (current->value < value) {
                current->right = new AvlNode();
                current->right->value = value;
                current->right->parent = current;
            }

            current->height = 1 + max(getHeight(current->left),
                                      getHeight(current->right));

            current = current->parent;
            while (current != nullptr) {
                current->height = 1 + max(getHeight(current->left),
                                          getHeight(current->right));

                if (getBalance(current) > 1) { // left child
                    if (value < current->left->value) { // left subtree of left child
                        rightRotate(current);
                    } else { // right subtree of left child
                        leftRotate(current->left);
                        rightRotate(current);
                    }
//                        current = current->parent;
                    break;
                } else if (getBalance(current) < -1) { // right
                    if (value < current->right->value) { // left
                        rightRotate(current->right);
                        leftRotate(current);
                    } else { // right
                        leftRotate(current);
                    }
//                        current = current->parent;
                    break;
                }

                current = current->parent;
            }
        } else {
//            return 0;
        }
    } else {
        root = new AvlNode();
        root->value = value;
//        return 0;
    }
}

AvlNode *AvlTree::treeMinimum(AvlNode *node) {
    if (node != nullptr) {
        while (node->left != nullptr) {
            node = node->left;
        }
    }
    return node;
}

AvlNode *AvlTree::treeMaximum(AvlNode *node) {
    if (node != nullptr) {
        while (node->right != nullptr) {
            node = node->right;
        }
    }
    return node;
}

AvlNode *AvlTree::findSuccessor(AvlNode *node) {

    if (node->right != nullptr) {
        return treeMinimum(node->right);
    }

    AvlNode *parent = node->parent;
    while (parent != nullptr && node == parent->right) {
        node = parent;
        parent = node->parent;
    }
}

void AvlTree::remove(int value) {
    AvlNode *node = find(value);

    if (node == nullptr) {
        std::cout << "Value not found..." << std::endl << std::endl;
        return;
    }

    AvlNode *x = node;
    if (node->left == nullptr || node->right == nullptr) {
        x = node;
    } else {
        x = findSuccessor(node);
    }

    AvlNode *xChild;
    if (x->left != nullptr) {
        xChild = x->left;
    } else {
        xChild = x->right;
    }

    if (xChild != nullptr) {
        xChild->parent = x->parent;
    }

    if (x->parent == nullptr) {
        root = xChild;
    } else if (x == x->parent->left) {
        x->parent->left = xChild;
    } else {
        x->parent->right = xChild;
    }

    if (x != node) {
        node->value = x->value;
    }

    x->parent->height -= 1;
    AvlNode *parent = x->parent;

    while (parent != nullptr) {
        parent->height = 1 + max(getHeight(parent->left),
                                 getHeight(parent->right));

        if (getBalance(parent) < -1) { // left subtree - right st = -2
            if (getBalance(parent->right) <= 0) { // left - right <= 0
                leftRotate(parent);
            } else {
                parent->right = rightRotate(parent->right);
                leftRotate(parent);
            }
            break;
        } else if (getBalance(parent) > 1) { // left - right = 2
            if (getBalance(parent->left) >= 0) { // left - right >= 0
                rightRotate(parent);
            } else {
                parent->left = leftRotate(parent->left);
                rightRotate(parent);
            }
            break;
        }
        parent = parent->parent;
    }

    delete x;
}

void AvlTree::prettyPrint(AvlNode *p, int indent) {
    if (p != nullptr) {
        if (p->right) {
            prettyPrint(p->right, indent + 4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->right) std::cout << " /\n" << std::setw(indent) << ' ';
        std::cout << p->value << "\n ";
        if (p->left) {
            std::cout << std::setw(indent) << ' ' << " \\\n";
            prettyPrint(p->left, indent + 4);
        }
    } else {
        std::cout << "Empty tree..." << std::endl << std::endl;
    }
    std::cout << std::endl;
}

AvlNode *AvlTree::getRoot() {
    return root;
}

int AvlTree::getBalance(AvlNode *node) {
    return getHeight(node->left) - getHeight(node->right);
}

int AvlTree::getHeight(AvlNode *node) {
    if (node == nullptr) {
        return 0;
    } else {
        return node->height;
    }
}

int AvlTree::max(int a, int b) {
    return a > b ? a : b;
}

void AvlTree::bfs() {
    Queue<AvlNode *> queue;

    queue.enqueue(root);

    AvlNode *current;
    for (int i = 0; !queue.isEmpty(); i++) {
        current = queue.dequeue();
        std::cout << current->value << " ";

        if (current->right != nullptr) {
            queue.enqueue(current->right);
        }
        if (current->left != nullptr) {
            queue.enqueue(current->left);
        }
    }

    std::cout << std::endl;
}

void AvlTree::preorder() {
    Stack<AvlNode *> stack;

    if (root == nullptr) {
        return;
    }

    stack.push(root);
    AvlNode *current = root;
    for (int i = 0; !stack.isEmpty(); i++) {
        current = stack.pop();
        std::cout << current->value << " ";
        if (current->right != nullptr) {
            stack.push(current->right);
        }
        if (current->left != nullptr) {
            stack.push(current->left);
        }
    }

    std::cout << std::endl;
}

void AvlTree::inorder() {
    if (root == nullptr) {
        return;
    }

    Stack<AvlNode *> stack;
    AvlNode *current = root;
    for (int i = 0; !stack.isEmpty() || current != nullptr; i++) {
        if (current != nullptr) {
            stack.push(current);
            current = current->left;
        } else {
            current = stack.pop();
            std::cout << current->value << " ";
            current = current->right;
        }
    }

    std::cout << std::endl;
}

void AvlTree::postorder() {
    if (root == nullptr)
        return;
    Stack<AvlNode *> stack;
    stack.push(root);
    AvlNode *prev = nullptr;
    while (!stack.isEmpty()) {
        AvlNode *current = stack.peak();

        if (prev == nullptr || prev->left == current
            || prev->right == current) {
            if (current->left)
                stack.push(current->left);
            else if (current->right)
                stack.push(current->right);
            else {
                stack.pop();
                std::cout << current->value << " ";
            }
        } else if (current->left == prev) {
            if (current->right)
                stack.push(current->right);
            else {
                stack.pop();
                std::cout << current->value << " ";
            }
        } else if (current->right == prev) {
            stack.pop();
            std::cout << current->value << " ";
        }
        prev = current;
    }

    std::cout << std::endl;
}

AvlTree::AvlTree(const BinaryTree &bt) : root(nullptr) {
    ArrayList<int> list;
    bt.getAllValues(list);

    for (int i = 0; i < list.size(); i++) {
        insert(list.get(i));
    }
}

void clearTreeHelper(AvlNode *&pNode) {
    if (pNode != nullptr) {
        clearTreeHelper(pNode->left);
        clearTreeHelper(pNode->right);
        delete pNode;
        pNode = nullptr;
    }
}

AvlTree::~AvlTree() {
    clearTreeHelper(root);
}

