#include <iostream>
#include"DynamicArr.h"

int main()
{
    int size;
    std::cout << "Enter array size = ";
    std::cin >> size;
    DynamicArr dynamicarr(size);
    dynamicarr.RandomArray();
    dynamicarr.timSort();
    std::cout << "\nSorted array:\n";
    dynamicarr.printArr();
    system("pause");
    return 0;
}

