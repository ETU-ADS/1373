#pragma once
#include "Tree.h"

class Stack
{
    Node** node;
    int size, top;
public:
    Stack(int stackSize);

    ~Stack();

    void push(Node* run);

    Node* pop();

    Node* peak();

    bool empty();

};