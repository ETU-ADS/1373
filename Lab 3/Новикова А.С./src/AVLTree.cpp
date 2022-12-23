#include <iostream>
#include "AVLTree.h"
#include "stack.h"
#include "queue.h"

AVLTree::AVLTree()
{
    head = nullptr;
}

AVLTree::~AVLTree()
{
    clear();
}

void AVLTree::deleteNode(AVLTreeNode* node)
{
    if (node == nullptr)
        return;
    deleteNode(node->left);
    deleteNode(node->right);
    delete node;
}

void AVLTree::clear()
{
    deleteNode(head);
    head = nullptr;
}

AVLTreeNode* AVLTree::insert(int data, AVLTreeNode* node) 
{
    if (node == nullptr)
    {
        node = new AVLTreeNode;
        node->value = data;
        node->height = 0;
        node->left = nullptr;
        node->right = nullptr;
    }
    else if (data < node->value)
        node->left = insert(data, node->left);
    else if (data > node->value)
        node->right = insert(data, node->right);

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    return toBalance(node);
}
AVLTreeNode* AVLTree::rightRotation(AVLTreeNode* node)
{
    AVLTreeNode* n = node->left;
    node->left = n->right;
    n->right = node;
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    n->height = std::max(getHeight(n->left), node->height) + 1;
    return n;
}

AVLTreeNode* AVLTree::leftRotation(AVLTreeNode* node) 
{
    AVLTreeNode* n = node->right;
    node->right = n->left;
    n->left = node;
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    n->height = std::max(getHeight(node->right), node->height) + 1;
    return n;
}

AVLTreeNode* AVLTree::doubleLeftRotation(AVLTreeNode* node) //право-левый поворот
{
    node->right = rightRotation(node->right);
    return leftRotation(node);
}

AVLTreeNode* AVLTree::doubleRightRotation(AVLTreeNode* node) //лево-правый поворот
{
    node->left = leftRotation(node->left);
    return rightRotation(node);
}

AVLTreeNode* AVLTree::toBalance(AVLTreeNode* node)
{
    int balance = getBalance(node);

    if (balance < -1) //левое поддерево больше
    {
        if (getBalance(node->left) <= 0)
            return leftRotation(node); 
        else
            return doubleLeftRotation(node); 
    }
    else if (balance > 1) //правое поддерево больше
    {
        if (getBalance(node->right) >= 0)
            return rightRotation(node); 
        else
            return doubleRightRotation(node); 
    }
    return node;
}

AVLTreeNode* AVLTree::getMin(AVLTreeNode* node) 
{
    if (node == nullptr)
        return nullptr;
    else if (node->left == nullptr)
        return node;
    else
        return getMin(node->left);
}

AVLTreeNode* AVLTree::remove(int data, AVLTreeNode* node) 
{
    AVLTreeNode* temp;

    if (node == nullptr)
        return nullptr;
    else if (data < node->value)
        node->left = remove(data, node->left);
    else if (data > node->value)
        node->right = remove(data, node->right);
    else if (node->left && node->right)
    {
        temp = getMin(node->right);
        node->value = temp->value;
        node->right = remove(node->value, node->right);
    }
    else 
    {
        temp = node;
        if (node->left == nullptr)
            node = node->right;
        else if (node->right == nullptr)
            node = node->left;
        delete temp;
    }
    if (node == nullptr)
        return node;

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    return toBalance(node);
}

AVLTreeNode* AVLTree::find(int data, AVLTreeNode* node)
{
    if (node == nullptr || data == node->value)
        return node;

    if (data < node->value)
        return find(data, node->left);
    else
        return find(data, node->right);
}

int AVLTree::getHeight(AVLTreeNode* node)
{
    return (node == nullptr ? -1 : node->height);
}

int AVLTree::getBalance(AVLTreeNode* node)
{
    if (node == nullptr)
        return 0;
    else
        return getHeight(node->left) - getHeight(node->right);
}

void AVLTree::preorderDFS(AVLTreeNode* node)
{
    if (node == NULL)   
        return;
    std::cout << ' ' << node->value;
    preorderDFS(node->left);   
    preorderDFS(node->right);  
}

void AVLTree::inorderDFS(AVLTreeNode* node)
{
    if (node == NULL)  
        return;
    inorderDFS(node->left);  
    std::cout << ' ' << node->value;
    inorderDFS(node->right);  
}

void AVLTree::postorderDFS(AVLTreeNode* node)
{
    Stack stack(10);
    stack.push(node);
    while (!stack.isEmpty())
    {
        AVLTreeNode* n = stack.peak();
        stack.pop();

        if (n->left != nullptr)
            stack.push(n->left);
        if (n->right != nullptr)
            stack.push(n->right);

        std::cout << ' ' << n->value;
    }
}

void AVLTree::BFS(AVLTreeNode* node)
{
    Queue queue(10);
    queue.push(node);
    while (!queue.isEmpty())
    {
        AVLTreeNode* n = queue.front();
        queue.pop();

        std::cout << ' ' << n->value;
        if (n->left != nullptr)
            queue.push(n->left);
        if (n->right != nullptr)
            queue.push(n->right);
    }
}

void AVLTree::insert(int data)
{
    head = insert(data, head);
}

void AVLTree::remove(int data)
{
    head = remove(data, head);
}

void AVLTree::find(int data)
{
    if (find(data, head) == nullptr)
        std::cout << "The element is not found" << std::endl;
    else
        std::cout << "The element is found" << std::endl;
}

void AVLTree::preorderDFS()
{
    preorderDFS(head);
}

void AVLTree::inorderDFS()
{
    inorderDFS(head);
}

void AVLTree::postorderDFS()
{
    postorderDFS(head);
}

void AVLTree::BFS()
{
    BFS(head);
}

void AVLTree::print(AVLTreeNode* node, std::string str, bool flag)
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

void AVLTree::print()
{
    print(head, "", true);
}