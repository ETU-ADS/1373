#pragma once
#pragma once
#include "Tree.h"

class Stack
{
    AVL::Node** node;
    int size, top;
public:
    Stack(int stackSize);

    ~Stack();

    void push(AVL::Node* run);

    AVL::Node* pop();

    AVL::Node* peak();

    bool empty();

};