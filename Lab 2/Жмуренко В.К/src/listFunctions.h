#pragma once
struct box				// Структура элемента односвязного списка
{
	int FirstInf, SecondInf;
	box* Adr;
};

class List
{
	box* Head;
	unsigned Size;

public:

	// Конструктор
	List();

	// Методы, работающие с односвязным списком
	void CreateList(unsigned Lenght);	// Создание односвязного списка
	box* addressGetter();	// Получение адреса самого верхнего элемента
	void dataInserting(int data1, int data2);	// Ввод данных в верхний элемент списка
	void sizeOfList(box* Beg);	// Функция, получающая размер списка
	void newItem(unsigned Index);	// Добавление нового элемента в список
	box* getItem(unsigned Index);	// Получение адреса определенного элемента по индексу
	unsigned IndexforData(int data1, int data2); // Получение индекса по значению внутри элемента
	void DeleteItem(unsigned Index);	// Удаляем элемент по индексу
	bool isListDataNotEmpty();	// Проверка списка на наличие данных в нем
	void DeleteList();	// Удаляем список и освобождаем память
};