//#include <iostream>
//#include <string>

#include "myList.h"
#include "myStack.h"
#include "myVector.h"
#include "shuntYardAlg.h"

void algoth(std::string input);

int main() {

    std::cout << "Enter expression: \navaliable symbols: 0123456789 sin cos +- */ ^ ()\n";
    std::string express;
    std::getline(std::cin, express);
    std::cout << "Your answer: "; 
    algoth(express);

    //std::cout << "Your answer: ";
    //algoth("3 * ( sin ( 4 ) - 1 ) + 4 * cos ( 2 ) * 7 )");

    //std::cout << "Your answer: ";
    //algoth("(2 * 1 - 3 * 0) * 4 + 3 * 5");

    //std::cout << "Your answer: ";
    //algoth("1 * sin ( 2 ) + 3 ^ 4 ^ 5 + 4 * 5 / 6 / 7");

    //std::cout << "Your answer: ";
    //algoth("1 ^ ( 3 ^ 2 + 4 ) * ( 5 / 6 / 7");

    system("pause");
	return 0;
}