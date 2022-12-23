#include <iostream>
#include <iomanip>
#include <fstream>
#include "ArrayList.h"
#include "Stack.h"
#include "timsort.h"

struct Edge {
    Edge() : indexA(-1), indexB(-1), weight(-1) {};

    Edge(int a, int b, int w) : indexA(a), indexB(b), weight(w) {};

    bool operator<(Edge const &other) const {
        return weight < other.weight;
    }

    bool operator>(Edge const &other) const {
        return !(*this < other);
    }

    bool operator<=(Edge const &other) const {
        return weight <= other.weight;
    }

    bool operator>=(Edge const &other) const {
        return !(*this <= other);
    }

    bool operator==(Edge const &other) const {
        return weight == other.weight;
    }

    bool operator!=(Edge const &other) const {
        return !(*this == other);
    }


    int indexA;
    int indexB;

    int weight;
};

struct Graph {
    ArrayList<std::string> vertices;
    ArrayList<Edge> edges;
};

void splitString(const std::string &line, ArrayList<std::string> &lineTokens, const std::string &spaceDelimiter = " ") {
    size_t beg = 0;
    size_t end = 0;

    lineTokens.makeEmpty();
    while ((end = line.find(spaceDelimiter, beg)) < line.length()) {
        lineTokens.append(line.substr(beg, end - beg));

        beg = end + spaceDelimiter.length();
    }

    end = line.length() - beg;
    lineTokens.append(line.substr(beg, end)) ;
}

struct Dsu {
    ArrayList<int> parent;
    ArrayList<int> size;

    explicit Dsu(int n) : parent(n), size(n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int x) {
        int root = x;

        while (parent[root] != root) {
            root = parent[root];
        }
        while (parent[x] != root) {
            int tmp = parent[x];
            parent[x] = root;
            x = tmp;
        }

        return root;
    }

    void unite(int x, int y) {
        // Replace nodes by roots
        y = find(y);
        x = find(x);

        if (x == y) {
            return;
        }

// это баг ide
        if (size[x] < size[y]) {
            parent[x] = y;
        } else if (size[x] > size[y]) {
            parent[y] = x;
        } else {
            parent[y] = x;
            size[x]++;
        }
    }
};

void findMst(Graph copied) {
    int mstWeight = 0;
    if (copied.edges.size() == 0) {
        std::cout << "|E| = 0" << std::endl;

        std::cout << std::endl << "Sum(Weight): " << mstWeight << std::endl;
    } else if (copied.edges.size() < copied.vertices.size() - 1) {
        std::cout << "Your graph is definitely not connected..." << std::endl;
    } else {
        copied.edges.sort();

        Dsu dsu(copied.vertices.size());

        int numAdded = 0;
        for (int i = 0; i < copied.edges.size(); i++) {
            int a = copied.edges[i].indexA;
            int b = copied.edges[i].indexB;
            int w = copied.edges[i].weight;

            if (dsu.find(a) != dsu.find(b)) {
                dsu.unite(a, b);

                std::cout << copied.vertices[a] << "—" << copied.vertices[b] << " ";
                mstWeight += w;
                numAdded++;

                if (numAdded == copied.vertices.size() - 1) {
                    std::cout << std::endl << "~Sum(Weight): " << mstWeight << std::endl;
                    return;
                }
            }
        }

        std::cout << "Your graph is not connected..." << std::endl;
    }
}

void graphFromFile(Graph &graph, std::string fileName) {
    // define your file name
    fileName = "../" + fileName;

    // attach an input stream to the wanted file
    std::ifstream input(fileName);

    graph.edges.makeEmpty();
    graph.vertices.makeEmpty();

    if (input.is_open()) {
        std::string line;

        // first line with names of ver
        std::getline(input, line);

//        line[line.size()] = '\0';
        splitString(line, graph.vertices);


        int n = graph.vertices.size();

        int x = 0;

        ArrayList<ArrayList<int>> M;


        std::string spaceDelimiter = " ";
        for (int iRows = 0; std::getline(input, line); iRows++) {
            ArrayList<int> row;
            int iCols = 0;
            line += 'x';
            for (char c: line) {
                if ('0' <= c && c <= '9') {
                    x = x * 10 + (c - '0');
                } else if (c == ' ' || c == '\r' || c == 'x') {
                    row.append(x);
                    x = 0;
                    iCols++;
                } else {
                    std::cout << "unknown symbol!\n";
                }
            }

            M.append(row);
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (M[i][j] != 0) {
                    graph.edges.append(Edge(i, j, M[i][j]));
                }
            }
        }

        input.close();
    }
}


int main() {
std::cout << "FIND MST ALGORITHM" << std::endl << std::endl;
    std::cout << "Do you want to run all test files [1] or enter filename [2]? 1/2" << std::endl;

    int c;
    std::cin >> c;

    switch (c) {
        case 1: {
            ArrayList<Graph> testGraphs;

            ArrayList<std::string> testFilenames;

            testFilenames.append("test.txt");
            testFilenames.append("wiki_1.txt");
            testFilenames.append("wiki_2.txt");
            testFilenames.append("weird.txt");
            testFilenames.append("min.txt");
            testFilenames.append("max.txt");
            testFilenames.append("not_connected.txt");

            for (int i = 0; i < testFilenames.size(); i++) {
                std::cout << testFilenames[i] << std::endl;

                Graph newGraph;
                testGraphs.append(newGraph);
                graphFromFile(testGraphs[i], testFilenames[i]);

                findMst(testGraphs[i]);

                std::cout << std::endl << std::endl;
            }
            break;
        }
        case 2: {
            std::cout << "File: " << std::endl;
            std::string s;
            std::cin >> s;

            Graph newGraph;
            graphFromFile(newGraph, s);

            findMst(newGraph);

            std::cout << std::endl << std::endl;
            break;
        }
        default:
            std::cout << "unknown symbol..." << std::endl;
    }
}
