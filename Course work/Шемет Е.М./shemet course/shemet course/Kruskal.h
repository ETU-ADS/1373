#pragma once
#include <string>

template<typename T>
class DynamicArray
{
    T* arr;
    int size, capacity;
public:

    DynamicArray()
    {
        capacity = 50;
        size = 0;
        arr = new T[50];
    }

    DynamicArray(int arrCap)
    {
        capacity = arrCap;
        size = 0;
        arr = new T[capacity];
    }

    ~DynamicArray()
    {
        delete[] arr;
    }

    T out(int index);

    void print();

    bool find(T data);

    void add(int index, T data);

    void addMoreElements(T data);

    void del(int index);

    int sizeArr();

    void swap(int i, int j);

    void fillArray(T x);

    T& operator[](int);
};


template<typename T>
class Queue
{
    T* arr;
    int top, size;
public:
    Queue(int sizeQ)
    {
        arr = new T[sizeQ];
        top = -1;
        size = sizeQ;
    }
    ~Queue()
    {
        delete[] arr;
    }
    void push(T node);
    T pop();
    bool empty();
};



struct Edges
{
    int vertex1;
    int vertex2;
    int weight;

};

class Graph
{
    DynamicArray<std::string> vertexs;
    DynamicArray<Edges> edges;
    DynamicArray<Edges> mst;
    DynamicArray<int> parent; // хранит раскраску
    DynamicArray<int> sizeUnderTree;

public:

    void insertionSort();
    void make_set(int x);
    int find_set(int x);
    void union_set(int x, int y);
    
    bool read(std::string fileName);
    void print();
    void BFS();
    void DFS(int v = 0);
    void MST();
    void algorithmKruskal();
};