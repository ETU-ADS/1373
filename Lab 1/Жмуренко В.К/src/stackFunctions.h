#pragma once
class stack
{
public:
	//Методы
	box* push(List& ourList); // Добавление элемента в начало стека
	void pop(List& ourList); // Удаление элемента из начала стека
	bool isEmpty(List& ourList); // Проверка стека на пустоту
};