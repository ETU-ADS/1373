#include <iostream>
#include <fstream>

#include "randNum.h"
#include "myList.h"
#include "myVector.h"
#include "myStack.h"
#include "mySorts.h"


int main() {
    int const N = 200;

    // first parametr - max value, last - amount of numbers
    //randomNumbers(1000, 2000, N);

    // full mass with rand num
    std::ifstream DATA("rand_num.txt");
    int DATA_arr[N];
    for (int i = 0; i < N; i++) {
        DATA >> DATA_arr[i];
    }

    Teamsort(DATA_arr, N);

    std::cout << '\n';
    system("pause");
    return 0;
}