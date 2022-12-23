#pragma once
#include <iostream>

struct Stack
{
    Stack* address;
    int runs[2];
};

class StackClass
{
private:
    Stack* current;
    int quantity;
public:
    StackClass();
    ~StackClass();
    int quant();
    int* pop();
    int* peek();
    void push(int start, int size);
};


void Reverse(int arr[], int start, int end);
int GetMinrun(int n);
void OutputArray(int arr[], int capacity);
void InsertionSort(int arr[], int start, int end);
int min(int first, int second);
int BinarySearch(int array1[], int key, int start, int end);
void merge(int check[], int out1[], int out2[], int result[]);
void TimSort(int check[], int size);