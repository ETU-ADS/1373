#include <iostream>
#include "DynamicArray.h"
#include "Stack.h"
#include "ctime"
using namespace std;

void RundomNumbers(int minValue, int maxValue, int amount, DynamicArray& arr) {
    srand(time(NULL));
    for (int i = 0; i < amount; i++) {
        arr.PushBack(minValue + rand() % maxValue);
    }
}

int GetMinRun(int n) 
{
    int flag = 0;
    while (n >= 64)
    {
        flag |= n & 1;
        n >>= 1;
    }
    return n + flag;
}

struct RunInfo {
    int left;
    int size;
};

void InsertionSort(int* arr, int size) {
    for (int i = 1; i <size; i++)
    {
        int tmp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > tmp)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = tmp;
    }
}

 void MergeSort(DynamicArray& arr, int ptr1, int size1, int size2) {
     DynamicArray arr1(size1);
     DynamicArray arr2(size2);
     int ptr2 = ptr1 + size2;
     int index1 = 0;
     int index2 = 0; 
     int indexRes = 0;
     int amount = 0;
     int arrID = 0;
     for (int i = 0; i < size1; i++) {
         arr1[i] = arr[ptr1 + i];
     }
     for (int i = 0; i < size2; i++) {
         arr2[i] = arr[ptr2 + i];
     }
     while (index1 < size1 && index2 < size2) {
         if (arr1[index1] <= arr2[index2]) {
             if (amount >=7 && arrID == 1) {
                 int jump = 1;
                 while ((index1 + jump) < size1 && arr1[index1 + jump] < arr2[index2]) {
                     jump *= 2;
                 }
                 jump / 2;
                 for (int i = index1; i < index1 + jump; i++){
                     arr[indexRes] = arr1[i];
                     indexRes++;
                 }
                 index1 += jump;
                 indexRes--;
                 amount = -1;
             }
             else{
                 arr[indexRes] = arr1[index1];
                 index1++;
                 if (arrID == 2 || arrID == 0){
                     arrID = 1;
                     amount = 0;
                 }
                 amount++;
             }
         }
         else {
             if (amount >= 7 && arrID == 2){
                 int jump = 1;
                 while (jump + index2 < size2 && arr2[index2 + jump] < arr1[index1]){
                     jump *= 2;
                 }
                 jump /= 2;
                 for (int i = index2; i < index2 + jump; i++){
                     arr[indexRes] = arr2[i];
                     indexRes++;
                 }
                 index2 += jump;
                 indexRes--;
                 amount = -1;
             }
             else{
                 arr[indexRes] = arr2[index2];
                 index2++;
                 if (arrID == 1 || arrID == 0){
                     arrID = 2;
                     amount = 0;
                 }
                 amount++;
             }
         }
         indexRes++;
         if (index1 >= size1) {
             for (int i = index2; i < size2; i++)           
             {
                 arr[indexRes] = arr2[i];
                 indexRes++;
             }
         }
         else if (index2 >= size2) {
             for (int i = index1; i < size1; i++)
             {
                 arr[indexRes] = arr1[i];
                 indexRes++;
             }
         }
     }
     for (int i = 0; i < size1 + size2; i++)
     {
         arr[ptr1 + i] = arr[i];                              
     }
}
 
void TimSort(DynamicArray& arr, int N) {
    int minrun = GetMinRun(N);
    RunInfo run;
    run.left = 0;
    run.size = 1;
    Stack <RunInfo> stack(N);
    for (int i = 1; i < N;) {
        if (arr[i - 1] <= arr[i]) {
            while (true) {
                if (arr[i - 1] <= arr[i]) {
                    run.size++;
                    i++;
                }
                else {
                    if (run.size < minrun) {
                        while (run.size < minrun && i < N) {
                            run.size++;
                            i++;
                        }
                        InsertionSort(&arr[run.left], run.size);
                    }
                    stack.push(run);
                    run.left = i;
                    run.size = 1;
                    i++;
                    break;
                }
            }
        }
        if (arr[i - 1] > arr[i]) {
            while (true) {
                if (arr[i - 1] > arr[i] && i < N) {
                    run.size++;
                    i++;
                }
                else {
                    for (int i = 0; i < run.size / 2; i++) {
                        int tmp = arr[i];
                        arr[i] = arr[run.size - 1 - i];
                        arr[run.size - 1 - i] = tmp;

                    }
                    if (run.size < minrun) {
                        while (run.size < minrun && i < N) {
                            run.size++;
                            i++;
                        }
                        InsertionSort(&arr[run.left], run.size);
                    }
                    stack.push(run);
                    run.left = i;
                    run.size = 1;
                    i++;
                    break;
                }
            }
        }
    }
    int countRun = 0;
    RunInfo X, Y, Z;
    X.size = 0;
    Y.size = 0;
    Z.size = 0;
    X = stack.peak();
    countRun++;
    stack.pop();
    while (!stack.isEmpty()) {
        if (!stack.isEmpty() && Y.size == 0) {
            Y = stack.peak();
            countRun++;
            stack.pop();
        }
        if (!stack.isEmpty() && Z.size == 0) {
            Z = stack.peak();
            countRun++;
            stack.pop();
        }
        while ((Z.size <= X.size + Y.size || X.size >= Y.size) && countRun > 1) {
            if (X.size >= Y.size && countRun >= 2) {
                MergeSort(arr, Y.left, Y.size, X.size);
                if (X.left > Y.left) {
                    X.left = Y.left;
                }
                X.size = X.size + Y.size;
                if (Z.size != 0) {
                    Y = Z;
                }
                else break;
                countRun--;
                if (!stack.isEmpty()) {
                    Z = stack.peak();
                    countRun++;
                    stack.pop();
                }
            }
            if (Z.size <= X.size + Y.size && countRun >= 3) {
                if (X.size < Z.size) {
                    MergeSort(arr, Y.left, Y.size, X.size);
                    if (X.left > Y.left) {
                        X.left = Y.left;
                    }
                    X.size = X.size + Y.size;
                    Y = Z;
                    Z.size = 0;
                    countRun--;
                    if (!stack.isEmpty()) {
                        Z = stack.peak();
                        countRun++;
                        stack.pop();
                    }
                }
                else {
                    MergeSort(arr, Z.left, Z.size, Y.size);
                    if (Y.left > Z.left) {
                        Y.left = Z.left;
                    }
                    Y.size = Y.size + Z.size;
                    Z.size = 0;
                    countRun--;
                    if (!stack.isEmpty()) {
                        Z = stack.peak();
                        countRun++;
                        stack.pop();
                    }
                }
            }
        }
    }
}
int main()
{
    int N=20;
    int minValue=1;
    int maxValue=500;
    DynamicArray arr;
    RundomNumbers(minValue, maxValue, N, arr);
    cout << "Unsorted array: ";
    arr.PrintDynamicArray();
    cout << endl;
    cout << endl;
    TimSort(arr, N);
    cout << "Sorted array: ";
    arr.PrintDynamicArray();
}