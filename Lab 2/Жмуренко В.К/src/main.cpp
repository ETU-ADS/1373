#include <iostream>
#include<stdlib.h>
#include<time.h>
#include "taskFunctions.h"
using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    int array[100];
    for (int i = 0; i < 100; i++)
        array[i] = rand() % (100 + 1);
    timSort(array, 100);
    for (int i = 0; i < 100; i++)
        cout << array[i] << " ";
    return 0;
}