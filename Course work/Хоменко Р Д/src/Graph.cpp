#include "Graph.h"
#include <string>
#include <fstream>
#include <iostream>

template<typename T>
T DynamicArray<T>::out(int index)
{
    if ((size - 1) < index)
    {
        std::cout << "There are no this index" << std::endl;
        return -1;
    }
    return arr[index];
}
template<typename T>
void DynamicArray<T>::print()
{
    setlocale(LC_ALL, "Russian");
    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
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
    std::cout << "There are no this element" << std::endl;
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
void DynamicArray<T>::addBack(T data)
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

/////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////


bool Graph::read(std::string fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "ERROR! File is not open!" << std::endl;
        return 1;
    }
    std::string str, buff = "";
    std::getline(file, str);
    for (int i = 0; i < str.size(); ++i)
    {
        buff.append(str, i, str.find_first_of(" ", i) - i);
        vertexs.addBack(buff);
        buff = "";
        i = str.find_first_of(" \n", i);
        if (i == -1)
            break;
    }
    Rib rib;
    for (int j = 0; j < vertexs.getSize() - 1; ++j)
    {
        std::getline(file, str);
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
                ribs.addBack(rib);
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
            ribs.addBack(rib);
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
                std::cout << 0 << " ";
            else
                for (int k = 0; k < ribs.getSize(); ++k)
                {
                    if ((ribs[k].start == i && ribs[k].end == j) || (ribs[k].start == j && ribs[k].end == i))
                    {
                        std::cout << ribs[k].w << " ";
                        break;
                    }
                    else if (k == ribs.getSize() - 1)
                        std::cout << 0 << " ";
                }
        }
        std::cout << std::endl;
    }
}

void Graph::printMST()
{
    int weight = 0;

    for (int i = 0; i < mst.getSize(); ++i)
    {
        std::cout << vertexs[mst[i].start] << " " << vertexs[mst[i].end] << std::endl;
        weight += mst[i].w;
    }
    std::cout << weight << std::endl;
}

void Graph::makeSet(int x)
{
    p.addBack(x);
    rank[x] = 0;
}

int Graph::findSet(int x)
{
    return (x == p[x] ? x : p[x] = findSet(p[x]));
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

void Graph::sort()
{
    Rib key;
    int j;
    for (int i = 1; i < ribs.getSize(); ++i)
    {
        key = ribs[i];
        j = i - 1;
        while (j >= 0 && ribs[j].w > key.w)
        {
            ribs[j + 1] = ribs[j];
            --j;
        }
        ribs[j + 1] = key;
    }
}

void Graph::kraskal()
{
    int first, second;
    sort();
    for (int i = 0; i < vertexs.getSize(); ++i)
        makeSet(i);
    for (int i = 0; mst.getSize() < vertexs.getSize() - 1; ++i)
    {
        first = findSet(ribs[i].start);
        second = findSet(ribs[i].end);
        if (first != second)
        {
            mst.addBack(ribs[i]);
            unionSet(first, second);
        }
    }
    printMST();
}

void Graph::bfs()
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
        std::cout << vertexs[v] << " ";
    }
    std::cout << std::endl;
}

void Graph::dfs(int v)
{
    static DynamicArray<bool> list;
    if (v == 0)
    {
        list.fill(0);
    }
    list[v] = 1;
    std::cout << vertexs[v] << " ";
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