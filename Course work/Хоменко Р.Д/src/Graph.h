#pragma once
#include <string>

template<typename T>
class DynamicArray
{
    T* arr;
    int size, cap;
public:

    DynamicArray()
    {
        cap = 50;
        size = 0;
        arr = new T[50];
    }

    DynamicArray(int arrCap)
    {
        cap = arrCap;
        size = 0;
        arr = new T[cap];
    }

    ~DynamicArray()
    {
        delete[] arr;
    }

    T out(int index);

    void print();

    bool find(T data);

    void add(int index, T data);

    void addBack(T data);

    void del(int index);

    int getSize();

    void swap(int i, int j);

    void fill(T x);

    T& operator[](int);
};

//////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////

struct Rib
{
    int start;
    int end;
    int w;

};

class Graph
{
    DynamicArray<Rib> ribs;
    DynamicArray<Rib> mst;
    DynamicArray<std::string> vertexs;
    DynamicArray<int> p;
    DynamicArray<int> rank;

    void makeSet(int x);
    int findSet(int x);
    void unionSet(int x, int y);
    void sort();

public:
    bool read(std::string fileName);
    void print();
    void printMST();
    void kraskal();
    void bfs();
    void dfs(int v = 0);
};
