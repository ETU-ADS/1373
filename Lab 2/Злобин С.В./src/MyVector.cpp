#include "MyVector.h"
#include <iostream>

using namespace std;

MyVector::MyVector() {
        data = nullptr;
        size = 0;
        capacity = 0;
    }
MyVector::MyVector(int newsize) {
        size = newsize;
        capacity = size * 2;
        data = new int[capacity];
    }
MyVector::MyVector(const MyVector& other) {
    data = new int[other.capacity];
    size = other.size;
    capacity = other.capacity;
    for (int i = 0; i < other.size; i++) {
        data[i] = other.data[i];
    }
}
MyVector::~MyVector() {
        delete[] data;
    }
    void MyVector::push_back(int val) {
        if (size == 0) {
            size = 1;
            capacity = size * 2;
            data = new int[capacity];
            data[0] = val;
        }
        else {
            if (size < capacity) {
                data[size] = val;
                size++;
            }
            else {
                capacity = size * 2;
                int* tmp = data;
                data = new int[capacity];
                for (int i = 0; i < size; i++) {
                    data[i] = tmp[i];
                }
                data[size] = val;
                size++;
                delete[] tmp;
            }
        }
    }
    void MyVector::add(int num, int val) {
        if (num < size) {
            if (size < capacity) {
                int* tmp = data;
                data = new int[capacity];
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
                int* tmp = data;
                data = new int[capacity];
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
    void MyVector::delete_a(int num) {
        if (num < size) {
            int* tmp = data;
            data = new int[capacity];
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
    int* MyVector::get_reference(int num) {
        if (num < size) {
            return (data + num);
        }
        else {
            cout << "Error! Out of the vector" << endl;
            return nullptr;
        }
    }
    int MyVector::get_size() {
        return size;
    }
    void MyVector::print_data() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << "  ";
        }
        cout << endl;
    }
    int MyVector::find(int val) {
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
    int& MyVector::operator[](int num) {
        if (num >= size) {
            cout << "Error! Out of the vector" << endl;
            exit(0);
        }
        return data[num];
    }
    void MyVector::swap(int a, int b) {
        if ((a < size) && (b < size)) {
            int tmp;
            tmp = data[a];
            data[a] = data[b];
            data[b] = tmp;
        }
        else cout << "Error! Out of the vector" << endl;
    }
    void MyVector::operator=(const MyVector& other) {
        data = new int[other.capacity];
        size = other.size;
        capacity = other.capacity;
        for (int i = 0; i < other.size; i++) {
            data[i] = other.data[i];
        }
    }