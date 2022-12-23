#pragma once
#include <string>
class Stack
{
    std::string* op;
    int size, top;
    
public:
    Stack(int stackSize);

    ~Stack();

    void push(std::string data);

    std::string pop();

    std::string see();

    bool empty();

};