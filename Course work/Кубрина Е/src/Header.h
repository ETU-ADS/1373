#pragma once
#define CAPACITY 2
#include <iostream>
#include <fstream>
#include <string>
using namespace std; 


template <typename T>
class _vector {
private:
	T* mas;
	int size;
	int realSize;
	int capacity;

	//проверка массива на заполнение
	bool checkForCompletion() {
		if (size == realSize) {
			return true;
		}
		else { return false; }
	}
	bool checkForCompletion(int _size) {
		if (_size == realSize) {
			return true;
		}
		else { return false; }
	}
	//создание нового массива после заполнения старого
	void newMas() {
		T* temp = new T[size * capacity];
		for (int i = 0; i < size; i++) {
			temp[i] = mas[i];
		}
		mas = temp;
		realSize = size * capacity;
	}
public:
	//конструктор копирования
	/*_vector(_vector <T>& temp) {
		for (int i = 0; i < temp.getSize(); i++) {
			push(temp[i], i);
		}
		size = temp.getSize();
		capacity = temp.getCapacity();
		realSize = size * capacity;

	}*/
	//оператор копирования
	/*_vector operator=(_vector temp) {
		for (int i = 0; i < temp.getSize(); i++) {
			push(temp[i], i);
		}
		size = temp.getSize();
		capacity = temp.getCapacity();
		realSize = size * capacity;
		return *this;
	}*/
	_vector() {
		size = 0;
		capacity = CAPACITY;
		realSize = capacity;
		mas = new T[capacity];
	}
	_vector(int _size) {
		size = _size;
		capacity = CAPACITY;
		realSize = _size * capacity;
		mas = new T[realSize];

	}
	//возвращает размер массива
	int getSize() { return size; }
	//возвращает количество элементов которые может содержать массив без выделения дополнительной памяти
	int getCapacity() {
		if (size == 0) { return capacity; }
		else { return realSize; }
	}

	//перегрузка оператора []
	T& operator [](int index) {
		if (index >= 0 && index < size) {
			return mas[index];
		}
	}

	int find(T data) {
		for (int i = 0; i < size; i++) {
			if (mas[i] == data) {
				return i;
			}

		}
		cout << "Error:element not found";
		return 0;
	}

	//вставка в конец массива
	void push_back(T temp) {
		if (checkForCompletion()) {
			newMas();
		}
		mas[size] = temp;
		size++;

	}
	//вставка элемента по индексу
	void push(T temp, int index) {
		if (index >= 0 && index < size) {
			int tmp;
			if (checkForCompletion(size + 1)) {
				newMas();
			}
			for (int i = 0; i < size + 1; i++) {
				if (i == index) {
					tmp = mas[i];
					mas[i] = temp;
					i++;
					while (i < size + 1) {
						temp = tmp;
						tmp = mas[i];
						mas[i] = temp;
						i++;
					}
					size++;
					return;
				}
			}
		}
		else {
			cout << "Error::array out of bounds";
		}
	}

	//Удаление по индексу
	void erase(int index) {
		if (index >= 0 && index < getSize()) {
			for (int i = index; i < getSize() - 1; i++) {
				mas[i] = mas[i + 1];
			}
			size--;
			realSize = size * capacity;
		}
		else {
			cout << "Error::array out of bounds";
		}

	}

	void SortMas() {
		int temp;
		for (int i = 1, j; i < size; i++) {
			j = i;
			while (j > 0 && mas[j] < mas[j - 1]) {
				temp = mas[j];
				mas[j] = mas[j - 1];
				mas[j - 1] = temp;
				j--;
			}

		}
	}

	/*~_vector() {
		delete mas;
	}*/
};



class Kraskal {
private:
	struct Vertex {
		string key;
		_vector<int> path;
	};
	struct Edge {
		string st;
		string fin;
		int weight;
	};
	_vector<Vertex> adj_matrix;
	_vector<Edge> edge;
	
public:

	//парсим матрицу смежности из файла
	void load_from_file() {
		
		ifstream f("Wiki 1.txt");
		string temp;
		int num;
		Vertex v;
		if (f.is_open()) {
			while (!f.eof()) {
				
				f >> temp;
				if (temp[0] < '0' || temp[0] > '9') {
					v.key = temp;
					adj_matrix.push_back(v);
				}
				else {
					break;
				}
			}
			num = 0;
			for (int k = 0; k < temp.size(); k++) {
				num = num * 10 + (temp[k] - '0');
			}
			adj_matrix[0].path.push_back(num);
			while (!f.eof()) {
				for (int i = 0; i < adj_matrix.getSize(); i++) {
					for (int j = 0; j < adj_matrix.getSize(); j++) {
						if (i == 0 && j == 0) {
							j++;
						}
						num = 0;
						f >> temp;
						for (int k = 0; k < temp.size(); k++) {
							num = num * 10 + (temp[k] - '0');
						}
						adj_matrix[i].path.push_back(num);
					}
					
				}
			}
		}
			f.close();
	}


	//собираем массив ребер
	void setEdge() {
		
		Edge temp;
		for (int i = 0; i < adj_matrix.getSize()-1; i++) {
			for (int j = 1+i; j < adj_matrix[i].path.getSize(); j++) {
				if (adj_matrix[i].path[j] != 0) {
					temp.st = adj_matrix[i].key;
					temp.fin = adj_matrix[j].key;
					temp.weight = adj_matrix[i].path[j];
					edge.push_back(temp);
				}
				
			}
		}
	}
	
	//сортируем массив ребер
	void SortEdge() {
		Edge temp;
		for (int i = 1, j; i < edge.getSize(); i++) {
			j = i;
			while (j > 0 && edge[j].weight < edge[j - 1].weight) {
				temp = edge[j];
				edge[j] = edge[j - 1];
				edge[j - 1] = temp;
				j--;
			}

		}
	}

	//рисуем матрицу смежности
	void printMatrix() {
		
		for (int i = 0; i < adj_matrix.getSize(); i++) {
			cout << adj_matrix[i].key<<" ";
		}
		cout << endl;
		for (int i = 0; i < adj_matrix.getSize(); i++) {
			for (int j = 0; j < adj_matrix[i].path.getSize(); j++) {
				cout << adj_matrix[i].path[j] << " ";
			}
			cout << endl;
		}
	}
	
	//рисуем переданный массив ребер
	void printEdge(_vector<Edge> edge) {
		
		for (int i = 0; i < edge.getSize(); i++) {
			cout << edge[i].st << " " << edge[i].fin  <<endl;

		}
	}

	//рисуем массив ребер
	void printEdge() {
		for (int i = 0; i < edge.getSize(); i++) {
			cout << edge[i].st << edge[i].fin << " " << edge[i].weight << endl;

		}
	}
	
	//ищем номер вершины
	int findIt(string temp) {
		for (int i = 0; i < adj_matrix.getSize(); i++) {
			if (adj_matrix[i].key == temp) {
				return i;
			}
		}
	}

	//карскаль
	void karscal() {
		_vector<Edge> eg;
		_vector<int> ver;
		int w = 0;
		for (int i = 0; i < adj_matrix.getSize(); i++) {
			ver.push_back(i);
		}
		eg.push_back(edge[0]);
		
		w += edge[0].weight;
		coloring(ver, eg);
		for (int i = 1; i < edge.getSize(); i++) {
			if (checkEdge(i, ver)) {
				eg.push_back(edge[i]);
				w += edge[i].weight;
				coloring(ver, eg);
			}
		}

		printEdge(eg);
		cout <<w << endl;
	}

	//перекраска вершин
	void coloring(_vector<int> &ver, _vector<Edge> &eg) {
		int temp;
		if (ver[findIt(eg[eg.getSize() - 1].st)]> ver[findIt(eg[eg.getSize() - 1].fin)]) {
			temp = ver[findIt(eg[eg.getSize() - 1].fin)];
			for (int i = 0; i < ver.getSize(); i++) {
				if (ver[i] == temp){
					ver[i] = ver[findIt(eg[eg.getSize() - 1].st)];
				}
			}
			
		}
		else {
			temp = ver[findIt(eg[eg.getSize() - 1].st)];
			for (int i = 0; i < ver.getSize(); i++) {
				if (ver[i] == temp) {
					ver[i] = ver[findIt(eg[eg.getSize() - 1].fin)];
				}
			}
			
		}
	}
	//проверка на пересечение множеств
	bool checkEdge(int i, _vector<int> ver) {
		if (ver[findIt(edge[i].st)] == ver[findIt(edge[i].fin)]) {
			return false;
		}
		return true;
	}


};