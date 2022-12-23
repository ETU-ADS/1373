#include <iostream>
#include "DynamicArr.h"
DynamicArr::DynamicArr(int arrCapacity)
{
    capacity = arrCapacity;
    size = 0;
    arr = new int[capacity];
}
DynamicArr::~DynamicArr()
{
    delete[] arr;
}
int DynamicArr::out(int index)
{
    if ((size - 1) < index)
    {
        std::cout << "Index is not here" << std::endl;
        return -1;
    }
    return arr[index];
}
int DynamicArr::find(int data)
{
    int index = 0;
    for (int i = 0; i < size; ++i)
    {
        if (arr[i] == data)
            return index;
        ++index;
    }
    std::cout << "Element is not here" << std::endl;
    return -1;
}
void DynamicArr::add(int data, int index)
{
    if (size == capacity)
    {
        int* arrIntermed = new int[capacity];
        for (int i = 0; i < size; ++i)
            arrIntermed[i] = arr[i];
        delete[] arr;
        capacity *= 2;
        arr = new int[capacity];
        for (int i = 0; i < size; ++i)
            arr[i] = arrIntermed[i];
        delete[] arrIntermed;
    }
    if (index >= size)
        arr[size] = data;
    else if (index < size)
    {
        int c = 0;
        while ((size - c) != index)
        {
            arr[size - c] = arr[size - c - 1];
            ++c;
        }
        arr[index] = data;
    }

    ++size;
}
void DynamicArr::del(int index)
{
    if (index == (size - 1))
        --size;
    else if (index < (size - 1))
    {
        for (int i = index; i < (size - 1); ++i)
            arr[i] = arr[i + 1];
    }
    --size;

}