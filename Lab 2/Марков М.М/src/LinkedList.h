#pragma once
#include <iostream>
template <typename type>
class LinkedList {
private:
    struct Node
    {
        Node* nextNode = nullptr;
        type data = 0;
    };
    Node* headNode = nullptr;
    Node* lastNode = nullptr;
    unsigned int size = 0;
public:
    // adds data in the end of list +
    void add(type newData) {
        if (size == 0) {
            headNode = new Node{ nullptr, newData };
            lastNode = headNode;
        }
        else if (size == 1) {
            lastNode = new Node{ nullptr, newData };
            headNode->nextNode = lastNode;
        }
        else {
            Node* tempNode = new Node{ nullptr , newData };
            lastNode->nextNode = tempNode;
            lastNode = tempNode;
        }
        ++size;
    }
    // adds data by index in list, returns 'true' if successful +
    bool addByIndex(unsigned int index, type newData) {
        if ((size == 0 && index == 0) || (index == size)) {
            add(newData);
            return true;
        }
        else if (index == 0) {
            Node* newNode = new Node{ headNode, newData };
            headNode = newNode;
            ++size;
            return true;
        }
        else if (index < size) {
            Node* currNode = headNode;
            for (int i = 1; i < index; ++i) {
                currNode = currNode->nextNode;
            }
            Node* newNode = new Node{ currNode->nextNode, newData };
            currNode->nextNode = newNode;
            ++size;
            return true;
        }
        else return false;
    }
    // search element by data, returns index of finded element, if no match - returns -1 +
    int find(type dataToFind) {
        Node* currNode = headNode;
        int i = 0;
        while (currNode->nextNode) {
            if (currNode->data != dataToFind) {
                currNode = currNode->nextNode;
            }
            else if (currNode->data == dataToFind) {
                return i;
            }
            ++i;
        }
        return -1;
    }
    // deletes element by index, returns 'true' if successful +
    bool deleteElem(unsigned int index) {
        if (index == 0 && size != 0) {
            Node* tempNode = headNode->nextNode;
            delete headNode;
            headNode = tempNode;
            --size;
            return true;
        }
        else if (index < size) {
            Node* currNode = headNode;
            Node* prevNode = currNode;
            for (int i = 0; i < index; ++i) {
                prevNode = currNode;
                currNode = currNode->nextNode;
            }
            prevNode->nextNode = currNode->nextNode;
            delete currNode;
            if (index == size - 1) lastNode = prevNode;
            --size;
            return true;
        }
        else return false;
        
    }
    // get size of list +
    unsigned int length() {
        return size;
    }
    // clears list with deleting elements +
    bool clear() {
        if (size > 0) {
            Node* tempNode;
            do {
                tempNode = headNode->nextNode;
                delete headNode;
                headNode = tempNode;
                --size;
            } while (tempNode);
            lastNode = nullptr;
            return true;
        }
        else return false;
    }
    // merges two lists +
    void merge(LinkedList<type> *list) {
        if (list->size > 0) {
            Node* nodeCopy;
            nodeCopy = list->headNode;
            add(nodeCopy->data);
            for (int i = 1; i < list->size; ++i) {
                nodeCopy = nodeCopy->nextNode;
                add(nodeCopy->data);
            }
        }
    }
    // get element by index +
    type operator[] (unsigned int index){
        if (index < size) {
            Node* currNode = headNode;
            for (int i = 1; i <= index; ++i) {
                currNode = currNode->nextNode;
            }
            return currNode->data;
        }
        else throw "Index out of bounds! Function: LinkedList[]";
    }
    // destructor +
    ~LinkedList() {
        if (size > 0) {
            Node* tempNode;
            int i = 0;
            do {
                tempNode = headNode->nextNode;
                delete headNode;
                headNode = tempNode;
                ++i;               
            } while (tempNode);
            std::cout << "DEBUG LinkedList: Node deleted x " << i << std::endl;
            std::cout << "DEBUG LinkedList: Memory cleared" << std::endl;
        }
    }
};