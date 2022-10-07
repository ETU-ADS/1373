#pragma once

struct box				// Структура элемента односвязного списка
{
	char Inf;
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
	void dataInserting(char data);	// Ввод данных в верхний элемент списка
	void sizeOfList(box* Beg);	// Функция, получающая размер списка
	void newItem(unsigned Index);	// Добавление нового элемента в список
	box* getItem(unsigned Index);	// Получение адреса определенного элемента по индексу
	unsigned IndexforData(char data); // Получение индекса по значению внутри элемента
	void DeleteItem(unsigned Index);	// Удаляем элемент по индексу
	bool isListDataNotEmpty();	// Проверка списка на наличие данных в нем
	void DeleteList();	// Удаляем список и освобождаем память
};

class ArrayList
{
	char* arr;
	unsigned arraySize;

public:
	
	// Конструктор и деструктор
	ArrayList(unsigned size);
	~ArrayList();

	// Методы, работающие с динамическим массивом
	char * getItem(unsigned Index); // Обращение к элементу по его индексу
	void addData(unsigned Index, char data); // Запись значения по индексу
	void deleteItem(unsigned Index); // Удаление значения элемента по индексу
	unsigned IndexforData(char data); // Получение индекса по значению элемента
};