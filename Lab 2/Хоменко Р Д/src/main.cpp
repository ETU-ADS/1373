#include <iostream>
#include"sort.h"
#include "tests.h"

void printArr(int const* arr, int size)
{
    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << "\t";
    std::cout << std::endl;
}

void randomInput(int* arr, int size)
{
    srand(time(NULL));
    for (int i = 0; i < size; ++i)
        arr[i] = rand() % 200 - 100;

}

void manualInput(int* arr, int size)
{
    for (int i = 0; i < size; ++i)
        std::cin >> arr[i];
}


int main()
{
    unitTest();
    int size;
    std::cout << "Enter size of your array: ";
    std::cin >> size;
    int* arr = new int[size];
    std::cout << "What input do you want: manual (1) or random (2): ";
    char choose;
    while (true)
    {
        std::cin >> choose;
        if (choose == '1')
        {
            std::cout << "\nManual input\n";
            manualInput(arr, size);
            break;
        }
        if (choose == '2')
        {
            std::cout << "\nRandom input\n";
            randomInput(arr, size);
            break;
        }
        else
        {
            std::cout << "ERROR! You must choose manual input (1) or random input (2): ";
            continue;
        }
    }
    std::cout << "\nYour array:\n";
    printArr(arr, size);
    timSort(arr, size);
    std::cout << "\nSorted array:\n";
    printArr(arr, size);
    delete[] arr;
    system("pause");
    return 0;
}
