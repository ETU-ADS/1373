#pragma once

struct Run
{
    int firstElement;
    int size;
};

class Stack
{
    Run* x;
    int size, top;
public:
    Stack(int stackSize);

    ~Stack();

    void push(Run arrRun);

    Run pop();

    Run peak();

    bool empty();

};

