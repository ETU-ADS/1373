#include<fstream>
#include <string>
#include <Windows.h>
#include <iostream>
#include "Graph.h"
using namespace std;

template<typename T>
void ArrayList<T>::addData(T data) // Запись значения в массив
{
    if (lastFilledPart < arraySize - 1)
    {
        lastFilledPart++;
        arr[lastFilledPart] = data;
    }
    else
    {
        sizeExpantion();
        lastFilledPart++;
        arr[lastFilledPart] = data;
    }
}
template<typename T>

int ArrayList<T>::getSize() // Получение размера заполненной части массива
{
    return(lastFilledPart + 1);
}

template<typename T>
T* ArrayList<T>::getItem(unsigned Index) // Обращение к элементу по его индексу
{
    if (Index >= 0 && Index <= lastFilledPart)
    {
        return(&arr[Index]);
    }
    else
    {
        std::cout << "\nThis array item is missing. Try again\n";
        return nullptr;
    }
}

template<typename T>
void ArrayList<T>::addDataForIndex(unsigned Index, T data) // Запись значения по индексу
{
    if (Index >= 0 && Index <= lastFilledPart)
    {
        arr[Index] = data;
    }
    else
    {
        cout << "Error. There isn't element with this index in our array";
    }
}

template<typename T>
void ArrayList<T>::fillEntireArray(T data) // Заполнение всех элементов массива указанными одинаковыми данными
{
    for (int i = 0; i < arraySize; i++)
    {
        addData(data);
    }
}

template<typename T>
void ArrayList<T>::deleteItem(unsigned Index) // Удаление значения элемента по индексу
{
    if (Index >= 0 && Index <= arraySize)
    {
        if (Index == 0)
        {
            for (int i = 1; i <= lastFilledPart; i++)
            {
                arr[i - 1] = arr[i];
            }
            lastFilledPart--;
        }
        else
        {
            for (int i = Index; i < lastFilledPart; i++)
            {
                arr[i - 1] = arr[i];
            }
            lastFilledPart--;
        }
    }
    else
    {
        std::cout << "\nThis array item is missing. Try again\n";
    }
}

template<typename T>
unsigned ArrayList<T>::IndexforData(T data) // Получение индекса по значению элемента
{
    unsigned Index = 0;
    bool isDataExists = 0;
    for (int i = 0; i < arraySize; i++)
    {
        if (arr[i] == data)
        {
            isDataExists = 1;
            break;
        }
        Index++;
    }
    if (isDataExists == 0)
        std::cout << "\nThere is no array element with such data\n";
    else
        return Index;
}

template<typename T>
T& ArrayList<T>::operator[](int i) // Оператор взятия элемента массива по его индексу
{
    return arr[i];
}

template<typename T>
void ArrayList<T>::sizeExpantion() //Функция автоматического расширения массива при его переполнении
{
    T* newArr = new T[arraySize * 2];
    for (int i = 0; i < arraySize; i++)
    {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    arraySize = arraySize * 2;
}


void Graph::MakeSet(int x) // Функция создания нового подмножества для элемента
{
    sets[x] = x;
    rank[x] = 0;
}

int Graph::Find(int x) // Функция, возвращающая подмножество, к которому принадлежит элемент
{
    return (x == sets[x] ? x : sets[x] = Find(sets[x]));
}

void Graph::Union(int x, int y) // Функция, объединяющая два подмножества в одно
{
    if ((x = Find(x)) == (y = Find(y)))
        return;

    if (rank[x] < rank[y])
        sets[x] = y;
    else {
        sets[y] = x;
        if (rank[x] == rank[y])
            ++rank[x];
    }
}

bool Graph::readDataFromFile(string fileName) // Функция считывания данных из файла
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string buffer = "", str;
    fstream file;
    file.open(fileName);
    if (file.is_open() != true)
    {
        cout << "Error. File wasn't opened" << endl;
        return 0;
    }
    Edge bufferEdge;
    getline(file, str);
    for (int i = 0; i < str.size(); i++)
    {
        buffer = "";
        while (str[i] != ' ' && i < str.size())
        {
            buffer = buffer + str[i];
            i++;
        }
        vertexesNames.addData(buffer);
    }
    int countOfVertexes = vertexesNames.getSize();
    for (int i = 0; i < countOfVertexes; i++)
    {
        int endOfEdge = -1; // Здесь будем фиксировать номер вершины, нахоодящейся в конце ребра
        getline(file, str);
        for (int j = 0; j < str.size(); j++)
        {
            buffer = "";
            while (str[j] != ' ' && j < str.size())
            {
                buffer = buffer + str[j];
                j++;
            }
            if (buffer != "")
            {
                endOfEdge++;
                if (buffer != "0")
                {
                    bufferEdge.firstVertex = i;
                    bufferEdge.secondVertex = endOfEdge;
                    bufferEdge.weight = stoi(buffer);
                    edges.addData(bufferEdge);
                }
            }
        }
    }
    file.close();
    return 1;
}

void Graph::printOurGraph() // Функция вывода считаного из файла графа
{
    for (int i = 0; i < vertexesNames.getSize(); i++)
    {
        cout << vertexesNames[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < vertexesNames.getSize(); i++)
    {
        for (int j = 0; j < vertexesNames.getSize(); j++)
        {
            if (i != j)
            {
                for (int z = 0; z < edges.getSize(); z++)
                {
                    if ((edges[z].firstVertex == i && edges[z].secondVertex == j) || (edges[z].firstVertex == j && edges[z].firstVertex == i))
                    {
                        cout << edges[z].weight << " ";
                        break;
                    }
                    else cout << edges[z].weight << " ";
                }
            }
            else
                cout << 0 << " ";
        }
        cout << endl;
    }
}

void Graph::insertionSortOfEdges() // Функция сортировки вставками
{
    for (int i = 1; i < edges.getSize(); i++)
    {
        for (int j = i; edges[j - 1].weight > edges[j].weight && j > 0; j--)
        {
            Edge buffer = edges[j - 1];
            edges[j - 1] = edges[j];
            edges[j] = buffer;
        }
    }
}

void Graph::kraskalAlgorithm() // Функция алгоритма Краскала
{
    int firstVertexSet, secondVertexSet;
    insertionSortOfEdges();
    for (int i = 0; i < vertexesNames.getSize(); i++)
    {
        MakeSet(i);
    }
    for (int i = 0; minimumSpanningTree.getSize() < vertexesNames.getSize() - 1; i++)
    {
        firstVertexSet = Find(edges[i].firstVertex);
        secondVertexSet = Find(edges[i].secondVertex);
        if (firstVertexSet != secondVertexSet)
        {
            minimumSpanningTree.addData(edges[i]);
            Union(firstVertexSet, secondVertexSet);
        }
    }
}

void Graph::printMinimumSpanningTree() // Функция вывода минимального остовного дерева (пары в порядке прохода + суммарный вес)
{
    int totalWeight = 0;
    for (int i = 0; i < minimumSpanningTree.getSize(); i++)
    {
        totalWeight = totalWeight + minimumSpanningTree[i].weight;
        cout << vertexesNames[minimumSpanningTree[i].firstVertex] << " " << vertexesNames[minimumSpanningTree[i].secondVertex] << endl;
    }
    cout << totalWeight;
}

void Graph::DFS(int vertexNumber) // Функция обхода графа поиском в глубину (одноразовый из-за статика)
{
    static ArrayList<bool> visitedOrNotList = ArrayList<bool>(minimumSpanningTree.getSize()+1);
    if (vertexNumber == 0)
        visitedOrNotList.fillEntireArray(false);
    visitedOrNotList.addDataForIndex(vertexNumber, true);
    cout << vertexesNames[vertexNumber] << " ";
    for (int i = 0; i < minimumSpanningTree.getSize(); i++)
    {
        int firstV = minimumSpanningTree[i].firstVertex;
        int secondV = minimumSpanningTree[i].secondVertex;
        if (firstV == vertexNumber && visitedOrNotList[secondV] != true)
            DFS(secondV);
        if (secondV == vertexNumber && visitedOrNotList[firstV] != true)
            DFS(firstV);
    }
}

void Graph::BFS(int vertexNumber) // Обход 
{
    ArrayList<bool> visitedOrNotList = ArrayList<bool>(minimumSpanningTree.getSize() + 1);
    Queue ourQueue = Queue(minimumSpanningTree.getSize() + 1);
    int buffer;
    if (vertexNumber == 0)
        visitedOrNotList.fillEntireArray(false);
    ourQueue.push(vertexNumber);
    while (ourQueue.isNotEmpty())
    {
        buffer = ourQueue.peak();
        vertexNumber = buffer;
        ourQueue.pop();
        visitedOrNotList.addDataForIndex(vertexNumber, true);
        cout << vertexesNames[buffer] << " ";
        for (int i = 0; i < minimumSpanningTree.getSize(); i++)
        {
            int firstV = minimumSpanningTree[i].firstVertex;
            int secondV = minimumSpanningTree[i].secondVertex;
            if (firstV == vertexNumber && visitedOrNotList[secondV] != true)
                ourQueue.push(secondV);
            if (secondV == vertexNumber && visitedOrNotList[firstV] != true)
                ourQueue.push(firstV);
        }
    }
}


