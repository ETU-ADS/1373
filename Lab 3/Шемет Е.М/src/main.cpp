#include <iostream>
#include<string>
#include "Tree.h"
int main()
{
    setlocale(LC_ALL, "Russian");
    std::string str;
    std::cout << "Введите имя текстового файла: ";
    std::getline(std::cin, str);
    BinTree binTree;
    if (binTree.parcing(str) == -1)
    {
        system("pause");
        return -1;
    }
    int c = 0;
    std::cout << std::endl;
    std::cout << "Вершины бинарного дерева:" << "\n" << std::endl;
    binTree.traversal();
    std::cout << std::endl;
    AVLTree avlTree;
    avlTree.make(binTree);
    
    while (true)
    {
        std::cout << std::endl;
        std::cout << "Выберите действие: 1 - Вывести дерево через обход; 2 - Найти элемент; 3 - Добавить элемент; 4 - Удалить элемент ";
        std::cin >> c;
        if (c == 1)
        {
            std::cout << "Выберите обход: 1 - Прямой; 2 - Центрированный; 3 - Обратный; 4 - В ширину: ";
            std::cin >> c;
            if ((c == 1) || (c == 2) || (c == 3) || (c == 4))
            {
                std::cout << std::endl;
                avlTree.traversal(c);
            }
            else
            {
                std::cout << "Ошибка! Сделайте правильный выбор." << std::endl;
            }
        }
        else if (c == 2)
        {
            std::cout << "Введите искомый элемент: ";
            std::cin >> c;
            std::cout << std::endl;
            avlTree.find(c);
        }
        else if (c == 3)
        {
            std::cout << "Введите добавляемый элемент: ";
            std::cin >> c;
            avlTree.insert(c);
        }
        else if (c == 4)
        {
            std::cout << "Введите удаляемый элемент: ";
            std::cin >> c;
            avlTree.remove(c);
        }
        else
        {
            std::cout << "Ошибка! Сделайте правильный выбор." << std::endl;
        }
    }
    return 0;
}
