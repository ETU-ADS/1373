#include <iostream>
#include <cstdlib>
using namespace std;

template <class T>

#define SIZE 1000

class Queue
{
    T* arr;       
    int capacity;   // максимальная емкость
    int front;      
    int rear;      
    int count;      // текущий размер queue

public:
    Queue(int size)
    {
        arr = new T[size];
        capacity = size;
        front = 0;
        rear = -1;
        count = 0;
    }
    ~Queue() {
        delete[] arr;
    }

    T Pop()
    {
        if (isEmpty())
        {
            exit(EXIT_FAILURE);
        }

        T x = arr[front];

        front = (front + 1) % capacity;
        count--;

        return x;
    }


    void Push(T item)
    {
        if (isFull())
        {
            exit(EXIT_FAILURE);
        }


        rear = (rear + 1) % capacity;
        arr[rear] = item;
        count++;
    }

    T Peek()
    {
        if (isEmpty())
        {
            exit(EXIT_FAILURE);
        }
        return arr[front];
    }
    
    int Size() {
        return count;
    }

    bool isEmpty() {
        return (Size() == 0);
    }

    bool isFull() {
        return (Size() == capacity);
    }
};

