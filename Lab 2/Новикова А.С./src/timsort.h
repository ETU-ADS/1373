#pragma once
#include "stack.h"

void randomInput(int* arr, int size);
void manualInput(int* arr, int size);
int getMinrun(int size); //вычисление minrun-а
void reverse(int* arr, int size);
void merge(int* arr, int left, int mid, int right); //слияние
void insertionSort(int* arr, int left, int right); //сортировка вставками
void timsort(int* arr, int size); //тимсорт

