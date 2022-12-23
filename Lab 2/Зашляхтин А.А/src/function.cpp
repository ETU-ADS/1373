#include "definition.h"


void InsertionSort(int arr[], int start, int end)
{
    int temp;
    for (int i = 1; i < (end - start + 1); i++)
    {
        for (int j = (end - start + 1) - i; j < (end - start + 1); j++)
        {
            if (arr[end - j] > arr[end - j + 1])
            {
                temp = arr[end - j];
                arr[end - j] = arr[end - j + 1];
                arr[end - j + 1] = temp;
            }
        }
    }
}


void OutputArray(int arr[], int capacity)
{
    for (unsigned i = 0; i < capacity; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int GetMinrun(int n)
{
    int r = 0;
    while (n >= 64)
    {
        r = r | n & 1;
        n >>= 1;
    }
    return n + r;
}

void Reverse(int arr[], int start, int end)
{
    int temp;
    for (int i = start; i < (end - start + 1) / 2; ++i)
    {
        temp = arr[i];
        arr[i] = arr[end - i];
        arr[end - i] = temp;
    }
}

int StackClass::quant()
{
    return quantity + 1;
}
int* StackClass::peek()
{
    return current->runs;
}
StackClass::~StackClass()
{
    while (current != NULL)
    {
        Stack* temp;
        temp = current->address;
        delete current;
        current = temp;
    }
}

StackClass::StackClass()
{
    current = NULL;
    quantity = -1;
}

int* StackClass::pop()
{
    Stack* temp;
    int temporary[2];
    int start;
    int amount;
    --quantity;
    temp = current->address;
    temporary[0] = current->runs[0];
    temporary[1] = current->runs[1];
    delete current;
    current = temp;
    return temporary;
}

void StackClass::push(int start, int size)
{

    ++quantity;
    Stack* newElement = new Stack;
    newElement->address = current;
    current = newElement;
    current->runs[0] = start;
    current->runs[1] = size;

}

int min(int first, int second)
{
    if (first > second)
        return second;
    else
        return first;
}
// -----------------------------------------------------------------------------------------
int BinarySearch(int array1[], int key, int start, int end)
{
    int left = start;
    int right = end;
    int mid;
    if (key > array1[right])
        return end + 1;
    while (left <= right)
    {
        mid = (right + left) / 2;

        if (key < array1[mid])
            right = mid - 1;
        else if (key > array1[mid])
            left = mid + 1;
        else if (key = array1[mid])
            return mid;
    }
    return right + 1;

}

void merge(int check[], int out1[], int out2[], int result[])
{
    int* left;
    int* right;
    if (out1[0] < out2[0])
    {
        left = out1;
        right = out2;
    }
    else
    {
        left = out2;
        right = out1;
    }
    int size = left[1];
    int* temp = new int[size];

    int t = left[0];
    for (int i = 0; i < left[1]; i++)
    {
        temp[i] = check[t];
        ++t;
    }

    int size2 = right[0] + right[1];
    int it1 = 0;
    int it2 = right[0];
    int it3 = left[0];
    result[0] = left[0];
    int itgal1 = 0;
    int itgal2 = 0;
    bool galop1 = 0;
    bool galop2 = 0;
    int k = 0;
    int l = 0;

    while (it1 < size && it2 < size2)
    {
        if (galop1 == 1)
        {
            k = BinarySearch(temp, check[it2], 0, size - 1);
            //std::cout << it1 << std::endl;

            while (it1 < k)
            {
                check[it3] = temp[it1];
                ++it1;
                ++it3;
            }
            if (k < size)
            {
                galop1 = 0;
            }
            else
            {
                while (it2 != size2)
                {
                    check[it3] = check[it2];
                    ++it2;
                    ++it3;
                }
            }
        }
        else if (galop2 == 1)
        {
            l = BinarySearch(check, temp[it1], it2, size2 - 1);
            //std::cout << it2 << std::endl;

            while (it2 < l)
            {
                check[it3] = check[it2];
                ++it2;
                ++it3;
            }
            if (k < size)
            {
                galop2 = 0;
            }
            else
            {
                while (it1 != size)
                {
                    check[it3] = temp[it1];
                    ++it1;
                    ++it3;
                }
            }
        }
        else
        {
            if (temp[it1] < check[it2])
            {
                check[it3] = temp[it1];
                ++it3;
                ++it1;
                ++itgal1;
                itgal2 = 0;
                if (itgal1 >= 7)
                {
                    galop1 = 1;
                    itgal1 = 0;
                }
            }
            else
            {
                check[it3] = check[it2];
                ++it2;
                ++it3;
                ++itgal2;
                itgal1 = 0;
                if (itgal2 >= 7)
                {
                    galop2 = 1;
                    itgal2 = 0;
                }
            }
        }


    }

    while (it1 != size)
    {
        check[it3] = temp[it1];
        ++it1;
        ++it3;
    }
    while (it2 != size2)
    {
        check[it3] = check[it2];
        ++it2;
        ++it3;
    }

    result[1] = it3 - result[0];

    delete[]temp;
}

void TimSort(int check[], int size)
{
    int minrun = GetMinrun(size);

    StackClass stack;
    int amount = 0;
    int i = 0;
    while (i < (size - 1))
    {
        if (check[i] <= check[i + 1])
        {
            i += 2;
            amount += 2;
            if (size - i > 1)
            {
                while ((i + 1) < size && check[i - 1] <= check[i])
                {
                    ++i;
                    ++amount;
                }
            }

        }
        else
        {
            i += 2;
            amount += 2;
            if (size - i > 1)
            {
                while ((i + 1) < size && check[i - 1] > check[i])
                {
                    ++i;
                    ++amount;
                }
            }
            Reverse(check, i - amount, i - 1);
        }
        if (i < size)
        {
            while (i < size && amount < minrun)
            {
                ++i;
                ++amount;
            }
        }

        InsertionSort(check, i - amount, i - 1);
        stack.push(i - amount, amount);
        amount = 0;
    }
    //delete []check;

    int capacity = 2 * stack.quant();
    int* data = new int[capacity];
    int ind = stack.quant() - 1;
    while (stack.quant() > 0)
    {
        data[2 * ind] = stack.peek()[0];
        data[2 * ind + 1] = stack.pop()[1];
        --ind;
    }
    // --------------------------------------------------------------------------------------
    stack.push(data[0], data[1]);
    ind = 1;
    int result[2];
    int out1[2];
    int out2[2];
    int out3[2];
    bool flag = 0;
    while (stack.quant() > 0 && flag == 0)
    {
        if (stack.quant() == 1)
        {
            if (ind <= ((capacity / 2) - 1))
            {
                stack.push(data[2 * ind], data[2 * ind + 1]);
                ++ind;
            }
            else
            {
                flag = 1;
            }
        }
        else if (stack.quant() == 2)
        {
            out1[0] = stack.peek()[0];
            out1[1] = stack.pop()[1];
            out2[0] = stack.peek()[0];
            out2[1] = stack.pop()[1];
            if (out1[1] < out2[1])
            {
                stack.push(out2[0], out2[1]);
                stack.push(out1[0], out1[1]);

                if (ind <= ((capacity / 2) - 1))
                {
                    stack.push(data[2 * ind], data[2 * ind + 1]);
                    ++ind;
                }
                else
                {
                    out1[0] = stack.peek()[0];
                    out1[1] = stack.pop()[1];
                    out2[0] = stack.peek()[0];
                    out2[1] = stack.pop()[1];
                    merge(check, out1, out2, result);
                    stack.push(result[0], result[1]);
                }
            }
            else
            {
                merge(check, out1, out2, result);
                stack.push(result[0], result[1]);
            }

        }
        else if (stack.quant() > 2)
        {
            out1[0] = stack.peek()[0];
            out1[1] = stack.pop()[1];
            out2[0] = stack.peek()[0];
            out2[1] = stack.pop()[1];
            out3[0] = stack.peek()[0];
            out3[1] = stack.pop()[1];
            if (out3[1] > out2[1] + out1[1] && out2[1] > out1[1])
            {
                stack.push(out3[0], out3[1]);
                stack.push(out2[0], out2[1]);
                stack.push(out1[0], out1[1]);
                if (ind <= ((capacity / 2) - 1))
                {
                    stack.push(data[2 * ind], data[2 * ind + 1]);
                    ++ind;
                }
                else
                {
                    out1[0] = stack.peek()[0];
                    out1[1] = stack.pop()[1];
                    out2[0] = stack.peek()[0];
                    out2[1] = stack.pop()[1];
                    merge(check, out1, out2, result);
                    stack.push(result[0], result[1]);
                }
            }
            else
            {
                int* min;
                int* max;
                if (out1[1] > out3[1])
                {
                    min = out3;
                    max = out1;
                }
                else
                {
                    min = out1;
                    max = out3;
                }
                merge(check, min, out2, result);
                stack.push(max[0], max[1]);
                stack.push(result[0], result[1]);
            }
        }
    }
}