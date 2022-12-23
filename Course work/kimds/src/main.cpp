#include <iostream>
#include "DynamicArray.h"
#include <string>
#include <fstream>
#include "Queue.h"

using namespace std;

struct Rib {
	int weight;
	int begin;
	int finish;
};

class Graph {
	DynamicArray<Rib> ribs;
	DynamicArray<Rib> min;
	DynamicArray<string> peaks;
	DynamicArray<int> p;
	DynamicArray<int> rank;
	
	void makeSet(int x) {
		p.PushBack(x);
		rank[x] = 0;
	}

	int Find(int x) {
		return (x == p[x] ? x : p[x] = Find(p[x]));
	}

	void Union(int x, int y) {
		if ((x = Find(x)) == (y = Find(y))) {
			return;
		}
		if (rank[x] < rank[y]) {
			p[x] = y;
		}
		else {
			p[y] = x;
			if (rank[x] == rank[y]) {
				++rank[x];
			}
		}
	}

	void Sort() {
		Rib data;
		int j;
		for (int i = 1; i < ribs.GetSize(); i++) {
			data = ribs[i];
			j = i - 1;
			while (j >= 0 && ribs[j].weight > data.weight) {
				ribs[j + 1] = ribs[j];
				j--;
			}
			ribs[j + 1] = data;
		}
	}

public:
	void readFile(string file) {
		string line, storage;
		ifstream fin(file);
		getline(fin, line);
		for (int i = 0; i < line.size(); i++) {
			storage.append(line, i, line.find_first_of(" ", i) - i);
			peaks.PushBack(storage);
			storage = "";
			i = line.find_first_of(" \n", i);
			if (i == -1) {
				break;
			}
		}
		Rib rib;
		for (int j = 0; j < peaks.GetSize() - 1; j++) {
			getline(fin, line);
			int finish = 0;
			for (int i = 0; i < line.size(); i++) {
				storage = "";
				storage.append(line, i, line.find_first_of(" ", i) - i);
				i = line.find_first_of(" ", i);
				if (storage != "0" && i == -1) {
					rib.begin = j;
					rib.finish = finish++;
					rib.weight = stoi(storage);
					ribs.PushBack(rib);
					break;
				}
				else if (storage == "0" && i == -1) {
					break;
				}
				if (storage == "0" || finish <= j) {
					finish++;
					continue;
				}
				rib.begin = j;
				rib.finish = finish++;
				rib.weight = stoi(storage);
				ribs.PushBack(rib);
			}
		}
		fin.close();
	}
	
	void print() {
		int weight = 0;
		for (int i = 0; i < min.GetSize(); i++) {
			cout << peaks[min[i].begin] << " " << peaks[min[i].finish] << endl;
			weight += min[i].weight;
		}
		cout << weight << endl;
	}

	void kraskal() {
		int first, second;
		Sort();
		for (int i = 0; i < peaks.GetSize(); i++) {
			rank.PushBack(0);
		}
		for (int i = 0; i < peaks.GetSize(); i++) {
			makeSet(i);
		}
		for (int i = 0; min.GetSize() < peaks.GetSize() - 1; i++) {
			first = Find(ribs[i].begin);
			second = Find(ribs[i].finish);
			if (first != second) {
				min.PushBack(ribs[i]);
				Union(first, second);
			}
		}
		print();
	}

	void dfs(int u = 0) {
		static DynamicArray<bool> visited;
		if (u == 0) {
			for (int i = 0; i < ribs.GetSize(); i++) {
				visited.PushBack(0);
			}
		}
		visited[u] = 1;
		cout << peaks[u] << " ";
		for (int i = 0; i < ribs.GetSize(); i++) {
			if (ribs[i].begin == u && visited[ribs[i].finish] == 0) {
				dfs(ribs[i].finish);
			}
			else if (ribs[i].finish == u && visited[ribs[i].begin] == 0) {
				dfs(ribs[i].begin);
			}
		}
	}

	void bfs() {
		Queue<int> queue(15);
		DynamicArray<bool> was;
		int u;
		for (int i = 0; i < ribs.GetSize(); i++) {
			was.PushBack(0);
		}
		queue.push(0);
		was[0] = 1;
		while (!queue.empty()) {
			u = queue.pop();
			for (int i = 0; i < ribs.GetSize(); i++) {
				if (ribs[i].begin == u && was[ribs[i].finish] == 0) {
					queue.push(ribs[i].finish);
					was[ribs[i].finish] = 1;
				}
				else if (ribs[i].finish == u && was[ribs[i].begin] == 0) {
					queue.push(ribs[i].begin);
					was[ribs[i].begin] = 1;
				}
			}
			cout << peaks[u] << " ";
		}
		cout << endl;
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	Graph graph;
	graph.readFile("graph2.txt");
	cout << "dfs: ";
	graph.dfs();
	cout << endl;
	cout << "bfs: ";
	graph.bfs();
	cout << endl;
	graph.kraskal();
}

