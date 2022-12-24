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
		HeadItem->FirstInf = 0;
		HeadItem->SecondInf = 0;
		HeadItem->Adr = Next;
		Next = HeadItem;
	}
	Head = HeadItem;
}

box* List::addressGetter() // Получение адреса самого верхнего элемента
{
	return(Head);
}

void List::dataInserting(int data1, int data2) // Ввод данных в верхний элемент списка
{
	Head->FirstInf = data1;
	Head->SecondInf = data2;
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
	if (Index == 1)	// Если новый элемент добавляется в начало списка
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

unsigned List::IndexforData(int data1, int data2) // Получение индекса по значению внутри элемента
{
	unsigned Index = 0;
	bool isDataExists = 0;
	box* Item = Head;
	while (Item)
	{
		Index++;
		if (Item->FirstInf == data1 && Item->SecondInf == data2)
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