#pragma once

template <class Type>

class myQueue {
private:

    struct node {
        Type element;
        node* adr = NULL;
        node* adr_pre = NULL;
    };

    int size = 0;
    node* next = NULL;
    node* cur = NULL;
    node* q_head = NULL;
    node* q_tail = NULL;

public:

    myQueue() {};

    bool isEmpty() {
        if (size) return false;
        else return true;
    }

    unsigned int sizeQueue() {
        return size;
    };

    Type pop_front() {
        Type temp = q_head->element;
        cur = q_head;
        q_head = q_head->adr_pre;
        delete cur; size--;
        return temp;
    };

    Type front() {
        return q_head;
    };

    void push(Type element) {
        node* newnode = new node;

        if (size == 0) {
            newnode->adr = NULL;
            newnode->adr_pre = NULL;
            newnode->element = element;
            q_head = newnode;
            q_tail = newnode;
        }
        else {
            q_tail->adr_pre = newnode;
            newnode->adr = q_tail;
            newnode->element = element;

            q_tail = newnode;
        }
        size++;
    };

    ~myQueue() {
        for (unsigned int i = 0; i < size; i++) {
            cur = q_head->adr_pre;
            delete q_head;
            q_head = cur;
        }
    };
};
