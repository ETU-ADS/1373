#include "stack.h"

void reverseArr(int* arr, int size)
{
    for (int i = 0; i < size / 2; ++i)
    {
        arr[i] = arr[i] + arr[size - 1 - i];
        arr[size - 1 - i] = arr[i] - arr[size - 1 - i];
        arr[i] = arr[i] - arr[size - 1 - i];
    }
}

int getMinrun(int n)
{
    int r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

void insertionSort(int* arr, int start, int end) {
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

void merge(int* arr, int start, int mid, int end)
{
    int lenl = mid - start + 1,
        lenr = end - mid;
    int* left = new int[lenl],
        * right = new int[lenr];
    for (int i = 0; i < lenl; ++i)
    {
        left[i] = arr[i + start]; //filling with elements of the original array
    }
    for (int i = 0; i < lenr; ++i)
    {
        right[i] = arr[i + mid + 1];
    }
    int indexl = 0, indexr = 0, index = start;
    int countl = 0, countr = 0, buff; //the number of elements that we take on the right and left for a gallop

    bool gallop = false, offGallop = false;
    bool leftLessRight = false;
    while (indexl < lenl && indexr < lenr)
    {
        if (gallop) {
            if (countl) {
                if (left[buff] <= right[indexr]) {
                    if (indexl + (2 << (countl - 7)) < lenl)
                        buff = indexl + (2 << (countl - 7));
                    else if (buff != lenl - 1)
                        buff = lenl - 1;
                    else
                    {
                        leftLessRight = true;
                        break;
                    }
                    ++countl;
                }
                else
                {
                    gallop = false;
                    offGallop = true;
                    countl = 0;
                }
            }
            else
            {
                if (right[buff] <= left[indexl])
                {
                    if (indexr + (2 << (countr - 7)) < lenr)
                        buff = indexr + (2 << (countr - 7));
                    else if (buff != lenr - 1)
                        buff = lenr - 1;
                    else
                    {
                        leftLessRight = false;
                        break;
                    }
                    ++countr;
                }
                else
                {
                    gallop = false;
                    offGallop = true;
                    countr = 0;
                }
            }
        }
        else if (left[indexl] <= right[indexr])
        {
            arr[index] = left[indexl];
            ++indexl;
            ++index;
            countr = 0;
            if ((++countl) == 7 && !offGallop)
            {
                gallop = true;
                buff = indexl; //memorization of the index in which entered the gallop
            }
        }
        else
        {
            arr[index] = right[indexr];
            ++indexr;
            ++index;
            countl = 0;
            if ((++countr) == 7 && !offGallop)
            {
                gallop = true;
                buff = indexr;
            }
        }
    }
    if (leftLessRight)
    {
        while (indexl < lenl)
        {
            arr[index] = left[indexl];
            ++index;
            ++indexl;
        }
        while (indexr < lenr)
        {
            arr[index] = right[indexr];
            ++index;
            ++indexr;
        }
    }
    else
    {
        while (indexr < lenr)
        {
            arr[index] = right[indexr];
            ++index;
            ++indexr;
        }
        while (indexl < lenl)
        {
            arr[index] = left[indexl];
            ++index;
            ++indexl;
        }
    }
    delete[] left;
    delete[] right;
}

void timSort(int* arr, int size)
{
    int minrun = getMinrun(size);
    Stack runStack(10);
    Run run;
    run.begin = 0;
    run.size = 1;
    for (int i = 1; i < size; ) //stack filling
    {
        if (arr[i] >= arr[i - 1])
        {
            while (arr[i] >= arr[i - 1] && i < size)
            {
                ++run.size;
                ++i;
            }
            if (run.size < minrun && i < size)
            {
                while (run.size < minrun && i < size)
                {
                    ++run.size;
                    ++i;
                }
                insertionSort(arr, run.begin, run.begin + run.size - 1);
            }
            runStack.push(run);
            run.begin = i;
            run.size = 1;
            if (i == size - 1)
            {
                runStack.push(run);
            }
            ++i;

        }
        else if (arr[i] < arr[i - 1])
        {
            while (arr[i] < arr[i - 1] && i < size)
            {
                ++run.size;
                ++i;
            }
            reverseArr(&arr[run.begin], run.size);
            if (run.size < minrun && i < size)
            {
                while (run.size < minrun && i < size)
                {
                    ++run.size;
                    ++i;
                }
                insertionSort(arr, run.begin, run.begin + run.size - 1);
            }
            runStack.push(run);
            run.begin = i;
            run.size = 1;
            if (i == size - 1)
            {
                runStack.push(run);
            }
            ++i;
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
            merge(arr, Y.begin, Y.begin + Y.size - 1, X.begin + X.size - 1);
            break;
        }
        if ((runStack.peak().size > X.size + Y.size && Y.size > X.size))
            break;
        else
        {
            if (X.size <= runStack.peak().size)
            {
                merge(arr, Y.begin, Y.begin + Y.size - 1, X.begin + X.size - 1);
                Y.size = X.size + Y.size;
                runStack.push(Y);
            }
            else
            {
                Run Z = runStack.pop();
                merge(arr, Z.begin, Z.begin + Z.size - 1, Y.begin + Y.size - 1);
                Z.size = Y.size + Z.size;
                runStack.push(Z);
                runStack.push(X);
            }
        }
    }
}