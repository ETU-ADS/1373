//
// Created by theta-sigma on 9/26/2022.
//

#ifndef ALGORITHMS_LAB1_STACK_H
#define ALGORITHMS_LAB1_STACK_H

#include "ArrayList.h"

// dequeue (снятие со стека),
// enqueue (добавление на стек),
// peakAddress (значение вершины стека без его снятия)

template<typename T>
class Stack {
private:
    ArrayList<T> ar;
public:
    Stack() = default;

    T pop() {
        if (ar.size() != 0) {
            int lastIndex = ar.size() - 1;
            T value = ar.get(lastIndex);
            ar.remove(lastIndex);
            return value;
        } else {
            throw std::out_of_range("stack size = 0");
        }
    }

    void push(const T &value) {
        int index = ar.size();
        ar.insert(index, value);
    }

    const T &peak() const {
        if (ar.size() >= 0) {
            int lastIndex = ar.size() - 1;
            return ar.get(lastIndex);
        } else {
            throw std::out_of_range("stack size = 0");
        }
    }

    bool isEmpty() const {
        return ar.size() == 0;
    }

    void makeEmpty() {
        ar.makeEmpty();
    }
};


#endif //ALGORITHMS_LAB1_STACK_H
