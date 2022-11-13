#pragma once
#include "LinkedList.h"

template <typename type>
class Stack {
private:
    LinkedList<type> list;
public:
    void pop(){
        if (list.length() > 0) list.deleteElem(list.length()-1);
    }
    void push(type data){
        list.add(data);
    }
    type peak(){
        if (list.length() > 0) return list[list.length() - 1];
    }
    unsigned int size(){
        return list.length();
    }
};