#pragma once
#include "BinaryTree.h"

class RBTree : public BinaryTree {
private:
    struct RBNode {
        RBNode* parent = nullptr;
        RBNode* childLeft = nullptr;
        RBNode* childRight = nullptr;
        bool color = false; // true - red, false - black
        int data = 0;
    };

    RBNode* root;
    DynamicArray<int> treeDataArray;

    // check and rebalance for adding
    void balanceTreeForAdd(RBNode* newNode){

        if (newNode->parent->color) {
            RBNode* parent = newNode->parent;
            RBNode* grandparent = parent->parent;
            RBNode* uncle = grandparent->childRight;
            bool isGrandLeftSide = true;
            bool isParentLeftSide = true;
            bool uncleColor = false;

            if (grandparent->childRight == parent) {
                uncle = grandparent->childLeft;
                isGrandLeftSide = false;
            }
            if (parent->childRight == newNode) {
                isParentLeftSide = false;
            }

            if (uncle) {
                uncleColor = uncle->color;
            }

            // first case add
            if ((!grandparent->color) && parent->color && (uncleColor)) {
                parent->color = false;
                uncle->color = false;
                if (grandparent != root) {
                    grandparent->color = true;
                    balanceTreeForAdd(grandparent);
                }
            }
            else if ((!grandparent->color) && parent->color && (!uncleColor)) {
                // second case add
                if (isGrandLeftSide == isParentLeftSide) {
                    parent->color = false;
                    grandparent->color = true;
                    if (isGrandLeftSide) turnRight(parent);
                    else if (!isGrandLeftSide) turnLeft(parent);
                    return;
                }
                // third case add
                else if (isGrandLeftSide == !isParentLeftSide) {
                    grandparent->color = true;
                    newNode->color = false;
                    if (isGrandLeftSide) turnLeftRight(newNode);
                    else if (!isGrandLeftSide) turnRightLeft(newNode);
                    return;
                }
            }
        }
        return;
    }

    // check and rebalance for deleting
    void balanceTreeForDelete(RBNode* deleteNode, bool isFourthCheck = true) {
        RBNode* parent = deleteNode->parent;
        RBNode* brother = parent->childRight;
        RBNode* cLeft = nullptr;
        RBNode* cRight = nullptr;

        bool isLeftSide = true;
        if (parent->childRight == deleteNode) {
            brother = parent->childLeft;
            isLeftSide = false;
        }

        bool cLeftColor = false;
        if (brother->childLeft) {
            cLeft = brother->childLeft;
            cLeftColor = cLeft->color;
        }

        bool cRightColor = false;
        if (brother->childRight)
        {
            cRight = brother->childRight;
            cRightColor = cRight->color;
        }
        
        // first case
        if (parent->color && !brother->color && !cLeftColor && !cRightColor) {
            parent->color = false;
            brother->color = true;
        }
        // second case
        else if (!brother->color && ((cRightColor) || (!isLeftSide && cLeftColor))) {
            brother->color = parent->color;
            parent->color = false;
            if (isLeftSide) {
                cRight->color = false;
                turnLeft(brother);
            }
            else{
                cLeft->color = false;
                turnRight(brother);
            }
        }
        // third case
        else if (!brother->color && (cLeftColor && !cRightColor || (!isLeftSide && !cLeftColor && cRightColor))) {
            brother->color = true;
            if (isLeftSide) {
                cLeft->color = false;
                turnRight(cLeft);
            }
            else {
                cRight->color = false;
                turnLeft(cRight);
            }

            // second case
            if (isLeftSide) {
                brother = cLeft;
                cRight = brother->childRight;

                brother->color = parent->color;
                parent->color = false;
                cRight->color = false;
                turnLeft(brother);
            }
            else {
                brother = cRight;
                cLeft = brother->childLeft;

                brother->color = parent->color;
                parent->color = false;
                cLeft->color = false;
                turnRight(brother);
            }
        }
        // fourth case
        else if ((!parent->color && brother->color && !cLeftColor && !cRightColor) && isFourthCheck) {
            parent->color = true;
            brother->color = false;
            balanceTreeForDelete(deleteNode, false);
        }
        //fifth case
        else if (!parent->color && !brother->color && !cLeftColor && !cRightColor) {
            brother->color = true;
            balanceTreeForDelete(parent, true);
        }
    }

    // need to find next value to this node
    RBNode* findNext(RBNode* node) {
        if (node->childRight) {
            RBNode* current = node->childRight;
            while (current->childLeft)
            {
                current = current->childLeft;
            }
            return current;
        }
        else {
            return node;
        }
    }

    // turn tree
    void turnLeft(RBNode* node){
        RBNode* parent = node->parent;
        if (parent->parent) {
            if (parent->parent->childLeft == parent) {
                parent->parent->childLeft = node;
            }
            else {
                parent->parent->childRight = node;
            }
        }
        node->parent = parent->parent;

        parent->childRight = node->childLeft;
        if (node->childLeft) {
            node->childLeft->parent = parent;
        }
        node->childLeft = parent;
        parent->parent = node;
        if (!node->parent) { root = node; }
    }
    void turnRight(RBNode* node){
        RBNode* parent = node->parent;
        if (parent->parent) {
            if (parent->parent->childLeft == parent) {
                parent->parent->childLeft = node;
            }
            else {
                parent->parent->childRight = node;
            }
        }
        node->parent = parent->parent;

        parent->childLeft = node->childRight;
        if (node->childRight) {
            node->childRight->parent = parent;
        }
        node->childRight = parent;
        parent->parent = node;
        if (!node->parent) { root = node; }
    }
    void turnLeftRight(RBNode* node){
        turnLeft(node);
        turnRight(node);
    }
    void turnRightLeft(RBNode* node){
        turnRight(node);
        turnLeft(node);
    }

    void insertElement(int data){
        RBNode* newNode = new RBNode;
        if (elementsAmount == 0) {
            newNode->color = false;
            newNode->data = data;
            root = newNode;
            ++elementsAmount;
            return;
        }
        else {
            newNode->color = true;
        }

        newNode->data = data;
        RBNode* currNode = root;
        while (currNode) {
            newNode->parent = currNode;
            if (data >= currNode->data) {
                currNode = currNode->childRight;
            }
            else {
                currNode = currNode->childLeft;
            }
        }
        if (newNode->parent->data > data) {
            newNode->parent->childLeft = newNode;
        }
        else {
            newNode->parent->childRight = newNode;
        }

        balanceTreeForAdd(newNode);

        ++elementsAmount;
    }

    bool destroyElement(RBNode* node) {
        if (elementsAmount == 0) {
            return false;
        }
        else if (elementsAmount == 1) {
            delete node;
            root = nullptr;
            --elementsAmount;
            return true;
        }

        bool color = node->color;

        if (node->childLeft && node->childRight) {
            RBNode* replaceNode = findNext(node);
            node->data = replaceNode->data;
            destroyElement(replaceNode);
        }
        else if (node->childLeft) {
            node->data = node->childLeft->data; // may be incorrect
            delete node->childLeft;
            node->childLeft = nullptr;
        }
        else if (node->childRight) {
            node->data = node->childRight->data; // may be incorrect
            delete node->childRight;
            node->childRight = nullptr;
        }
        else {
            if (!color) {
                balanceTreeForDelete(node);
            }
            if (node->parent->childLeft == node) {
                node->parent->childLeft = nullptr;
            }
            else if (node->parent->childRight == node) {
                node->parent->childRight = nullptr;
            }
            delete node;
        }

        --elementsAmount;
        return true;
    }

    bool isCorrect(char symbol) {
        char symbols[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        for (int i = 0; i < 10; ++i) {
            if (symbol == symbols[i]) return true;
        }
        return false;
    }
    // need to rewrite data from binary tree from char* to int
    void createTreeDataArray(Node* node) {
        if (node) {
            char* tempChar = node->data;
            int newIntData = 0;

            for (int i = 0; tempChar[i] != '\0'; ++i) {
                if (isCorrect(tempChar[i])) {
                    newIntData = newIntData * 10 + (tempChar[i] - '0');
                }
                else {
                    throw "Incorrect symbols! Can't create a RB-tree! Change your input.\n\n";
                }
            }
            treeDataArray.add(newIntData);
            createTreeDataArray(node->childLeft);
            createTreeDataArray(node->childRight);
        }
        else {
            return;
        }
    }

    // traverses

    void directTraversePrint(RBNode* node) {
        if (node) {
            printNode(node);
            directTraversePrint(node->childLeft);
            directTraversePrint(node->childRight);
        }
        else {
            return;
        }
    }
    void centeredTraversePrint(RBNode* node) {
        if (node) {
            centeredTraversePrint(node->childLeft);
            printNode(node);
            centeredTraversePrint(node->childRight);
        }
        else {
            return;
        }
    }
    void reverseTraversePrint(RBNode* node) {
        if (node) {
            reverseTraversePrint(node->childLeft);
            reverseTraversePrint(node->childRight);
            printNode(node);
        }
        else {
            return;
        }
    }

    // for destructor to delete tree
    void traverseDelete(RBNode* node) {
        if (node) {
            traverseDelete(node->childLeft);
            traverseDelete(node->childRight);
            delete node;
        }
        else {
            return;
        }
    }

    // just prints a node
    void printNode(RBNode* node) {
        if (node) {
            std::cout << (node->data) << '-' << node->color << ' ';
        }
        else {
            std::cout << "Null";
        }
    }

    int calcualteHeight(RBNode* node) {
        int max = 1;
        int a = 0;
        int b = 0;
        if (node) {
            a = calcualteHeight(node->childLeft);
            b = calcualteHeight(node->childRight);
        }
        else {
            return 0;
        }
        if (a > b) {
            max += a;
        }
        else {
            max += b;
        }
        return max;
    }

public:
    void addElement(int data){
        insertElement(data);
    }

    // true - if deleted, false - if not deleted (not found)
    bool deleteElement(int data){
        RBNode* currNode = root;
        bool isFound = false;
        while (currNode) {
            if (data > currNode->data) {
                currNode = currNode->childRight;
            }
            else if (data < currNode->data){
                currNode = currNode->childLeft;
            }
            else {
                destroyElement(currNode);
                isFound = true;
                break;
            }
        }
        return isFound;
    }

    void create(BinaryTree* binTree) {
        createTreeDataArray(binTree->getRoot());
        for (int i = 0; i < treeDataArray.length(); ++i) {
            insertElement(treeDataArray[i]);
        }
    }

    // iterative traversal
    void iterativePrintWideSearch() {
        std::cout << "Iterative wide traversal:\n";
        DynamicArray<RBNode*> arr;
        arr.add(root);
        while (arr.length() != 0) {
            RBNode* temp = arr[0];
            if (temp) {
                printNode(temp);
                arr.add(temp->childLeft);
                arr.add(temp->childRight);
            }
            arr.deleteElem(0);
        }
        std::cout << "\n\n";
    }

    // different recursion traversals

    void directPrintTree() {
        std::cout << "Recursion direct traversal:\n";
        directTraversePrint(root);
        std::cout << "\n\n";
    }
    void centeredPrintTree() {
        std::cout << "Recursion centered traversal:\n";
        centeredTraversePrint(root);
        std::cout << "\n\n";
    }
    void reversePrintTree() {
        std::cout << "Recursion reverse traversal:\n";
        reverseTraversePrint(root);
        std::cout << "\n\n";
    }

    int getRootData(){
        return (root->data);
    }

    RBNode* getRoot() {
        return root;
    }

    bool findNode(int data) {
        RBNode* node = root;
        while (node->data != data) {
            if (data > node->data) {
                node = node->childRight;
                if (!node) return false;
            }
            else {
                node = node->childLeft;
                if (!node) return false;
            }
        }
        return true;
    }

    void draw() {
        std::cout << "It is a tree 0_0 x_x -_-\n";
        DynamicArray<RBNode*> tempArray, arrayToDraw;

        treeHeight = calcualteHeight(root);

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
            arrayToDraw.add(tempArray[0]);
            tempArray.deleteElem(0);
        }

        int amountOfElOnLastLevel = 1 << treeHeight;
        for (int i = 0; i < treeHeight; ++i) {
            for (int j = 0; j < amountOfElOnLastLevel / ((1 << i) + 1); ++j) {
                std::cout << ' ';
            }
            for (int k = (1 << i) - 1; k < (1 << i) + (1 << i) - 1; ++k) {
                printNode(arrayToDraw[k]);
                for (int j = 0; j < amountOfElOnLastLevel / ((1 << i) + 1); ++j) {
                    std::cout << ' ';
                }
            }
            std::cout << '\n';
        }
    }

    ~RBTree() {
        traverseDelete(root);
    }
};