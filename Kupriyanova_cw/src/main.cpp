#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <fstream>

#define SIZE 50
using namespace std;

template<typename T>
class Arr {//массив для хранения переданных ребер
private:
    T* arr;
    int capacity;
    int size;
public:
    Arr(int arrSize)
    {
        arr = new T[arrSize];
        capacity = arrSize;
        size = arrSize;
    };
    Arr()
    {
        arr = new T[SIZE*SIZE];
        capacity = SIZE*SIZE;
        size = 0;
    };
    ~Arr(){delete[] arr;}
    T& operator[](int i)
    {
        return arr[i];
    };


    int arrCapacity(){
        return capacity;
    }
    int arrSize(){
        return size;
    }

     void swapEdges(int i, int j) //для сортировки вставками
    {
        T temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    
    void addElement(int i, T val)
    {
        if (i<0 || i>=capacity)
            cout<<"Number is out of range!"<<endl;
        else{
            T *tempArr = new T[capacity+1];
            int k = 0;
            for(int j=0; j<capacity; j++){
                if(j==i){
                    tempArr[k]=val;
                    k++;
                }
                tempArr[k]=arr[j];
                k++;
            }
        size++;

        arr = new T[capacity];
        for(int j=0; j<capacity; j++)
              arr[j] = tempArr[j];
        delete [] tempArr;
        }
    }
};

struct Edge 
{
    int start;
    int end;
    int weight;

};

struct Graph 
{
	int nodeCount, edgeCount;
	Arr<Edge> edges;
    Arr<Edge> resMST;


	Graph(int nodeCount, int edgeCount)
	{
		this->nodeCount = nodeCount;
		this->edgeCount = edgeCount;
	}
	int kruskal(string firstRow[]);//а
	void sort();
	void sortByName();
	void traversal(int index, string firstRow[]);
};

struct DisjointSets//система непересекающихся множеств
{
	int *parent, *rnk;
	int n;

	DisjointSets(int n)
	{
		//выделение памяти
		this->n = n;
		parent = new int[n+1];
		rnk = new int[n+1];

		// каждая вершина принадлежит своему мно-ву и ее ранг = 0
		for (int i = 0; i <= n; i++)
		{
			rnk[i] = 0;

			//создание массива, хранящего для каждой вершины дерева ее родителя
			parent[i] = i;
		}
	}

	// ф-я ищет родителя для узла
	int find(int u)
	{
		//все вершины присоединяются к корню
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}

	// объединение: дерево меньшей длины присоединяется к большему
	void merge(int x, int y)
	{
		x = find(x), y = find(y);

		if (rnk[x] > rnk[y])
			parent[y] = x;
		else 
			parent[x] = y;

		if (rnk[x] == rnk[y])
			rnk[y]++;
	}
};

void Graph::traversal(int index,string firstRow[]) //обходы графа
{

        static Arr<int> printedNodes;
        if (index == 0)
            for (int i = 0; i < edgeCount; ++i)
                printedNodes[i] = false;

        printedNodes[index] = true; //
        cout << firstRow[index] << " ";
        for (int i = 0; i < edges.arrSize(); ++i){
            if(edges[i].start == index && printedNodes[edges[i].end] == false)
                traversal(edges[i].end,firstRow);
            else if(edges[i].end == index && printedNodes[edges[i].start] == false)
                traversal(edges[i].start,firstRow);

        }
}

void Graph::sort() //сортировка ребер вставками из 2 лр
{
    for(int k=0;k<edges.arrSize();k++){
        for(int l=k;l>0 && edges[l-1].weight>edges[l].weight;l--)
            edges.swapEdges(l-1,l);
        }
}

void Graph::sortByName() //вывод ребер по порядку при помощи сравнения 1 и 2 индекса
{
    for(int k=0;k<resMST.arrSize();k++){
        for(int l=k;l>0 && resMST[l-1].start>resMST[l].start;l--)
            resMST.swapEdges(l-1,l);
        }
     for(int k=0;k<resMST.arrSize();k++){
        for(int l=k;l>0 && resMST[l-1].end>resMST[l].end && resMST[l-1].start==resMST[l].start;l--)
            resMST.swapEdges(l-1,l);
        }
}

int Graph::kruskal(string firstRow[])//Краскал
{

	int weightResult = 0;
    for(int i=0; i<edgeCount; i++) //вывод неотсорт ребер
        cout<<edges[i].start<<" - "<<edges[i].end<<" : "<<edges[i].weight<<endl;
    sort();//сортируем все ребра по возрастанию
    cout<<"________"<<endl;
    for(int i=0; i<edgeCount; i++) //вывод отсорт ребер
        cout<<edges[i].start<<" - "<<edges[i].end<<" : "<<edges[i].weight<<endl;

	DisjointSets ds(nodeCount);

	Edge r;
	Graph g(nodeCount,edgeCount);
    int el = 0;
	for(int k=0; k<edgeCount;k++) //цикл при добавлении ребра
	{
        int u = edges[k].start;
        int v = edges[k].end;

		int set_u = ds.find(u);
		int set_v = ds.find(v);

		if (set_u != set_v)
		{
		    r.end = v;
		    r.start = u;
		    r.weight = edges[k].weight;
		    g.resMST.addElement(el,r); //передача подходящего ребра в resMST
		    el++;
			//cout << u << " - " << v << endl;
			weightResult+=edges[k].weight;
			ds.merge(set_u, set_v); //слияние
		}
	}
    //for(int i=0; i<el; i++)
       // cout<<g.resMST[i].start<<" - "<<g.resMST[i].end<<" : "<<g.resMST[i].weight<<endl;
    g.sortByName();//для вывода отсортированных по буквам ребер
    cout<<"________"<<endl;
    for(int i=0; i<el; i++)
        cout<<g.resMST[i].start<<" - "<<g.resMST[i].end<<" : "<<g.resMST[i].weight<<endl;

    for(int i=0; i<el; i++)
        cout<<firstRow[g.resMST[i].start]<<" - "<<firstRow[g.resMST[i].end]<<endl; //вывод соотв букв

	return weightResult;
}

int getMatrixSize(string filePath) //получаем размер матрицы из файла при помощи пробела между буквами + 1
{
    string s;
    int i,count=0;
    ifstream file(filePath);
    getline(file,s);
    for(i=0;i<s.size();i++)
        if(s[i]==' ')// \t
            count++;
    return count+1;
}

int main() //чтение из файла
{
    setlocale(LC_ALL, "Russian");
    char divideSymbol = ' ';// \t
    string filePath = "Wiki 1.txt";

    int matrixSize = getMatrixSize(filePath);//получаем размер матрицы из файла

    string eachrow; //считываемая строка
    ifstream myfile(filePath);

    int** matrix = new int*[matrixSize]; //память для матрицы
    for(int i = 0; i < matrixSize; ++i)
        matrix[i] = new int[matrixSize];
    string firstRow[matrixSize];

    int line = 0;
    int m_col = 0;
    int m_row = 0;
    while (getline(myfile, eachrow))
    {
        if(line !=0 ){//для самой матрицы
            for (int i=0; i<eachrow.length();i++)
            {
                int num = 0;
                while (i < eachrow.length() && eachrow[i] != divideSymbol){ //проверка чисел в строке
                    int num_here = (int)eachrow[i]-48;
                    if(num_here >=0 && num_here<=9)
                        num = num * 10 + num_here;
                    else
                        cout<<"WRONG SYMBOLS"<<endl;
                    i+=1;
                }
                matrix[m_col][m_row] = num;
                m_row++;
            }
            m_col++;
            m_row = 0;

        }
        else{//для буквенной строки
            string word; 
            int index = 0;
            for(int i=0; i<eachrow.length(); i++){
                if(eachrow[i]!=divideSymbol){
                    word+=eachrow[i];

                }
                else{
                    firstRow[index] = word;
                    if(i<=eachrow.length())
                        word.clear();
                    index+=1;

                }
            }
            firstRow[index] = word;
        }
        line+=1;
    }
    for(int i=0; i<matrixSize;i++){ //вывод буквенной строки
        cout << firstRow[i] << ' ';
    }
    cout << '\n';

    for(int i=0; i<matrixSize;i++){ //вывод матрицы
        for(int j=0; j<matrixSize;j++){
            cout << matrix[j][i] << ' ';
        }cout << '\n';
    }

	int nodeCount = matrixSize;//число узлов из getMatrixSize
    int edgeCount = 0;
	for(int i=0;i<matrixSize;i++)
	    for(int j=0;j<matrixSize;j++)
                if(matrix[j][i]!=0)
                    edgeCount++;//счетчик ребер с положительными весами


	Graph g(nodeCount, edgeCount);//передача в граф
	Edge r;

	int el = 0; //передача ребра в граф
	for(int i=0;i<matrixSize;i++){
	    for(int j=0;j<matrixSize;j++){
                if(matrix[j][i]!=0){
                    r.start = i;
                    r.end = j;
                    r.weight = matrix[j][i];
                    g.edges.addElement(el,r);
                    el++; 
                }
	    }
	}


	cout << "Edges: \n";
	int mst_wt = g.kruskal(firstRow);

	cout << "\nWeight: " << mst_wt<<endl;
    cout << "\n";

	g.traversal(g.edges[0].start, firstRow);
    cout << "\n";

	return 0;
}
