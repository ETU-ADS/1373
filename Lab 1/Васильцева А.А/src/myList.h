#pragma once
#include <iostream>

template <class Type>

class myList {
private:
    int size = 0;
    struct Leaf {
        Type element;
        Leaf* adr = NULL;
    };

    Leaf* next = NULL;
    Leaf* cur = NULL;
    Leaf* list_head = NULL;

public:

    myList() {};
    myList(unsigned int num) {
        for (unsigned int i = 0; i < num; i++) {
            cur = new Leaf;
            cur->adr = next;
            next = cur;
        }
        list_head = cur;
        size = num;
    };

    unsigned int sizeList() {
        return size;
    };

    // get first element
    Type headList() {
        if (size) return list_head->element;
    };

    // get last element
    Type tailList() {
        if (size) {
            cur = list_head;
            for (unsigned int i = 0; i < size - 1; i++) {
                cur = cur->adr;
            }
            return cur->element;
        }
    };

    // get index by value
    int findByValue(Type element) {
        cur = list_head;
        for (int i = 0; i < size; i++) {
            if (cur->element == element) {
                return i;
            }
            cur = cur->adr;
        }
    };

    // add element by index, count from 0
    void addByIndex(unsigned int index, Type element) {
        if (index > size + 1) {
            std::cout << "error";
        }
        else {
            cur = list_head;
            Leaf* newleaf = new Leaf;
            for (unsigned int i = 0; i < index - 1; i++) {
                cur = cur->adr;
            }
            newleaf->adr = cur->adr;
            newleaf->element = element;

            cur->adr = newleaf;

            size++;
        }
    };
  
    // delete eiement by index, count from 0
    void deleteByIndex(unsigned int index) {
        if (index > size) {
            std::cout << "error: out of list \n";
        }
        else {
            cur = list_head;

            if (!index) {
                list_head = cur->adr;
                delete cur;
            }
            else {
                Leaf* pre = NULL;
                for (unsigned int i = 0; i < index; i++) {
                    pre = cur;
                    cur = cur->adr;
                }

                next = cur->adr;
                delete cur;
                pre->adr = next;
            }

            size--;
        }
    };

    void addToTheEnd(Type element) {
        cur = list_head;
        Leaf* newleaf = new Leaf;

        if (size == 0) {
            newleaf->adr = NULL;
            newleaf->element = element;
            list_head = newleaf;
        }
        else {
            for (unsigned int i = 0; i < size - 1; i++) {
                cur = cur->adr;
            }
            newleaf->adr = cur->adr;
            newleaf->element = element;

            cur->adr = newleaf;
        }

        size++;
    };

    void addInTheBegin(Type element) {
        cur = list_head;
        Leaf* newleaf = new Leaf;

        newleaf->adr = cur;
        newleaf->element = element;

        list_head = newleaf;

        size++;
    };

    void deleteHead() {
        cur = list_head;
        list_head = list_head->adr;
        delete cur;
        size--;
    };

    ~myList() {
        for (unsigned int i = 0; i < size; i++) {
            cur = list_head->adr;
            delete list_head;
            list_head = cur;
        }
    };

    // instead of "set"
    Type& operator[](unsigned int index) {
        if (index > size) {
            std::cout << "error: out of list \n";
        }
        else {
            cur = list_head;
            for (int i = 0; i < index; i++) {
                cur = cur->adr;
            }
            return cur->element;
        }
    }
};
