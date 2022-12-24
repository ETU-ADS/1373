#include <math.h>
#include <iostream>
#include "sortFunctions.h"
#include "stackFunctions.h"
#include "listFunctions.h"


void swapArray(int* array, int lenght, int beggining)
{
	int s = lenght / 2;
	s = s + beggining;
	int j = lenght + beggining - 1;
	for (int i = beggining; i < s; i++)
	{
		int tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
		j--;
	}
}

void insertionSort(int* array, unsigned lenght, unsigned beggining, bool ascendingOrDescending) // Функция сортировки вставками (по выбору - возрастание или убывание)
{
	if (ascendingOrDescending) // По возрастанию
	{
		for (int i = beggining + 1; i < beggining + lenght; i++)
		{
			for (int j = i; array[j - 1] > array[j] && j > beggining; j--)
			{
				int tmp = array[j - 1];
				array[j - 1] = array[j];
				array[j] = tmp;
			}
		}
	}
	else // По убыванию
	{
		for (int i = beggining + 1; i < beggining + lenght; i++)
		{
			for (int j = i; array[j - 1] < array[j] && j > beggining; j--)
			{
				int tmp = array[j - 1];
				array[j - 1] = array[j];
				array[j] = tmp;
			}
		}
	}
}

void mergeSort(int* array, int firstBeggining, int secondBeggining, int firstLenght, int secondLenght) // Функция сортировки слиянием
{
	int firstBeg = firstBeggining, secondBeg = secondBeggining, y = 0, totalLength = firstLenght + secondLenght;
	int* bigBufferArray = new int[totalLength];
	if (true)
	{
		int bigBufferPosition = 0;
		int firstPosition = firstBeggining;
		int previousArrayWas = 2; // Если '0', то первый. Если '1', то второй
		int repetitions = 0;
		int j = secondBeggining, i = firstBeggining;
		while (j < (secondBeggining + secondLenght) && i < (firstLenght + firstBeggining))
		{
			if (array[j] <= array[i]) // Очередной элемент из второго подмассива оказался меньше элемента из первого
			{
				if (repetitions == 6) // Режим галопа
				{
					int point = 0;
					int stopNumber = secondBeggining + secondLenght;
					bool flag = false;
					int rightBorder = 0;
					while (flag != true)
					{
						if ((j + pow(2, point)) < (secondBeggining + secondLenght))
						{
							int place = j + pow(2, point);
							if (array[place] <= array[i])
							{
								point++;
								rightBorder = j + pow(2, point);
							}
							else
							{
								flag = true;
								if (point == 0)
								{
									point = 1;
									rightBorder = j + pow(2, point);
								}
							}
						}
						else
						{
							rightBorder = secondBeggining + secondLenght - 1;
							if (point == 0)
								point = 1;
							break;
						}
					}
					for (int a = (j + pow(2, point - 1)); a <= rightBorder; a++)
					{
						stopNumber = a;
						if (array[a] > array[i])
						{
							break;
						}
					}
					for (j; j < stopNumber; j++)
					{
						bigBufferArray[bigBufferPosition] = array[j];
						bigBufferPosition++;
					}
				}
				else // Стандартный режим
				{
					bigBufferArray[bigBufferPosition] = array[j];
					bigBufferPosition++;
					j++;
					if (previousArrayWas == 1)
						repetitions++;
					else
						repetitions = 0;
					previousArrayWas = 1;
				}
			}
			else // Очередной элемент из первого подмассива оказался меньше элемента из второго
			{
				if (repetitions == 6) // Режим галопа
				{
					int point = 0;
					int stopNumber = firstLenght + firstBeggining;
					bool flag = false;
					int rightBorder = 0;
					while (flag != true)
					{
						if ((i + pow(2, point)) < (firstLenght + firstBeggining))
						{
							int place = i + pow(2, point);
							if (array[place] <= array[j])
							{
								point++;
								rightBorder = i + pow(2, point);
							}
							else
							{
								flag = true;
								if (point == 0)
								{
									point = 1;
									rightBorder = i + pow(2, point);
								}
							}
						}
						else
						{
							rightBorder = firstLenght + firstBeggining - 1;
							if (point == 0)
								point = 1;
							break;
						}
					}
					for (int a = (i + pow(2, point - 1)); a <= rightBorder; a++)
					{
						stopNumber = a;
						if (array[a] > array[j])
						{
							break;
						}
					}
					for (i; i < stopNumber; i++)
					{
						bigBufferArray[bigBufferPosition] = array[i];
						bigBufferPosition++;
					}
				}
				else // Стандартный режим
				{
					bigBufferArray[bigBufferPosition] = array[i];
					bigBufferPosition++;
					i++;
					if (previousArrayWas == 0)
						repetitions++;
					else
						repetitions = 0;
					previousArrayWas = 0;
				}
			}
			if (j == (secondLenght + secondBeggining) && i < (firstLenght + firstBeggining)) // Второй подмассив закончился раньше первого
			{
				for (i; i < (firstLenght + firstBeggining); i++)
				{
					bigBufferArray[bigBufferPosition] = array[i];
					bigBufferPosition++;
				}
			}
			if (i == (firstLenght + firstBeggining) && j < (secondLenght + secondBeggining)) // Первый подмассив закончился раньше второго
			{
				for (j; j < (secondLenght + secondBeggining); j++)
				{
					bigBufferArray[bigBufferPosition] = array[j];
					bigBufferPosition++;
				}
			}
		}
		if (firstBeg < secondBeg) // Переносим отсортированные значения в изначальный массив
		{
			for (int i = 0; i < totalLength; i++)
			{
				array[firstBeg] = bigBufferArray[i];
				firstBeg++;
			}
		}
		else
		{
			for (int i = 0; i < totalLength; i++)
			{
				array[secondBeg] = bigBufferArray[i];
				secondBeg++;
			}
		}
		// Высвобождаем динамическую память
		delete bigBufferArray;
	}
}

void creatingRuns(int* array, unsigned lenght, int minrun, List& ourList, Stack& ourStack) // Функция разбиения массива на подмассивы
{
	int begin = 0;
	for (int i = 0; i < lenght; i++)
	{
		int j = i + 1;
		if (array[i] <= array[j]) // Случай сортировки подмассива по возрастанию
		{
			bool isMinrunBroken = false; // false - если упорядоченность ломается, true - если упорядоченность сохраняется
			int len;
			if ((i + minrun) < lenght)
				len = minrun;
			else
				len = lenght - begin;
			for (int a = i + 1; a < len + begin; a++)
			{
				if (array[a - 1] > array[a])
				{
					insertionSort(array, len, begin, 1);
					isMinrunBroken = true;
					break;
				}
			}
			if ((begin + minrun) < lenght)
				i = i + minrun - 1;
			else
				i = lenght - 1;
			if (isMinrunBroken == false && i < (lenght - 1))
			{
				while (array[i] <= array[i + 1])
				{
					i++;
				}
			}
			ourStack.push(ourList);
			ourList.dataInserting(begin, i - begin + 1);
			if (i < (lenght - 1))
				begin = i + 1;
		}
		else // Случай сортировки подмассива по убыванию
		{
			bool isMinrunBroken = false; // false - если упорядоченность ломается, true - если упорядоченность сохраняется
			int len;
			if ((begin + minrun) < lenght)
				len = minrun;
			else
				len = lenght - begin;
			for (int a = i + 1; a < len + begin; a++)
			{
				if (array[a - 1] < array[a])
				{
					insertionSort(array, len, begin, 0);
					isMinrunBroken = true;
					break;
				}
			}
			if ((begin + minrun) < lenght)
				i = i + minrun - 1;
			else
				i = lenght - 1;
			if (isMinrunBroken == false && i < (lenght - 1))
			{
				while (array[i] >= array[i + 1])
				{
					i++;
				}
			}
			swapArray(array, i - begin + 1, begin);
			ourStack.push(ourList);
			ourList.dataInserting(begin, i - begin + 1);
			if (i < (lenght - 1));
			begin = i + 1;
		}
	}
}
