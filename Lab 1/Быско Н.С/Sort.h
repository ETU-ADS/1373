#pragma once
#include "Stack.h"
#include <string>

//operation priority function
int prior(std::string t) {

	if (t == "-") {
		return 1;
	}
	else if (t == "+") {
		return 1;
	}
	else if (t == "*") {
		return 2;
	}
	else if (t == "/") {
		return 2;
	}
	else if (t == "^") {
		return 3;
	}
	else if (t == "sin") {
		return 4;
	}
	else if (t == "cos") {
		return 4;
	}
	else {
		return 0;
	}
}

//check function for numbers 1-9
bool isNumber(std::string t) {
	if (t == "0"||t == "1" || t == "2" || t == "3" ||
		t == "4" || t == "5" || t == "6" ||
		t == "7" || t == "8" || t == "9") {
		return true;
	}
	else {
		return false;
	}
}

//checking for operations
bool isOperation(std::string t) {
	if (t == "^" || t == "+" || t == "-" ||
		t == "*" || t == "/" || t == "sin" ||
		t == "cos" || t == "(" || t == ")") {
		return true;
	}
	else {
		return false;
	}
}

std::string RPN(std::string str) {

	int sortStackSize = 10;
	Stack <int> sortStack(sortStackSize);

	str += " ";

	std::string outputString = "";
	std::string stackOfTokens = "";

	int openBracket = 0;
	int closingBracket = 0;

	for (int i = 0; i < str.size(); i++) {
		if (str[i] != ' ') {
			stackOfTokens += str[i];
		}
		else if (isNumber(stackOfTokens)) {
			outputString += (stackOfTokens + " ");
			stackOfTokens = "";
		}
		else if (isOperation(stackOfTokens)) {

			if (stackOfTokens == "(") {
				sortStack.push(stackOfTokens);
				openBracket++;
				stackOfTokens = "";
			}
			else if (stackOfTokens == ")") {
				closingBracket++;
				if (openBracket < closingBracket) {
					return "ERROR: The number of opening brackets is less than the number of closing brackets";
				}

				while (sortStack.peek() != "(") {
					outputString += (sortStack.pop() + " ");
				}

				sortStack.pop();
				stackOfTokens = "";
			}
			else if ((prior(stackOfTokens) <= prior(sortStack.peek())) && !sortStack.empty()) {

				while ((prior(stackOfTokens) <= prior(sortStack.peek())) && !sortStack.empty()) {

					outputString += (sortStack.pop() + " ");
				}

				sortStack.push(stackOfTokens);
				stackOfTokens = "";
			}
			else {
				sortStack.push(stackOfTokens);
				stackOfTokens = "";
			}
		}
		else {
			return "ERROR: Invalid input";
		}
	}
	if (openBracket > closingBracket) {
		return "ERROR: The number of opening brackets is greater than the number of closing brackets";
	}
	while (!sortStack.empty()) {
		if (sortStack.peek() == "(" || sortStack.peek() == ")") {
			sortStack.pop();
		}
		outputString += (sortStack.pop() + " ");
	}
	return outputString;
}