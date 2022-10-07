#include <iostream>
#include "listFunctions.h"

List::List() // Конструктор
{
	Head = nullptr;
	Size = 0;
}

void List::CreateList(unsigned Lenght) // Создание односвязного списка
{
	box* HeadItem = nullptr; // Адрес очередного элемента списка
	box* Next = nullptr; // Адрес следующего за очередным элемента списка
	for (unsigned i = 1; i <= Lenght; ++i)
	{
		HeadItem = new box;
		HeadItem->Inf = ' ';
		HeadItem->Adr = Next;
		Next = HeadItem;
	}
	Head = HeadItem;
}

box * List::addressGetter() // Получение адреса самого верхнего элемента
{
	return(Head);
}

void List:: dataInserting(char data) // Ввод данных в верхний элемент списка
{
	Head->Inf = data;
}

void List::sizeOfList(box* Beg) // Функция, получающая размер списка
{
	while (Beg)
	{
		++Size;
		Beg = Beg->Adr;
	}
}

void List::newItem(unsigned Index) // Добавление нового элемента в список
{
	box* Item = new box;
	if (Index==1)	// Если новый элемент добавляется в начало списка
	{
		Item->Adr = Head;
		Head = Item;
	}
	else
	{
		box* PredItem = Head; // Элемент, который будет находится в списке перед добавленным
		Index--;
		while (PredItem->Adr && (Index--))
			PredItem = PredItem->Adr;
		Item->Adr = PredItem->Adr;
		PredItem->Adr = Item;
	}
}

box* List::getItem(unsigned Index) // Получение адреса определенного элемента по индексу
{
	box* Item = Head;
	while (Item && --Index)
		Item = Item->Adr;
	if (!Item) // Предупреждение при отсутсвии индекса по данному номеру
		std::cout << "This list item is missing. Try again\n";
	return Item;
}

unsigned List::IndexforData(char data) // Получение индекса по значению внутри элемента
{
	unsigned Index=0;
	bool isDataExists = 0;
	box* Item = Head;
	while (Item)
	{
		Index++;
		if (Item->Inf == data)
		{
			isDataExists = 1;
			break;
		}
	}
	if (isDataExists == 0)
	{
		std::cout << "\nThere is no list element with such data\n";
		return 0;
	}
	else
		return Index;
}

void List::DeleteItem(unsigned Index) // Удаляем элемент по индексу
{
	box* Item = new box;
	if (Index == 1) // Если удаляем первый элемент списка
	{
		Item = Head->Adr;
		delete Head;
		Head = Item;
	}
	else
	{
		Index--;
		Item = getItem(Index);
		box* DelItem = Item->Adr;
		Item->Adr = DelItem->Adr;
		delete DelItem;
	}
}

bool List::isListDataNotEmpty() // Проверка списка на наличие данных в нем
{
	if (Head == nullptr) // Если у Head нулевой адрес, то список пуст
		return 0;
	else				// Если остается хотя бы один элемент, то список не пуст
		return 1;
}

void List::DeleteList() // Удаляем список и освобождаем память
{
	box* Next; // Адрес следующего за очередным элемента списка
	while (Head)
	{
		Next = Head->Adr;
		delete Head;
		Head = Next;
	}
}

ArrayList::ArrayList(unsigned size) // Конструктор
{
	arraySize = size;
	arr = new char[arraySize];
	for (int i = 0; i < arraySize; i++)
	{
		arr[i] = ' ';
	}
}

char * ArrayList::getItem(unsigned Index) // Обращение к элементу по его индексу
{
	if (Index >= 0 && Index < arraySize)
	{
		return(&arr[Index]);
	}
	else
	{
		std::cout << "\nThis array item is missing. Try again\n";
	}
}

void ArrayList::addData(unsigned Index, char data) // Запись значения по индексу
{
	if (Index >= 0 && Index < arraySize)
	{
		arr[Index] = data;

	}
	else
	{
		std::cout << "\nThis array item is missing. Try again\n";
	}
}

void ArrayList::deleteItem(unsigned Index) // Удаление значения элемента по индексу
{
	if (Index >= 0 && Index < arraySize)
	{
		if (Index == 0)
		{
			for (int i = 1; i < (arraySize - 1); i++)
			{
				arr[i - 1] = arr[i];
			}
			arraySize--;
		}
		else
		{
			for (int i = Index; i < (arraySize - 1); i++)
			{
				arr[i - 1] = arr[i];
			}
			arraySize--;
		}
	}
	else
	{
		std::cout << "\nThis array item is missing. Try again\n";
	}
}

unsigned ArrayList::IndexforData(char data) // Получение индекса по значению элемента
{
	unsigned Index = 0;
	bool isDataExists = 0;
	for (int i = 0; i < arraySize; i++)
	{
		if (arr[i] == data)
		{
			isDataExists = 1;
			break;
		}
		Index++;
	}
	if (isDataExists == 0)
		std::cout << "\nThere is no array element with such data\n";
	else
		return Index;
}

ArrayList::~ArrayList() // Деструктор
{
	delete arr;
}