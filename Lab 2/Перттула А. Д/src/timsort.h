//
// Created by theta-sigma on 12/19/2022.
//

#pragma once

#include <utility>

int calculateMinrun(int n);

int reverse(int *arr, int len);

void insertionSort(int *arr, int n);

int binarySearch(int x, const int *sortedArr, int low, int high);

int mergeFunc(int *arr, std::pair<int, int> pairX, std::pair<int, int> pairY);

int timsort(int *arr, int len);
