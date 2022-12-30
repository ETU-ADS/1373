#pragma once

struct Run
{
    int begin;
    int size;
};

class Stack
{
    Run* x;
    int size, top;
public:
    Stack(int stackSize);

    ~Stack();

    void push(Run run);

    Run pop();

    Run peak();

    bool empty();

};