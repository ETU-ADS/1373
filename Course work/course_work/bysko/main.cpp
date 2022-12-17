#include <iostream>
#include <fstream>
#include <string>

#include "Array.h"
#include "DoubleArray.h"
#include "kruskal.h"

int main() {
	system("chcp 1251");
	system("cls");
	
	int matrixElementsCount = 1, value = 0, buffIndex = 0, alpIdex = 0, alpCurrentIndex = 0;
	std::string fileName, vertexName;
	std::fstream file;

	file.open("Weirdt.txt");
	getline(file, fileName, '\n');

	for (int i = 0; i < fileName.length(); i++) {
		vertexName.clear();

		while (i < fileName.length() && fileName[i] == ' ') {
			matrixElementsCount++;
			i++;
		}

		while (i < fileName.length() && fileName[i] != ' ') {
			vertexName += fileName[i];
			alpCurrentIndex++;
			i++;
		}

		vertexs.addToTheEnd(vertexName);
		i--;
		alpIdex++;
		alpCurrentIndex = 0;
	}

	Array<int> buffer = Array<int>(matrixElementsCount);
	DoubleArray graph = DoubleArray(matrixElementsCount, matrixElementsCount);

	Array<EDGE> edgeArr = Array<EDGE>();

	for (int i = 0; i < matrixElementsCount; i++) {
		for (int j = 0; j < matrixElementsCount; j++) {
			file >> value;
			buffer.addToTheEnd(value);

			graph[i][j] = buffer[buffIndex];
			buffIndex++;
		}
	}

	for (int i = 0; i < matrixElementsCount - 1; i++) {
		for (int j = i + 1; j < matrixElementsCount; j++) {
			if (graph[i][j] != 0) {
				EDGE rib = EDGE(graph[i][j], i, j);
				edgeArr.addToTheEnd(rib);
			}
		}
	}

	kruskalAlgo(edgeArr, matrixElementsCount);
	std::cout << std::endl;

	traversal(edgeArr, matrixElementsCount);
	std::cout << std::endl;

	return 0;
}