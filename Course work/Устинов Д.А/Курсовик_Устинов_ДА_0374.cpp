#include <iostream>
#include <fstream>
#include <string>

#define MaxVertex 50
#define INF 1023


typedef class MGraph* Graph;
typedef int Vertex;

using namespace std;

class Edge
{
public:
	int v1, v2;
	int weight;
	int E[MaxVertex];// ������� ������
};

class MGraph :public Edge
{
public:
	void Build(Graph Gra, int i, int temp, int first[MaxVertex][MaxVertex]);
	int FindMin(Graph Gra);
	Vertex Find(Graph Gra, Vertex v);
	bool Union(Graph Gra, Vertex v, Vertex w);
	void Kruskal(Graph Gra);
	void Output(Graph Gra, string row[MaxVertex]);
private:
	int G[MaxVertex][MaxVertex];
	int parent[MaxVertex];// � ��������� �����
	int MST[MaxVertex];// ����������� �������� ������
	int sum;// ��� 
	int Nv;
	int Ne;
};
// �������������
void MGraph::Build(Graph Gra, int i, int temp, int first[MaxVertex][MaxVertex])
{
	Vertex v1, v2;
	int weight;
	Gra->sum = 0;
	Gra->Nv = i;
	cout << "���������� ������ : ";
	cout << Gra->Nv;
	for (Vertex v = 1; v <= Gra->Nv; v++)
	{
		for (Vertex w = 1; w <= Gra->Nv; w++)
			Gra->G[v][w] = 0;
		Gra->parent[v] = -1;
	}
	cout << endl << endl;
	
	Gra->Ne = temp;
	cout << "���������� ����� : ";
	cout << Gra->Ne;
	Vertex v = 1;
	cout << "\n\n������� ����� <v1, v2> � ��������������� ��� : " << endl;
	while (v <= Gra->Ne)
	{
		//cin >> v1 >> v2 >> weight;
		for (int i = 0; (i < Gra->Nv); i++)
		{
			v1 = i+1;
			for (int j = 0; (j < Gra->Nv); j++)
			{
				
				v2 = j+1;
				if ((first[i][j] != 0) && ((i == j) || (first[i][j] == first[j][i])))
				{		
					weight = first[i][j];
					Gra->weight = weight;
					Gra->E[v] = weight;
					Gra->G[v1][v2] = weight;// �������������� ����
					Gra->G[v2][v1] = weight;
					cout << Gra->G[v1][v2] << " ";
					v++;
				}
				else if (first[i][j] != 0)
				{
					weight = first[i][j];
					Gra->weight = weight;
					Gra->E[v] = weight;
					Gra->G[v1][v2] = weight;
					cout << Gra->G[v1][v2] << " ";
					v++;
				}
			}
			cout << endl;
		}
	}
}
// ������� ���������� � ��������� �����, ������� � ���������� ����������
int MGraph::FindMin(Graph Gra)
{
	Vertex v, w;
	int min = INF;// ����������
	for (v = 1; v <= Gra->Nv-1; v++)// ������ ��� ����� ��������� ������ ���� ������������ ����, ����� ������� ������� ������ ����
		for (w = v+1; w <= Gra->Nv; w++)
		{
			if (Gra->G[v][w] < min && Gra->G[v][w] != 0)
			{
				min = Gra->G[v][w];
				Gra->v1 = v;
				Gra->v2 = w;
			}
		}
	return min;
}
// � ��������� �������� ��������
Vertex MGraph::Find(Graph Gra, Vertex v)
{
	if (Gra->parent[v] < 0)
		return v;
	else
		return Gra->parent[v] = Find(Gra, Gra->parent[v]);
}

bool MGraph::Union(Graph Gra, Vertex v, Vertex w)
{
	v = Find(Gra, v);
	w = Find(Gra, w);
	if (v != w)
	{
		if (Gra->parent[v] < Gra->parent[w]) {
			Gra->parent[v] += Gra->parent[w];
			Gra->parent[w] = v;
		}
		else {
			Gra->parent[w] += Gra->parent[v];
			Gra->parent[v] = w;
		}
		return true;
	}
	else
		return false;

}
// �������� ��������
void MGraph::Kruskal(Graph Gra)
{
	int i = 0;// �������� ���� ������
	int E = 0;
	Gra->MST[MaxVertex-1] = {};// ������ �����
	while (i < Gra->Nv - 1 && FindMin(Gra) != INF)// ���� ������ ������ ��� Nv-1, � ��� ��� ���� �����
	{
		E = FindMin(Gra);
		Gra->G[Gra->v1][Gra->v2] = INF;// ���������� ��� ��������
		if (Union(Gra, Gra->v1, Gra->v2))// �� ������������ ����� ����
		{
			i++;
			Gra->MST[i] = E;// ������ ������
			Gra->sum += E;
		}
		else;// ���������� ��� �������

	}
	if (i < Gra->Nv - 1)
		*Gra->MST = NULL;
}
//�����
void MGraph::Output(Graph Gra, string row[MaxVertex])
{
	if (*Gra->MST == NULL)
	{
		cout << "������������ ��������� ������ �� ����������" << endl;
	}
	else
	{
		cout << "������� ��������� : " << endl;
		for (int i = 1; i <= Gra->Nv - 1; i++)
			cout << Gra->MST[i] << " ";
		cout << endl;
		cout << "����� �����:" << Gra->sum << endl;
		cout << "Spanning Tree:" << endl;
		for (Vertex v = 1; v <= Gra->Nv-1; v++)
		{

			cout << row[v-1] << "--" << row[Gra->parent[v]-1] << endl;
		}
	}
}
int main()
{
	setlocale(LC_ALL, "rus");

	MGraph MG;
	Graph Gra = new MGraph;

	string line = "", row[MaxVertex];
	int i = 0 , j = 0, k = 0, temp = 0, first[MaxVertex][MaxVertex];
	char ch = ' ';

	string path = "grafout.txt";

	ifstream in;
	in.open(path);
	if (!in.is_open())
	{
		cout << "������ �������� �����!" << endl << endl;
	}
	else
	{
		cout << "Open" << endl;
		
		while (!in.eof())
		{
			
			while ((ch != '\n') && (in >> row[i]) && i < MaxVertex)
			{
				
				cout << row[i] << " ";
				in.get(ch);
				i++;
			}
			
			cout << endl;	
			ch = ' ';

			while ( j < i)
			{
				k = 0;
				while (k < i)
				{
					in >> first[j][k];
					if (first[j][k] != 0)
						temp++;
					cout << first[j][k] << " ";
					k++;
					
					in.get(ch);
					
				}
				j++;
				
				cout << endl;
			}				

		}
	}
	in.close();
	cout << '\n';
	MG.Build(Gra, i, temp, first);
	MG.Kruskal(Gra);
	MG.Output(Gra, row);
	delete Gra;
	return 0;
}