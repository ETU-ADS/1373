#pragma once

#include<iostream>

template <class Type>

class myVector
{
private:
    Type* arrName = NULL;
    Type* newArrName = NULL;
    int capsty = 1;
    int size = 0;

    void newMemory() {

        capsty = int(capsty * 2);
        newArrName = new Type[capsty]; // выдел€ем пам€ть под "расширенный" массив
        
        for (int i = 0; i < size; i++) {
            newArrName[i] = arrName[i];
        }

        delete[] arrName; // удал€ем исходный полный массив
        arrName = newArrName; // прив€зывваем старый указатель к новому массиву
        //delete newArrName; // удал€ем новый указатель
    }

public:

    myVector() {};

    myVector(unsigned int num) {
        arrName = new Type[num];
        size = num;
        capsty = num;
    };

    // add by index ??
    void addByIndex(unsigned int index, Type element) {
        if (size == capsty) {
            newMemory();
        }

        for (unsigned int i = 0; i < size - index; i++) {
            arrName[size - i] = arrName[size - i - 1];
        }
        arrName[index] = element;
        size++;
    };

    // delete by index ??
    void deleteByIndex(unsigned int index) {
        for (unsigned int i = index; i < size - 1; i++) {
            arrName[i] = arrName[i + 1];
        }
        arrName[size - 1] = 0;
        size--;
    };

    // number of elements
    int sizeVector() {
        return size;
    };

    // add element to the end
    void addToTheEnd(Type element) {
        if (size == capsty || size == 0) {
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

template <class Type>
std::ostream& operator << (std::ostream& os, myVector<Type>& p)
{
    return os << p;
}


