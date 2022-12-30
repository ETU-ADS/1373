#include "Queue.h"
Queue::Queue(int sizeQ)
{
    arr = new AVL::Node * [sizeQ];
    top = -1;
    size = sizeQ;
}
Queue::~Queue()
{
    delete[] arr;
}
void Queue::push(AVL::Node* node)
{
    if (size - 1 == top)
    {
        AVL::Node** arrBuff = new AVL::Node * [size];
        for (int i = 0; i <= top; ++i)
            arrBuff[i] = arr[i];
        delete[] arr;
        size *= 2;
        arr = new AVL::Node * [size];
        for (int i = 0; i <= top; ++i)
            arr[i] = arrBuff[i];
        delete[] arrBuff;
    }
    for (int i = top + 1; i > 0; --i)
        arr[i] = arr[i - 1];
    arr[0] = node;
    ++top;
}
AVL::Node* Queue::pop()
{
    return arr[top--];
}
bool Queue::empty()
{
    return top == -1;
}