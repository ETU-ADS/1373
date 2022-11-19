#include "tests.h"
#include "sort.h"
#include "dynArray.h"

int main()
{
	tests();
	std::string toSort = "";
	std::cout << "Enter the expression you want to sort: ";
	std::getline(std::cin, toSort);
	std::cout << "We've sorted your expression! Here it is: " << sort(toSort) << std::endl;

	system("pause");
	return 0;
}

