#include <iostream>
#include "DynamicArray.h"
DynamicArray::DynamicArray(int arrCap)
{
    cap = arrCap;
    size = 0;
    arr = new int[cap];
}
DynamicArray::~DynamicArray()
{
    delete[] arr;
}
int DynamicArray::out(int index)
{
    if ((size - 1) < index)
    {
        std::cout << "There are no this index" << std::endl;
        return -1;
    }
    return arr[index];
}
void DynamicArray::print()
{
    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}
int DynamicArray::find(int data)
{
    int index = 0;
    for (int i = 0; i < size; ++i)
    {
        if (arr[i] == data)
            return index;
        ++index;
    }
    std::cout << "There are no this element" << std::endl;
    return -1;
}
void DynamicArray::add(int index, int data)
{
    if (size == cap)
    {
        int* arrBuff = new int[cap];
        for (int i = 0; i < size; ++i)
            arrBuff[i] = arr[i];
        delete[] arr;
        cap *= 2;
        arr = new int[cap];
        for (int i = 0; i < size; ++i)
            arr[i] = arrBuff[i];
        delete[] arrBuff;
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
void DynamicArray::addBack(int data)
{
    if (size == cap)
    {
        int* arrBuff = new int[cap];
        for (int i = 0; i < size; ++i)
            arrBuff[i] = arr[i];
        delete[] arr;
        cap *= 2;
        arr = new int[cap];
        for (int i = 0; i < size; ++i)
            arr[i] = arrBuff[i];
        delete[] arrBuff;
    }
    arr[size] = data;
    ++size;
}
void DynamicArray::del(int index)
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

int DynamicArray::getSize()
{
    return size;
}
int DynamicArray::operator[](int i)
{
    return arr[i];
}