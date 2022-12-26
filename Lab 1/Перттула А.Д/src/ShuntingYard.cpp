//
// Created by theta-sigma on 9/27/2022.
//

#include "ShuntingYard.h"

ShuntingYard::ShuntingYard() : rawInfixExpression(), infixExpression(), postfixExpression(),
                               tokensStack(), error(UNKNOWN_ERROR), digits("0123456789") {}


void ShuntingYard::setRawInfixExpression(const std::string &expression) {
    rawInfixExpression = expression;
}

bool ShuntingYard::isNumber(const std::string &token) const {
    bool flag;
    for (char character: token) {
        flag = false;
        for (int j = 0; j < strlen(digits) && !flag; j++) {
            if (character == digits[j]) {
                flag = true;
            }
        }

        if (!flag) {
            return false;
        }
    }

    return flag;
}

ShuntingYard::TokenType ShuntingYard::tokenTypeIdentifier(const std::string &token) const {
    if (isNumber(token)) {
        return NUMBER;
    }

    if (token == "^") {
        return POW;
    }

    if (token == "*") {
        return MULTIPLICATION;
    }

    if (token == "/") {
        return DIVISION;
    }

    if (token == "+") {
        return PLUS;
    }

    if (token == "-") {
        return MINUS;
    }

    if (token == "sin") {
        return SIN;
    }

    if (token == "cos") {
        return COS;
    }

    if (token == "max") {
        return MAX;
    }

    if (token == "min") {
        return MIN;
    }

    if (token == ",") {
        return COMMA;
    }

    if (token == "(") {
        return LEFT_PARENTHESES;
    }

    if (token == ")") {
        return RIGHT_PARENTHESES;
    }

    return BAD_TOKEN;
}

ShuntingYard::TokenCategory ShuntingYard::tokenCategoryIdentifier(ShuntingYard::TokenType tt) {
    switch (tt) {
        case NUMBER:
            return NUMBER_CAT;
        case POW:
        case MULTIPLICATION:
        case DIVISION:
        case PLUS:
        case MINUS:
            return OPERATOR;
        case SIN:
        case COS:
        case MAX:
        case MIN:
            return FUNCTION;
        case COMMA:
            return SEPARATOR;
        case LEFT_PARENTHESES:
            return LEFT_PARENTHESES_CAT;
        case RIGHT_PARENTHESES:
            return RIGHT_PARENTHESES_CAT;
        case BAD_TOKEN:
        case UNKNOWN:
            return UNKNOWN_CAT;
    }
}

ShuntingYard::TokenPriority ShuntingYard::tokenPriorityIdentifier(ShuntingYard::TokenType tt) {
    switch (tt) {
        case POW:
            return FIRST;
        case MULTIPLICATION:
        case DIVISION:
            return SECOND;
        case PLUS:
        case MINUS:
            return THIRD;
        case NUMBER:
        case SIN:
        case COS:
        case MAX:
        case MIN:
        case COMMA:
        case LEFT_PARENTHESES:
        case RIGHT_PARENTHESES:
        case BAD_TOKEN:
        case UNKNOWN:
            return UNKNOWN_PRIORITY;
    }
}

ShuntingYard::TokenAssociativity ShuntingYard::tokenAssociativityIdentifier(ShuntingYard::TokenType tt) {
    switch (tt) {
        case POW:
            return RIGHT;
        case MULTIPLICATION:
        case DIVISION:
        case PLUS:
        case MINUS:
            return LEFT;
        case NUMBER:
        case SIN:
        case COS:
        case MAX:
        case MIN:
        case COMMA:
        case LEFT_PARENTHESES:
        case RIGHT_PARENTHESES:
        case BAD_TOKEN:
        case UNKNOWN:
            return UNKNOWN_ASSOCIATIVITY;
    }
}

void ShuntingYard::convert() {
    std::istringstream ss(rawInfixExpression);
    std::string token;
    postfixExpression = "";
    infixExpression = "";
    error = UNKNOWN_ERROR;
    tokensStack.makeEmpty();
    while (ss >> token) {
        infixExpression += token + " ";
        TokenType tokenType = tokenTypeIdentifier(token);

        if (tokenType == BAD_TOKEN) {
            error = BAD_TOKEN_ERROR;
            postfixExpression = getErrorMessage();
            return;
        }

        auto currentPair =
                std::pair<std::string, TokenType>({token, tokenType});

        TokenCategory tokenCat = tokenCategoryIdentifier(tokenType);
        if (tokenCat == NUMBER_CAT) {
            postfixExpression += token + " ";
            continue;
        }

        if (tokenCat == FUNCTION) {
            tokensStack.push(currentPair);
            continue;
        }

        if (tokenCat == SEPARATOR) {
            while (!tokensStack.isEmpty()) {
                const auto &topToken = std::get<std::string>(tokensStack.peak());
                TokenType topType = std::get<TokenType>(tokensStack.peak());
                if (topType != LEFT_PARENTHESES) {
                    postfixExpression += topToken + " ";
                    tokensStack.pop();
                } else {
                    break;
                }
            }
            if (tokensStack.isEmpty()) {
                error = MISMATCHED_PARENTHESES_OR_MISSED_SEP_ERROR;
                postfixExpression = getErrorMessage();
                return;
            }
            continue;
        }

        if (tokenCat == OPERATOR) {
            if (!tokensStack.isEmpty()) {
                const auto *top = &tokensStack.peak();
                auto topType = std::get<TokenType>(*top);
                const std::string *topToken = &std::get<std::string>(*top);

                while (tokenCategoryIdentifier(topType) == OPERATOR &&
                       (tokenPriorityIdentifier(topType) <= tokenPriorityIdentifier(tokenType)) &&
                       (tokenPriorityIdentifier(topType) != tokenPriorityIdentifier(tokenType) ||
                        tokenAssociativityIdentifier(tokenType) != RIGHT)) {
                    postfixExpression += *topToken + " ";
                    tokensStack.pop();

                    if (!tokensStack.isEmpty()) {
                        top = &tokensStack.peak();
                        topType = std::get<TokenType>(*top);
                        topToken = &std::get<std::string>(*top);
                    } else {
                        break;
                    }
                }
            }

            tokensStack.push(currentPair);
            continue;
        }

        if (tokenCat == LEFT_PARENTHESES_CAT) {
            tokensStack.push(std::pair<std::string, TokenType>({token, tokenType}));
            continue;
        }

        if (tokenCat == RIGHT_PARENTHESES_CAT) {
            const std::string *topToken;
            TokenType topType = UNKNOWN;

            while (topType != LEFT_PARENTHESES) {
                if (!tokensStack.isEmpty()) {
                    topToken = &std::get<std::string>(tokensStack.peak());
                    topType = std::get<TokenType>(tokensStack.peak());
                } else {
                    error = MISMATCHED_PARENTHESES_ERROR;
                    postfixExpression = getErrorMessage();
                    return;
                }
                if (tokenCategoryIdentifier(topType) == OPERATOR) {
                    postfixExpression += *topToken + " ";
                    tokensStack.pop();
                }
            }

            if (tokenTypeIdentifier(*topToken) == LEFT_PARENTHESES) {
                tokensStack.pop();
                if (!tokensStack.isEmpty()) {
                    topToken = &std::get<std::string>(tokensStack.peak());
                    topType = std::get<TokenType>(tokensStack.peak());
                }
            }

            if (tokenCategoryIdentifier(topType) == FUNCTION) {
                postfixExpression += *topToken + " ";
                tokensStack.pop();
                continue;
            }
        }
    }

    while (!tokensStack.isEmpty()) {
        const auto &topToken = std::get<std::string>(tokensStack.peak());

        if (tokenTypeIdentifier(topToken) == LEFT_PARENTHESES) {
            error = MISMATCHED_PARENTHESES_ERROR;
            postfixExpression = getErrorMessage();
            return;
        }

        postfixExpression += topToken + " ";
        tokensStack.pop();
    }

    error = NO_ERROR;
}

const std::string &ShuntingYard::getRawInfixExpression() const {
    return rawInfixExpression;
}

const std::string &ShuntingYard::getInfixExpression() const {
    return infixExpression;
}

const std::string &ShuntingYard::getPostfixExpression() const {
    return postfixExpression;
}

const char *ShuntingYard::getErrorMessage() const {
    switch (error) {
        case NO_ERROR:
            return "NO_ERROR";
        case BAD_TOKEN_ERROR:
            return "BAD_TOKEN_ERROR";
        case MISMATCHED_PARENTHESES_ERROR:
            return "MISMATCHED_PARENTHESES_ERROR";
        case MISMATCHED_PARENTHESES_OR_MISSED_SEP_ERROR:
            return "MISMATCHED_PARENTHESES_OR_MISSED_SEP_ERROR";
        case UNKNOWN_ERROR:
            return "UNKNOWN_ERROR";
    }
}
