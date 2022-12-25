#include "Tree.h"
#include"DynamicArray.h"
#include "Queue.h"
#include "Stack.h"
#include <iostream>
#include <string>
#include <fstream>

void BinTree::traversal()
{
    if (this != nullptr)
    {
        std::cout << this->key << " ";
        this->left->traversal();
        this->right->traversal();
    }
}

void BinTree::traversal(DynamicArray& arr)
{
    if (this != nullptr)
    {
        arr.addBack(this->key);
        this->left->traversal(arr);
        this->right->traversal(arr);
    }
}

int BinTree::parcing(std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Неверное имя файла" << std::endl;
        return -1;
    }

    std::string str;
    std::getline(file, str);
    int start = 0;
    if (this->parcing(str, start, str.length() - 1) == -1)
    {
        file.close();
        return -1;
    }
    file.close();
    return 0;
}

int BinTree::parcing(std::string& str, int& i, int end)
{
    int brackets = 1, count = 0;
    static char first = 0;
    static std::string keyFirst = "";
    std::string buff;
    ++i;
    buff.append(str, i, str.find_first_of(" )", i) - i);
    if (str[str.find_first_of(" )", i)] == ')')
        --brackets;
    i = str.find_first_of(" )", i) + 1;
    if (buff.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "Ошибка! " << buff << " - не число." << std::endl;
        return -1;
    }
    if (buff == "")
    {
        std::cout << "Ошибка!" << std::endl;
        return -1;
    }
    key = stoi(buff);
    if (!first)
    {
        first = true;
        keyFirst = buff;
    }
    while (i <= end)
    {
        if (brackets == 0)
            break;
        else if (brackets < 0)
            return-1;
        else if (count > 2)
            return -1;
        else if (str[i] == ' ')
        {
            ++i;
        }
        else if (str[i] == '(' && count == 0)
        {
            if (str[i + 1] == ')')
            {
                i += 2;
            }
            else
            {
                this->left = new BinTree;
                if (this->left->parcing(str, i, end) == -1)
                    return -1;
            }
            ++count;


        }
        else if (str[i] == '(' && count == 1)
        {
            if (str[i + 1] == ')')
            {
                i += 2;
            }
            else
            {
                this->right = new BinTree;
                if (this->right->parcing(str, i, end) == -1)
                    return -1;
            }
            ++count;


        }
        else if (str[i] == ')')
        {
            --brackets;
            ++i;


        }
        else
            ++i;
    }

    if (buff == keyFirst && i != str.length())
    {
        std::cout << "Ошибка!" << std::endl;
        return -1;
    }
    return 0;
}



AVLTree::AVLTree()
{
    root = nullptr;
}

unsigned char AVLTree::height(Node* node) 
{
    return node ? node->height : 0;
}

int AVLTree::bfactor(Node* node) 
{
    return height(node->right) - height(node->left);
}

void AVLTree::fixheight(Node* node) 
{
    unsigned char hl = height(node->left),
        hr = height(node->right);
    node->height = (hl > hr ? hl : hr) + 1;
}

void AVLTree::traversal(char mode) 
{
    if (root != nullptr)
    {
        Node* buff = root;
        Stack stack(10);
        Queue queue(10);
        switch (mode)
        {
        case 1: 
            stack.push(root);
            while (!stack.empty())
            {
                buff = stack.pop();
                std::cout << buff->key << " "; 
                if (buff->right != nullptr) 
                    stack.push(buff->right);
                if (buff->left != nullptr)
                    stack.push(buff->left);
            }
            break;
        case 2: 
            while (!stack.empty() || buff != nullptr)
            {
                while (buff != nullptr)
                {
                    stack.push(buff);
                    buff = buff->left;
                }
                if (!stack.empty())
                {
                    buff = stack.pop();
                    std::cout << buff->key << " ";
                    if (buff->right != nullptr)
                        buff = buff->right;
                    else
                        buff = nullptr;
                }
            }
            break;
        case 3: 
            while (!stack.empty() || buff != nullptr)
            {
                while (buff != nullptr)
                {
                    stack.push(buff);
                    if (buff->right != nullptr)
                    {
                        stack.push(buff->right);
                        stack.push(buff);
                    }
                    buff = buff->left;
                }
                if (!stack.empty())
                {
                    buff = stack.pop();
                    if (!stack.empty() && buff->right == stack.peak())
                    {
                        buff = stack.pop();
                    }
                    else
                    {
                        std::cout << buff->key << " ";
                        buff = nullptr;
                    }
                }
            }
            break;
        case 4: 
            queue.push(root);
            while (!queue.empty())
            {
                buff = queue.pop();
                std::cout << buff->key << " ";
                if (buff->left != nullptr)
                    queue.push(buff->left);
                if (buff->right != nullptr)
                    queue.push(buff->right);
            }
            break;
        }
    }
    else
        std::cout << "Дерево пустое" << std::endl;
}

void AVLTree::make(BinTree& tree)
{
    DynamicArray arr(10);
    tree.traversal(arr);
    for (int i = 0; i < arr.getSize(); ++i)
        root = this->insert(arr[i], root);
}

Node* AVLTree::insert(int k, Node* node) 
{
    if (node == nullptr)
    {
        node = new Node;
        node->key = k;
        node->height = 0;
        node->left = nullptr;
        node->right = nullptr;
    }
    else if (k <= node->key)
        node->left = insert(k, node->left);
    else
        node->right = insert(k, node->right);
    fixheight(node);
    return balance(node);
}

void AVLTree::insert(int x)
{
    root = insert(x, root);
}

Node* AVLTree::leftRotate(Node* node)  
{
    Node* p = node->right;
    node->right = p->left;
    p->left = node;
    fixheight(node);
    fixheight(p);
    return p;
}

Node* AVLTree::rightRotate(Node* node) 
{
    Node* q = node->left;
    node->left = q->right;
    q->right = node;
    fixheight(node);
    fixheight(q);
    return q;
}

Node* AVLTree::balance(Node* node) 
{
    fixheight(node);
    if (bfactor(node) == 2) 
    {
        if (bfactor(node->right) < 0) 
            node->right = rightRotate(node->right); 
        return leftRotate(node); 
    }
    if (bfactor(node) == -2) 
    {
        if (bfactor(node->left) > 0) 
            node->left = leftRotate(node->left); 
        return rightRotate(node); 
    }
    return node; 
}

Node* AVLTree::findmin(Node* node) 
{
    return (node->left == nullptr) ? node : findmin(node->left);
}

Node* AVLTree::remove(int wantDelete, Node* node) 
{
    if (node == nullptr)
        return nullptr;
    if (wantDelete < node->key) 
        node->left = remove(wantDelete, node->left); 
    else if (wantDelete > node->key)
        node->right = remove(wantDelete, node->right);

    else
    {
        Node* min = nullptr; 
        if (node->left && node->right)
        {
            min = findmin(node->right);
            node->key = min->key;
            node->right = remove(node->key, node->right);
            return balance(node);
        }
        else if (node->left == nullptr)
        {
            min = node;
            node = node->right;
        }
        else if (node->right == nullptr)
        {
            min = node;
            node = node->left;
        }
    
    }
    if (node == nullptr)
        return node;
    return balance(node);
}

void AVLTree::remove(int wantDelete) 
{
    root = remove(wantDelete, root); 
}

Node* AVLTree::find(int findElement, Node* node) 
{
    if (node == nullptr)
        return node;
    else if (node->key == findElement)
        return node;
    else if (findElement < node->key)
        return find(findElement, node->left);
    else
        return find(findElement, node->right);
}

void AVLTree::find(int findElement) 
{
    if (find(findElement, root) == nullptr)
        std::cout << findElement << " не находится в дереве" << std::endl;
    else
        std::cout << findElement << " находится в дереве" << std::endl;
}