#include "DynamicArray.h"

#include <iostream>

class Cruscal {
private:
	struct vert
	{
		char* name = new char[16];
		int color = -1;
	};
	struct edge
	{
		vert* vertStart;
		vert* vertEnd;
		int weight = 0;
	};
	struct set
	{
		int color = -1;
		DynamicArray<vert*> verts;
	};

	void clearVert(vert* vert) {
		for (int i = 0; i < 16; ++i) {
			vert->name[i] = '\0';
		}
	}

	DynamicArray<set*> setsArray;

	void makeSet(vert* vert) {
		set* newSet = new set;
		newSet->color = vert->color;
		newSet->verts.add(vert);
		setsArray.add(newSet);
	}
	int find(vert* vert) {
		for (int i = 0; i < setsArray.length(); ++i) {
			if (vert->color == setsArray[i]->color) {
				return i;
			}
		}
		return -1;
	}
	void unite(set* first, set* second) {
		int a = setsArray.find(first);
		setsArray.deleteElem(a);
		int b = setsArray.find(second);
		setsArray.deleteElem(b);
		for (int i = 0; i < second->verts.length(); ++i) {
			first->verts.add(second->verts[i]);
			second->verts[i]->color = first->color;
		}
		setsArray.add(first);
		delete second;
	}

	DynamicArray<vert*> vertsArray;
	DynamicArray<edge*> edgesArray;
	DynamicArray<edge*> result;
public:
	void createGraph(DynamicArray<char>& matrix) {
		unsigned int i = 0;
		while (matrix[i] != '\n') {
			vert* newVert = new vert;
			clearVert(newVert);
			unsigned int j = 0;

			while (matrix[i] != ' ' && matrix[i] != '\n')
			{
				newVert->name[j] = matrix[i];
				++j;
				++i;
			}

			newVert->color = vertsArray.length();
			vertsArray.add(newVert);
			++i;
			if (matrix[i - 1] == '\n') {
				break;
			}
		}

		unsigned int rowCounter = 0;
		for (; matrix[i-1] != '\0'; ++i) {
			unsigned int columnCounter = rowCounter;
			while (columnCounter > 0)
			{
				int weight = 0;
				edge* newEdge = new edge;
				while (matrix[i] != ' ') {
					weight = weight * 10 + (matrix[i] - '0');
					newEdge->weight = weight;
					++i;
				}
				newEdge->vertStart = vertsArray[rowCounter];
				newEdge->vertEnd = vertsArray[rowCounter - columnCounter];
				if (weight == 0) {
					delete newEdge;
				}
				else {
					edgesArray.add(newEdge);
				}
				--columnCounter;
				++i;
			}
			while (matrix[i] != '\n' && matrix[i] != '\0') {
				++i;
			}
			++rowCounter;
		}
	}
	void printVerts() {
		std::cout << "Verts of the graph:\n";
		for (int i = 0; i < vertsArray.length(); ++i) {
			std::cout << vertsArray[i]->name;
			if (i != vertsArray.length() - 1)
				std::cout << ", ";
		}
		std::cout << '\n' << '\n';
	}
	void printEdges() {
		std::cout << "Edges of the graph:\n";
		for (int i = 0; i < edgesArray.length(); ++i) {
			std::cout << edgesArray[i]->weight << ' ' << edgesArray[i]->vertStart->name << ' ' << edgesArray[i]->vertEnd->name << '\n';
		}
		std::cout << '\n';
	}
	void sortEdges() {
		for (int i = 1; i < edgesArray.length(); ++i) {
			int j = i;
			while (j > 0 && (edgesArray[j-1]->weight > edgesArray[j]->weight))
			{
				edgesArray.swap(j - 1, j);
				--j;
			}
		}
	}
	void buildMST() {
		int weight = 0;
		for (int i = 0; i < vertsArray.length(); ++i) {
			makeSet(vertsArray[i]);
		}
		for (int i = 0; i < edgesArray.length(); ++i) {
			if (find(edgesArray[i]->vertStart) != find(edgesArray[i]->vertEnd)) {
				unite(setsArray[find(edgesArray[i]->vertStart)], setsArray[find(edgesArray[i]->vertEnd)]);
				result.add(edgesArray[i]);
				std::cout << edgesArray[i]->vertStart->name << ' ' << edgesArray[i]->vertEnd->name << ' ' << edgesArray[i]->weight << '\n';
				weight += edgesArray[i]->weight;
			}
		}
		std::cout << "MST weight: " << weight << '\n';
	}
	~Cruscal() {
		for (int i = 0; i < vertsArray.length(); ++i) {
			delete vertsArray[i]->name;
			delete vertsArray[i];
		}
		for (int i = 0; i < edgesArray.length(); ++i) {
			delete edgesArray[i];
		}
		for (int i = 0; i < setsArray.length(); ++i) {
			delete setsArray[i];
		}
	}
};