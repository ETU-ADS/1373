#pragma once
#include "wiseTreesFunctions.h"

class Queue
{
	int size;
	int lastElementPostition;
	AVLnode** infArr;

public:

	Queue(int Size); // Конструктор

	void push(AVLnode* Inf); // Добавление элемента в начало очереди

	void pop(); // Удаление элемента из конца очереди

	AVLnode* peak(); // Взятие элемента с конца очереди

	bool isNotEmpty(); // Проверка очереди на пустоту

	~Queue(); // Деструктор
};