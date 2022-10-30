#include <iostream>

#include "randNum.h"
#include "myStack.h"
#include "myVector.h"
#include "mySorts.h"


int main() {
    int const N = 500;

    // our work-data
    myVector<int> DATA_arr;

    int minValue = 1, maxValue = 2000;

    // first parametr - min value, middle - max value, last - amount of numbers
    randomNumbers(minValue, maxValue, N, DATA_arr);
    std::cout << "For rand numbers (in amount of "<< N << ") from " << minValue << " to " << maxValue << " your sort array is:\n\n";

    unsigned int start_time = clock();
    Teamsort(DATA_arr, N);
    unsigned int end_time = clock();

    int prevElement = -1;
    for (int i = 0; i < N; i++) {
        if (prevElement > DATA_arr[i]) {
            std::cout << "\nTeamSort massage -> ERROR: UNCORRECT PROCESS";
            break;
        }
        else
            prevElement = DATA_arr[i];

        std::cout << DATA_arr[i] << ' ';
    }

    std::cout << "\n\nWork time: " << end_time - start_time << " ms";

    std::cout << '\n';
    system("pause");
    return 0;
}