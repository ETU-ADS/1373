#include <iostream>
#include <fstream>

#include "DynamicArray.h"
#include "BinaryTree.h"
#include "RBTree.h"

int main()
{
    BinaryTree binTree;
    RBTree rbTree;

    std::ifstream inputStream;
    inputStream.open("task.txt");
    char* abc = new char[50];
    for (int i = 0; i < 50; ++i) {
        abc[i] = '\0';
        if (inputStream) {
            inputStream >> abc[i];
        }
    }

    std::cout << "Readed data from file:\n";
    for (int i = 0; i < 50; ++i) {
        std::cout << abc[i];
    }
    std::cout << '\n';

    inputStream.close();

    try {
        binTree.create(abc);

        std::cout << "Deep-first search in binary tree (center):\n";
        binTree.printWithDepthFirstSearch();
        std::cout << '\n';

        std::cout << "This is the tree :D\n";
        binTree.draw();

        rbTree.create(&binTree);
    }
    catch (const char* e){
        std::cout << e;
    };

    rbTree.directPrintTree();
    rbTree.draw();

    for (int i = 16; i < 25; ++i) { 
        rbTree.addElement(i);
    }
    for (int i = 50; i < 55; ++i) { 
        rbTree.addElement(i);
    }

    rbTree.draw();

    rbTree.directPrintTree();

    rbTree.deleteElement(8);
    rbTree.deleteElement(15);
    rbTree.deleteElement(2);
    rbTree.deleteElement(3);

    rbTree.directPrintTree();
    rbTree.centeredPrintTree();
    rbTree.reversePrintTree();
    rbTree.iterativePrintWideSearch();

    rbTree.draw();

    system("pause");
    return 0;
}

