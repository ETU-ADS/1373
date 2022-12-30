#include "graph.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

template<typename T>
T DynamicArray<T>::out(int index)
{
    if ((size - 1) < index)
    {
        cout << "There are no this index" << endl;
        return -1;
    }
    return arr[index];
}
template<typename T>
void DynamicArray<T>::print()
{
    setlocale(LC_ALL, "Russian");
    for (int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << std::endl;
}
template<typename T>
bool DynamicArray<T>::find(T data)
{
    int index = 0;
    for (int i = 0; i < size; ++i)
    {
        if (arr[i] == data)
            return index;
        ++index;
    }
    cout << "There are no this element" << endl;
    return -1;
}
template<typename T>
void DynamicArray<T>::add(int index, T data)
{
    if (size == cap)
    {
        T* arrBuff = new T[cap];
        for (int i = 0; i < size; ++i)
            arrBuff[i] = arr[i];
        delete[] arr;
        cap *= 2;
        arr = new T[cap];
        for (int i = 0; i < size; ++i)
            arr[i] = arrBuff[i];
        delete[] arrBuff;
    }
    if (index >= size)
        arr[size] = data;
    else if (index < size)
    {
        int c = 0;
        while ((size - c) != index)
        {
            arr[size - c] = arr[size - c - 1];
            ++c;
        }
        arr[index] = data;
    }

    ++size;
}
template<typename T>
void DynamicArray<T>::addEnd(T data)
{
    if (size == cap)
    {
        T* arrBuff = new T[cap];
        for (int i = 0; i < size; ++i)
            arrBuff[i] = arr[i];
        delete[] arr;
        cap *= 2;
        arr = new T[cap];
        for (int i = 0; i < size; ++i)
            arr[i] = arrBuff[i];
        delete[] arrBuff;
    }
    arr[size] = data;
    ++size;
}
template<typename T>
void DynamicArray<T>::del(int index)
{
    if (index == (size - 1))
        --size;
    else if (index < (size - 1))
    {
        for (int i = index; i < (size - 1); ++i)
            arr[i] = arr[i + 1];
    }
    --size;
}
template<typename T>
int DynamicArray<T>::getSize()
{
    return size;
}
template<typename T>
void DynamicArray<T>::swap(int i, int j)
{
    T buff = arr[i];
    arr[i] = arr[j];
    arr[j] = buff;
}
template<typename T>
void DynamicArray<T>::fill(T x)
{
    size = cap;
    for (int i = 0; i < size; ++i)
        arr[i] = x;
}
template<typename T>
T& DynamicArray<T>::operator[](int i)
{
    return arr[i];
}

template<typename T>
void Queue<T>::push(T node)
{
    if (size - 1 == top)
    {
        T* arrBuff = new T[size];
        for (int i = 0; i <= top; ++i)
            arrBuff[i] = arr[i];
        delete[] arr;
        size *= 2;
        arr = new T[size];
        for (int i = 0; i <= top; ++i)
            arr[i] = arrBuff[i];
        delete[] arrBuff;
    }
    for (int i = top + 1; i > 0; --i)
        arr[i] = arr[i - 1];
    arr[0] = node;
    ++top;
}
template<typename T>
T   Queue<T>::pop()
{
    return arr[top--];
}
template<typename T>
bool Queue<T>::empty()
{
    return top == -1;
}


bool Graph::read(string fileName)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        cout << "Error! File is not open!" << endl;
        return 1;
    }
    string str, buff = "";
    getline(file, str);

    for (int i = 0; i < str.size(); ++i)
    {
        buff.append(str, i, str.find_first_of(" ", i) - i);
        vertexs.addEnd(buff);
        buff = "";
        i = str.find_first_of(" \n", i);
        if (i == -1)
            break;
    }
    Rib rib;
    for (int j = 0; j < vertexs.getSize() - 1; ++j)
    {
        getline(file, str);
        int end = 0;

        for (int i = 0; i < str.size(); ++i)
        {
            buff = "";
            buff.append(str, i, str.find_first_of(" ", i) - i);
            i = str.find_first_of(" ", i);

            if (i == -1 && buff != "0")
            {
                rib.start = j;
                rib.end = end++;
                rib.w = stoi(buff);
                ribs.addEnd(rib);
                break;
            }
            else if (i == -1 && buff == "0")
                break;
            if (end <= j || buff == "0")
            {
                ++end;
                continue;
            }

            rib.start = j;
            rib.end = end++;
            rib.w = stoi(buff);
            ribs.addEnd(rib);
        }
    }
    print();
    file.close();
    return 0;
}

void Graph::print()
{
    vertexs.print();
    int size = vertexs.getSize();
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (i == j)
                cout << 0 << " ";
            else
                for (int k = 0; k < ribs.getSize(); ++k)
                {
                    if ((ribs[k].start == i && ribs[k].end == j) || (ribs[k].start == j && ribs[k].end == i))
                    {
                        cout << ribs[k].w << " ";
                        break;
                    }
                    else if (k == ribs.getSize() - 1)
                        cout << 0 << " ";
                }
        }
        cout << endl;
    }
}

//Minimum spanning tree print
void Graph::printMST()
{
    int weight = 0;
    for (int i = 0; i < mst.getSize(); ++i)
    {
        cout << vertexs[mst[i].start] << " " << vertexs[mst[i].end] << endl;
        weight += mst[i].w;
    }

    cout << weight << endl;
}

//Implementation of the system of disjoint sets
void Graph::makeSet(int x)
{
    p.addEnd(x);
    rank[x] = 0;
}
void Graph::unionSet(int x, int y)
{
    if ((x = findSet(x)) == (y = findSet(y)))
        return;
    if (rank[x] < rank[y])
        p[x] = y;
    else {
        p[y] = x;
        if (rank[x] == rank[y])
            ++rank[x];
    }
}
int Graph::findSet(int x)
{
    return (x == p[x] ? x : p[x] = findSet(p[x]));
}


//Sorted by weight
void Graph::sortIns()
{
    Rib root;
    int j;
    for (int i = 1; i < ribs.getSize(); ++i)
    {
        root = ribs[i];
        j = i - 1;
        while (j >= 0 && ribs[j].w > root.w)
        {
            ribs[j + 1] = ribs[j];
            --j;
        }
        ribs[j + 1] = root;
    }
}

//Implementation of Kruskal's algorithm
void Graph::kruskal()
{
    int firstV, secondV;
    sortIns();

    for (int i = 0; i < vertexs.getSize(); ++i)
        makeSet(i);

    for (int i = 0; mst.getSize() < vertexs.getSize() - 1; ++i)
    {
        firstV = findSet(ribs[i].start);
        secondV = findSet(ribs[i].end);

        if (firstV != secondV)
        {
            mst.addEnd(ribs[i]);
            unionSet(firstV, secondV);
        }
    }
    printMST();
}

void Graph::bfs() //Breadth-first search
{
    Queue<int> queue(10);
    DynamicArray<bool> list;
    int v;

    list.fill(0);
    queue.push(0);
    list[0] = 1;
    while (!queue.empty())
    {
        v = queue.pop();
        for (int i = 0; i < ribs.getSize(); ++i)
        {
            if (ribs[i].start == v && list[ribs[i].end] == 0)
            {
                queue.push(ribs[i].end);
                list[ribs[i].end] = 1;
            }
            else if (ribs[i].end == v && list[ribs[i].start] == 0)
            {
                queue.push(ribs[i].start);
                list[ribs[i].start] = 1;
            }
        }
        cout << vertexs[v] << " ";
    }
    cout << endl;
}

void Graph::dfs(int v) //Depth-First Search
{
    static DynamicArray<bool> list;
    if (v == 0)
    {
        list.fill(0);
    }

    list[v] = 1;
    cout << vertexs[v] << " ";

    for (int i = 0; i < ribs.getSize(); ++i)
    {
        if (ribs[i].start == v && list[ribs[i].end] == 0)
        {
            dfs(ribs[i].end);
        }
        else if (ribs[i].end == v && list[ribs[i].start] == 0)
        {
            dfs(ribs[i].start);
        }
    }
}