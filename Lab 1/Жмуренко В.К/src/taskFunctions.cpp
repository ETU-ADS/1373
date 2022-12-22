#include "listFunctions.h"
#include "stackFunctions.h"
#include "taskFunctions.h"
#include <iostream>
#include <string>
using namespace std;

void dataVerification(string data, int arrayLenght, bool & resultOfChecking) // Функция проверки корректности введенных данных
{
	int openingCounter = 0, closingCounter = 0;
	for (int i=0; i < arrayLenght; i++)
	{
		switch (data[i])
		{
			case ' ':
				break;
			case '0':
				break;
			case '1':
				break;
			case '2':
				break;
			case '3':
				break;
			case '4':
				break;
			case '5':
				break;
			case '6':
				break;
			case '7':
				break;
			case '8':
				break;
			case '9':
				break;
			case '+':
				break;
			case '-':
				break;
			case '/':
				break;
			case '*':
				break;
			case '(':

				break;
			case ')':

				break;
			case 's':
				if (data[i + 1] == 'i' && data[i + 2] == 'n')
				{
					i = i + 2;
					break;
				}
				else
				{
					std::cout << "Error. You entered invalid characters\n";
					resultOfChecking = 0;
					break;
				}
			case 'c':
				if (data[i + 1] == 'o' && data[i + 2] == 's')
				{
					i = i + 2;
					break;
				}
				else
				{
					std::cout << "Error. You entered invalid characters\n";
					resultOfChecking = 0;
					break;
				}
			case '\0':
				break;
			default:
				std::cout << "Error. You entered invalid characters\n";
				resultOfChecking = 0;
				break;
		}
		if (resultOfChecking == 0)
			break;
	}
	if (resultOfChecking!= 0 && openingCounter != closingCounter)
	{
		cout << "Error. Incorrect data entered\n";
		resultOfChecking = 0;
	}
}
void sortingStation(string data, int arrayLenght, bool resultOfChecking)
{
	if (resultOfChecking == 1)
	{
		List Stack = List();
		stack stackWorking;
		box* listBeggining = nullptr;
		bool Error = 0;
		for (int i = 0; i < arrayLenght; i++)
		{
			switch (data[i])
			{
				case ' ':
					break;

				case '+':
					listBeggining = Stack.addressGetter();
					while (listBeggining!=nullptr && (listBeggining->Inf == '-' || listBeggining->Inf == '+' || listBeggining->Inf == '*' || listBeggining->Inf == '/'))
					{
						cout << listBeggining->Inf;
						stackWorking.pop(Stack);
						listBeggining = Stack.addressGetter();
					}
					listBeggining = stackWorking.push(Stack);
					Stack.dataInserting('+');
					break;

				case '-':
					listBeggining = Stack.addressGetter();
					while (listBeggining != nullptr && (listBeggining->Inf == '-' || listBeggining->Inf == '+' || listBeggining->Inf == '*' || listBeggining->Inf == '/'))
					{
						cout << listBeggining->Inf;
						stackWorking.pop(Stack);
						listBeggining = Stack.addressGetter();
					}
					listBeggining = stackWorking.push(Stack);
					Stack.dataInserting('-');
					break;

				case '/':
					listBeggining = Stack.addressGetter();
					while (listBeggining != nullptr && (listBeggining->Inf == '*' || listBeggining->Inf == '/'))
					{
						cout << listBeggining->Inf;
						stackWorking.pop(Stack);
						listBeggining = Stack.addressGetter();
					}
					listBeggining = stackWorking.push(Stack);
					Stack.dataInserting('/');
					break;

				case '*':
					listBeggining = Stack.addressGetter();
					while (listBeggining != nullptr && (listBeggining->Inf == '*' || listBeggining->Inf == '/'))
					{
						cout << listBeggining->Inf;
						stackWorking.pop(Stack);
						listBeggining = Stack.addressGetter();
					}
					listBeggining = stackWorking.push(Stack);
					Stack.dataInserting('*');
					break;

				case 's':
					listBeggining = Stack.addressGetter();
					listBeggining = stackWorking.push(Stack);
					Stack.dataInserting('s');
					i = i + 2;
					break;

				case 'c':
					listBeggining = Stack.addressGetter();
					listBeggining = stackWorking.push(Stack);
					Stack.dataInserting('c');
					i = i + 2;
					break;

				case '(':
					listBeggining = Stack.addressGetter();
					listBeggining = stackWorking.push(Stack);
					Stack.dataInserting('(');
					break;

				case ')':
					listBeggining = Stack.addressGetter();
					if (listBeggining == nullptr)
					{
						Error = 1;
						break;
					}
					else
					{
						while (listBeggining != nullptr && listBeggining->Inf != '(')
						{
							cout << listBeggining->Inf;
							stackWorking.pop(Stack);
							listBeggining = Stack.addressGetter();
							if (listBeggining == nullptr)
							{
								Error = 1;
								break;
							}
						}
						if (listBeggining != nullptr && listBeggining->Inf == '(')
							stackWorking.pop(Stack);
						listBeggining = Stack.addressGetter();
						if (listBeggining != nullptr && listBeggining->Inf == 's')
						{
							cout << "sin";
							stackWorking.pop(Stack);
							listBeggining = Stack.addressGetter();
						}
						if (listBeggining != nullptr && listBeggining->Inf == 'c')
						{
							cout << "cos";
							stackWorking.pop(Stack);
							listBeggining = Stack.addressGetter();
						}
					}
					break;

				case '\0':
					while (bool answer = stackWorking.isEmpty(Stack))
					{
						listBeggining = Stack.addressGetter();
						if (listBeggining->Inf == '(')
						{
							Error = 1;
							break;
						}
						else
						{
							cout << listBeggining->Inf;
							stackWorking.pop(Stack);
						}
						listBeggining = Stack.addressGetter();
					}
					break;

				default:
					cout << data[i];
					break;
			}
			if (Error == 1)
			{
				cout << "\nError. Incorrect data entered\n";
				break;
			}
		}
	}
}

unsigned strLen(string data)
{
	int l=0;
	for (int i = 0; data[i] != '\0'; i++)
		l++;
	l++;
	return l;
}