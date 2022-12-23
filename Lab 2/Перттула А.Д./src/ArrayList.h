//
// Created by theta-sigma on 9/25/2022.
//

#ifndef ALGORITHMS_LAB1_ARRAYLIST_H
#define ALGORITHMS_LAB1_ARRAYLIST_H

#include <exception>

template<typename T>
class ArrayList {
private:
    T *mArray;
    int mCapacity;
    int mSize;

    const int defaultCapacity = 3;

    void extend() {
        T *xxx = new T[mCapacity *= 2];
        for (int i = 0; i < mSize; i++) {
            xxx[i] = mArray[i];
        }

        delete[] mArray;
        mArray = xxx;
    }

    bool isCorrectIndex(int index) const {
        return (0 <= index && index < mSize);
    }

public:
    ArrayList() {
        mCapacity = defaultCapacity;
        mArray = new T[mCapacity];
        mSize = 0;
    }

    ~ArrayList() {
        delete[] mArray;
    }

    void append(const T &x) {
        if (mSize == mCapacity) {
            this->extend();
        }

        mArray[mSize] = x;
        mSize++;
    }

    void set(int index, const T &x) { // существующий, до этого когда-то был вызван метод append
        if (isCorrectIndex(index)) {
            mArray[index] = x;
            return mArray[index];
        } else {
            throw std::out_of_range("ArrayList<T> SET: OUT_OF_RANGE EXCEPTION");
        }
    }

    void insert(int index, const T &x) {
        if (isCorrectIndex(index) || index == mSize) {
            if (mSize == mCapacity) {
                this->extend();
            }

            for (int i = mSize; i > index; i--) {
                mArray[i] = mArray[i - 1];
            }

            mArray[index] = x;
            mSize++;
        } else {
            throw std::out_of_range("ArrayList<T> INSERT: OUT_OF_RANGE EXCEPTION");
        }
    }

    void remove(int index) {
        if (isCorrectIndex(index)) {
            for (int i = index; i < mSize - 1; i++) {
                mArray[i] = mArray[i + 1];
            }
            mSize--;
        } else {
            throw std::out_of_range("ArrayList<T> REMOVE: OUT_OF_RANGE EXCEPTION");
        }
    }

    void makeEmpty() {
        delete[] mArray;
        mCapacity = defaultCapacity;
        mSize = 0;

        mArray = new T[mCapacity];
    }

    // CONST METHODS

    const T &get(int index) const { // существующий, до этого когда-то был вызван метод append
        if (isCorrectIndex(index)) {
            return mArray[index];
        } else {
            throw std::out_of_range("ArrayList<T> GET: OUT_OF_RANGE EXCEPTION");
        }
    }

    int find(const T &x) const {
        for (int i = 0; i < mSize; i++) {
            if (mArray[i] == x) {
                return i;
            }
        }
        return -1;
    }

    int size() const {
        return mSize;
    }

    bool isEmpty() const {
        return mSize == 0;
    }
};


#endif //ALGORITHMS_LAB1_ARRAYLIST_H
