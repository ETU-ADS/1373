#pragma once

class Queue
{
	int size;
	int lastElementPostition;
	int* infArr;

public:

	Queue(int Size); // Конструктор

	void push(int Inf); // Добавление элемента в начало очереди

	void pop(); // Удаление элемента из конца очереди

	int peak(); // Взятие элемента с конца очереди

	bool isNotEmpty(); // Проверка очереди на пустоту

	~Queue(); // Деструктор
};