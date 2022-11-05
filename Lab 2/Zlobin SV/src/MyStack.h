#pragma once
#include <iostream>
#include "MyRun.h"
using namespace std;

class MyStack
{
public:
    class MyNode {
    public:
        MyRun data;
        MyNode* next = nullptr;
    };
    MyNode* head = nullptr;
    int size = 0;

    MyStack() {
    }
    ~MyStack() {
        MyNode* tmp = head;
        while (head != nullptr) {
            tmp = head->next;
            delete head;
            head = tmp;
        }
    }
    void push(MyRun newData) {
        if (head == nullptr) {
            head = new MyNode;
            head->data = newData;
        }
        else {
            MyNode* tmp = head;
            head = new MyNode;
            head->data = newData;
            head->next = tmp;
        }
        size++;
    }
    void push(MyRun newData, int num) {
        MyNode* tmp = head;
        for (int i = 0; i < num-1; i++)
            tmp = tmp->next;
        if (size >= 2) {
            MyNode* tmp2 = tmp->next->next;
            tmp->next = new MyNode;
            tmp->next->data = newData;
            tmp->next->next = tmp2;
        }
        else {
            tmp->next = new MyNode;
            tmp->next->data = newData;
        }
        size++;
    }
    void pop() {
        if (head != nullptr) {
            MyNode* tmp = head->next;
            delete head;
            head = tmp;
            size--;
        }
        else cout << "Error! Stack is empty" << endl;
    }
    void pop(int num) {
        MyNode* tmp = head;
        for (int i = 0; i < num-1; i++)
            tmp = tmp->next;
        MyNode* tmp2 = tmp->next;
        tmp->next = tmp2->next;
        delete tmp2;
        size--;
    }
    MyRun peak() {
        if (size == 0) {
            exit(0);
        }
        return head->data;
    }
    MyRun peak(int num) {
        if (size == 0) {
            exit(0);
        }
        MyNode* tmp=head;
        for (int i = 0; i < num; i++)
            tmp = tmp->next;
        return tmp->data;
    }
    void print_data() {
        MyNode* tmp = head;
        while (tmp != nullptr) {
            cout << tmp->data.begin << "   " << tmp->data.size << "\n";
            tmp = tmp->next;
        }
        cout << "~~~\n";
    }
};