#include <iostream>
#include <string>

#include "LinkedList.h"
#include "DynamicArray.h"
#include "Stack.h"

void tests();
std::string shuntingYard(std::string expression);

int main()
{
    std::cout << "Hello, User! This program demonstrates the operation of a shunting-yard\n";
    bool isFirstTime = true;
    do{
        if (!isFirstTime) std::cin.get();
        std::cout << "Please, enter your expression: ";
        std::string enteredExpression;
        std::getline(std::cin, enteredExpression);
        std::cout << "Postfix expression: " << shuntingYard(enteredExpression) << std::endl;
        std::cout << "Do you wanna one more time? y/n" << std::endl;
        isFirstTime = false;
    } while (std::cin.get() == 'y');
    std::cout << "Goodbye! :D\n";
    system("pause");
    
    return 0;
}
