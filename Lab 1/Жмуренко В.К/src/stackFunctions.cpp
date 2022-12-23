#include "listFunctions.h"
#include "stackFunctions.h"

box* stack::push(List& ourList) // Добавление элемента в начало стека
{
	if (ourList.addressGetter() == nullptr) // Случай, когда добавляемый элемент будет единственным в стеке
		ourList.CreateList(1);
	else
		ourList.newItem(1);
	return(ourList.addressGetter());
}

void stack::pop(List& ourList) // Удаление элемента из начала стека
{
	ourList.DeleteItem(1);
}

bool stack::isEmpty(List& ourList) // Проверка стека на пустоту
{
	bool answer = ourList.isListDataNotEmpty();
	return (answer);
}