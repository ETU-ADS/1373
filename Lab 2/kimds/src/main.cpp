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

 void MergeSort(DynamicArray& arr, RunInfo run1, RunInfo run2) {
     DynamicArray general;
     int ptr1 = run1.left;
     int ptr2 = run2.left;
     int galop1 = 0;
     int galop2 = 0;
     while ((ptr1 < run1.size + run1.left) && (ptr2 < run2.size + run2.left)) {
         if ((galop1 < 7) && (galop2 < 7)) {
             if (arr[ptr1] <= arr[ptr2]) {
                 general.PushBack(arr[ptr1]);
                 ptr1++;
                 galop1++;
                 galop2 = 0;
             }
             else {
                 general.PushBack(arr[ptr2]);
                 ptr2++;
                 galop2++;
                 galop1 = 0;
             }
         }
         else {
             int jump = 1;
             int ind = 0;
             if ((galop1 > 7) && (arr[ptr1] <= arr[ptr2])) {
                 ind = ptr1;
                 while ((ind + jump < run1.size + run1.left) && (arr[ind + jump] <= arr[ptr2])) {
                     ind += jump;
                     jump *= 2;
                 }
                 if (arr[run1.size + run1.left - 1] <= arr[ptr2]) {
                     ind = run1.size + run1.left - 1;
                 }
                 else {
                     int left = ind;
                     int right = 0; 
                     int mid = 0;
                     bool flag = false;
                     if (ind + jump < run1.size + run1.left) {
                         right = ind + jump;
                     }
                     else {
                         right = run1.size + run1.left - 1;
                     }
                     while ((left <= right) && (!flag)) {
                         mid = (left + right) / 2;
                         if ((arr[mid] <= arr[ptr2]) && (arr[mid + 1] > arr[ptr2])) {
                             flag = true;
                         }
                         if (arr[mid] > arr[ptr2]) {
                             right = mid - 1;
                         }
                         else {
                             left = mid + 1;
                         }
                     }
                     if (flag) {
                         ind = mid;
                     }
                 }
                 while (ptr1 <= ind) {
                     general.PushBack(arr[ptr1]);
                     ptr1++;
                 }
                 galop1 = 0;
             }
             else {
                 galop1 = 0;
             }
             if ((galop2 > 7) && (arr[ptr2] <= arr[ptr1])) {
                 ind = ptr2;
                 while ((ind + jump < run2.size + run2.left) && (arr[ind + jump] <= arr[ptr2])) {
                     ind += jump;
                     jump *= 2;
                 }
                 if (arr[run2.size + run2.left - 1] <= arr[ptr2]) {
                     ind = run2.size + run2.left - 1;
                 }
                 else {
                     int left = ind; 
                     int right = 0;
                     int mid=0;
                     bool flag = false;

                     if (ind + jump < run2.size + run2.left) {
                         right = ind + jump;
                     }
                     else {
                         right = run2.size + run2.left - 1;
                     }
                     while ((left <= right) && (!flag)) {
                         mid = (left + right) / 2;
                         if ((arr[mid] <= arr[ptr2]) && (arr[mid + 1] > arr[ptr1])) {
                             flag = true;
                         }
                         if (arr[mid] > arr[ptr1]) {
                             right = mid - 1;
                         }
                         else {
                             left = mid + 1;
                         }
                     }
                     if (flag) {
                         ind = mid;
                     }
                 }
                 while (ptr2 <= ind) {
                     general.PushBack(arr[ptr2]);
                     ptr2++;
                 }
                 galop2 = 0;
             }
             else {
                 galop2 = 0;
             }
         }
     }

     while (ptr1 < run1.size + run1.left) {
         general.PushBack(arr[ptr1]);
         ptr1++;
     }
     while (ptr2 < run2.size + run2.left) {
         general.PushBack(arr[ptr2]);
         ptr2++;
     }

     int j = 0;
     for (int i = run2.left; i < run1.left + run1.size; i++) {
         arr[i] = general[j];
         j++;
     }
 }

 void TimSort(DynamicArray& arr, int N) {
     int minrun = GetMinRun(N);
     RunInfo run;
     run.left = 0;
     run.size = 1;
     int i = 1;
     int size_of_stack = 0;
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
                     size_of_stack++;
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
                     size_of_stack++;
                     run.left = i;
                     run.size = 1;
                     i++;
                     break;
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
                     MergeSort(arr, X, Y);
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
                         MergeSort(arr, X, Y);
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
                         MergeSort(arr, Y, Z);
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
 }

int main()
{
    int N=100;
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
    cout << endl;
}