#include <iostream>
#include "Queue.h"
#include "Vector.h"
#include <fstream>
#include <string>



struct Edge
{
    int begin;
    int end;
    int weight;
};


class Graph
{
    Vector<string> Vertex;
    Vector<Edge> vector_edge;
    Vector<Edge> min_cost;
    Vector<int> p;
    Vector<int> rank;
    void MakeSet(int x);
    int Find(int x);
    void Union(int x, int y);
    void Sort();

public:
    void MakeGraph(Queue& queue);
    void Out();
    void printMinCost();
    void Kraskal();
};



void Graph::MakeGraph(Queue& queue)
{
    bool flag = true;
    Edge edge;
    string temp;
    string str = queue.pop() + " ";
    for (int i = 0; i < str.size(); i++)
    {
        temp = "";
        while (str[i] != ' ')
        {
            temp += str[i];
            i++;
        }
        Vertex.push_back(temp);
    }
    for (int i = 0; i < Vertex.get_size() - 1; i++)
    {
        str = queue.pop() + " ";
        int end = 0;
        for (int j = 0; j < str.size(); j++)
        {
            temp = "";
            flag = false;
            while (str[j] != ' ')
            {
                temp += str[j];
                j++;
                flag = true;
                
            }


            if (temp == "0" && flag == false)
            {
                
                break;
                
            }
            if (end <= i || temp == "0")
            {
                ++end;
                continue;
            }
            edge.begin = i;
            edge.end = end++;
            edge.weight = stoi(temp);
            vector_edge.push_back(edge);
        }
    }
}


void Graph::Out()
{
    Vertex.print();
    int size = Vertex.get_size();
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (i == j)
                std::cout << 0 << " ";
            else
                for (int k = 0; k < vector_edge.get_size(); ++k)
                {
                    if ((vector_edge[k].begin == i && vector_edge[k].end == j) || (vector_edge[k].begin == j && vector_edge[k].end == i))
                    {
                        std::cout << vector_edge[k].weight << " ";
                        break;
                    }
                    else if (k == vector_edge.get_size() - 1)
                        std::cout << 0 << " ";
                }
        }
        std::cout << std::endl;
    }
}


void Graph::printMinCost()
{
    int weight = 0;

    for (int i = 0; i < min_cost.get_size(); ++i)
    {
        std::cout << Vertex[min_cost[i].begin] << " " << Vertex[min_cost[i].end] << std::endl;
        weight += min_cost[i].weight;
    }
    std::cout << weight << std::endl;
}


void Graph::MakeSet(int x)
{
    p.push_back(x);
    rank[x] = 0;
}

int Graph::Find(int x)
{
    return (x == p[x] ? x : p[x] = Find(p[x]));
}


void Graph::Union(int x, int y)
{
    if ((x = Find(x)) == (y = Find(y)))
        return;

    if (rank[x] < rank[y])
        p[x] = y;
    else {
        p[y] = x;
        if (rank[x] == rank[y])
            ++rank[x];
    }
}

void Graph::Sort()
{
    int j;
    for (int i = 1; i < vector_edge.get_size(); i++) {
        j = i - 1;
        while ((j >= 0) && (vector_edge[j].weight > vector_edge[j + 1].weight)) {
            Edge temp;
            temp = vector_edge[j];
            vector_edge[j] = vector_edge[j + 1];
            vector_edge[j + 1] = temp;
            j--;
        }
    }
}


void Graph::Kraskal()
{
    int first, second;
    Sort();
    for (int i = 0; i < Vertex.get_size(); ++i)
        MakeSet(i);
    for (int i = 0; min_cost.get_size() < Vertex.get_size() - 1; ++i)
    {
        first = Find(vector_edge[i].begin);
        second = Find(vector_edge[i].end);
        if (first != second)
        {
            min_cost.push_back(vector_edge[i]);
            Union(first, second);
        }
    }
    printMinCost();
}

int main()
{
    setlocale(LC_ALL, "ru");
    Queue queue;
    string line;
    ifstream fin("1.txt");
    int count = 0;
    if (fin.is_open()) {
        while (getline(fin, line)) {
            queue.push(line);
        }
    }
    fin.close();


    Graph a;
    a.MakeGraph(queue);
    a.Out();
    std::cout << std::endl;
    a.Kraskal();


    return 0;
}
