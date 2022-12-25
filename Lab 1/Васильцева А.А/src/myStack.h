#pragma once
#include <iostream>

template <class Type>

class myStack {
private:
    int size = 0;
    struct Plate {
        Type element;
        Plate* adr = NULL;
    };

    Plate* next = NULL;
    Plate* cur = NULL;
    Plate* stack_head = NULL;

public:

    bool isEmpty() {
        if (size) return false;
        else return true;
    }

    // size of stack
    unsigned int sizeStack() {
        return size;
    };

    // get first element
    Type peak() {
        if (size) return stack_head->element;
    };

    // delete head-element
    void pop() {
        if (size) {
            cur = stack_head;

            stack_head = cur->adr;
            delete cur;

            size--;
        }
    };

    // add head-element
    void push(Type element) {
        cur = stack_head;
        Plate* newPlate = new Plate;

        newPlate->adr = cur;
        newPlate->element = element;

        stack_head = newPlate;

        size++;
    };

    ~myStack() {
        for (unsigned int i = 0; i < size; i++) {
            cur = stack_head->adr;
            delete stack_head;
            stack_head = cur;
        }
    };

};
