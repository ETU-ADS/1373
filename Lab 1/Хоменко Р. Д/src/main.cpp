#include <iostream>
#include <string>
#include "Sort.h"
#include"Tests.h"

int main()
{
    unitTest();
    std::string str;
    std::cout << "Enter your expression: ";
    std::getline(std::cin, str);
    std::cout << "Sorted expression: " << sort(str) << std::endl;
    system("pause");
    return 0;
}