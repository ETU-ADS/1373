#pragma once
#include <iostream>
template <typename type>
class DynamicArray {
private:
    bool isDebug = false;
    unsigned int size = 0;
    unsigned int capacity = 4;
    unsigned int magnifFactor = 2;
    type* arr = new type[capacity];

    // function to raise capacity by magnifFactor +
    bool raiseCapacity() {
        type* newArr = new type[capacity * magnifFactor];
        capacity *= magnifFactor;
        for (unsigned int i = 0; i < size; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        return true;
    }
public:
    // adds an element by index, returns true if capacity raised +
    bool add(int index, type newData){
        bool isRaised = false;
        if (size == capacity) {
            isRaised = raiseCapacity();
        }

        if (index == size) {
            arr[index] = newData;
        }
        else if (index < size) {
            for (int i = size - 1; i >= index; --i) {
                arr[i + 1] = arr[i];
            }
            arr[index] = newData;
        }
        else if (index > size) {
            throw "Index out of bounds! Function: add()";
        }
        ++size;
        return isRaised;
    }
    // adds an element at the end, returns true if capacity raised +
    bool add(type newData){
        bool isRaised = false;
        if (size == capacity) {
            isRaised = raiseCapacity();
        }
        arr[size] = newData;
        ++size;
        return isRaised;
    }
    // looking for a data in dinamic array, returns index of element, -1 if not found +
    int find(type dataToFind){
        for (int i = 0; i < size; ++i) {
            if (arr[i] == dataToFind) {
                return i;
            }
        }
        return -1;
    }
    // delete element by its index with moving other elements to free space +
    void deleteElem(unsigned int index){
        if (index < size) {
            type* newArr = new type[capacity];
            for (int i = 0; i < size - 1; ++i) {
                if (i < index) {
                    newArr[i] = arr[i];
                }
                else {
                    newArr[i] = arr[i + 1];
                }
            }
            delete[] arr;
            arr = newArr;
            --size;
        }
        else throw "Index out of bounds! Function: deleteElem()";
    }
    // returns current length of array +
    unsigned int length(){
        return size;
    }
    // returns capacity of array +
    unsigned int getCapacity(){
        return capacity;
    }
    // clears array with deleting all elements +
    void clear(){
        type* newArr = new type[capacity];
        delete[] arr;
        arr = newArr;
        size = 0;
    }
    // merges with other array +
    void merge(DynamicArray<type> *otherArr){
        while (size + otherArr->size > capacity) {
            raiseCapacity();
        }
        for (int i = size; i < size + otherArr->size; ++i) {
            arr[i] = otherArr->arr[i - size];
        }
        size += otherArr->size;
    }
    // shrinks capacity to the real size of array +
    void shrink(){
        type* newArr = new type[size];
        for (int i = 0; i < size; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = size;
    }
    // resizes array with user's capacity, returns true if no data loss +
    bool resize(unsigned int newCapacity){
        if (size <= newCapacity) {
            type* newArr = new type[newCapacity];
            for (int i = 0; i < size; ++i) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
            capacity = newCapacity;
            return true;
        }
        else {
            type* newArr = new type[newCapacity];
            for (int i = 0; i < newCapacity; ++i) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
            size = newCapacity;
            capacity = newCapacity;
            return false;
        }
    }
    // swaps two elements by their indexes +
    void swap(unsigned int index1, unsigned int index2){
        if (index1 < size && index2 < size) {
            type temp = arr[index1];
            arr[index1] = arr[index2];
            arr[index2] = temp;
        }
        else throw "Index out of bounds! Function: swap()";
    }
    // get element by index
    type operator[] (unsigned int index){
        return arr[index];
    }
    // destructor
    ~DynamicArray(){
        delete[] arr;
        if (isDebug) {
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "DEBUG DynamicArray: Memory cleared";
            std::cout << std::endl;
            std::cout << std::endl;
        }
    }
};