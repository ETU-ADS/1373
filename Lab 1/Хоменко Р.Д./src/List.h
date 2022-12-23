#pragma once
#include <iostream>
struct List
{
    int data;
    List* adr;
};
int listOut(List* list, int index);

int listFind(List* list, int data);

List* listAdd(List*& beg, int data, int index);

void listDell(List*& beg, int index);

