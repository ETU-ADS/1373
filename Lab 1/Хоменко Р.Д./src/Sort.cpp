#include<iostream>
#include <string>
#include "Stack.h"
int priority(std::string op)
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
std::string sort(std::string str)
{
    Stack stack(10);
    str += " ";
    std::string strbuff = "", strout = "";
    int countl = 0, countr = 0;
    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] != ' ')
            strbuff += str[i];
        else if (strbuff == "1" || strbuff == "2" || strbuff == "3" || strbuff == "4" || strbuff == "5" || strbuff == "6" || strbuff == "7" || strbuff == "8" || strbuff == "9")
        {
            strout += (strbuff + " ");
            strbuff = "";
        }
        else if (strbuff == "+" || strbuff == "-" || strbuff == "*" || strbuff == "/" || strbuff == "^" || strbuff == "sin" || strbuff == "cos" || strbuff == "(" || strbuff == ")")
        {
            if (strbuff == "(")
            {
                stack.push(strbuff);
                ++countl;
                strbuff = "";
            }
            else if (strbuff == ")")
            {
                ++countr;
                if (countl < countr)
                {
                    std::cout << "\nERROR! Count of \"(\" is not equal count of \")\"!\n" << std::endl;
                    return "";
                }
                while (stack.see() != "(")
                {
                    strout += (stack.pop() + " ");
                }
                stack.pop();
                strbuff = "";
            }
            else if ((priority(strbuff) <= priority(stack.see())) && !stack.empty())
            {
                while ((priority(strbuff) <= priority(stack.see())) && !stack.empty())
                {
                    strout += (stack.pop() + " ");
                }
                stack.push(strbuff);
                strbuff = "";
            }
            else
            {
                stack.push(strbuff);
                strbuff = "";
            }
        }
        else
        {
            std::cout << "\nERROR! \"" << strbuff << "\" is not token!" << std::endl;
            return "";
        }
    }
    if (countl > countr)
    {
        std::cout << "\nERROR! Count of \"(\" is not equal count of \")\"!\n" << std::endl;
        return "";
    }
    while (!stack.empty())
    {
        if (stack.see() == "(" || stack.see() == ")")
            stack.pop();
        strout += (stack.pop() + " ");
    }
    return strout;
}