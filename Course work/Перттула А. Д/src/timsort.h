//
// Created by theta-sigma on 12/14/2022.
//

#ifndef SRC_TIMSORT_H
#define SRC_TIMSORT_H

#include <cstring>
#include <iostream>
#include "Stack.h"

const int MIN_GALLOP = 7;
const int MINRUN = 64;
const int LARGE_N = 20000;

int calculateMinrun(int n) {
    if (n < 64) {
        return MINRUN;
    }

    char flag = 0;
    while (n >= 64) {
        flag |= n & 1;
        n >>= 1;
    }

    return n + flag;
}

template<typename T>
int reverse(T *arr, int len) {
    for (int i = 0; i < len / 2; i++) {
        T tmp = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = tmp;
    }

    return 1;
}

template<typename T>
void insertionSort(T *arr, int n) {
    for (int j = 1; j < n; j++) {
        T value = arr[j];
        int i = j - 1;

        while ((i >= 0) && (arr[i] > value)) {
            arr[i + 1] = arr[i];
            arr[i] = value;
            i--;
        }
    }
}

template<typename T>
int binarySearch(T x, const T *sortedArr, int low, int high) {
    while (low <= high) {
        int mid = (low + high) / 2;
        if (sortedArr[mid] > x) {
            high = mid - 1;
        } else if (sortedArr[mid] < x) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return low;
}

template<typename T>
int mergeFunc(T *arr, std::pair<int, int> pairX, std::pair<int, int> pairY) {
    int lenX = pairX.second;
    int lenY = pairY.second;

    T *xArr = arr + pairX.first;
    T *yArr = arr + pairY.first;

    T *mergedArr = new T[lenX + lenY];

    int choseX = 0, choseY = 0;
    int i = 0, j = 0, k = 0;
    for (; (i < lenX) && (j < lenY);) {
        if (xArr[i] < yArr[j]) {
            mergedArr[k++] = xArr[i++];

            choseX++;
            choseY = 0;
        } else {
            mergedArr[k++] = yArr[j++];

            choseX = 0;
            choseY++;
        }

        int foundPosition;
        if (choseX == MIN_GALLOP) {
            foundPosition = binarySearch(yArr[j], xArr, i, lenX - 1);

//            memcpy(mergedArr + k, xArr + i, (foundPosition - i) * sizeof(int));

            for(int ccc = i; ccc < (foundPosition - i); ccc++) {
                mergedArr[k + ccc] = xArr[i + ccc];
            }

            k += foundPosition - i;
            i = foundPosition;
        } else if (choseY == MIN_GALLOP) {
            foundPosition = binarySearch(xArr[i], yArr, j, lenY - 1);

//            memcpy(mergedArr + k, yArr + j, (foundPosition - j) * sizeof(int));

            for(int ccc = j; ccc < (foundPosition - j); ccc++) {
                mergedArr[k + ccc] = yArr[j + ccc];
            }

            k += foundPosition - j;
            j = foundPosition;
        }
    }

    if (i < lenX) {
//        memcpy(mergedArr + k, xArr + i, (lenX - i) * sizeof(int));

        for(int ccc = i; ccc < (lenX - i); ccc++) {
            mergedArr[k + ccc] = xArr[i + ccc];
        }

    } else if (j < lenY) {
//        memcpy(mergedArr + k, yArr + j, (lenY - j) * sizeof(int));

        for(int ccc = j; ccc < (lenY - j); ccc++) {
            mergedArr[k + ccc] = xArr[j + ccc];
        }
    } else {
        std::cout << "something strange happened..." << std::endl;

        return 0;
    }

//    memcpy(arr + pairX.first, mergedArr, (lenX + lenY) * sizeof(int));

    for(int ccc = 0; ccc < (lenX + lenY); ccc++) {
        arr[pairX.first + ccc] = xArr[ccc];
    }

    delete[] mergedArr;

    return 1;
}

template<typename T>
int timsort(T *arr, int len) {
    // step 1
    int minrun = calculateMinrun(len);

    // step 2
    int shift = 0;
//    ArrayList<std::pair<int, int>> shiftLenArray;
    Stack<std::pair<int, int>> shiftLenStack;
    while (shift + 1 < len) {
        int run = 2;
        bool ascending = arr[shift] < arr[shift + 1];
        for (int i = shift + 2; i < len; i++) {
            if (ascending && (arr[i - 1] > arr[i])) {
                break;
            }

            if (!ascending && (arr[i - 1] < arr[i])) {
                break;
            }

            run++;
        }

        if (!ascending) {
            reverse(arr + shift, run);
        }

        int sss = shift + minrun < len ? minrun : len - shift;
        if (run < minrun) {
            insertionSort(arr + shift, sss);
            auto pairZ = std::pair<int, int>(shift, sss);
            shiftLenStack.push(pairZ);

            shift += minrun;
        } else {
            auto pairZ = std::pair<int, int>(shift, run);
            shiftLenStack.push(pairZ);
            shift += run;
        }

        if (shift + 1 == len) {
            auto pairZ = std::pair<int, int>(shift, 1);
            shiftLenStack.push(pairZ);
            break;
        }
    }

    // step 3

    while (true) {
        if (shiftLenStack.size() <= 1) {
            break;
        } else if (shiftLenStack.size() == 2) {
            auto pairZ = shiftLenStack.pop();
            auto pairY = shiftLenStack.pop();

            mergeFunc(arr, pairY, pairZ);

            auto mergedPair = std::pair<int, int>(pairY.first, pairY.second + pairZ.second);
            shiftLenStack.push(mergedPair);
        } else if (shiftLenStack.size() > 2) {
            auto pairZ = shiftLenStack.pop();
            auto pairY = shiftLenStack.pop();
            auto pairX = shiftLenStack.pop();
            if (pairX.second > pairY.second + pairZ.second) {
                if (pairZ.second > pairY.second) {
                    mergeFunc(arr, pairY, pairZ);
                    auto mergedPair = std::pair<int, int>(pairY.first, pairY.second + pairZ.second);
                    shiftLenStack.push(pairX);
                    shiftLenStack.push(mergedPair);
                } else {
                    break;
                }
            } else {
                if (pairZ.second < pairX.second) {
                    mergeFunc(arr, pairY, pairZ);
                    auto mergedPair = std::pair<int, int>(pairY.first, pairY.second + pairZ.second);
                    shiftLenStack.push(pairX);
                    shiftLenStack.push(mergedPair);
                } else {
                    mergeFunc(arr, pairX, pairY);
                    auto mergedPair = std::pair<int, int>(pairX.first, pairX.second + pairY.second);
                    shiftLenStack.push(mergedPair);
                    shiftLenStack.push(pairZ);
                }
            }
        }
    }

    return 1;
}

#endif //SRC_TIMSORT_H
