#include <iostream>
#include <string>
#include <fstream>
#include "Kruskal.h"

template<typename T>
T DynamicArray<T>::out(int index)
{
    if ((size - 1) < index)
    {
        std::cout << "Ошибка! Такого индекса нет." << std::endl;
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
    std::cout << "Ошибка! Этого элемента здесь нет." << std::endl;
    return -1;
}

template<typename T>
void DynamicArray<T>::add(int index, T data)
{
    if (size == capacity)
    {
        T* arrBuff = new T[capacity];
        for (int i = 0; i < size; ++i)
            arrBuff[i] = arr[i];
        delete[] arr;
        capacity *= 2;
        arr = new T[capacity];
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
void DynamicArray<T>::addMoreElements(T data)
{
    if (size == capacity)
    {
        T* arrIntermed = new T[capacity];
        for (int i = 0; i < size; ++i)
            arrIntermed[i] = arr[i];
        delete[] arr;
        capacity *= 2;
        arr = new T[capacity];
        for (int i = 0; i < size; ++i)
            arr[i] = arrIntermed[i];
        delete[] arrIntermed;
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
int DynamicArray<T>::sizeArr() 
{
    return size;
}

template<typename T>
void DynamicArray<T>::swap(int i, int j)
{
    T intermed = arr[i];
    arr[i] = arr[j];
    arr[j] = intermed;
}

template<typename T>
void DynamicArray<T>::fillArray(T x)
{
    size = capacity;
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
        T* arrIntermed = new T[size];
        for (int i = 0; i <= top; ++i)
            arrIntermed[i] = arr[i];
        delete[] arr;
        size *= 2;
        arr = new T[size];
        for (int i = 0; i <= top; ++i)
            arr[i] = arrIntermed[i];
        delete[] arrIntermed;
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


bool Graph::read(std::string fileName) 
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Ошибка! Такого файла не существует." << std::endl;
        return 1;
    }

    std::string str, intermed = "";
    std::getline(file, str);
    for (int i = 0; i < str.size(); ++i)
    {
        while (i < str.size() && str[i] != ' ')
        {
            intermed = intermed + str[i];
            i = i + 1;
        }
        vertexs.addMoreElements(intermed);
        intermed = "";
        if (i == -1)
            break;
    }
    Edges edge;
    for (int j = 0; j < vertexs.sizeArr() - 1; ++j)
    {
        std::getline(file, str);
        int end = 0;

        for (int i = 0; i < str.size(); ++i)
        {
            intermed = "";
            while (i < str.size() && str[i] != ' ')
            {
                intermed = str[i];
                i = i + 1;
            }
            i = str.find_first_of(" ", i);

            if (i == -1 && intermed != "0")
            {
                edge.vertex1 = j;
                edge.vertex2 = end++;
                edge.weight = stoi(intermed);
                edges.addMoreElements(edge);
                break;
            }
            else if (i == -1 && intermed == "0")
                break;
            if (end <= j || intermed == "0")
            {
                ++end;
                continue;
            }

            edge.vertex1 = j;
            edge.vertex2 = end++;
            edge.weight = stoi(intermed);
            edges.addMoreElements(edge);
        }
    }
    file.close();
    return 0;
}

void Graph::insertionSort()
{
    Edges key;
    int j;
    for (int i = 1; i < edges.sizeArr(); ++i)
    {
        key = edges[i];
        j = i - 1;
        while (j >= 0 && edges[j].weight > key.weight)
        {
            edges[j + 1] = edges[j];
            --j;
        }
        edges[j + 1] = key;
    }
}

void Graph::BFS()
{
    Queue<int> queue(10);
    DynamicArray<int> color;
    int indexVertex; 
    color.fillArray(0); 
    queue.push(0); 
    while (!queue.empty()) 
    {
        indexVertex = queue.pop(); 
        color[0] = 1; 
        for (int i = 0; i < edges.sizeArr(); ++i)
        {
            if (edges[i].vertex1 == indexVertex && color[edges[i].vertex2] == 0) 
            {
                queue.push(edges[i].vertex2); 
                color[edges[i].vertex2] = 1;  
            }
            else if (edges[i].vertex2 == indexVertex && color[edges[i].vertex1] == 0)
            {
                queue.push(edges[i].vertex1);
                color[edges[i].vertex1] = 1;
            }
        }
        std::cout << vertexs[indexVertex] << " ";
    }
    std::cout << std::endl;
}

void Graph::DFS(int indexVertex)
{
    static DynamicArray<int> color; 
    if (indexVertex == 0) 
    {
        color.fillArray(0);
    }
    color[indexVertex] = 1; 
    std::cout << vertexs[indexVertex] << " ";
    for (int i = 0; i < edges.sizeArr(); ++i)
    {
        if (edges[i].vertex1 == indexVertex && color[edges[i].vertex2] == 0)
        {
            DFS(edges[i].vertex2);
        }
        else if (edges[i].vertex2 == indexVertex && color[edges[i].vertex1] == 0)
        {
            DFS(edges[i].vertex1);
        }
    }
}

void Graph::make_set(int a)
{
    parent.addMoreElements(a); 
    sizeUnderTree[a] = 1;
}

int Graph::find_set(int a)
{
    return (a == parent[a] ? a : parent[a] = find_set(parent[a]));
}

void swapSize(int* a, int* b) 
{
    a = b;
    b = a;
}

void Graph::union_set(int a, int b)
{
    a = find_set(a), b = find_set(b);
    if (parent[a] > sizeUnderTree[b])
        swapSize(&a, &b);
    sizeUnderTree[b] += sizeUnderTree[a];
    parent[a] = b;
}

void Graph::MST()
{
    int weight = 0;
    for (int i = 0; i < mst.sizeArr(); ++i)
    {
        std::cout << vertexs[mst[i].vertex1] << " - " << vertexs[mst[i].vertex2] << std::endl ;
        weight += mst[i].weight;
    }
    std::cout << "\n" << "Вес минимального остовного дерева: " << weight << std::endl;
}

void Graph::algorithmKruskal()
{
    int i = 0;
    int parent1, parent2;
    insertionSort();
    
    while (i < vertexs.sizeArr())
    {
        make_set(i);
        i += 1;
    }
    
    for (int i = 0; mst.sizeArr() < (vertexs.sizeArr() - 1); ++i)
    {
        parent1 = find_set(edges[i].vertex1);
        parent2 = find_set(edges[i].vertex2);
        if (parent1 != parent2)
        {
            mst.addMoreElements(edges[i]);
            union_set(parent1, parent2);
        }
    }
    
    MST();
}

