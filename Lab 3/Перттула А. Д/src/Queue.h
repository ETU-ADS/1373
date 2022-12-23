//
// Created by theta-sigma on 11/30/2022.
//

#ifndef SRC_QUEUE_H
#define SRC_QUEUE_H


#include <stdexcept>

#include "LinkedList.h"

// dequeue (снятие со стека),
// enqueue (добавление на стек),
// peakAddress (значение вершины стека без его снятия)

template<typename T>
class Queue {
private:
    LinkedList<T> ar;
public:
    Queue() = default;

    T dequeue() {
        if (ar.size() != 0) {
            T value = ar.get(0);
            ar.remove(0);
            return value;
        } else {
            throw std::out_of_range("queue size = 0");
        }
    }

    void enqueue(const T &value) {
        ar.pushBack( value);
    }

    const T &peak() const {
        if (ar.size() >= 0) {
            return ar.get(0);
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


#endif //SRC_QUEUE_H
