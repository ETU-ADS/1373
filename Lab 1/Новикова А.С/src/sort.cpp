#include "Stack.h"

int opPriority(std::string op)
{
	if (op == "+" || op == "-")
		return 1;
	else if (op == "*" || op == "/")
		return 2;
	else if (op == "^")
		return 3;
	else if (op == "cos" || op == "sin")
		return 4;
	else
		return 0;

}

std::string sort(std::string data)
{
	std::string resultData = "";
	std::string buffer = "";
	Stack opStack(10);

	for (int i = 0; i < data.length(); i++)
	{
		if (data[i] != ' ')
		{
			buffer += data[i];
		}

		if (buffer == "0" || buffer == "1" || buffer == "2" || buffer == "3" || buffer == "4" || buffer == "5" || buffer == "6" || buffer == "7" || buffer == "8" || buffer == "9")
		{
			resultData += buffer;
			resultData += " ";
			buffer = "";
		}
		else if (buffer == "+" || buffer == "-" || buffer == "*" || buffer == "/" || buffer == "^" || buffer == "cos" || buffer == "sin" || buffer == "(" || buffer == ")")
		{
			
			if (opStack.isEmpty() || opPriority(buffer) > opPriority(opStack.peak()) || buffer == "(")
			{
				opStack.push(buffer);
				buffer = "";
			}
			else if (buffer == ")")
			{
				while (opStack.peak() != "(")
				{
					resultData += opStack.peak();
					resultData += " ";
					opStack.pop();

					if (opStack.isEmpty())
					{
						std::cout << "Error! You've forgotten to enter (.";
						exit(EXIT_FAILURE);
					}
				}
				buffer = "";
				opStack.pop();
			}
			else if (opPriority(buffer) <= opPriority(opStack.peak()))
			{
				while (opPriority(buffer) <= opPriority(opStack.peak()) && !opStack.isEmpty())
				{
					resultData += opStack.peak();
					resultData += " ";
					opStack.pop();
				}
				opStack.push(buffer);
				buffer = "";
			}
		}
	}
	while (!opStack.isEmpty())
	{
		if (opStack.peak() == ")")
		{
			std::cout << "Error! You've forgotten to enter (. " << std::endl;
			exit(EXIT_FAILURE);
		}
		else if (opStack.peak() == "(")
		{
			std::cout << "Error! You've forgotten to enter ). " << std::endl;
			exit(EXIT_FAILURE);
		}
		resultData += opStack.peak();
		resultData += " ";
		opStack.pop();
	}
	return resultData;
}