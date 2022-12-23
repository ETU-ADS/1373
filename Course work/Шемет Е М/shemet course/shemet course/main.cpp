#include <iostream>
#include "Kruskal.h"

int main()
{
    setlocale(LC_ALL, "Russian");
  //  system("chcp 1251");
    Graph graph;
    std::string str;
    std::cout << "Введите имя файла с матрицей смежности: ";
    std::getline(std::cin, str);
    graph.read(str);
    std::cout << "\n";
    std::cout << "Обход графа в глубину: ";
    graph.DFS();
    std::cout << std::endl << "\n";
    std::cout << "Обход графа в ширину: ";
    graph.BFS();
    std::cout << "\n" << "Минимальное остовное дерево по алгоритму Краскала:" << std::endl;
    graph.algorithmKruskal();
    std::cout << "\n";
    std::cout << "Обход MST в глубину: ";
    graph.DFS();
    system("pause");
    return 0;
}