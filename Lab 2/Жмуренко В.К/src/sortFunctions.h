#pragma once
#include "listFunctions.h"
#include "stackFunctions.h"

void swapArray(int* array, int lenght, int beggining);// Функция перевертывания массива

void insertionSort(int* array, unsigned lenght, unsigned beggining, bool ascendingOrDescending); // Функция сортировки вставками

void mergeSort(int* array, int firstBeggining, int secondBeggining, int firstLenght, int secondLenght); // Функция сортировки слиянием

void creatingRuns(int* array, unsigned lenght, int minrun, List& ourList, Stack& ourStack); // Функция разбиения массива на подмассивы