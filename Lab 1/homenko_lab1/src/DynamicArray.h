#pragma once
class DynamicArray
{
    int* arr;
    int size, cap;
public:
    DynamicArray(int arrCap);

    ~DynamicArray();

    int out(int index);

    int find(int data);

    void add(int data, int index);

    void del(int index);

};