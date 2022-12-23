#include <iostream>
#include <cstdlib>
#include <ctime>
#include "definition.h"

int main()
{   
    int size;
    std::cout << "Enter size of array:" << std::endl;
    std::cin >> size;
    bool random;
    std::cout << "Choose <0> if you want to generate random array or <1> if you want to fill array" << std::endl;
    std::cin >> random;

    int* check = new int[size];
    if (random == 0)
    {
        srand(unsigned(time(0)));
        for (int i = 0; i < size; ++i)
        {
            check[i] = rand() % 100;
        }
        OutputArray(check, size);
        std::cout << std::endl;
    }
    else
    {
        for (int i = 0; i < size; ++i)
        {
            std::cin >> check[i];
        }
    }

    TimSort(check, size);

    std::cout << std::endl;
    OutputArray(check, size);
    delete[] check;
    system("pause");
    return 0;
}

