#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "DoubleArray.h"
#include "Array.h"
#include "Stack.h"

Array<std::string> vertexs = Array<std::string>();

void kruskalAlgo(Array<EDGE>& list, int matrixElementsCount) {
	int totalWeight = 0, index = 0, amountOfElements = matrixElementsCount;
	DoubleArray graph = DoubleArray(matrixElementsCount, matrixElementsCount);

	list.insertionSort(0, list.getSize() - 1);

	for (int i = 0; i < matrixElementsCount; i++)
		graph[i].addToTheEnd(i);

	int set_1 = -1, set_2 = -2;

	std::cout << "Edges:" << std::endl;

	while (amountOfElements != 1) {
		EDGE edge = EDGE(list[index].weight, list[index].start, list[index].end);

		for (int i = 0; i < matrixElementsCount; i++) {
			if (graph[i].findByValue(edge.start) != -1)
				set_1 = i;
			if (graph[i].findByValue(edge.end) != -1)
				set_2 = i;
		}

		if (set_1 != set_2) {
			int iInd = 0;

			while (vertexs[edge.start][iInd] != '\0') {
				std::cout << vertexs[edge.start][iInd];
				iInd++;
			}

			iInd = 0;
			std::cout << "  ------>  ";

			while (vertexs[edge.end][iInd] != '\0') {
				std::cout << vertexs[edge.end][iInd];
				iInd++;
			}

			std::cout << std::endl;
			totalWeight += edge.weight;

			while (graph[set_2][0] != -1) {
				int a = graph[set_2][0];
				graph[set_2].deleteByIndex(0);
				graph[set_1].addToTheEnd(a);
			};
			index++;
			amountOfElements--;
		}
		else {
			index++;
		}
	}
	std::cout << std::endl;
	std::cout << "Total weight of graph edges: " << totalWeight << std::endl;
}
void traversal(Array<EDGE>& list, int numberOfHeights) {
	Array<int> visited = Array<int>(), que = Array<int>();
	int a = list[0].start;

	que.addToTheEnd(a);

	std::cout << "Traversal of the graph in breadth (by vertice indices):" << std::endl;

	while (visited.getSize() != numberOfHeights) {
		for (int i = 0; i < list.getSize(); i++) {
			bool isIncluded = false;
			if (list[i].start == a) {
				if (que.findByValue(list[i].end) == -1)
					if (visited.findByValue(list[i].end) == -1)
						que.addToTheEnd(list[i].end);
			}
			else
				if (list[i].end == a)
					if (que.findByValue(list[i].start) == -1)
						if (visited.findByValue(list[i].start) == -1)
							que.addToTheEnd(list[i].start);
		}

		visited.addToTheEnd(a);
		que.deleteByIndex(0);
		a = que[0];
	}
	for (int i = 0; i < visited.getSize(); i++)
		std::cout << visited[i] << " ";
}