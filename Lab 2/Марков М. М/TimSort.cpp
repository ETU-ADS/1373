#include "DynamicArray.h"
#include "Stack.h"
#include <iostream>

namespace {
    int getMinrun(int size) {
        int flag = 0;
        while (size >= 64) {
            flag |= (size & 1);
            size >>= 1;
        }
        return size + flag;
    }

    void merge(DynamicArray<int>& arrayToSort, int startIndex, int midIndex, int endIndex) {
        int i = 0, j = 0;
        int gallopI = 0, gallopJ = 0;
        bool gallopingMode = false;
        DynamicArray<int> tempArray;
        for (int l = 0; l < arrayToSort.length(); l++) { // copying array to temp
            tempArray.add(arrayToSort[l]);
        }
        tempArray.add(midIndex + 1, INT32_MAX); // maximum value to make comparation correct
        tempArray.add(endIndex + 1, INT32_MAX);

        for (int k = startIndex; k <= endIndex; ++k) {
            if (!(tempArray[startIndex + i] == INT32_MAX &&
                tempArray[midIndex + 2 + j] == INT32_MAX)) {

                if (!gallopingMode) {

                    if (tempArray[startIndex + i] <= tempArray[midIndex + 2 + j]) { // we can reach 'mid+1' index, so we need maximum value here
                        arrayToSort.add(k, tempArray[startIndex + i]);
                        arrayToSort.deleteElem(k + 1);
                        ++i;
                        ++gallopI;
                        gallopJ = 0;
                    }
                    else {
                        arrayToSort.add(k, tempArray[midIndex + 2 + j]); // same
                        arrayToSort.deleteElem(k + 1);
                        ++j;
                        ++gallopJ;
                        gallopI = 0;
                    }
                    if (gallopI == 7 || gallopJ == 7) {
                        gallopingMode = true;
                    }
                }

                else {
                    if (gallopI == 7) {
                        int gallopingIndex = startIndex + i;
                        int counter;

                        for (counter = 2; tempArray[gallopingIndex] <= tempArray[midIndex + 2 + j]; counter *= 2) {
                            if (gallopingIndex + counter <= midIndex) {
                                gallopingIndex += counter;
                            }
                            else {
                                break;
                            }
                        }
                        for (i; startIndex + i < gallopingIndex; ++i) {
                            arrayToSort.add(k, tempArray[startIndex + i]);
                            arrayToSort.deleteElem(k + 1);
                            ++k;
                        }
                    }

                    else if (gallopJ == 7) {
                        int gallopingIndex = midIndex + 2 + j;
                        int counter;

                        for (counter = 2; tempArray[startIndex + i] > tempArray[gallopingIndex]; counter *= 2) {
                            if (gallopingIndex + counter <= endIndex) {
                                gallopingIndex += counter;
                            }
                            else {
                                break;
                            }
                        }
                        for (j; midIndex + 2 + j < gallopingIndex; ++j) {
                            arrayToSort.add(k, tempArray[midIndex + 2 + j]);
                            arrayToSort.deleteElem(k + 1);
                            ++k;
                        }
                    }
                    --k;
                    gallopingMode = false;
                    gallopI = 0;
                    gallopJ = 0;
                }
            }
        }
    }

    /*void mergeSort(DynamicArray<int>& arrayToSort, int startIndex, int endIndex) {
        if (startIndex < endIndex) {
            int midIndex = (startIndex + endIndex) / 2;
            mergeSort(arrayToSort, startIndex, midIndex);
            mergeSort(arrayToSort, midIndex + 1, endIndex);
            merge(arrayToSort, startIndex, midIndex, endIndex);
        }
    }*/

    void insertionSort(DynamicArray<int> &arrayToSort, int startIndex, int endIndex) {
        for (int i = startIndex + 1; i <= endIndex; ++i) {
            int j = i;
            while (j > startIndex && arrayToSort[j - 1] > arrayToSort[j]) {
                arrayToSort.swap(j - 1, j);
                --j;
            }
        }
    }

    struct beginSizePair
    {
        int index;
        int size;
    };
}

void sort(DynamicArray<int> &arrayToSort) {
    int minrun = getMinrun(arrayToSort.length());
    int currentIndex = 0;
    Stack<beginSizePair> stack;
    beginSizePair pair;

    while (currentIndex < arrayToSort.length() - 1) {
        int runSize = 0;
        if (arrayToSort[currentIndex] > arrayToSort[currentIndex + 1]) { // searching 'run' with descending
            for (int i = currentIndex; arrayToSort[i] > arrayToSort[i + 1] && i < arrayToSort.length() - 1; ++i) {
                ++runSize;
            }
            for (int i = 0; i < runSize / 2; ++i) { // reverting founded 'run'
                arrayToSort.swap(currentIndex + i, currentIndex + runSize - 1 - i);
            }
            if (currentIndex + minrun - 1 < arrayToSort.length()) {
                if (runSize < minrun) runSize = minrun;
            }
            else runSize = arrayToSort.length() - currentIndex;
            
        }
        else { // with ascending
            for (int i = currentIndex; arrayToSort[i] <= arrayToSort[i + 1] && i < arrayToSort.length() - 1; ++i) {
                ++runSize;
            }
            if (currentIndex + minrun - 1 < arrayToSort.length()) {
                if (runSize < minrun) runSize = minrun;
            }
            else runSize = arrayToSort.length() - currentIndex;
        }
        insertionSort(arrayToSort, currentIndex, currentIndex + runSize-1);

        pair.index = currentIndex;
        pair.size = runSize;
        stack.push(pair);

        if (stack.size() > 1) {
            bool threeValueCorrect = true;
            bool twoValueCorrect = false;

            beginSizePair first;
            beginSizePair second;
            beginSizePair third;

            do {
                first = stack.peak();
                stack.pop();
                second = stack.peak();
                stack.pop();

                twoValueCorrect = false;
                threeValueCorrect = true;

                if (second.size <= first.size) {
                    merge(arrayToSort, second.index, second.index + second.size - 1, first.index + first.size);
                    stack.push({ second.index, first.size + second.size });
                    continue;
                }
                else {
                    twoValueCorrect = true;
                    stack.push(second);
                    stack.push(first);
                }

                if (stack.size() > 2) {
                    first = stack.peak();
                    stack.pop();
                    second = stack.peak();
                    stack.pop();
                    third = stack.peak();
                    threeValueCorrect = false;

                    if (third.size <= first.size + second.size) {
                        if (third.size < first.size) {
                            merge(arrayToSort, third.index, third.index + third.size - 1, second.index + second.size);
                            stack.pop();
                            stack.push({ third.index, (third.size + second.size) });
                            stack.push(first);
                            continue;
                        }
                        else {
                            merge(arrayToSort, second.index, second.index + second.size - 1, first.index + first.size);
                            stack.push({ second.index, (second.size + first.size) });
                            continue;
                        }
                    }

                    else {
                        threeValueCorrect = true;
                        stack.push(second);
                        stack.push(first);
                    }
                }
            } while (!(twoValueCorrect && threeValueCorrect) && stack.size() > 1);
        }
        
        currentIndex += runSize;

        while (currentIndex == arrayToSort.length() && stack.size() > 1) {
            beginSizePair first;
            beginSizePair second;

            first = stack.peak();
            stack.pop();
            second = stack.peak();
            stack.pop();

            merge(arrayToSort, second.index, second.index + second.size - 1, first.index + first.size);
            stack.push({ second.index, first.size + second.size });
        }
    }

    int len = arrayToSort.length();

    for (int i = 0; i < len; ++i) {
        std::cout << arrayToSort[i] << " ";
    }
    std::cout << "\n\n";
}