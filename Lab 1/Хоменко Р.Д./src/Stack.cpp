#include <iostream>
#include <string>
#include "Stack.h"
Stack::Stack(int stackSize)
{
    size = stackSize;
    op = new std::string[size];
    top = 0;
}
Stack::~Stack()
{
    delete[] op;
}
void Stack::push(std::string data)
{
    if (top == size - 1)
    {
        std::string* opBuff = new std::string[size];
        for (int i = 0; i < size; ++i)
            opBuff[i] = op[i];
        delete[] op;
        int sizeBuff = size;
        size *= 2;
        op = new std::string[size];
        for (int i = 0; i < sizeBuff; ++i)
            op[i] = opBuff[i];
        delete[] opBuff;
    }
    op[++top] = data;
}
std::string Stack::pop()
{
    return op[top--];
}
std::string Stack::see()
{
    return op[top];
}
bool Stack::empty()
{
    return top == 0;
}