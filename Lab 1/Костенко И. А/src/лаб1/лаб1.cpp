#include <iostream>
#include "List.h"
#include <string>
#include "UnitTest.h"
using namespace std;

void sortingStation(string input) {
	int index = 0;
	bool isCrashed = true;
	ArrayList<char> queueCall = ArrayList<char>(32);
	Stack<char> stack = Stack<char>();
	while (true)
	{
		ArrayList<char> token = ArrayList<char>(5);
		if ((input.length() == index))
		{
			break;
		}
		while (input[index] != ' ' && (input.length() != index))
		{
			token.add(input[index]);
			index++;
		}
		while (input[index] == ' ' && (input.length() != index))
		{
			index++;
		}
		token.add(0);
		if (token[0] >= 48 && token[0] <= 57 && token[1] == 0)
		{
			isCrashed = false;
			queueCall.add(token[0]);
		}
		else {
			isCrashed = false;
			if ((token[0] == 's' && token[1] == 'i' && token[2] == 'n' && token[3] == 0) || (token[0] == 'c' && token[1] == 'o' && token[2] == 's' && token[3] == 0))
			{
				if ((token[0] == 's' && token[1] == 'i' && token[2] == 'n' && token[3] == 0))
				{
					stack.push('s');
				}
				else
				{
					stack.push('c');
				}
			}
		}
		if ((token[1] == 0) && ((token[0] == '+') || (token[0] == '-') || (token[0] == '*') || (token[0] == '/') || (token[0] == '^')))
		{
			isCrashed = false;
			if (!stack.isEmpty())
			{
				if (token[0] == '^')
				{
					while ((!stack.isEmpty()) && stack.peak() == '^')
					{
						queueCall.add(stack.pop());
					}
					stack.push(token[0]);
				}
				else
				{
					if ((token[0] == '*') || (token[0] == '/'))
					{
						while ((!stack.isEmpty()) && ((stack.peak() == '^') || (stack.peak() == '*') || (stack.peak() == '/')))
						{
							queueCall.add(stack.pop());
						}
						stack.push(token[0]);
					}
					else
					{

						while ((!stack.isEmpty()) && ((stack.peak() == '+') || (stack.peak() == '-') || (stack.peak() == '*') || (stack.peak() == '/') || (stack.peak() == '^')))
						{
							queueCall.add(stack.pop());
						}
						stack.push(token[0]);
					}
				}
			}
			else { 
				isCrashed = false; 
			stack.push(token[0]); }
		}

		if ((token[0] == ')' && token[1] == 0))
		{
			isCrashed = false;
			while (stack.peak() != '(')
			{
				if (stack.isEmpty())
				{
					cout << "Ошибка, неверный токен-скобка:";
					token.print();
					return;
				}
				queueCall.add(stack.pop());
			}
			stack.pop();
			if (stack.peak() == ('s'))
			{
				queueCall.add(stack.pop());
			}
			if (stack.peak() == ('c'))
			{
				queueCall.add(stack.pop());
			}
		}

		if (token[0] == '(' && token[1] == 0) {
			stack.push('(');
		}
		if (isCrashed == true)
		{
			cout << "Неверный токен: ";
			token.print();
			return;
		}
	}
	while (!stack.isEmpty())
	{
		if (stack.peak() == '(')
		{
			cout << "Ошибка, открывающая скобка на вершине стека:";
			return;
		}
		queueCall.add(stack.pop());
	}
	queueCall.print();
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	tests();
	ArrayList<int> list = ArrayList<int>(5);
	string input;
	getline(cin, input, '\n');
	sortingStation(input);
	system("pause");
}
