#include "stack.h"
Stack::Stack(int stackSize)
{
    size = stackSize;
    node = new Node * [size];
    top = -1;
}
Stack::~Stack()
{
    delete[] node;
}
void Stack::push(Node* x)
{
    if (top == size - 1)
    {
        Node** runBuff = new Node * [size];
        for (int i = 0; i < size; ++i)
            runBuff[i] = node[i];
        delete[] node;
        int sizeBuff = size;
        size *= 2;
        node = new Node * [size];
        for (int i = 0; i < sizeBuff; ++i)
            node[i] = runBuff[i];
        delete[] runBuff;
    }
    node[++top] = x;
}
Node* Stack::pop()
{
    return node[top--];
}
Node* Stack::peak()
{
    return node[top];
}
bool Stack::empty()
{
    return top == -1;
}