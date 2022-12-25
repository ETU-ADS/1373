#include <string>
#include <iostream>

using namespace std;

class Queue {
public:
    class MyNode {
    public:
        string data;
        MyNode* next = nullptr;
        MyNode* prev = nullptr;
    };
    MyNode* head = nullptr;
    MyNode* end = nullptr;
    int size = 0;

    Queue() {
    }
    ~Queue() {
        MyNode* tmp = head;
        while (head != nullptr) {
            tmp = head->next;
            delete head;
            head = tmp;
        }
    }
    void push(string node) {
        if (head == nullptr) {
            head = new MyNode;
            head->data = node;
            end = head;
        }
        else {
            end->next = new MyNode;
            end->next->prev = end;
            end = end->next;
            end->data = node;
        }
        size++;
    }
    string pop() {
        size--;
        if (size > 0) {
            string tmp = head->data;
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
            return tmp;
        }
        if (size == 0) {
            string tmp = head->data;
            delete head;
            end = nullptr;
            head = nullptr;
            return tmp;
        }
        cout << "Error! Queue is empty\n";
    }
};