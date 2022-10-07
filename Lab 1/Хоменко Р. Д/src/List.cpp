#include <iostream>
#include"List.h"
int listOut(List* list, int index)
{
    while (list->adr && (index--))
        list = list->adr;
    return list->data;
}
int listFind(List* list, int data)
{
    int index = 0;
    while (list->adr)
    {
        if (list->data == data)
            return index;
        list = list->adr;
        ++index;
    }
    std::cout << "There are no this data" << std::endl;
    return -1;
}
List* listAdd(List*& beg, int data, int index)
{
    List* item = new List;
    if (!index || !beg)
    {
        beg = item;
        beg->adr = nullptr;
        beg->data = data;
        return item;
    }
    List* prev_item = beg;
    index--;
    while (prev_item->adr && (index--))
        prev_item = prev_item->adr;
    item->adr = prev_item->adr;
    prev_item->adr = item;
    item->data = data;
    return item;
}
void listDell(List*& beg, int index)
{
    List* cur, * prev;
    if (!index)
    {
        cur = beg->adr;
        delete beg;
        beg = cur;
    }
    else
    {
        cur = beg;
        while (--index)
        {
            cur = cur->adr;
        }
        prev = cur;
        cur = cur->adr;
        prev->adr = cur->adr;
        delete cur;
    }
}