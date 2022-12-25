#pragma once
#include <iostream>

template <class Type>

class myVector
{
private:
    Type* arrName = NULL;
    int capcty = 0;
    int size = 0;

    void newMemory() {
        capcty = int(size * 1.41); // remember new capacity
        Type* newArrName = new Type[capcty]; // memory for new array
         

        for (int i = 0; i < size; i++) {
            newArrName[i] = arrName[i];
        }

        delete[] arrName; // delete old arr
        arrName = newArrName; // old ptr to new
        delete newArrName; // delete new ptr arr
    }

public:

    myVector() {};

    myVector(unsigned int num) {
        arrName = new Type[int(num * 1.41)];
        size = num;
        capcty = int(num * 1.41);
    };

    // search by value
    int findByValue(Type element) {
        for (int i = 0; i < size; i++) {
            if (element == arrName[i]) {
                return i;
            }
        }
    }

    // add by index
    void addByIndex(unsigned int index, Type element) {
        if (size == capcty) {
            newMemory();
        }

        for (unsigned int i = 0; i < size - index; i++) {
            arrName[size - i] = arrName[size - i - 1];
        }
        arrName[index] = element;
        size++;
    };

    // delete by index
    void deleteByIndex(unsigned int index) {
        for (unsigned int i = index; i < size - 1; i++) {
            arrName[i] = arrName[i + 1];
        }
        arrName[size - 1] = 0;
        size--;
    };

    // array out with \n
    void out() {
        for (unsigned int i = 0; i < size; i++) {
            std::cout << arrName[i] << ' ';
        }
        std::cout << '\n';
    };

    // number of elements
    int sizeVector() {
        return size;
    };

    // add element to the end
    void addToTheEnd(Type element) {
        if (size == capcty) {
            newMemory();
        }

        arrName[size] = element;
        size++;
    };

    // get by index
    Type& operator[](unsigned int index) {
        return arrName[index];
    }

    ~myVector() {
        delete[]arrName;
    };
};
