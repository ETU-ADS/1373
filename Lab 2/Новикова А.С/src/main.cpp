#include "timsort.h"

int main()
{
    int size;
    int answer = 5;

    std::cout << "Enter the size of the array: ";
    std::cin >> size;
    std::cout << "Choose input method: manual input - 0, random input - 1" << std::endl << "Your choice: ";
    std::cin >> answer;

    while (!(answer == 0 || answer == 1))
    {
        std::cout << "You've enter an invalid number. Try again. Your choice: ";
        std::cin >> answer;
    }

    int* arr = new int[size];
    if (answer == 0)
        manualInput(arr, size);
    else
        randomInput(arr, size);

    std::cout << "Your array: ";
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;

    timsort(arr, size);

    std::cout << "Sorted array: ";
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;

    delete[] arr;

    system("pause");
    return 0;
}
