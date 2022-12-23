#pragma once
#include "Queue.h"
#include <string>


template<typename T>
class ArrayList
{
	T* arr;
	int arraySize;
	int lastFilledPart;

public:

	// Конструкторы и деструктор
	ArrayList()
	{
		arraySize = 50;
		arr = new T[arraySize];
		lastFilledPart = -1;
	}
	ArrayList(unsigned size)
	{
		arraySize = size;
		arr = new T[arraySize];
		lastFilledPart = -1;
	}
	~ArrayList()
	{
		delete[]arr;
	}

	// Методы, работающие с динамическим массивом
	void addData(T data); // Запись значения в массив
	int getSize(); // Получение размера заполненной части массива
	T* getItem(unsigned Index); // Обращение к элементу по его индексу
	void addDataForIndex(unsigned Index, T data); // Запись значения по индексу
	void fillEntireArray(T data); // Заполнение всех элементов массива указанными одинаковыми данными
	void deleteItem(unsigned Index); // Удаление значения элемента по индексу
	unsigned IndexforData(T data); // Получение индекса по значению элемента
	T& operator[](int i); // Оператор взятия элемента массива по его индексу
	void sizeExpantion(); //Функция автоматического расширения массива при его переполнении
};


struct Edge // Структура ребра
{
	int firstVertex; // Первая вершина, соединенная ребром
	int secondVertex; // Вторая вершина, соединенная ребром
	int weight; // Вес ребра
};


class Graph
{
	ArrayList<Edge> minimumSpanningTree; // Массив для хранения получаемого минимального остовного дерева графа
	ArrayList<Edge> edges; // Массив для хранения ребер
	ArrayList<int> sets; // Массив для хранения непересекающихся подмножеств
	ArrayList<int> rank; // Массив для размеров непересекающихся подмножеств
	ArrayList<std::string> vertexesNames; // Массив для хранения названий вершин, берущихся из файла
	bool resultOfChecking; // Булевая переменная, для хранения результата открытия файла

public:

	// Функции системы непересекающихся множеств
	void MakeSet(int x); // Функция создания нового подмножества для элемента
	int Find(int x); // Функция, возвращающая подмножество, к которому принадлежит элемент
	void Union(int x, int y); // Функция, объединяющая два подмножества в одно

	// Функции графа
	bool readDataFromFile(std::string fileName); // Функция считывания данных из файла
	void printOurGraph(); // Функция вывода считаного из файла графа
	void insertionSortOfEdges(); // Функция сортировки вставками для массива ребер
	void kraskalAlgorithm(); // Функция алгоритма Краскала
	void printMinimumSpanningTree(); // Функция вывода минимального остовного дерева (пары в порядке прохода + суммарный вес)
	void DFS(int vertexNumber); // Функция обхода графа поиском в глубину
	void BFS(int vertexNumber); // Функция обхода графа поиском в ширину
};

