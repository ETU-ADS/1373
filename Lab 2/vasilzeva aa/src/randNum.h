#pragma once

#include <iostream>
#include <fstream>
#include <ctime>

void randomNumbers(int min_value, int max_value, int max_count) {

    std::ofstream DATA("rand_num.txt");

    srand(time(0));
    for (int i = 0; i < max_count; i++) {
        DATA << min_value + rand() % max_value << "\n";
    }
}
