#include <iostream>
#include<string>
#include "Tree.h"
int main()
{
    std::string str;
    std::cout << "Enter file name: ";
    std::getline(std::cin, str);
    BinTree binTree;
    if (binTree.parcing(str) == -1)
    {
        system("pause");
        return -1;
    }
    int c = -1;
    while (true)
    {
        std::cout << std::endl;
        std::cout << "Choose option: 0 - end program; 1 - traversal; 2 - make AVL tree: ";
        std::cin >> c;
        if (c == 0 || c == 2)
            break;
        std::cout << std::endl;
        if (c == 1)
            binTree.traversal();
        else
            std::cout << "ERROR! You enter wrong number!";
        std::cout << std::endl;
    }
    if (c == 0)
        return 0;

    AVLTree avlTree;
    avlTree.make(binTree);
    while (true)
    {
        std::cout << std::endl;
        std::cout << "Choose option: 0 - end program; 1 - traversal; 2 - search element; 3 - add element; 4 - delete element: ";
        std::cin >> c;
        if (c == 0)
            break;
        switch (c)
        {
        case 1:
        {
            std::cout << "Choose the type of traversal: 1 - straight; 2 - centered; 3 - reverse; 4 - wide: ";
            std::cin >> c;
            if (c != 1 && c != 2 && c != 3 && c != 4)
            {
                std::cout << "ERROR! You enter wrong number!" << std::endl;
                break;
            }
            std::cout << std::endl;
            avlTree.traversal(c);
            break;
        }
        case 2:
        {
            std::cout << "Enter number: ";
            std::cin >> c;
            std::cout << std::endl;
            avlTree.find(c);
            break;
        }
        case 3:
        {
            std::cout << "Enter number: ";
            std::cin >> c;
            avlTree.insert(c);
            break;
        }
        case 4:
        {
            std::cout << "Enter number: ";
            std::cin >> c;
            avlTree.remove(c);
            break;
        }
        default:
        {
            std::cout << "ERROR! You enter wrong number!" << std::endl;
            break;
        }
        }
    }
    return 0;
}