#pragma once

#include <iostream>
#include <ctime>

template <class Type>
void randNum(int min_value, int max_value, int max_count, rbTree<Type>* tree) {

    int data;
    srand(time(0));
    for (int i = 0; i < max_count; i++) {
        data = min_value + rand() % max_value;
        tree->addElem(data);
    }
}