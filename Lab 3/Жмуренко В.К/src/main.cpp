#include <iostream>
#include<fstream>
#include "wiseTreesFunctions.h"
#include "taskFunctions.h"
using namespace std;

int main()
{
    int counter = 0;
    char buffer[60];
    fstream file;
    if (file.is_open() == true)
    {
        cout << "Ошибка, файл уже открыт" << endl;
        return 0;
    }
    file.open("G://parse.txt");
    while (!file.eof())
    {
        file >> buffer[counter];
        counter++;
    }
    int* array=nullptr;
    int size = 0;
    bool checking = dataVerification(buffer, 60);
    parsing(buffer, 60, checking, array, size);
    cout << endl;
    AVLTree Tree = AVLTree();
    for (int i = 0; i < size; i++)
    {
        Tree.insert(array[i]);
    }
    Tree.widePassing();
    cout << endl;
    Tree.insert(20);
    Tree.insert(30);
    Tree.widePassing();
    cout << endl;
    Tree.deleteTreeElement(20);
    Tree.widePassing();
    cout << endl;
    Tree.straightPassing();
    cout << endl;
    Tree.reversePassing();
    cout << endl;
    Tree.centralPassing();
    cout << endl;
    return 0;
 
}