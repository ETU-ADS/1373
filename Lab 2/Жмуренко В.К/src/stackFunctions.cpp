#include "listFunctions.h"
#include "stackFunctions.h"

box* Stack::push(List& ourList) // Добавление элемента в начало стека
{
	if (ourList.addressGetter() == nullptr) // Случай, когда добавляемый элемент будет единственным в стэке
		ourList.CreateList(1);
	else
		ourList.newItem(1);
	return(ourList.addressGetter());
}

void Stack:: pop(List& ourList) // Удаление элемента из начала стека
{
	ourList.DeleteItem(1);
}

void Stack::popForIndex(List& ourList, unsigned Index) // Удаление элемента из стека по его индексу
{
	ourList.DeleteItem(Index);
}

bool Stack::isEmpty(List& ourList) // Проверка стека на пустоту
{
	bool answer = ourList.isListDataNotEmpty();
	return (answer);
}