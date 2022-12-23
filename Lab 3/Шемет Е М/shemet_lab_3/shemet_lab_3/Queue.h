#pragma once
#include "Tree.h"

class Queue
{
    Node** arr;
    int top, size;
public:
    Queue(int size);
    ~Queue();
    void push(Node* node);
    Node* pop();
    bool empty();
};