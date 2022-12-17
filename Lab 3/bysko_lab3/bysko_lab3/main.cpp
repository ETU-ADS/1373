#include <iostream>
#include <fstream>
#include <string>

#include"BTree.h"
#include"RBTree.h"

int main() {
	char fileName[20];
	std::cout << "Enter file name:" << std::endl;
	std::cin.get(fileName, 20);

	std::ifstream file(fileName);
	char userArr[60];
	while (!file.eof())
		file.getline(userArr, sizeof(file));

	BTree user;
	if (user.createBTree(userArr) == true) {
		std::cout << std::endl;
		std::cout << "Your binary tree: " << std::endl;
		user.inOrderPrint();
		std::cout << std::endl;
		std::cout << "________________________________________________________________________________________________________________" << std::endl;
		std::cout << std::endl;

		RBTree userRB;
		userRB.create(&user);

		std::cout << "Your RB tree: " << std::endl;
		std::cout << std::endl;
		userRB.traverse();
		std::cout << std::endl;
		std::cout << "________________________________________________________________________________________________________________" << std::endl;
		std::cout << std::endl;

		std::cout << "Adding(16-28)" << std::endl;
		userRB.add(16);
		userRB.add(17);
		userRB.add(18);
		userRB.add(19);
		userRB.add(20);
		userRB.add(21);
		userRB.add(22);
		userRB.add(23);
		userRB.add(24);
		userRB.add(25);
		userRB.add(26);
		userRB.add(27);
		userRB.add(28);
		std::cout << std::endl;

		userRB.traverse();
		std::cout << std::endl;
		std::cout << "________________________________________________________________________________________________________________" << std::endl;
		std::cout << std::endl;

		std::cout << "Removing(16-17)" << std::endl;
		userRB.del(16);
		userRB.del(17);
		userRB.del(2);
		userRB.del(3);
		userRB.del(20);
		userRB.del(21);
		userRB.del(15);


		std::cout << std::endl;

		userRB.traverse();
		std::cout << std::endl;
		std::cout << "________________________________________________________________________________________________________________" << std::endl;
		std::cout << std::endl;

		std::cout << std::endl;
	}
	return 0;
}