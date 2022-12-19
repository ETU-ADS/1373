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

    int defaultCapacity = 3;

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
        mArray = new T[defaultCapacity];
        mSize = 0;
    }

    explicit ArrayList(int n) {
        mCapacity = n + defaultCapacity;
        mArray = new T[n];
        mSize = n;
    }

    ArrayList &operator=(const ArrayList<T> &other) {
        // Guard self assignment
        if (this == &other)
            return *this;

        // assume *this manages a reusable resource, such as a heap-allocated buffer mArray
        if (mSize != other.mSize)           // resource in *this cannot be reused
        {
            delete[] mArray;              // release resource in *this
            mCapacity = other.mCapacity;
            mArray = new T[other.mCapacity]; // allocate resource in *this
            mSize = other.mSize;
        }

        for (int i = 0; i < mSize; i++) {
            mArray[i] = other.mArray[i];
        }
        return *this;
    }

    ArrayList(const ArrayList<T> &other) {
        if (this == &other) {
            return;
        }

        mCapacity = other.mCapacity;
        mSize = other.mSize;

        mArray = new T[mCapacity];

        for (int i = 0; i < mSize; i++) {
            mArray[i] = other.mArray[i];
        }
    }

    ~ArrayList() {
        delete[] mArray;
    }

    void sort() {
        if (mArray != nullptr) {
            timsort(mArray, mSize);
        }
    }

    void append(const T &x) {
        if (mArray != nullptr) {
            if (mSize == mCapacity) {
                this->extend();
            }

            mArray[mSize] = x;
            mSize++;
        } else {
            mCapacity = defaultCapacity;
            mArray = new T[mCapacity];
            mArray[0] = x;
            mSize++;
        }
    }

    void set(int index, const T &x) { // существующий, до этого когда-то был вызван метод append
        if (mArray != nullptr) {
            if (isCorrectIndex(index)) {
                mArray[index] = x;
                return mArray[index];
            } else {
                throw std::out_of_range("ArrayList<T> SET: OUT_OF_RANGE EXCEPTION");
            }
        }
    }

    void insert(int index, const T &x) {
        if (mArray != nullptr) {
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
    }

    void remove(int index) {
        if (mArray != nullptr) {
            if (isCorrectIndex(index)) {
                for (int i = index; i < mSize - 1; i++) {
                    mArray[i] = mArray[i + 1];
                }
                mSize--;

                if (mSize == 0) {
                    //
                }
            } else {
                throw std::out_of_range("ArrayList<T> REMOVE: OUT_OF_RANGE EXCEPTION");
            }
        }
    }

    void makeEmpty() {
        delete[] mArray;
        mCapacity = defaultCapacity;
        mSize = 0;

        mArray = new T[defaultCapacity];
    }

    // CONST METHODS

    const T &get(int index) const { // существующий, до этого когда-то был вызван метод append
        if (mArray != nullptr) {
            if (isCorrectIndex(index)) {
                return mArray[index];
            } else {
                throw std::out_of_range("ArrayList<T> GET: OUT_OF_RANGE EXCEPTION");
            }
        }
    }

    int find(const T &x) const {
        if (mArray != nullptr) {
            for (int i = 0; i < mSize; i++) {
                if (mArray[i] == x) {
                    return i;
                }
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

    T &operator[](int i) {
        if (mArray != nullptr) {
            if (i > mSize || i < 0) {
                std::cerr << "Index out of bounds\n";
                // return first element.
                exit(0);
            }

            return mArray[i];
        }
        exit(0);
    }

};


#endif //ALGORITHMS_LAB1_ARRAYLIST_H
