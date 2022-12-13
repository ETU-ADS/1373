#pragma once
#include <iostream>

using namespace std;

template <typename T>
class MyVector {
public:
    T* data = nullptr;
    int size = 0;
    int capacity = 0;
    MyVector() {
        data = nullptr;
        size = 0;
        capacity = 0;
    }
    MyVector(int newsize) {
        size = newsize;
        capacity = size * 2;
        data = new T[capacity];
    }
    ~MyVector() {
        if (size != 0) {
            delete_vec();
        }
    }
    void operator=(MyVector& vec) {
        delete_vec();
        for (int i = 0; i < vec.size; i++) {
            push_back(vec[i]);
        }
    }
    void push_back(T val) {
        if (size == 0) {
            size = 1;
            capacity = size * 2;
            data = new T[capacity];
            data[0] = val;
        }
        else {
            if (size < capacity) {
                data[size] = val;
                size++;
            }
            else {
                capacity = size * 2;
                T* tmp = data;
                data = new T[capacity];
                for (int i = 0; i < size; i++) {
                    data[i] = tmp[i];
                }
                data[size] = val;
                size++;
                delete[] tmp;
            }
        }
    }
    void delete_vec() {
        if (size != 0) {
            delete[] data;
            size = 0;
        }
    }
    void add(int num, int val) {
        if (num < size) {
            if (size < capacity) {
                T* tmp = data;
                data = new T[capacity];
                for (int i = 0; i < num; i++) {
                    data[i] = tmp[i];
                }
                data[num] = val;
                size++;
                for (int i = num + 1; i < size; i++) {
                    data[i] = tmp[i - 1];
                }
                delete[] tmp;
            }
            else {
                capacity = size * 2;
                T* tmp = data;
                data = new T[capacity];
                for (int i = 0; i < num; i++) {
                    data[i] = tmp[i];
                }
                data[num] = val;
                size++;
                for (int i = num + 1; i < size; i++) {
                    data[i] = tmp[i - 1];
                }
                delete[] tmp;
            }
        }
        else if (num == size) {
            push_back(val);
        }
        else { cout << "Error! Out of the vector" << endl; }
    }
    void delete_a(int num) {
        if (num < size) {
            T* tmp = data;
            data = new T[capacity];
            for (int i = 0; i < num; i++) {
                data[i] = tmp[i];
            }
            for (int i = num + 1; i < size; i++) {
                data[i - 1] = tmp[i];
            }
            size--;
            delete[] tmp;
        }
        else { cout << "Error! Out of the vector" << endl; }
    }
    T* get_reference(int num) {
        if (num < size) {
            return (data + num);
        }
        else {
            cout << "Error! Out of the vector" << endl;
            return nullptr;
        }
    }
    int get_size() {
        return size;
    }
    void print_data() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
    int find(int val) {
        int count = 0;
        while ((count < size) && (val != data[count])) {
            count++;
        }
        if (count == size) {
            cout << "Error! The element not found" << endl;
            count = -1;
        }
        return count;
    }
    T& operator[](int num) {
        if (num >= size) {
            cout << "Error! Out of the vector" << endl;
            exit(0);
        }
        return data[num];
    }
};