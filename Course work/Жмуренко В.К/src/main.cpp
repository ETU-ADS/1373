#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
	Graph ourGraph;
	ourGraph.readDataFromFile("G://Wiki 2.txt");
	cout << endl << endl;
	ourGraph.kraskalAlgorithm();
	ourGraph.printMinimumSpanningTree();
	cout << endl<< endl;
	ourGraph.DFS(0);
	cout << endl << endl;
	ourGraph.BFS(0);
	return 0;
}