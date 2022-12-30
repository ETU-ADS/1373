#include <iostream>
#include "sort.h"
#include <iomanip>
using namespace std;

void manualInput(int* arr, int size)
{
    for (int i = 0; i < size; ++i)
        cin >> arr[i];
}

void randomInput(int* arr, int size)
{
    srand(time(NULL));
    for (int i = 0; i < size; ++i)
        arr[i] = rand() % 1000;

}
void printArr(int const* arr, int size)
{
    for (int i = 0; i < size; ++i)
        cout << arr[i] << "\t";
    cout << endl;
}

int main()
{
    system("color B1");
    cout << setw(60) << setfill(' ') << "Hello!\n";
    cout << setw(70) << setfill(' ') << "This is a sorting program.\n";
    cout << setw(157) << setfill('*') << "\nPlease enter the size of the array: ";
    int size;
    cin >> size;
    int* arr = new int[size];
    std::cout << "What input do you want: manual (1) or random (2): ";
    char choose;
    while (true)
    {
        cin >> choose;
        if (choose == '1')
        {
            cout << "\nManual input\n";
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
            std::cout << "Oh...You must choose manual input (1) or random input (2)!";
            continue;
        }
    }
    cout << "\nYour array:\n";
    printArr(arr, size);
    timSort(arr, size);
    cout << "\nSorted array:\n";
    printArr(arr, size);
    delete[] arr;
    system("pause");
    return 0;
}