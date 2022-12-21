#include <iostream>
#include <string>
#include "Stack.h"
Stack::Stack(int stackSize)
{
    size = stackSize;
    op = new std::string[size];
    top = -1;
}
Stack::~Stack()
{
    delete[] op;
}
void Stack::push(std::string data)
{
    if (top == size - 1)
    {
        std::string* opIntermed = new std::string[size];
        for (int i = 0; i < size; ++i)
            opIntermed[i] = op[i];
        delete[] op;
        int sizeIntermed = size;
        size *= 2;
        op = new std::string[size];
        for (int i = 0; i < sizeIntermed; ++i)
            op[i] = opIntermed[i];
        delete[] opIntermed;
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
    return top == -1;
}