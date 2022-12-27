#include <iostream>
#include <fstream>
#include <string>

struct Edge
{
    int firstVertex;
    int SecondVertex;
    int weight;
};

template<typename T>
class DynamicArray
{
private:
	T* dArray;
	unsigned numberOfElemets;
public:
	~DynamicArray()
	{
		delete[] dArray;
	}
	void create(int n)
	{
		dArray = new T[n];
	}
	T indexAccess(int index);
	T indexByValue(int value);
	void addingByIndex(int index, T value);
	void deleteByIndex(int index);
	T* returndarray()
	{
		return dArray;
	}
	void addarray(const T* value, int length)
	{
		for (int i = 0; i < length; ++i)
		{
			dArray[i] = value[i];
		}
	}
	T& operator[](int i)
	{
		return dArray[i];
	}
};

template <typename T> 
T DynamicArray<T>::indexAccess(int index)
{
	if (index >= numberOfElemets)
	{
		std::cout << "error";
		return -1;
	}
	return dArray[index];
}

template <typename T>
T DynamicArray<T>::indexByValue(int value)
{
	while (numberOfElemets != -1)
	{
		if (dArray[numberOfElemets - 1] == value)
			return numberOfElemets;
		else
			--numberOfElemets;
	}
	std::cout << "error";
	return -1;
}

template<typename T>
void DynamicArray<T>::addingByIndex(int index, T value)
{
	++numberOfElemets;
	if (index > numberOfElemets)
		std::cout << "error";
	T* array1 = new T[numberOfElemets + 1];
	for (int i = 0; i < index; i++)
	{
		array1[i] = dArray[i];
	}
	for (int i = (index + 1); i < numberOfElemets; i++)
	{
		array1[i] = dArray[i];
	}
	array1[index] = value;
	delete[] dArray;
	dArray = array1;
}

template<typename T>
void DynamicArray<T>::deleteByIndex(int index)
{
	if (index > numberOfElemets)
		std::cout << "error";
	for (int i = index; i < numberOfElemets; i++)
	{
		dArray[i] = dArray[i + 1];
	}
	--numberOfElemets;
}

template<typename T>
void OutputArray(T arr[], int capacity)
{
	for (unsigned i = 0; i < capacity; ++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

template<typename T>
std::string* inputGraph(char nameOfFile[], DynamicArray<char>& vertexes, int& quantity, DynamicArray<T>* main)
{
	quantity = 0;
	std::ifstream fileInput(nameOfFile);
	if (!fileInput.is_open())
	{
		std::cout << "File not found! " << std::endl;
		exit(-1);
	}
	std::string inputWord;
	std::getline(fileInput, inputWord, '\n');
	vertexes.create(inputWord.length());
	vertexes.addarray(inputWord.c_str(), inputWord.length());
	int i = 0;
	while (vertexes.returndarray()[i] != '\0')
	{
		if (vertexes.returndarray()[i] == ' ')
			++quantity;
		++i;
	}
	quantity++;
	std::string *vertex = new std::string[quantity];
	std::string vertexe = vertexes.returndarray();
	int index = 0, index2 = 0;
	for (int i = 0; i < quantity; ++i)
	{
		if (quantity == 1)
		{
			vertex[0] += vertexe;
			std::cout << vertex[0] << std::endl;
			break;
		}
		if (i == 0)
		{
			index2 = vertexe.find(' ', index + 1);
			vertex[i] = vertexe.substr(index, index2 - index);
			index = index2;
			//std::cout << vertex[i] << std::endl;
		}
		else
		{
			index2 = vertexe.find(' ', index + 1);
			vertex[i] = vertexe.substr(index + 1, index2 - index);
			index = index2;
			//std::cout << vertex[i] << std::endl;

		}
	}
	// выше работает
	if (main != nullptr)
	{
		for (int i = 0; i < quantity; ++i)
		{
			main[i].create(quantity);
			int* temp = main[i].returndarray();
			for (int j = 0; j < quantity; ++j)
			{
				int number;
				fileInput >> number;
				temp[j] = number;
			}
		}
	}
	fileInput.close();
	return vertex;
}

template<typename T>
void fillEdges(DynamicArray<T>* main, Edge edges[], int quantity, int &quantity2)
{
	int index = 0;
	for (int i = 0; i < quantity; ++i)
	{
		if (quantity == 1)
			break;
		int* temp = main[i].returndarray();
		for (int j = i + 1; j < quantity; ++j)
		{
			if (temp[j] != 0)
			{
				edges[index].firstVertex = i;
				edges[index].SecondVertex = j;
				edges[index++].weight = temp[j];
				++quantity2;
			}
		}
	}
}

void sort(Edge edges[], int quantity2)
{
	for (int j = 1; j < quantity2; ++j)
	{
		for (int i = 0; i < quantity2 - 1; ++i)
		{
			if (edges[i].weight > edges[i + 1].weight)
			{
				int f[] = { edges[i].firstVertex, edges[i].SecondVertex, edges[i].weight };
				edges[i].firstVertex = edges[i + 1].firstVertex;
				edges[i].SecondVertex = edges[i + 1].SecondVertex;
				edges[i].weight = edges[i + 1].weight;
				edges[i + 1].firstVertex = f[0];
				edges[i + 1].SecondVertex = f[1];
				edges[i + 1].weight = f[2];
			}
		}
	}
}

void getColorAll(int color[],int quantity)
{
	for (int i = 0; i < quantity; ++i)
	{
		color[i] = i;
	}
}

void changeColor(int color[], int startcolor, int endcolor, int quantity2)
{
	for (int i = 0; i < quantity2; ++i)
	{
		if (color[i] == startcolor)
		{
			color[i] = endcolor;
		}
	}
}
void copy(Edge* edges, Edge* edges2, int quantity2)
{
	for (int i = 0; i < quantity2; ++i)
	{
		int temp1 = edges[i].firstVertex;
		int temp2 = edges[i].SecondVertex;
		int temp3 = edges[i].weight;
		edges2[i].firstVertex = temp1;
		edges2[i].SecondVertex = temp2;
		edges2[i].weight = temp3;
	}
}

void Kruskal(Edge edges[], int color[], int quantity2, std::string *vertex)
{
	int sum = 0;
	for (int i = 0; i < quantity2; ++i)
	{
		if (quantity2 == 1)
		{
			std::cout << vertex[0] << std::endl;
			break;
		}
		if (color[edges[i].firstVertex] > color[edges[i].SecondVertex])
		{
			changeColor(color, color[edges[i].SecondVertex], color[edges[i].firstVertex], quantity2);
			std::cout << vertex[edges[i].firstVertex] << ' ' << vertex[edges[i].SecondVertex] << std::endl;
			sum += edges[i].weight;

		}
		else if (color[edges[i].firstVertex] < color[edges[i].SecondVertex])
		{
			changeColor(color, color[edges[i].firstVertex], color[edges[i].SecondVertex], quantity2);
			std::cout << vertex[edges[i].firstVertex] << ' ' << vertex[edges[i].SecondVertex] << std::endl;
			sum += edges[i].weight;
		}
	}
	std::cout << sum << std::endl;
}

int main()
{
	setlocale(LC_ALL, ".UTF8");
	std::cout << "Enter name of file: " << std::endl;
	char nameOfFile[30];
	std::cin >> nameOfFile;

	int quantity = 0;
	DynamicArray<char> vertexes;
	
	std::cout << std::endl;
	DynamicArray<int>* mainArr = nullptr;
	
	std::string *vertex = inputGraph(nameOfFile, vertexes, quantity, mainArr);
	mainArr = new DynamicArray<int>[quantity];
	inputGraph(nameOfFile, vertexes, quantity, mainArr);
	
	for (int i = 0; i < quantity; ++i)
	{
		//OutputArray(mainArr[i].returndarray(), quantity);
	}
	
	int max = (quantity * (quantity - 1)) / 2;
	Edge* edges = new Edge[max];
	int quantity2 = 0;
	fillEdges(mainArr, edges, quantity, quantity2);
	Edge* edges2 = new Edge[quantity2];
	copy(edges, edges2, quantity2);
	delete[] edges;
	sort(edges2, quantity2);
	
	if (quantity != 1)
	{
		std::cout << "List smezhnosti : " << std::endl;
		for (int i = 0; i < quantity2; ++i)
		{
			std::cout << edges2[i].firstVertex
			 << ' ' << edges2[i].SecondVertex << ' ' << edges2[i].weight << std::endl;
		}
	}
	
	std::cout << "Otvet: " << std::endl;
	int* color = new int[quantity];
	getColorAll(color, quantity);
	Kruskal(edges2, color, quantity2, vertex);
	delete []vertex;
	delete []color;
	delete[] edges2;
	delete[] mainArr;
	return 0;
}
