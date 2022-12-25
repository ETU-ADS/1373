#pragma once
class DynamicArray
{
    int* arr;
    int size, cap;
public:
    DynamicArray(int arrCap);

    ~DynamicArray();

    int out(int index);

    void print();

    int find(int data);

    void add(int index, int data);

    void addBack(int data);

    void del(int index);

    int getSize();

    int operator[](int);
};