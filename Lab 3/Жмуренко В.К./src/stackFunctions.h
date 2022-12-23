#pragma once
#include "listFunctions.h"

class Stack
{
public:
	box* push(List& ourList); // Добавление элемента в начало стека

	void pop(List& ourList); // Удаление элемента из начала стека

	void popForIndex(List& ourList, unsigned Index); // Удаление элемента из стека по его индексу

	bool isNotEmpty(List& ourList); // Проверка стека на пустоту
};