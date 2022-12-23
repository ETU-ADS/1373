/*#include "Stack.h"

int getMinrun(int n)
{
    int r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

void insertionSort(int* arr, int start, int end)
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

void reverse(int* arr, int size)
{
    for (int i = 0; i < size / 2; ++i)
    {
        arr[i] = arr[i] + arr[size - 1 - i];
        arr[size - 1 - i] = arr[i] - arr[size - 1 - i];
        arr[i] = arr[i] - arr[size - 1 - i];
    }
}

void merge(int* arr, int lowerBegin, int lowerEnd, int upperEnd)
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
    int indexLow = 0, indexUp = 0, index = lowerBegin,countLow = 0, countUp = 0, intermed;
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
        else
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

void timSort(int* arr, int size)
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
            while (arr[i] >= arr[i - 1])
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
                insertionSort(arr, arrRun.firstElement, arrRun.firstElement + arrRun.size - 1);
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

        if (arr[i] < arr[i - 1])
        {
            while (arr[i] < arr[i - 1])
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
                insertionSort(arr, arrRun.firstElement, arrRun.firstElement + arrRun.size - 1);
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

    while (true)
    {
        Run X, Y;
        X = runStack.pop();
        if (runStack.empty())
            break;
        Y = runStack.pop();
        if (runStack.empty())
        {
            merge(arr, Y.firstElement, Y.firstElement + Y.size - 1, X.firstElement + X.size - 1);
            break;
        }
        if ((runStack.peak().size > X.size + Y.size && Y.size > X.size))
            break;
        else
        {
            if (X.size <= runStack.peak().size)
            {
                merge(arr, Y.firstElement, Y.firstElement + Y.size - 1, X.firstElement + X.size - 1);
                Y.size = X.size + Y.size;
                runStack.push(Y);
            }
            else
            {
                Run Z = runStack.pop();
                merge(arr, Z.firstElement, Z.firstElement + Z.size - 1, Y.firstElement + Y.size - 1);
                Z.size = Y.size + Z.size;
                runStack.push(Z);
                runStack.push(X);
            }
        }
    }
}*/