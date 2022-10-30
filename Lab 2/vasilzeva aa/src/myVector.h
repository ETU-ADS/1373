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
       // delete newArrName; // удал€ем новый указатель
    }

public:

    myVector() {};

    myVector(unsigned int num) {
        arrName = new Type[num];
        size = num;
        capsty = num;
    };

    //bool isEmpty() {
    //    if (size = 0) return 1;
    //    else 0;
    //}
    
    // search by value ??
    int findByValue(Type element) {
        for (int i = 0; i < size; i++) {
            if (element == arrName[i]) {
                return i;
            }
        }
    }

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

    // gett link of element
    Type* link(unsigned int index) {
        if (index < size) {
            return arrName + index * sizeof(Type);
        }
        else {
            std::cout << "You out of array" << std::endl;
            return 0;
        }
    };

    ~myVector() {
        delete[]arrName;
    };
};

template <class Type>
std::ostream& operator << (std::ostream& os, myVector<Type>& p)
{
    return os << p;
}


