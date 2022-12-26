#include <iostream>
#include <windows.h>
#include "Graph.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    Graph graph;
    std::cout << "Данный граф" << std::endl;
    graph.read("Graph.txt");
    std::cout << ""<<std::endl;
    std::cout << "\nАлгоритм Краскала" << std::endl;
    graph.kraskal();
    system("chcp 1251");
    system("pause");
    return 0;
}