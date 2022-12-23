#pragma once
class DynamicArr
{
    int* arr;
    int size, capacity;
public:
    DynamicArr(int arrCapacity);

    ~DynamicArr();

    int out(int index);

    int find(int data);

    void add(int data, int index);

    void del(int index);

};