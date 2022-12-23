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
    void RandomArray();
    void reverse(int* arr, int size);
    void merge(int lowerBegin, int lowerEnd, int upperEnd);

    
    void insertionSort(int startt, int endd);

    void timSort();

    void printArr();

};
