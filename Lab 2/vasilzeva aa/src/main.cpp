#include <iostream>
#include <fstream>

#include "randNum.h"
#include "myStack.h"
#include "mySorts.h"


int main() {
    int const N = 500;
    int minValue = 1, maxValue = 2000;

    // first parametr - min value, middle - max value, last - amount of numbers
    randomNumbers(minValue, maxValue, N);
    std::cout << "For rand numbers (in amount of "<< N << ") from " << minValue << " to " << maxValue << " your sort array is:\n\n";

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