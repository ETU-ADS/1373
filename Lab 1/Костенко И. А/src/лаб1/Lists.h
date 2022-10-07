#pragma once
template<typename T>
struct Item
{
	T field;
	Item* next;
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
	Item<T>* head;
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
};

