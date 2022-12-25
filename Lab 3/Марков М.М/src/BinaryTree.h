#pragma once
#include <iostream>

#include "DynamicArray.h"
#include "Stack.h"

class BinaryTree {
protected:
    unsigned int treeHeight = 0;
    unsigned int elementsAmount = 0;
    unsigned int dataSize = 4;
    struct Node
    {
        Node* parent = nullptr;
        Node* childLeft = nullptr;
        Node* childRight = nullptr;
        char* data = nullptr;
    };
    Node* root = nullptr;
    DynamicArray<Node*> treeArray;

    // fills tree array
    template <typename type>
    void fillTreeArray(DynamicArray<type*>& arrayToFill, type* root) {
        DynamicArray<type*> tempArray;
        int elementsToAdd = 0;
        if (root) {
            tempArray.add(root);
        }
        for (int i = 0; i < treeHeight; ++i) {
            elementsToAdd += 1 << i;
        }

        for (int i = 0; i < elementsToAdd; ++i) {
            if (tempArray[0]) {
                if (tempArray[0]->childLeft) {
                    tempArray.add(tempArray[0]->childLeft);
                }
                else {
                    tempArray.add(nullptr);
                }
                if (tempArray[0]->childRight) {
                    tempArray.add(tempArray[0]->childRight);
                }
                else {
                    tempArray.add(nullptr);
                }
            }
            else {
                tempArray.add(nullptr);
                tempArray.add(nullptr);
            }
            arrayToFill.add(tempArray[0]);
            tempArray.deleteElem(0);
        }
    }

private:
    unsigned int openCloseBracketsCounter = 0;

    // method to do deep-first search
    void directTraversePrint(Node* node) {
        if (node) {
            directTraversePrint(node->childLeft);
            printNode(node);
            std::cout << ' ';
            directTraversePrint(node->childRight);
        }
        else {
            return;
        }
    }

    // prints data of node
    void printNode(Node* node) {
        if (node) {
            std::cout << (node->data);
        }
        else {
            std::cout << "Nu";
        }
    }

    int findNotBinary(int start, int end, DynamicArray<char>& brackets) {
        int count1 = 0, count2 = 0, maxCount = 0;
        int newStart = start + 1;
        if ((start == end) || (start == end - 1)) {
            return 0;
        }
        
        for (int i = start + 1; i <= end - 1; ++i) {
            if (brackets[i] == '(') {
                ++count1;
            }
            else if (brackets[i] == ')') {
                --count1;
            }
            if (count1 == 0) {
                ++count2;
                int innerCount = findNotBinary(newStart, i, brackets);
                newStart = i + 1;
                if (innerCount > 2) {
                    throw "Not binary tree! Check your input.\n\n";
                }
            }
        }
        return count2;
    }

public:
    // creates tree from special char sequel. For example: (8 (9 (4 (5) (3)) (2 (1))) (65 () (32 (62) (23))))
    void create(char* arrayToParse) {
        unsigned int maxTreeHeight = 0;
        bool isNull = false;
        bool isRightAdd = false;
        bool isEndOfTree = false;
        Node* prevNode = root;
        DynamicArray<char> brackets;

        for (unsigned int i = 0; !isEndOfTree; ++i)
        {
            switch (arrayToParse[i])
            {
            case '(': {
                ++openCloseBracketsCounter;
                brackets.add('(');

                if (arrayToParse[i + 1] == ')') {
                    isNull = true;
                }
                else {
                    ++maxTreeHeight;
                    if (maxTreeHeight > treeHeight) {
                        treeHeight = maxTreeHeight;
                    }
                    isNull = false;
                }
                break;
            }
            case ' ': {
                break;
            }
            case ')': {
                brackets.add(')');
                --openCloseBracketsCounter;

                if (arrayToParse[i + 1] != ')') {
                    isRightAdd = !isRightAdd;
                }
                // if null, we shouldn't go back
                // get back because ')' - end of left adding and start of right add
                if (!isNull) {
                    --maxTreeHeight;
                    prevNode = prevNode->parent;
                }
                break;
            }
            case '\0': {
                isEndOfTree = true;
                break;
            }
            default: {
                unsigned int index = 0;
                // reading all simbols between brackets
                char* tempCharArr = new char[dataSize];
                while (arrayToParse[i] != '(' && arrayToParse[i] != ')' && arrayToParse[i] != ' ')
                {
                    if (index < dataSize) {
                        tempCharArr[index] = arrayToParse[i];
                        ++i;
                        ++index;
                    }
                    else {
                        throw "Incorrect size of data! Try change dataSize";
                    }
                }
                while (index < dataSize) {
                    tempCharArr[index] = '\0';
                    ++index;
                }

                Node* tempNode = new Node;
                tempNode->data = tempCharArr;

                // adding root
                if (elementsAmount == 0) {
                    root = tempNode;
                    root->parent = root;
                }
                // adding left node of root
                else if (elementsAmount == 1) {
                    root->childLeft = tempNode;
                    tempNode->parent = root;
                    prevNode = tempNode;
                }
                // adding left node
                else if (!isRightAdd) {
                    prevNode->childLeft = tempNode;
                    tempNode->parent = prevNode;
                    prevNode = tempNode;
                }
                // adding right node
                else if (isRightAdd) {
                    prevNode->childRight = tempNode;
                    tempNode->parent = prevNode;
                    prevNode = tempNode;
                    isRightAdd = false;
                }
                ++elementsAmount;
                --i;
                break;
            }
            }
        }
        
        if (openCloseBracketsCounter != 0) {
            throw "Missing brackets, can't create a tree! Check your input.\n\n";
        }
        bool isCorrect = false;
        int indexOfFirtsBracket = 0;
        int indexOfLastBracket = brackets.length() - 1;
        findNotBinary(indexOfFirtsBracket, indexOfLastBracket, brackets);

        fillTreeArray<Node>(treeArray, root);
    }

    // returns amount of nodes in tree
    unsigned int getAmountOfElements() {
        return treeArray.length();
    }

    // returns tree height
    unsigned int getHeight() {
        return treeHeight;
    }

    // changes size of array to store data
    void changeDataSize(unsigned int newSize) {
        dataSize = newSize;
    }

    // prints result of deep-first search
    void printWithDepthFirstSearch() {
        directTraversePrint(root);
        std::cout << '\n';
    }

    // returns data in root node
    char* getRootData() {
        return root->data;
    }

    // returns root of tree
    Node* getRoot(){
        return root;
    }

    // prints array with tree
    void printTreeArray() {
        for (int i = 0; i < treeArray.length(); ++i) {
            printNode(treeArray[i]);
            std::cout << ' ';
        }
        std::cout << '\n';
    }

    void draw() {
        int amountOfElOnLastLevel = 1 << treeHeight;
        for (int i = 0; i < treeHeight; ++i) {
            for (int j = 0; j < amountOfElOnLastLevel / ((1 << i) + 1); ++j) {
                std::cout << ' ';
            }
            for (int k = (1 << i) - 1; k < (1 << i) + (1 << i) - 1; ++k) {
                printNode(treeArray[k]);
                for (int j = 0; j < amountOfElOnLastLevel / ((1 << i) + 1); ++j) {
                    std::cout << ' ';
                }
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    ~BinaryTree() {
        for (int i = 0; i < treeArray.length(); ++i) {
            if (treeArray[i]) {
                delete[] (treeArray[i]->data);
                delete treeArray[i];
            }
        }
    }
};