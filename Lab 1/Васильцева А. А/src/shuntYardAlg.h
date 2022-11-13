#pragma once
#include <iostream>
#include <string>

#include "myList.h"
#include "myStack.h"
#include "myVector.h"
#include "shuntYardAlg.h"

bool niceExpress(std::string input) {

    int length = input.size();
    std::string allowSymb = " 0123456789+-*/^()sincos";
    int countOpen = 0, countClosed = 0;

    for (int i = 0; i < length; i++) {

        bool findSymb = allowSymb.find(input[i]) != std::string::npos;
        if (!findSymb) {
            return false;
        }
    }
    if (countOpen != countClosed) {
        return false;
    }
    return true;
}

void algoth(std::string input) {

    if (!niceExpress(input)) {
        std::cout << "error: unexpected symbol\n";
    }
    else {
        int length = input.size();

        myStack<char> express;

        for (int i = 0; i < length; i++) {

            // operand
            if (input[i] >= 48 && input[i] <= 57) {
                std::cout << input[i];
                if (input[i + 1] < 48 || input[i + 1] > 57) {
                    std::cout << ' ';
                }
            }

            if (input[i] == 's' || input[i] == 'c') {
                express.push(input[i]);
                i += 3;
            }

            if (input[i] == '+' || input[i] == '-') {
                if (express.isEmpty()) {
                    express.push(input[i]);
                }
                else {
                    while (!express.isEmpty() && express.peak() != '(' && express.peak() != ')'
                        && express.peak() != 's' && express.peak() != 'c')
                    {
                        std::cout << express.peak() << ' ';
                        express.pop();
                    }

                    express.push(input[i]);
                }
            }

            if (input[i] == '*' || input[i] == '/') {
                if (express.isEmpty()) {
                    express.push(input[i]);
                }
                else {
                    while (!express.isEmpty() && express.peak() != '(' && express.peak() != ')'
                        && express.peak() != 's' && express.peak() != 'c'
                        && express.peak() != '+' && express.peak() != '-')
                    {
                        std::cout << express.peak() << ' ';
                        express.pop();
                    }

                    express.push(input[i]);
                }
            }

            if (input[i] == '^') {
                if (express.isEmpty()) {
                    express.push(input[i]);
                }
                else {
                    while (!express.isEmpty() && express.peak() != '(' && express.peak() != ')'
                        && express.peak() != 's' && express.peak() != 'c' && express.peak() != '+' 
                        && express.peak() != '-' && express.peak() != '*' && express.peak() != '/')
                    {
                        std::cout << express.peak() << ' ';
                        express.pop();
                    }

                    express.push(input[i]);
                }
            }

            if (input[i] == '(') {
                express.push(input[i]);
            }

            if (input[i] == ')') {

                while (express.peak() != '(') {
                    std::cout << express.peak() << ' ';
                    express.pop();

                    if (express.isEmpty()) {
                        std::cout << "no skobka\n";
                        return;
                    }
                }

                express.pop();

                if (express.peak() == 'c') {
                    std::cout << "cos ";
                    express.pop();
                }
                if (express.peak() == 's') {
                    std::cout << "sin ";;
                    express.pop();
                }
            }
        }

        while (!express.isEmpty()) {
            if (express.peak() == '(') {
                std::cout << "no skobka\n";
                return;
            }
            if (express.peak() == 'c') {
                std::cout << "cos ";
                express.pop();
            } 
            else 
            if (express.peak() == 's') {
               std::cout << "sin ";;
               express.pop();
            }
            else
            std::cout << express.peak() << ' ';
            express.pop();
        }
        std::cout << '\n';
    }
}
