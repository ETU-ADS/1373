#pragma once

#include <iostream>
#include <fstream>
#include <ctime>

#include"myVector.h"

void randomNumbers(int min_value, int max_value, int max_count, myVector<int>& data) {

    std::ofstream DATA("rand_num.txt");

    srand(time(0));
    for (int i = 0; i < max_count; i++) {
         data.addToTheEnd(min_value + rand() % max_value);
    }
}
