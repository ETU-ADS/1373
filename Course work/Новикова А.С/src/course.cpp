#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

template <class T>
class Queue
{
private:
	T* data;
	int top;
	int size;

	void expand();
public:

	Queue(int elemAmount);
	~Queue();

	void pop();

	void push(T value);

	T front();

	bool isEmpty();
};

template <class T>
Queue<T>::Queue(int elemAmount)
{
	size = elemAmount;
	data = new T [size];
	top = -1;
}

template <class T>
Queue<T>::~Queue()
{
	delete[] data;
}

template <class T>
void Queue<T>::expand()
{
	size *= 2;

	T* temp = new T[size];

	for (int i = 0; i <= top; i++)
		temp[i] = data[i];

	delete[] data;
	data = temp;
}

template <class T>
void Queue<T>::pop()
{
	if (isEmpty())
		std::cout << "The queue is empty! Nothing to pop!";

	else
		top--;
}

template <class T>
void Queue<T>::push(T value)
{
	if (top == size - 1)
		expand();

	for (int i = top + 1; i > 0; --i)
		data[i] = data[i - 1];

	data[0] = value;
	top++;
}

template <class T>
T Queue<T>::front()
{
	if (!isEmpty())
		return data[top];

	return -1;
}

template <class T>
bool Queue<T>::isEmpty()
{
	return (top < 0);
}

///////////////////////////////////////

template<class T>
class DynArray
{
private:
	int capacity;
	int size;
	T* data;

	void expand();

public:
	DynArray();
	DynArray(int elemAmount);
	~DynArray();

	int find(T value); //найти индекс по значению

	void add(int index, T value); //добавить элемент

	void remove(int index); // удалить элемент из списка по индексу

	int getSize();

	void pushBack(T value);

	void swap(int i, int j);

	T& operator[](const int index);
};

template<class T>
DynArray<T>::DynArray()
{
	capacity = 1;
	size = 0;
	data = new T[capacity];
}

template<class T>
DynArray<T>::DynArray(int elemAmount)
{
	capacity = elemAmount;
	size = 0;
	data = new T[capacity];
}

template<class T>
DynArray<T>::~DynArray()
{
	delete[] data;
}


template<class T>
void DynArray<T>::expand()
{
	capacity *= 2;

	T* temp = new T[capacity];

	for (int i = 0; i < size; i++)
		temp[i] = data[i];

	delete[] data;
	data = temp;
}

template<class T>
int DynArray<T>::find(T value)
{
	for (int i = 0; i < size; i++) {
		if (data[i] == value)
			return i;
	}

	std::cout << "Not found";
	return -1;
}

template<class T>
void DynArray<T>::add(int index, T value)
{
	if (index >= 0)
	{
		if (size >= capacity)
			expand();

		data[index] = value;
		size++;
	}
	else
	{
		std::cout << "Incorrect index";
	}
}

template<class T>
void DynArray<T>::remove(int index)
{
	if (index >= 0)
	{
		for (int i = index; i < size; i++)
			data[i] = data[i + 1];

		data[size] = '-';
		size--;
	}
	else
	{
		std::cout << "Incorrect index";
	}
}

template<class T>
int DynArray<T>::getSize()
{
	return size;
}

template<class T>
void DynArray<T>::pushBack(T value)
{
	if (size >= capacity)
		expand();

	data[size++] = value;
}

template<class T>
void DynArray<T>::swap(int i, int j)
{
	T temp = data[i];
	data[i] = data[j];
	data[j] = temp;
}

template<class T>
T& DynArray<T>::operator[](const int index)
{
	return data[index];
}


////////////////////////////////////

struct Edge
{
	int from;
	int to;
	int weight;

	bool operator < (Edge const& other)
	{
		return weight < other.weight;
	}

	bool operator > (Edge const& other)
	{
		return weight > other.weight;
	}

};

class Graph
{
private:

	DynArray<Edge> edges;
	DynArray<Edge> MST;
	DynArray<std::string> verteces;
	DynArray<int> parent;
	DynArray<int> rank;

	void sort();
	void makeSet(int i);
	int findSet(int i);
	void unionSets(int i, int j);

public:

	void kruskal();
	void printMST();
	bool read(std::string filename);
	void DFS(int v);
	void BFS();
};

void Graph::sort()
{
	int j;
	Edge key;
	for (int i = 1; i < edges.getSize(); i++)
	{
		key = edges[i];
		j = i - 1;

		while (j >= 0 && edges[j] > key)
		{
			edges[j + 1] = edges[j];
			j--;
		}
		edges[j + 1] = key;
	}
}

void Graph::makeSet(int i)
{
	parent.pushBack(i);
	rank[i] = 0;
}

int Graph::findSet(int i)
{
	if (i == parent[i])
		return i;
	return parent[i] = findSet(parent[i]);
}

void Graph::unionSets(int i, int j)
{
	i = findSet(i);
	j = findSet(j);

	if (i != j)
	{
		if (rank[i] < rank[j])
			parent[i] = j;
		else
		{
			parent[j] = i;
			if (rank[i] == rank[j])
				rank[i]++;
		}
	}
}

void Graph::kruskal()
{
	sort();

	int first, second;

	for (int i = 0; i < verteces.getSize(); i++) 
	{
		rank.pushBack(0);
		makeSet(i);
	}

	for (int i = 0; MST.getSize() < verteces.getSize() - 1; i++) 
	{
		first = findSet(edges[i].from);
		second = findSet(edges[i].to);

		if (first != second) 
		{
			MST.pushBack(edges[i]);
			unionSets(first, second);
		}
	}
}

void Graph::printMST()
{
	int weight = 0;

	for (int i = 0; i < MST.getSize(); i++)
	{
		std::cout << verteces[MST[i].from] << ' ' << verteces[MST[i].to] << std::endl;
		weight += MST[i].weight;
	}
	std::cout << weight << std::endl;
}


void Graph::BFS()
{
	DynArray<bool> visited(verteces.getSize());
	for (int i = 0; i < verteces.getSize(); i++)
		visited[i] = false;
	Queue<int> q(10);
	q.push(0);
	visited[0] = true;
	while (!q.isEmpty())
	{
		int v = q.front();
		q.pop();

		std::cout << ' ' << verteces[v];

		for (int i = 0; i < edges.getSize(); i++)
		{
			if (v == edges[i].from && !visited[edges[i].to])
			{
				q.push(edges[i].to);
				visited[edges[i].to] = true;
			}
			else if (v == edges[i].to && !visited[edges[i].from])
			{
				q.push(edges[i].from);
				visited[edges[i].from] = true;
			}
		}
	}

}

void Graph::DFS(int v)
{
    static DynArray<bool> visited(verteces.getSize());

	if (v == 0)
	{
		for (int i = 0; i < verteces.getSize(); i++)
			visited[i] = false;
	}

	visited[v] = true;
	std::cout << ' ' << verteces[v];

	for (int i = 0; i < edges.getSize(); i++)
	{
		if (edges[i].from == v && !visited[edges[i].to])
			DFS(edges[i].to);
		else if (edges[i].to == v && !visited[edges[i].from])
			DFS(edges[i].from);
	}
}


bool Graph::read(std::string filename)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(65001);

	if (filename == "")
		return false;
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "Failed to open file." << std::endl;
		return false;
	}

	std::string str;
	std::getline(file, str);

	std::string buffer = "";


	for (int i = 0; i <= str.length(); i++)
	{
		while (str[i] != ' ' && i != str.length())
			buffer += str[i++];

		verteces.pushBack(buffer);
		buffer = "";
	}

	int from = 0;
	while(std::getline(file, str))
	{
		Edge e;
		int i = 0;
		int to = 0;
		int buff = 0;

		while (i < str.length())
		{
			while (str[i] != ' ' && i < str.length())
			{
				buff *= 10;
				buff = buff + str[i++] - '0';
			}
			i++;
			if (buff != 0 && from < to)
			{
				e.weight = buff;
				e.from = from;
				e.to = to;
				edges.pushBack(e);
			}
			buff = 0;
			to++;
		}
		from++;
	}
	for (int i = 0; i < verteces.getSize(); i++)
		std::cout << verteces[i] << ' ';
	std::cout << std::endl;

	std::cout << std::endl;
	for (int i = 0; i < edges.getSize(); i++)
		std::cout << edges[i].weight << ' ';
	std::cout << std::endl;

	file.close();
	return true;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(65001);

	std::string filename;
	std::cout << "Enter the name of the file: ";
	std::getline(std::cin, filename);
	
	Graph g;
	if (g.read(filename))
	{
		std::cout << "kruskal: " << std::endl;
		g.kruskal();
		g.printMST();
		std::cout << std::endl;
		std::cout << "dfs: " << std::endl;
		g.DFS(0);
		std::cout << std::endl;
		std::cout << "bfs: " << std::endl;
		g.BFS();
		std::cout << std::endl;
	}

	system("pause");
	return 0;
}
