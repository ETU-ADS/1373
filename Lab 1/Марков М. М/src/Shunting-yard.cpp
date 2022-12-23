#include <string>
#include "Stack.h"

bool isOperator(std::string operators, char token) {
    for (int i = 0; i < operators.size(); ++i) {
        if (token == operators[i]) return true;
    }
    return false;
}
// 1 if token1 > token2, 2 if token1 < token2, 3 if equal
unsigned int checkPriority(char token1, char token2) {
    int priority1 = 0;
    int priority2 = 0;
    switch (token1)
    {
    case '+':
    case '-':
        priority1 = 1;
        break;
    case '*':
    case '/':
        priority1 = 2;
        break;
    case '^':
        priority1 = 3;
        break;
    default:
        priority1 = 0;
        break;
    }
    switch (token2)
    {
    case '+':
    case '-':
        priority2 = 1;
        break;
    case '*':
    case '/':
        priority2 = 2;
        break;
    case '^':
        priority2 = 3;
        break;
    default:
        priority1 = 0;
        break;
    }
    if (priority1 > priority2) return 1;
    else if (priority1 < priority2) return 2;
    else return 3;
}

std::string shuntingYard(std::string expression) {
    Stack<char> stack;
    std::string outputExpression;
    std::string numbers = "1234567890";
    std::string operators = "+-*/^";
    char token;
    for (int i = 0; i < expression.size(); ++i) {
        token = expression[i];
        if (token != ' ') {
            // if function
            if (token == 's' || token == 'c') {
                i += 2;
                stack.push(token);
                continue;
            }
            
            if (token == '(') {
                stack.push(token);
                continue;
            }

            if (token == ')') {
                while (stack.peak() != '(') {
                    if (stack.size() != 0) {
                        outputExpression += stack.peak();
                        stack.pop();
                    }
                    else return "ERROR! Missing bracket \'(\'!";
                }
                stack.pop();

                if (stack.peak() == 's') {
                    outputExpression += "sin";
                    stack.pop();
                }
                else if (stack.peak() == 'c') {
                    outputExpression += "cos";
                    stack.pop();
                }
                continue;
            }
            // if operator
            if (isOperator(operators, token)) {
                if (stack.size() > 0) {
                    while (isOperator(operators, stack.peak())) {
                        unsigned int priority = checkPriority(stack.peak(), token);
                        if (priority == 1 || (priority == 3 && (stack.peak() != '^'))) { // if priority > or ==
                            outputExpression += stack.peak();
                            stack.pop();
                        }
                        else break;
                    }
                }
                stack.push(token);
                continue;
            }

            // if number
            for (int j = 0; j < numbers.size(); ++j) {
                if (token == numbers[j]) {
                    outputExpression += token;
                }
            }
        }
    }
    while (stack.size() != 0) {
        if (stack.peak() == '(') return "ERROR! Missing bracket! \')\'";
        else {
            outputExpression += stack.peak();
            stack.pop(); 
        }
    }

    return outputExpression;
}