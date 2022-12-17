#include <iostream>
#include "Stack.h"
#include "Array.h"
#include "Sort.h"

int main() {
	int  N = 0;	//number of elements in custom array
	std::cout << "Enter the number of array elements:" << std::endl;
	std::cin >> N;
	std::cout << std::endl << std::endl;

	if (N > 1) {
		Array<int> userArr;	//custom array
		userArr.random(N);

		std::cout << "Your array has " << N << " elements:" << std::endl;	//custom array output
		userArr.print();
		std::cout << std::endl << std::endl;

		TimSort(userArr, N);	//sorting TimSort
		
		std::cout << "Your sorted array:" << std::endl;	//output sorted custom array
		userArr.print();
		std::cout << std::endl << std::endl;
	}
	else {
		std::cout << "Invalid input" << std::endl << std::endl;
	}

	system("pause");
	return 0;
}