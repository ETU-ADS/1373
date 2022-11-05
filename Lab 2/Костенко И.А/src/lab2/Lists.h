#pragma once
template<typename T>
struct Item
{
	T field;
	Item* next;
};

struct Interval
{
	int start;//in
	int finish;//out
};
template<typename T>
class LinkedList
{
private:
	Item<T>* head = new Item<T>();//������ ������

public:
	LinkedList();
	LinkedList(const int count);
	~LinkedList();
	Item<T>& operator[](int index);
	bool deleteItem(unsigned pos);//�������� �� �������
	unsigned find(T item);//����� �������.
	bool add(T field, unsigned index);//������� �� �������.
	unsigned size();//�������� ������ ������
	void print();//�����
};

template<typename T>
class Stack
{
private:
	Item<T>* head = (0, nullptr);
public:
	Stack();
	Stack(const int count);
	~Stack();
	void push(T item);//���������� �������� � ����� �����
	void print();
	T pop();//������ �������
	T peak();//�������� �������� �������� �������� �����

	bool isEmpty();//�������� �� ������� 
};

template<typename T>
class ArrayList
{
public:

	void add(T field, int index);//��������� �� �������
	void add(T field);//��������� � �����
	void deleteItem(int index);//������� �� �������
	unsigned find(T index);//����� �� ��������
	void insertionSort(int left, int right);
	void insertArray(T* buffer, int length);
	void merge(int leftBarrier, int rightBarrier, int secondEndIndex);
	void timsort();
	int size();//
	void print();
	T getLast();//�������� ��������� �������
	T& operator[](int index);
	ArrayList();
	ArrayList(int count);//������ ������ ������ count
	~ArrayList();

private:
	T* arr = nullptr;
	int lastItemIndex = 0;//������ �������� ���������� ��������
	int maxSize = 0;//������������ ������ 
	void expansionArr();
	int calculateMinRun(int arraySize);
};
