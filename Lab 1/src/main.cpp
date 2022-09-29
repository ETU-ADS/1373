#include <iostream>

#include "ArrayList.h"
#include "ShuntingYard.h"
#include "project_tests.h"

#include <iomanip>

int main() {
    std::cout << "Testing ArrayList.." << std::endl;
    arrayListTests();
    std::cout << "Success!" << std::endl << std::endl;

    std::cout << "Testing ArrayList.." << std::endl;
    linkedListTests();
    std::cout << "Success!" << std::endl << std::endl;

    std::cout << "SHUNTING YARD" << std::endl << std::endl;

    ArrayList<std::string> ti;
    ti.append("( 1 + 2 ) )");
    ti.append("( 2 - 3 + 4 ) * ( 5 + 6 * 7 )");
    ti.append("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3");
    ti.append("sin ( cos ( 2 , 3 ) / 3 * 314 )");
    ti.append("sin ( cos ( 2, 3 ) / 3 * 314 )");
    ti.append("( 1 + 2 ) )");
    ti.append("3 * 7 - sin ( 2 )");


    ArrayList<std::string> to;
    to.append("MISMATCHED_PARENTHESES_ERROR");
    to.append("2 3 - 4 + 5 6 7 * + * ");
    to.append("3 4 2 * 1 5 - 2 3 ^ ^ / + ");
    to.append("2 3 cos 3 / 314 * sin ");
    to.append("BAD_TOKEN_ERROR");
    to.append("MISMATCHED_PARENTHESES_ERROR");
    to.append("3 7 * 2 sin - ");

    ShuntingYard sy;

    std::string line;

    std::cout << "Testing algorithm..." << std::endl;

    bool flag = false;
    for (int i = 0; i < ti.size() && i < to.size(); i++) {
        sy.setRawInfixExpression(ti.get(i));
        sy.convert();
        const std::string &rpn = sy.getPostfixExpression();
        if (rpn == to.get(i)) {
            std::cout << i << ": correct!" << std::endl;
        } else {
            std::cout << i << ": incorrect!" << std::endl;
            std::cout << ti.get(i) << std::endl;
            std::cout << to.get(i) << std::endl;
            std::cout << rpn << std::endl;
            flag = true;
        }
    }

    if (flag) {
        return 0;
    }

    std::cout << "Success!" << std::endl << std::endl;

    bool toContinue = true;
    do {
        std::cout << "Enter your infix expression:\t";
        std::getline(std::cin, line);
        sy.setRawInfixExpression(line);
        sy.convert();
        std::string rie = sy.getRawInfixExpression();
        std::string ie = sy.getInfixExpression();
        std::string rpn = sy.getPostfixExpression();
        auto syErrorMessage = sy.getErrorMessage();

        std::cout << std::setw(20) << "your input: " << rie << std::endl;
        std::cout << std::setw(20) << "infix expression: " << ie << std::endl;
        std::cout << std::setw(20) << "postfix expression: " << rpn << std::endl;
        std::cout << std::setw(20) << "error message: " << syErrorMessage << std::endl;

        bool innerFlag = true;
        char answer;
        while (innerFlag) {
            std::cout << "Do you want to restart the program? y/n:" << std::endl;
            std::cin >> answer;
            switch (answer) {
                case 'n':
                    std::cout << "Closing...";
                    toContinue = false;
                    innerFlag = false;
                    break;
                case 'y':
                    innerFlag = false;
                    break;
                default:
                    break;
            }
        }
        std::cin.ignore();
        std::cout << std::endl << std::endl;
    } while (toContinue);

    return 0;
}
