#include "stack.h"

Stack::Stack(int stackSize)
{
    size = stackSize;
    x = new Run[size];
    top = -1;
}
Stack::~Stack()
{
    delete[] x;
}
void Stack::push(Run run)
{
    if (top == size - 1)
    {
        Run* runBuff = new Run[size];
        for (int i = 0; i < size; ++i)
            runBuff[i] = x[i];
        delete[] x;
        int sizeBuff = size;
        size *= 2;
        x = new Run[size];
        for (int i = 0; i < sizeBuff; ++i)
            x[i] = runBuff[i];
        delete[] runBuff;
    }
    x[++top] = run;
}
Run Stack::pop()
{
    return x[top--];
}
Run Stack::peak()
{
    return x[top];
}
bool Stack::empty()
{
    return top == -1;
}