//
// Created by theta-sigma on 9/27/2022.
//

#ifndef ALGORITHMS_LAB1_SHUNTINGYARD_H
#define ALGORITHMS_LAB1_SHUNTINGYARD_H

#include <string>
#include <cstring>   // strlen
#include <iostream>  // std::cout, std::cin;
#include <algorithm> // std::get<T>(std::pair<T, S>())
#include <sstream>   // std::istringstream

#include "Stack.h"

class ShuntingYard {
public:
    ShuntingYard();

    ~ShuntingYard() = default;

    void setRawInfixExpression(const std::string &expression);;

    void convert();

    const std::string &getRawInfixExpression() const;

    const std::string &getInfixExpression() const;

    const std::string &getPostfixExpression() const;

    const char *getErrorMessage() const;

private:
    enum TokenType {
        NUMBER,

        POW,

        MULTIPLICATION,
        DIVISION,

        PLUS,
        MINUS,

        SIN,
        COS,
        MAX,
        MIN,

        COMMA,

        LEFT_PARENTHESES,
        RIGHT_PARENTHESES,

        BAD_TOKEN,

        UNKNOWN
    };

    enum TokenCategory {
        NUMBER_CAT,
        OPERATOR,
        SEPARATOR,
        FUNCTION,
        LEFT_PARENTHESES_CAT,
        RIGHT_PARENTHESES_CAT,
        UNKNOWN_CAT
    };

    enum TokenPriority {
        FIRST,
        SECOND,
        THIRD,
        UNKNOWN_PRIORITY
    };

    enum TokenAssociativity {
        LEFT,
        RIGHT,
        UNKNOWN_ASSOCIATIVITY
    };

    enum errorType {
        NO_ERROR,
        BAD_TOKEN_ERROR,
        MISMATCHED_PARENTHESES_ERROR,
        MISMATCHED_PARENTHESES_OR_MISSED_SEP_ERROR,
        UNKNOWN_ERROR
    };

    std::string rawInfixExpression;
    std::string infixExpression;
    std::string postfixExpression;

    Stack<std::pair<std::string, TokenType>> tokensStack;

    errorType error;

    char digits[11];

    bool isNumber(const std::string &token) const;

    TokenType tokenTypeIdentifier(const std::string &token) const;

    static TokenCategory tokenCategoryIdentifier(TokenType tt);

    static TokenPriority tokenPriorityIdentifier(TokenType tt);

    static TokenAssociativity tokenAssociativityIdentifier(TokenType tt);
};


#endif //ALGORITHMS_LAB1_SHUNTINGYARD_H
