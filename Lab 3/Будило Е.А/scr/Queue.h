#pragma once
#include "Tree.h"

class Queue
{
    AVL::Node** arr;
    int top, size;
public:
    Queue(int size);
    ~Queue();
    void push(AVL::Node* node);
    AVL::Node* pop();
    bool empty();
};