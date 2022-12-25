//
// Created by theta-sigma on 9/24/2022.
//

#ifndef ALGORITHMS_LAB1_LINKEDLIST_H
#define ALGORITHMS_LAB1_LINKEDLIST_H

template<typename T>
class LinkedList {
private:
    struct Node {
    public:
        explicit Node(const T &data) : data(data), pNext(nullptr) {};

        T data;
        Node *pNext;
    };

    int mSize;
    Node *pHead;

public:
    LinkedList<T>() {
        pHead = nullptr;
        mSize = 0;
    }

    ~LinkedList<T>() {
        Node *cur = pHead;
        for (int i = 0; i < mSize; i++) {
            Node *next = cur->pNext;
            delete cur;
            cur = next;
        }
    }

    // NOT CONST METHODS
    void pushFront(const T &x) {
        Node *pNodeX = new Node(x);
        if (mSize == 0) {
            pHead = pNodeX;
        } else {
            Node *pNext = pHead;
            pHead = pNodeX;
            pNodeX->pNext = pNext;
        }
        mSize++;
    }

    void pushBack(const T &x) {
        Node *pNodeX = new Node(x);
        if (mSize == 0) {
            pHead = pNodeX;
        } else {
            Node *current = pHead;
            for (int i = 0; i < mSize - 1; i++) {
                current = current->pNext;
            }
            current->pNext = pNodeX;
        }
        mSize++;
    }

    void insert(int index, const T &x) { // 0 <= index <= mSize
        if (index == 0) {
            this->pushFront(x);
        } else if (0 < index && index <= mSize) {
            Node *pNodeX = new Node(x);
            Node *current = pHead;
            for (int i = 0; i < index - 1; i++) {
                current = current->pNext;
            }
            if (index < mSize) { // in the middle
                Node *pNext = current->pNext;
                current->pNext = pNodeX;
                pNodeX->pNext = pNext;
            } else if (index == mSize) {
                current->pNext = pNodeX;
            } else {
                throw std::out_of_range("LINKED LIST INSERT: OUT_OF_RANGE EXCEPTION");
            }
        }

        mSize++;
    }

    void remove(int index) {
        if (index == 0) {
            Node *xxx = pHead->pNext;
            delete pHead;
            pHead = xxx;
        } else if (0 < index && index < mSize) {
            Node *current = pHead;
            for (int i = 0; i < index - 1; i++) {
                current = current->pNext;
            }

            Node *xxx = current->pNext;
            current->pNext = current->pNext->pNext;
            delete xxx;
        } else {
            throw std::out_of_range("LINKED LIST REMOVE: OUT_OF_RANGE EXCEPTION");
        }

        mSize--;
    }

    // CONST METHODS
    const T &get(int index) const {
        Node *current = pHead;
        for (int i = 0; i < index; i++) {
            current = current->pNext;
        }
        return current->data;
    }

    const T *getElementAddress(int index) const {
        Node *current = pHead;
        for (int i = 0; i < index; i++) {
            current = current->pNext;
        }
        return &(current->data);
    }

    int find(const T &x) const {
        Node *current = pHead;
        for (int i = 0; current != nullptr; i++) {
            if (current->data == x) {
                return i;
            }
            current = current->pNext;
        }
        return -1;
    }

    int size() const {
        return mSize;
    }
};

#endif //ALGORITHMS_LAB1_LINKEDLIST_H
