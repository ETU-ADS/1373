#include <iostream>
#include <fstream>
#include <string>
#include "MyQueue.h"
#include "MyVector.h"
#include "MyVectorVec.h"
#include <time.h>

using namespace std;

class MyGraph {
public:
    class Node {
    public:
        string name;
        int num;
        MyVector<int> way;
    };
    MyVectorVec<string> graph;
    MyVectorVec<int> ways;
    int size = 0;
    Node* data;
    MyGraph(MyVector<string>& names, MyVectorVec<int>& graph1) {
        data = new Node[graph1.size];
        size = graph1.size;
        for (int i = 0; i < graph1.size; i++) {
            data[i].name = names[i];
            graph.push_back();
            for (int k = 0; k < graph1[i].size; k++) {
                data[i].way.push_back(graph1[i][k]);
                data[i].num = i;
                
                if (graph1[i][k] != 0 && i < k) {
                    ways.push_back();
                    ways[ways.size - 1].push_back(i);
                    ways[ways.size - 1].push_back(k);
                    ways[ways.size - 1].push_back(graph1[i][k]);
                }
                graph[i].push_back(to_string(graph1[i][k]));
            }
            cout << "\n";
        }
    }
    MyGraph(MyVectorVec<int>& graph1) {
        size = graph1.size - 1;
        data = new Node[size];
        graph.push_back();
        for (int i = 0; i < graph1.size-1; i++) {
            data[i].name = graph1[0][i];
            char a = graph1[0][i];
            string str = "";
            str += a;
            graph[0].push_back(str);
            graph.push_back();
            for (int k = 0; k < graph1[i+1].size; k++) {
                data[i].way.push_back(graph1[i+1][k]);
                data[i].num = i;

                if (graph1[i+1][k] != 0 && i < k) {
                    ways.push_back();
                    ways[ways.size - 1].push_back(i);
                    ways[ways.size - 1].push_back(k);
                    ways[ways.size - 1].push_back(graph1[i+1][k]);
                }
                graph[i+1].push_back(to_string(graph1[i + 1][k]));
            }
            cout << "\n";
        }
    }
    MyGraph(MyQueue& que) {
        string str;
        str = que.pop();
        int i = 0;
        size = que.size;
        data = new Node[size];
        string name = "";
        int k = 0;
        graph.push_back();
        while (i < str.size()) {
            while (str[i] != ' ' && i < str.size()) {
                name += str[i];
                i++;
            }
            i++;
            data[k].name = name;
            data[k].num = i;
            k++;
            graph[0].push_back(name);
            name = "";
        }
        k = 0;
        while (que.size != 0) {
            str = que.pop();
            int i = 0;
            int i_str = 0;
            int a = 0;
            graph.push_back();
            while (i_str < str.size()) {
                while (str[i_str] != ' ' && i_str < str.size()) {
                    a = a * 10 + str[i_str] - '0';
                    i_str++;
                }
                i_str++;
                data[k].way.push_back(a);
                if (a != 0 && k < i) {
                    ways.push_back();
                    ways[ways.size - 1].push_back(k);
                    ways[ways.size - 1].push_back(i);
                    ways[ways.size - 1].push_back(a);
                }
                graph[k + 1].push_back(to_string(a));
                a = 0;
                i++;
            }
            k++;
        }
    }
    ~MyGraph() {
        delete[] data;
    }
    void print_data() {
        for (int i = 0; i < size; i++) {
            cout << data[i].name << " ";
        }
        cout << "\n";
        for (int i = 0; i < size; i++) {
            for (int k = 0; k < data[i].way.size; k++) {
                cout << data[i].way[k] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    void kraskal() {
        ways.sort();
        MyVector<int> col;
        int way = 0;
        for (int i = 0; i < size; i++) {
            col.push_back(i);
        }
        for (int i = 0; i < ways.size; i++) {
            if (col[ways.data[i][0]] != col[ways.data[i][1]]) {
                way += ways.data[i][2];
                cout << data[ways.data[i][0]].name << " " << data[ways.data[i][1]].name << "\n";
                
                int color = col[ways.data[i][0]];
                for (int k = 0; k < col.size; k++) {
                    if (col[k] == color) {
                        col[k] = col[ways.data[i][1]];
                    }
                }
            }
        }
        cout << way << "\n";
    }
};

void generate_graph(MyVectorVec<int>& vec, int n) {
    srand(time(NULL));
    char a = 'A';
    for (int i = 0; i < n; i++) {
        vec[0].push_back(a);
        a++;
    }
    for (int i = 1; i <= n; i++) {        
        for (int k = 0; k < n; k++) {
            if (k < i-1) {
                vec[i].push_back(vec[k+1][i-1]);
            }
            else if (i-1 == k) {
                vec[i].push_back(0);
            }
            else {
                vec[i].push_back(rand() % 30);
            }
        }
    }
}

int main()
{
    setlocale(LC_ALL, "ru");

    MyQueue que;
    string line;
    ifstream fin("file.txt");
    if (fin.is_open()) {
        while (getline(fin, line)) {
            que.push(line);
        }
    }
    fin.close();
    
    MyGraph graph(que);

    graph.print_data();
 
    graph.kraskal();
}