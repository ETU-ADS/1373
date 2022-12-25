#include <iostream>
#include "myTree.h"
#include "randNum.h"

int main() {

	//rbTree<int> randTree;
	//randNum(10, 30, 10, &randTree);
	//randTree.textTree();

	binTree<int> f;
	f.readTree();
	std::cout << "-------binary tree-----" << std::endl;
	std::cout << "In-oreder for bin tree:" << std::endl;
	f.in_order();
	std::cout  << std::endl;

	rbTree<int> puber;
	myStack<int> value;
	f.in_order_val(&value);
	while (!value.isEmpty()) {
		puber.addElem(value.peak());
		value.pop();
	}
	std::cout << "--------red-black tree------" << std::endl;
	std::cout << "Pre-oreder path for rb tree:" << std::endl;
	puber.pre_order();
	std::cout << std::endl;

	std::cout << "In-oreder path for rb tree:" << std::endl;
	puber.in_order();
	std::cout << std::endl;

	std::cout << "Post-oreder path for rb tree:" << std::endl;
	puber.post_order();
	std::cout << std::endl;

	std::cout << "BFS path for rb tree:" << std::endl;
	puber.breadthFS();
}