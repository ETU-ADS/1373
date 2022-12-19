//
// Created by theta-sigma on 12/19/2022.
//

#include <cstring>
#include <iostream>

#include "Stack.h"

const int MIN_GALLOP = 7;
const int MINRUN = 64;

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

int reverse(int *arr, int len) {
    for (int i = 0; i < len / 2; i++) {
        int tmp = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = tmp;
    }

    return 1;
}

void insertionSort(int *arr, int n) {
    for (int j = 1; j < n; j++) {
        int value = arr[j];
        int i = j - 1;

        while ((i >= 0) && (arr[i] > value)) {
            arr[i + 1] = arr[i];
            arr[i] = value;
            i--;
        }
    }
}

int binarySearch(int x, const int *sortedArr, int low, int high) {
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

int mergeFunc(int *arr, std::pair<int, int> pairX, std::pair<int, int> pairY) {
    int lenX = pairX.second;
    int lenY = pairY.second;

    int *xArr = arr + pairX.first;
    int *yArr = arr + pairY.first;

    int *mergedArr = new int[lenX + lenY];

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
            memcpy(mergedArr + k, xArr + i, (foundPosition - i) * sizeof(int));
            k += foundPosition - i;
            i = foundPosition;
        } else if (choseY == MIN_GALLOP) {
            foundPosition = binarySearch(xArr[i], yArr, j, lenY - 1);
            memcpy(mergedArr + k, yArr + j, (foundPosition - j) * sizeof(int));

            k += foundPosition - j;
            j = foundPosition;
        }
    }

    if (i < lenX) {
        memcpy(mergedArr + k, xArr + i, (lenX - i) * sizeof(int));
    } else if (j < lenY) {
        memcpy(mergedArr + k, yArr + j, (lenY - j) * sizeof(int));
    } else {
        std::cout << "something strange happened..." << std::endl;

        return 0;
    }

    memcpy(arr + pairX.first, mergedArr, (lenX + lenY) * sizeof(int));

    delete[] mergedArr;

    return 1;
}

int timsort(int *arr, int len) {
    // step 1
    int minrun = calculateMinrun(len);

    // step 2
    int shift = 0;
//    ArrayList<std::pair<int, int>> shiftLenArray;
    Stack<std::pair<int, int>> shiftLenStack;
    while (shift < len) {
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

//            if (pairZ.second > pairY.second) {
//                mergeFunc(arr, pairY, pairZ);
//                auto mergedPair = std::pair<int, int>(pairY.first, pairY.second + pairZ.second);
//                shiftLenStack.push(mergedPair);
//            } else {
//                break;
//            }
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
