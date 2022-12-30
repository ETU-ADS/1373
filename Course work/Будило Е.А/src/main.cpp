#include <iostream>
#include <windows.h>
#include "graph.h"
#include <iomanip>
using namespace std;

int main()
{
    system("color B1");
    cout << setw(60) << setfill(' ') << "Hello!\n";
    cout << setw(82) << setfill(' ') << "This program implements the Kruskal algorithm!\n";
    cout << setw(146) << setfill('*') << "\nYour Adjacency Matrix: " << endl;
    Graph graph;

    graph.read("Wiki 1.txt");
    cout << "\nDFS: " << endl;
    graph.dfs();
    cout << endl;
    cout << "\nBFS: " << endl;
    graph.bfs();
    cout << "\nKRUSKAL:" << endl;
    graph.kruskal();

    system("pause");
    system("cls");
    return 0;
}