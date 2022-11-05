#include <iostream>
#include <random>

#include "DynamicArray.h"

void sort(DynamicArray<int>& arrayToSort);

int main()
{
    srand(7);
    DynamicArray<int> dinArray;
    dinArray.add(543);
    dinArray.add(342);
    dinArray.add(123);
    for (int i = 0; i < 543; ++i) { //543
        dinArray.add(rand());
        std::cout << dinArray[i] << " ";
    }
    std::cout << "\n\n";
    sort(dinArray);
    sort(dinArray);

    for (int i = 0; i < 546/2; ++i) {
        dinArray.swap(i, dinArray.length() - 1 - i);
    }
    for (int i = 0; i < 546; ++i) {
        std::cout << dinArray[i] << " ";
    }
    std::cout << "\n\n";
    sort(dinArray);

    system("pause");
}
