#include <iostream>
#include "listFunctions.h"

List::List() // �����������
{
	Head = nullptr;
	Size = 0;
}

void List::CreateList(unsigned Lenght) // �������� ������������ ������
{
	box* HeadItem = nullptr; // ����� ���������� �������� ������
	box* Next = nullptr; // ����� ���������� �� ��������� �������� ������
	for (unsigned i = 1; i <= Lenght; ++i)
	{
		HeadItem = new box;
		HeadItem->Inf = ' ';
		HeadItem->Adr = Next;
		Next = HeadItem;
	}
	Head = HeadItem;
}

box * List::addressGetter() // ��������� ������ ������ �������� ��������
{
	return(Head);
}

void List:: dataInserting(char data) // ���� ������ � ������� ������� ������
{
	Head->Inf = data;
}

void List::sizeOfList(box* Beg) // �������, ���������� ������ ������
{
	while (Beg)
	{
		++Size;
		Beg = Beg->Adr;
	}
}

void List::newItem(unsigned Index) // ���������� ������ �������� � ������
{
	box* Item = new box;
	if (Index==1)	// ���� ����� ������� ����������� � ������ ������
	{
		Item->Adr = Head;
		Head = Item;
	}
	else
	{
		box* PredItem = Head; // �������, ������� ����� ��������� � ������ ����� �����������
		Index--;
		while (PredItem->Adr && (Index--))
			PredItem = PredItem->Adr;
		Item->Adr = PredItem->Adr;
		PredItem->Adr = Item;
	}
}

box* List::getItem(unsigned Index) // ��������� ������ ������������� �������� �� �������
{
	box* Item = Head;
	while (Item && --Index)
		Item = Item->Adr;
	if (!Item) // �������������� ��� ��������� ������� �� ������� ������
		std::cout << "This list item is missing. Try again\n";
	return Item;
}

unsigned List::IndexforData(char data) // ��������� ������� �� �������� ������ ��������
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

void List::DeleteItem(unsigned Index) // ������� ������� �� �������
{
	box* Item = new box;
	if (Index == 1) // ���� ������� ������ ������� ������
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

bool List::isListDataNotEmpty() // �������� ������ �� ������� ������ � ���
{
	if (Head == nullptr) // ���� � Head ������� �����, �� ������ ����
		return 0;
	else				// ���� �������� ���� �� ���� �������, �� ������ �� ����
		return 1;
}

void List::DeleteList() // ������� ������ � ����������� ������
{
	box* Next; // ����� ���������� �� ��������� �������� ������
	while (Head)
	{
		Next = Head->Adr;
		delete Head;
		Head = Next;
	}
}

ArrayList::ArrayList(unsigned size) // �����������
{
	arraySize = size;
	arr = new char[arraySize];
	for (int i = 0; i < arraySize; i++)
	{
		arr[i] = ' ';
	}
}

char * ArrayList::getItem(unsigned Index) // ��������� � �������� �� ��� �������
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

void ArrayList::addData(unsigned Index, char data) // ������ �������� �� �������
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

void ArrayList::deleteItem(unsigned Index) // �������� �������� �������� �� �������
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

unsigned ArrayList::IndexforData(char data) // ��������� ������� �� �������� ��������
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

ArrayList::~ArrayList() // ����������
{
	delete arr;
}