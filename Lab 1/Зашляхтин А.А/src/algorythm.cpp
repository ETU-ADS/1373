#include <iostream>
#include "algo.h"
#include "definitions.h"

std::string sortStation(std::string sourceString)
{
	sourceString += " ";
	StackClass stack;
	std::string buffer = "";
	std::string buffer2 = "";
	int i = 0;
	//for (int i = 0; i < sourceString.size(); ++i)

	while (sourceString[i])
	{
		if (sourceString[i] != ' ')
		{
			buffer2 += sourceString[i];
		}
		else 
		{
			if (buffer2 == "1" || buffer2 == "2" || buffer2 == "3" || buffer2 == "4" || buffer2 == "5" || buffer2 == "6" || buffer2 == "7" || buffer2 == "8" || buffer2 == "9")
			{
				buffer += buffer2;
				buffer += " ";   // кавычки
				buffer2.clear();
			}
			else if (buffer2 == "+" || buffer2 == "-")
			{
				if (stack.peek() == "0" || stack.peek() == "(")
				{
					stack.push(buffer2);
					buffer2.clear();
				}
				else if (stack.peek() == "+" || stack.peek() == "-" || stack.peek() == "*" || stack.peek() == "/" || stack.peek() == "^" || stack.peek() == "sin" || stack.peek() == "cos")
				{
					buffer += stack.pop();
					buffer += " ";
					
					while (stack.peek() != "(" && stack.peek() != "0")
					{
						buffer += stack.pop();
						buffer += " ";
					}
					stack.push(buffer2);
					buffer2.clear();
				}
			}
			else if (buffer2 == "*" || buffer2 == "/")
			{
				if (stack.peek() == "0" || stack.peek() == "(")
				{
					stack.push(buffer2);
					buffer2.clear();
				}
				else if (stack.peek() == "+" || stack.peek() == "-")
				{
					stack.push(buffer2);
					buffer2.clear();
				}
				else if (stack.peek() == "*" || stack.peek() == "/" || stack.peek() == "^" || stack.peek() == "sin" || stack.peek() == "cos")
				{
					buffer += stack.pop();
					buffer += " ";
					while (stack.peek() != "(" && stack.peek() != "0" && stack.peek() != "+" && stack.peek() != "-")
					{
						buffer += stack.pop();
						buffer += " ";
					}
					stack.push(buffer2);
					buffer2.clear();
				}

			}
			else if (buffer2 == "^")
			{
				if (stack.peek() == "0" || stack.peek() == "(")
				{
					stack.push(buffer2);
					buffer2.clear();
				}
				else if (stack.peek() == "+" || stack.peek() == "-" || stack.peek() == "*" || stack.peek() == "/")
				{
					stack.push(buffer2);
					buffer2.clear();
				}
				else if (stack.peek() == "^" || stack.peek() == "sin" || stack.peek() == "cos")
				{
					buffer += stack.pop();
					buffer += " ";
					while (stack.peek() != "(" && stack.peek() != "0" && stack.peek() != "+" && stack.peek() != "-" && stack.peek() != "*" && stack.peek() != "/")
					{
						buffer += stack.pop();
						buffer += " ";
					}
					stack.push(buffer2);
					buffer2.clear();
				}
			}
			else if (buffer2 == "cos" || buffer2 == "sin")
			{
				if (stack.peek() == "0" || stack.peek() == "(")
				{
					stack.push(buffer2);
					buffer2.clear();
				}
				else if (stack.peek() == "+" || stack.peek() == "-" || stack.peek() == "*" || stack.peek() == "/" || stack.peek() == "^")
				{
					stack.push(buffer2);
					buffer2.clear();
				}
				else if (stack.peek() == "sin" || stack.peek() == "cos")
				{
					buffer += stack.pop();
					buffer += " ";
					while (stack.peek() != "(" && stack.peek() != "0" && stack.peek() != "+" && stack.peek() != "-" && stack.peek() != "*" && stack.peek() != "/" && stack.peek() != "^")
					{
						buffer += stack.pop();
						buffer += " ";
					}
					stack.push(buffer2);
					buffer2.clear();
				}
			}
			else if (buffer2 == "(")
			{
				stack.push(buffer2);
				buffer2.clear();
			}
			else if (buffer2 == ")")
			{
				while (stack.peek() != "(")
				{
					buffer += stack.pop();
					buffer += ' ';
					if (stack.peek() == "0")
					{
						buffer.clear();
						buffer += "Wrong number of stamples!";
						return buffer;
					}

				}
				stack.deleteElement();
				buffer2.clear();
			}
		}
		++i;
		
	}
	while (stack.peek() != "0")
	{
		if (stack.peek() == "(")
		{
			buffer.clear();
			buffer += "Wrong number of stamples!";
			return buffer;
		}
			
		buffer += stack.pop();
		buffer += " ";
	}
	return buffer;
}

