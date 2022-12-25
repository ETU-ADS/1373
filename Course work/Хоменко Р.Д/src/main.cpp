#include <iostream>
#include <windows.h>
#include "Graph.h"

int main()
{
    Graph graph;
    std::cout << "GRAPH" << std::endl;
    graph.read("Graph.txt");
    std::cout << "\nDFS: ";
    graph.dfs();
    std::cout << std::endl;
    std::cout << "\nBFS: ";
    graph.bfs();
    std::cout << "\nKRASKAL" << std::endl;
    graph.kraskal();
    system("pause");
    return 0;
}