#include <iostream>
#include <string>
#include "Sort.h"
#include "Tests.h"

int main() {
	tests();

	std::string userString;
	std::cout << "enter the expression using 1, 2, 3, 4, 5, 6, 7, 8, 9, +, -, *, /, ^" << std::endl;

	std::getline(std::cin, userString);

	std::cout << "reverse polish notation: " << std::endl << RPN(userString) << std::endl;
	system("pause");
	return 0;
}