#pragma once
#include "DynamicArray.h"
#include <string>
class BinTree
{
    int key;
    BinTree* left = nullptr, * right = nullptr;

    int parcing(std::string& str, int& start, int end);
public:
    void traversal();
    void traversal(DynamicArray& arr);
    int parcing(std::string& fileName);
};


struct Node 
{
    int key; 
    Node* left = nullptr, * right = nullptr; 
    unsigned char height; 
};

class AVLTree
{
    Node* root = nullptr;

    unsigned char height(Node* node);
    int bfactor(Node* node);
    void fixheight(Node* node);
    Node* insert(int x, Node* node);
    Node* leftRotate(Node* node);
    Node* rightRotate(Node* node);
    Node* balance(Node* node);
    Node* findmin(Node* node);
    Node* remove(int x, Node* node);
    Node* find(int x, Node* node);
public:
    AVLTree();
    void traversal(char mode);
    void make(BinTree& tree);
    void insert(int x);
    void remove(int x);
    void find(int x);
};