#include <iostream>
#include <fstream>
#include "BinaryTree.h"
#include "Tree.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    int counter = 0;
    char buffer[50];
    fstream file;
    if (file.is_open() == true)
    {
        cout << "Ошибка, файл уже открыт" << endl;
        return 0;
    }
    file.open("parse.txt");
    while (!file.eof())
    {
        file >> buffer[counter];
        counter++;
    }
    BinaryTree<int> tree = BinaryTree<int>();
    RBTree<int> rb = RBTree<int>();
    bool isParsed = tree.parse(buffer, counter);
    if (isParsed == false)
        return 0;
    rb.transformation(tree.getRoot());

    cout << "Обход в ширину: ";
    rb.inWidth();
    cout << endl;

    cout << "Прямой обход в глубину: ";
    rb.forward();
    cout << endl;

    cout << "Центрированный обход в глубину: ";
    rb.central();
    cout << endl;

    cout << "Обратный обход в глубину: ";
    rb.reverse();
    cout << endl;
    rb.print();
    cout << "\n\n\n";

    for (int i = 16; i < 31; i++)
        rb.insert(i);
    rb.print();
    cout << "\n\n\n";
    rb.deleteItem(2);
    rb.deleteItem(6);

    rb.deleteItem(4);

    rb.deleteItem(3);
    rb.deleteItem(2);
    rb.deleteItem(19);
    rb.print();
    file.close();
    return 0;
}

