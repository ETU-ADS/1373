#include <iostream>
#include<fstream>
#include<string>
#include "AList.h"
#include "DoubleArr.h"
#include <Windows.h>

using namespace std;

ArrayList<string> alp = ArrayList<string>();

void kruskalAlgo(ArrayList<Rib>& list, int numberOfHeights) {
	int total = 0;
	int listIndex = 0;
	int check = numberOfHeights;
	list.insertionSort(0, list.size() - 1);


	DoubleArray graph = DoubleArray(numberOfHeights, numberOfHeights);
	for (int i = 0; i < numberOfHeights; i++)
		graph[i].add(i);

	int firstSet = -1, secondSet = -2;

	while (check != 1)
	{
		Rib rib = Rib(list[listIndex].weight, list[listIndex].from, list[listIndex].to);
		for (int i = 0; i < numberOfHeights; i++)
		{
			if (graph[i].find(rib.from) != -1)
				firstSet = i;
			if (graph[i].find(rib.to) != -1)
				secondSet = i;

		}
		if (firstSet != secondSet)
		{
			int iInd = 0;
			while (alp[rib.from][iInd] != '\0')
			{
				std::cout << alp[rib.from][iInd];
				iInd++;
			}
			iInd = 0;
			std::cout << "  ";
			while (alp[rib.to][iInd] != '\0')
			{
				std::cout << alp[rib.to][iInd];
				iInd++;
			}
			std::cout << endl;
			total += rib.weight;
			while (graph[secondSet][0] != -1)
			{
				int a = graph[secondSet][0];
				graph[secondSet].deleteItem(0);
				graph[firstSet].add(a);
			};
			listIndex++;
			check--;
		}
		else
		{
			listIndex++;
		}
	}
	std::cout << "\nСумма весов рёбер: ";
	std::cout << total << endl;
}

void inWidth(ArrayList<Rib>& list, int numberOfHeights) {
	ArrayList<int> visited = ArrayList<int>();
	ArrayList<int> que = ArrayList<int>();
	int a = list[0].from;
	que.add(a);
	while (visited.size() != numberOfHeights)
	{
		for (int i = 0; i < list.size(); i++)//i counter for list
		{
			bool isIncluded = false;
			if (list[i].from == a)
			{
				if (que.find(list[i].to) == -1)
				{
					if (visited.find(list[i].to) == -1)
					{
						que.add(list[i].to);
					}
				}
			}
			else
			{
				if (list[i].to == a)
				{
					if (que.find(list[i].from) == -1)
					{
						if (visited.find(list[i].from) == -1)
						{
							que.add(list[i].from);
						}
					}
				}
			}
		}
		visited.add(a);
		que.deleteItem(0);
		a = que[0];
	}
	for (int i = 0; i < visited.size(); i++)
	{
		std::cout << visited[i] << " ";
	}
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int counter = 1;//число значений в матрице
	int value = 0;//считанное значение
	int index = 0;//индекс buffer
	int alIdex = 0;//индекс alp
	int alCurrentIndex = 0;//индекс alp
	string s;
	string heightName;
	fstream file;
	file.open("test.txt");
	getline(file, s, '\n');
	for (int i = 0; i < s.length(); i++) {
		heightName.clear();
		while (i < s.length() && s[i] == ' ')
		{
			counter++;
			i++;
		}
		while (i < s.length() && s[i] != ' ')
		{
			heightName += s[i];
			alCurrentIndex++;
			i++;
		}
		alp.add(heightName);
		i--;
		alIdex++;
		alCurrentIndex = 0;
	}
	ArrayList<int> buffer = ArrayList<int>(counter);
	ArrayList<Rib> list = ArrayList<Rib>();
	DoubleArray graph = DoubleArray(counter, counter);

	for (int i = 0; i < counter; i++)
		for (int j = 0; j < counter; j++)
		{
			file >> value;
			buffer.add(value);
		}
	for (int i = 0; i < counter; i++)
		for (int j = 0; j < counter; j++)
		{
			graph[i][j] = buffer[index];
			index++;
		}
	for (int i = 0; i < counter - 1; i++)// создаем список (вес, из, в)
		for (int j = i + 1; j < counter; j++)
		{
			if (graph[i][j] == 0)
				continue;
			Rib rib = Rib(graph[i][j], i, j);
			list.add(rib);
		}
	kruskalAlgo(list, counter);
	inWidth(list, counter);
	return 0;
}

