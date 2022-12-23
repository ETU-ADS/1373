#include <iostream>
#include "DynamicArr.h"
#include "Stack.h"
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
void DynamicArr::RandomArray()
{
    int i;
    srand(time(0));
    size = capacity;
    for (i = 0; i < size; i++)
        arr[i] = rand() % 400 - 200;
    for (i = 0; i < size; i++)
        std::cout << arr[i] << " ";
}

void DynamicArr::printArr()
{
    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << "\t";
    std::cout << std::endl;
}
int getMinrun(int n)
{
    int r = 0;
    while (n >= 64)
    {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

void DynamicArr::insertionSort(int start, int end)
{
    int key, j;
    for (int i = start + 1; i <= end; ++i)
    {
        key = arr[i];
        j = i - 1;
        while (j >= start && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void DynamicArr::reverse(int* arr, int size)
{
    for (int i = 0; i < size / 2; ++i)
    {
        arr[i] = arr[i] + arr[size - 1 - i];
        arr[size - 1 - i] = arr[i] - arr[size - 1 - i];
        arr[i] = arr[i] - arr[size - 1 - i];
    }
}

void DynamicArr::merge(int lowerBegin, int lowerEnd, int upperEnd)
{
    int lengLow = lowerEnd - lowerBegin + 1,
        lengUp = upperEnd - lowerEnd;
    int* lower = new int[lengLow],
        * upper = new int[lengUp];
    for (int i = 0; i < lengLow; ++i)
    {
        lower[i] = arr[i + lowerBegin];
    }
    for (int i = 0; i < lengUp; ++i)
    {
        upper[i] = arr[i + lowerEnd + 1];
    }
    int indexLow = 0, indexUp = 0, index = lowerBegin, countLow = 0, countUp = 0, intermed;
    bool gallop = false, offGallop = false;
    bool LowerLessUpper = false;
    while (indexLow < lengLow && indexUp < lengUp)
    {
        if (lower[indexLow] <= upper[indexUp])
        {
            arr[index] = lower[indexLow];
            ++indexLow;
            ++index;
            countUp = 0;
            if ((++countLow) == 7 && gallop)
            {
                gallop = true;
                intermed = indexLow;
            }
        }
        else if (lower[indexLow] > upper[indexUp])
        {
            arr[index] = upper[indexUp];
            ++indexUp;
            ++index;
            countLow = 0;
            if ((++countUp) == 7 && gallop)
            {
                gallop = true;
                intermed = indexUp;
            }
        }
        if (gallop)
        {
            if (countLow)
            {
                if (lower[intermed] <= upper[indexUp])
                {
                    if (indexLow + (2 << (countLow - 7)) < lengLow)
                        intermed = indexLow + (2 << (countLow - 7));
                    else if (intermed != lengLow - 1)
                        intermed = lengLow - 1;
                    else
                    {
                        LowerLessUpper = true;
                        break;
                    }
                    ++countLow;
                }
                else
                {
                    gallop = false;
                    offGallop = true;
                    countLow = 0;
                }
            }
            else
            {
                if (upper[intermed] <= lower[indexLow])
                {
                    if (indexUp + (2 << (countUp - 7)) < lengUp)
                        intermed = indexUp + (2 << (countUp - 7));
                    else if (intermed != lengUp - 1)
                        intermed = lengUp - 1;
                    else
                    {
                        LowerLessUpper = false;
                        break;
                    }
                    ++countUp;
                }
                else
                {
                    gallop = false;
                    offGallop = true;
                    countUp = 0;
                }
            }
        }
    }
    if (LowerLessUpper)
    {
        while (indexLow < lengLow)
        {
            arr[index] = lower[indexLow];
            ++index;
            ++indexLow;
        }
        while (indexUp < lengUp)
        {
            arr[index] = upper[indexUp];
            ++index;
            ++indexUp;
        }
    }
    else
    {
        while (indexUp < lengUp)
        {
            arr[index] = upper[indexUp];
            ++index;
            ++indexUp;
        }
        while (indexLow < lengLow)
        {
            arr[index] = lower[indexLow];
            ++index;
            ++indexLow;
        }
    }
    delete[] lower;
    delete[] upper;
}

void DynamicArr::timSort()
{
    int minrun = getMinrun(size);
    Stack runStack(20);
    int i = 1;
    Run arrRun;
    arrRun.firstElement = 0;
    arrRun.size = 1;

    while (i < size)
    {
        if (arr[i] >= arr[i - 1])
        {
            while (arr[i] >= arr[i - 1] && i < size)
            {
                i += 1;
                arrRun.size += 1;
            }
            if (arrRun.size < minrun && i < size)
            {
                while (arrRun.size < minrun && i < size)
                {
                    i += 1;
                    arrRun.size += 1;
                }
                insertionSort(arrRun.firstElement, arrRun.firstElement + arrRun.size - 1);
            }
            runStack.push(arrRun);
            arrRun.firstElement = i;
            arrRun.size = 1;

            if (i == size - 1)
            {
                runStack.push(arrRun);
            }
            i += 1;
        }

        else if (arr[i] < arr[i - 1])
        {
            while (arr[i] < arr[i - 1] && i < size)
            {
                i += 1;
                arrRun.size += 1;
            }
            reverse(&arr[arrRun.firstElement], arrRun.size);
            if (arrRun.size < minrun && i < size)
            {
                while (arrRun.size < minrun && i < size)
                {
                    i += 1;
                    arrRun.size += 1;
                }
                insertionSort(arrRun.firstElement, arrRun.firstElement + arrRun.size - 1);
            }
            runStack.push(arrRun);
            arrRun.firstElement = i;
            arrRun.size = 1;
            if (i == size - 1)
            {
                runStack.push(arrRun);
            }
            i += 1;
        }
    }
    std::cout << std::endl;
    printArr();
    while (true)
    {
        Run X, Y;
        X = runStack.pop();
        if (runStack.empty())
            break;
        Y = runStack.pop();
        if (runStack.empty())
        {
            merge(Y.firstElement, Y.firstElement + Y.size - 1, X.firstElement + X.size - 1);
            break;
        }
        if ((runStack.peak().size > X.size + Y.size && Y.size > X.size))
            break;
        else
        {
            if (X.size <= runStack.peak().size)
            {
                merge(Y.firstElement, Y.firstElement + Y.size - 1, X.firstElement + X.size - 1);
                Y.size = X.size + Y.size;
                runStack.push(Y);
            }
            else
            {
                Run Z = runStack.pop();
                merge(Z.firstElement, Z.firstElement + Z.size - 1, Y.firstElement + Y.size - 1);
                Z.size = Y.size + Z.size;
                runStack.push(Z);
                runStack.push(X);
            }
        }
    }
}