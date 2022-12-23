#pragma once
#include "DynamicArray.h"
#include <string>
class BinTree
{
    int key;
    BinTree* l = nullptr, * r = nullptr;

    int parcing(std::string& str, int& start, int end);
public:
    void traversal();
    void traversal(DynamicArray& arr);
    int parcing(std::string& fileName);
};

namespace AVL
{
    struct Node
    {
        int key;
        AVL::Node* l = nullptr, * r = nullptr;
        unsigned char h;
    };
}
class AVLTree
{
    AVL::Node* root = nullptr;

    unsigned char height(AVL::Node* node);
    int bfactor(AVL::Node* node);
    void fixheight(AVL::Node* node);
    AVL::Node* insert(int x, AVL::Node* node);
    AVL::Node* leftRotate(AVL::Node* node);
    AVL::Node* rightRotate(AVL::Node* node);
    AVL::Node* balance(AVL::Node* node);
    AVL::Node* findmin(AVL::Node* node);
    AVL::Node* remove(int x, AVL::Node* node);
    AVL::Node* find(int x, AVL::Node* node);
public:
    AVLTree();
    void traversal(char mode);
    void make(BinTree& tree);
    void insert(int x);
    void remove(int x);
    void find(int x);
};