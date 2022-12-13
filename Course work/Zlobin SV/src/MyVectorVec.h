#pragma once
#include <iostream>
#include "MyVector.h"

using namespace std;

template <typename T>
class MyVectorVec {
public:
    MyVector<T>* data;
    int size;
    int capacity;
    MyVectorVec() {
        data = nullptr;
        size = 0;
        capacity = 0;
    }
    MyVectorVec(int newsize) {
        size = newsize;
        capacity = size * 2;
        data = new MyVector<T>[capacity];
    }
    ~MyVectorVec() {
        delete_vec();
    }
    void delete_vec() {
        for (int i = 0; i < size; i++) {
            data[i].delete_vec();
        }
        delete[] data;
    }
    void push_back() {
        if (size == 0) {
            size = 1;
            capacity = size * 4;
            data = new MyVector<T>[capacity];
        }
        else {
            if (size < capacity) {
                size++;
            }
            else {
                capacity = size * 2;
                MyVector<T>* tmp = data;
                data = new MyVector<T>[capacity];
                for (int i = 0; i < size; i++) {
                    data[i] = tmp[i];
                }
                size++;
                delete[] tmp;
            }
        }
    }
    void sort() {
        int j;
        for (int i = 1; i < size; i++) {
            j = i - 1;
            while ((j >= 0) && (data[j][2] > data[j + 1][2])) {
                MyVector<T> tmp;
                tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
                j--;
            }
        }
    }
    int get_size() {
        return size;
    }
    void print_data() {
        for (int i = 0; i < size; i++) {
            data[i].print_data();
        }
    }
    MyVector<T>& operator[](int num) {
        if (num >= size) {
            cout << "Error! Out of the vector" << endl;
            exit(0);
        }
        return data[num];
    }
};