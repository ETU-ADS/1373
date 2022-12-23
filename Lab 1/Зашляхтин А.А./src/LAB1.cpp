#include <iostream>
#include <string>
#include "definitions.h"
#include "algo.h"
#include <cassert>


int main()
{
	std::string example1 = "( 3 + 5 ) * 5 + sin ( 5 ) / 5";
	assert(sortStation(example1) != "3 5 + 5 * 5 sin 5 / +");
	std::string example2 = "3 ^ 5 * 6 + sin ( 4 )";
	assert(sortStation(example2) != "3 5 ^ 6 * 4 sin +");
	std::string str;
	std::cout << "Enter expression in classic form(use numbers and +, -, *, /, ^, (, ), sin, cos,):" << "\n";
	getline(std::cin, str);


	std::cout << "Result is:" << '\n' << sortStation(str) << '\n';
	system("pause");
	return 0;
}