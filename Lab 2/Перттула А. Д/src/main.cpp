#include <iostream>
#include <iomanip>
#include <random>

#include "timsort.h"

int LARGE_N = 20000;

int main() {
    std::cout << "Hello, World!" << std::endl;

    int tests[][10] = {{1, 2, 80, 70, 55, 50, 3, 5, 4, 1},
                       {1, 2, 0,  70, 55, 50, 3, 5, 4, 1}};

    for (auto &t: tests) {
        std::cout << "*. ";
        for (int i: t) {
            std::cout << std::setw(3) << i << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (auto &t: tests) {
        timsort(t, 10);
    }

    for (auto &t: tests) {
        std::cout << "*. ";
        for (int i: t) {
            std::cout << std::setw(3) << i << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // LARGE N
    int n = LARGE_N;
    int insertionArr[n];
    int timArr[n];

    clock_t begin = clock();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 99);

    for (int i = 0; i < n; i++) {
        timArr[i] = insertionArr[i] = dist(mt);
    }

    insertionSort(insertionArr, n);

    std::cout << "N = " << LARGE_N << std::endl;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Insertion sort: Elapsed(ms) = " << elapsed_secs << std::endl;

    begin = clock();

    timsort(timArr, n);

    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Timsort: Elapsed(ms) = " << elapsed_secs << std::endl;

    bool flag = true;
    for (int i = 0; i < n; i++) {
        if (timArr[i] != insertionArr[i]) {
            flag = false;
            break;
        }
    }

    std::cout << "Generated random array has been sorted by insertion sort and timsort and " << std::endl;
    if(flag) {
        std::cout << "result arrays are equal!" << std::endl;
    } else {
        std::cout << "result arrays are not equal!" << std::endl;
    }

    return 0;
}
