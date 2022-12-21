#include<iostream>
#include <string>
#include "Stack.h"

bool inArray(const std::string& temp, 
            std::string* arr,
            int operSize) {
    for (int i = 0; i < operSize; i++) 
        if (arr[i] == temp)
            return true;
    return false;
}


int priorityOperation(std::string op)
{
    if (op == "+" || op == "-")
        return 1;
    else if (op == "*" || op == "/")
        return 2;
    else if (op == "^")
        return 3;
    else if (op == "sin" || op == "cos")
        return 4;
    else return 0;
}

bool isNumber(std::string num) 
{
    if (num.size() == 0) 
        return false;
    if (num[0] == '0')
        return false;
    for (const auto& to : num) 
        if (to < '0' || to > '9')
            return false;
    return true;
}

std::string sort(std::string str)
{
    const int COUNT_OPERATORS = 9;
    std::string operators[COUNT_OPERATORS] = { "+", "-", "*", "/", "^", "sin", "cos", "(", ")"};
    Stack stack(10);
    Stack bracketstack(20);
    str += " ";
    std::string strIntermed = "", strout = "";
    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] != ' ')
            strIntermed += str[i];
        else if (isNumber(strIntermed))
        {
            strout += (strIntermed + " ");
            /*std::cout << strIntermed << std::endl;*/
            strIntermed = "";
        }
        else if (inArray(strIntermed, operators, COUNT_OPERATORS))
        {
            if (strIntermed == "(")
                stack.push(strIntermed);
            else if (strIntermed == ")")
            {
                if (!bracketstack.empty() && bracketstack.see() == ")")
                {
                    std::cout << "\nERROR! Count of \")\" is not equal count of \"(\"!\n" << std::endl;
                    return "";
                }
                while (!stack.empty() && stack.see() != "(")
                    strout += (stack.pop() + " ");
                if (stack.empty())
                {
                    std::cout << "\nERROR! Count of \")\" is not equal count of \"(\"!\n" << std::endl;
                    return "";
                }
                bracketstack.push(stack.pop());
            }
            else if (stack.empty() || priorityOperation(strIntermed) <= priorityOperation(stack.see()))
            {
                while (!stack.empty() && priorityOperation(strIntermed) <= priorityOperation(stack.see()))
                    strout += stack.pop() + " ";
                stack.push(strIntermed);
            }
            else
                stack.push(strIntermed);
            strIntermed = "";
        }
        else
        {
            std::cout << "\nERROR! \"" << strIntermed << "\" is not token!" << std::endl;
            return "";
        }
    }

    while (!stack.empty())
    {
        if (stack.see() == "(")
        {
            if (bracketstack.empty() || bracketstack.see() == "(")
            {
                std::cout << "\nERROR! Count of \"(\" is not equal count of \")\"!\n" << std::endl;
                return "";
            }
            else
                bracketstack.push(stack.pop());
        }
        else
            strout += (stack.pop() + " ");   
    }
    return strout;

}