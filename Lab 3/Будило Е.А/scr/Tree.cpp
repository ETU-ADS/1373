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
        this->l->traversal();
        this->r->traversal();
    }
}

void BinTree::traversal(DynamicArray& arr)
{
    if (this != nullptr)
    {
        arr.addBack(this->key);
        this->l->traversal(arr);
        this->r->traversal(arr);
    }
}

int BinTree::parcing(std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Error! File is not open!" << std::endl;
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
        std::cout << "Error! " << buff << " is not number!" << std::endl;
        return -1;
    }
    if (buff == "")
    {
        std::cout << "Error! Wrong!" << std::endl;
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
                this->l = new BinTree;
                if (this->l->parcing(str, i, end) == -1)
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
                this->r = new BinTree;
                if (this->r->parcing(str, i, end) == -1)
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
        std::cout << "Error! Wrong brackets!" << std::endl;
        return -1;
    }
    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////


AVLTree::AVLTree()
{
    root = nullptr;
}

unsigned char AVLTree::height(AVL::Node* node)
{
    return node ? node->h : 0;
}

int AVLTree::bfactor(AVL::Node* node)
{
    return height(node->r) - height(node->l);
}

void AVLTree::fixheight(AVL::Node* node)
{
    unsigned char hl = height(node->l),
        hr = height(node->r);
    node->h = (hl > hr ? hl : hr) + 1;
}

void AVLTree::traversal(char mode)
{
    if (root != nullptr)
    {
        AVL::Node* buff = root;
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
                if (buff->r != nullptr)
                    stack.push(buff->r);
                if (buff->l != nullptr)
                    stack.push(buff->l);
            }
            break;
        case 2:
            while (!stack.empty() || buff != nullptr)
            {
                while (buff != nullptr)
                {
                    stack.push(buff);
                    buff = buff->l;
                }
                if (!stack.empty())
                {
                    buff = stack.pop();
                    std::cout << buff->key << " ";
                    if (buff->r != nullptr)
                        buff = buff->r;
                    else
                        buff = nullptr;
                }
            }
            break;
        case 3:
            while (!stack.empty() || buff != nullptr) //reverse
            {
                while (buff != nullptr)
                {
                    stack.push(buff);
                    if (buff->r != nullptr)
                    {
                        stack.push(buff->r);
                        stack.push(buff);
                    }
                    buff = buff->l;
                }
                if (!stack.empty())
                {
                    buff = stack.pop();
                    if (!stack.empty() && buff->r == stack.peak())
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
                if (buff->l != nullptr)
                    queue.push(buff->l);
                if (buff->r != nullptr)
                    queue.push(buff->r);
            }
            break;
        }
    }
    else
        std::cout << "Tree is empty" << std::endl;
}

void AVLTree::make(BinTree& tree)
{
    DynamicArray arr(10);
    tree.traversal(arr);
    for (int i = 0; i < arr.getSize(); ++i)
        root = this->insert(arr[i], root);
}

AVL::Node* AVLTree::insert(int x, AVL::Node* node)
{
    if (node == nullptr)
    {
        node = new AVL::Node;
        node->key = x;
        node->h = 0;
        node->l = nullptr;
        node->r = nullptr;
    }
    else if (x <= node->key)
        node->l = insert(x, node->l);
    else
        node->r = insert(x, node->r);
    fixheight(node);
    return balance(node);
}

void AVLTree::insert(int x)
{
    root = insert(x, root);
}

AVL::Node* AVLTree::leftRotate(AVL::Node* node)
{
    AVL::Node* p = node->r;
    node->r = p->l;
    p->l = node;
    fixheight(node);
    fixheight(p);
    return p;
}

AVL::Node* AVLTree::rightRotate(AVL::Node* node)
{
    AVL::Node* q = node->l;
    node->l = q->r;
    q->r = node;
    fixheight(node);
    fixheight(q);
    return q;
}

AVL::Node* AVLTree::balance(AVL::Node* node)
{
    fixheight(node);
    if (bfactor(node) == 2)
    {
        if (bfactor(node->r) < 0)
            node->r = rightRotate(node->r);
        return leftRotate(node);
    }
    if (bfactor(node) == -2)
    {
        if (bfactor(node->l) > 0)
            node->l = leftRotate(node->l);
        return rightRotate(node);
    }
    return node;
}

AVL::Node* AVLTree::findmin(AVL::Node* node)
{
    return (node->l == nullptr) ? node : findmin(node->l);
}

AVL::Node* AVLTree::remove(int x, AVL::Node* node)
{
    if (node == nullptr)
        return nullptr;
    if (x < node->key)
        node->l = remove(x, node->l);
    else if (x > node->key)
        node->r = remove(x, node->r);

    else
    {
        AVL::Node* min = nullptr;
        if (node->l && node->r)
        {
            min = findmin(node->r);
            node->key = min->key;
            node->r = remove(node->key, node->r);
            return balance(node);
        }
        else if (node->l == nullptr)
        {
            min = node;
            node = node->r;
        }
        else if (node->r == nullptr)
        {
            min = node;
            node = node->l;
        }
        delete min;
    }
    if (node == nullptr)
        return node;
    return balance(node);
}

void AVLTree::remove(int x)
{
    root = remove(x, root);
}

AVL::Node* AVLTree::find(int x, AVL::Node* node)
{
    if (node == nullptr)
        return node;
    else if (node->key == x)
        return node;
    else if (x < node->key)
        return find(x, node->l);
    else
        return find(x, node->r);
}

void AVLTree::find(int x)
{
    if (find(x, root) == nullptr)
        std::cout << x << " is not in the tree" << std::endl;
    else
        std::cout << x << " is in the tree" << std::endl;
}