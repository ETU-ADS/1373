#pragma once
#include <cassert>
#include "Stack.h"

void tests() {
	Stack <int> testStack(3);

	testStack.push("2");
	testStack.push("4");
	testStack.push("6");

	assert(testStack.peek() == "6");
	assert(testStack.pop() == "6");

	assert(testStack.peek() == "4");
	assert(testStack.pop() == "4");

	assert(testStack.empty() == 0);

	assert(testStack.peek() == "2");
	assert(testStack.pop() == "2");

	assert(testStack.empty() == 1);

	assert(RPN("3 * ( sin ( 4 ) - 1 ) + 4 * ( cos ( 2 ) * 7 )") == "3 4 sin 1 - * 4 2 cos 7 * * + ");
	assert(RPN("3 + ( 2 * 7 + 3 ) * 7") == "3 2 7 * 3 + 7 * + ");
	assert(RPN("cos 9 - 1 / 2 * sin ( 7 ^ 2 - 2 )") == "9 cos 1 2 / 7 2 ^ 2 - sin * - ");
}