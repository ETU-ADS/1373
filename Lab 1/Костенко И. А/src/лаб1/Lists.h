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
	Item<T>* head = new Item<T>();//корень списка

public:
	LinkedList();
	LinkedList(const int count);
	~LinkedList();
	Item<T>& operator[](int index);
	bool deleteItem(unsigned pos);//удаление по индексу
	unsigned find(T item);//поиск индекса.
	bool add(T field, unsigned index);//вставка по индексу.
	unsigned size();//получить размер списка
	void print();//вывод
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
	void push(T item);//добавление элемента в вверх стека
	void print();
	T pop();//достаём элемент
	T peak();//получаем значение верхнего элемента стека

	bool isEmpty();//проверка на пустоту 
};

template<typename T>
class ArrayList
{
public:

	void add(T field, int index);//добавляем по индексу
	void add(T field);//добавляем в конец
	void deleteItem(int index);//удаляем по индексу
	unsigned find(T index);//поиск по значение
	int size();//
	void print();
	T getLast();//получаем последний элемент
	T& operator[](int index);
	ArrayList();
	ArrayList(int count);//создаём массив длиной count
	~ArrayList();

private:
	T* arr = nullptr;
	int lastItemIndex = 0;//индекс будущего последнего элемента
	int maxSize = 0;//максимальный размер 
	void expansionArr();
};

