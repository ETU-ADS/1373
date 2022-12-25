#include <iostream>
#include <fstream>

#include "DynamicArray.h"
#include "Cruscal.h"

int main()
{
    std::ifstream inputStream;
    system("chcp 1251");
    system("cls");

    std::cout << "Hello! I need a filename to take the data. Enter it below :-)\n";
    char* filename = new char[50];
    for (int i = 0; i < 50; ++i) {
        filename[i] = '\0';
        if (std::cin.peek() != '\n') {
            std::cin >> filename[i];
        }
    }
    std::cout << "Your filename is '" << filename << "'. Thanks for the input!\n\n";

    inputStream.open(filename);

    DynamicArray<char> matrix;

    for (int i = 0; inputStream; ++i) {
        char a = inputStream.peek();
        matrix.add(inputStream.get());
    }
    matrix.deleteElem(matrix.length() - 1);
    matrix.add('\0');

    std::cout << "Data in file:\n";
    for (int i = 0; i < matrix.length(); ++i) {
        std::cout << matrix[i];
    }
    std::cout << '\n' << '\n';

    Cruscal graphWithAlgotithm;

    graphWithAlgotithm.createGraph(matrix);
    graphWithAlgotithm.printEdges();
    graphWithAlgotithm.printVerts();

    graphWithAlgotithm.sortEdges();
    std::cout << "After sorting\n";
    graphWithAlgotithm.printEdges();

    std::cout << "MST tree edges:\n";
    graphWithAlgotithm.buildMST();
    std::cout << '\n';

    inputStream.close();
    
    delete[] filename;
    return 0;
}
