#include "listFunctions.h"
#include "stackFunctions.h"

 box * push(List & ourList) // ���������� �������� � ������ �����
{
	if (ourList.addressGetter() == nullptr) // ������, ����� ����������� ������� ����� ������������ � �����
		ourList.CreateList(1);
	else
		ourList.newItem(1);
	return(ourList.addressGetter());
}

void pop(List & ourList) // �������� �������� �� ������ �����
{
	ourList.DeleteItem(1);
}

bool isEmpty(List & ourList) // �������� ����� �� �������
{
	bool answer = ourList.isListDataNotEmpty();
	return (answer);
}