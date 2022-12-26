#include <iostream>
#include "Stack.h"
#include "TimSort.h"
#include <ctime>


int getMinrun(int size)
{
	int r = 0;
	while (size >= 64)
	{
		r |= size & 1;
		size >>= 1;
	}
	return size + r;
}

void Reverse(int* arr, int size)
{
	int j = size - 1;
	for (int i = 0; i < size; i++)
	{
		if (i >= j)
			break;

		int temp = arr[j];
		arr[j] = arr[i];
		arr[i] = temp;

		j--;
	}
}
//Сортировка вставками
void InsertionSort(int *arr, int l, int r)
{
	for (int i = l + 1; i <= r; i++)
	{
		int temp = arr[i];
		int j = i - 1;
		while (j >= l && arr[j] > temp)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}
}

//Сортировка слиянием
void Merge(int *arr, int first_index, int first_size, int second_size)
{
	int lenl = first_size - first_index + 1,
		lenr = second_size - first_size;
	int second_index = first_index + first_size+1;
	int *first_array=new int[lenl];
	int *second_array=new int[lenr];

	for (int i = 0; i < lenl; i++)
	{
		first_array[i] = arr[i + first_index];
	}
	for (int j = 0; j < lenr; j++)
	{
		second_array[j] = arr[j + second_index];
	}
	int i_first = 0;                                                     
	int i_second = 0;                                                    
	int i_result = first_index;                                          
	int first_count = 0;                                                 
	int second_count = 0;                                                
	int time_to_gallop = 7;                                              
	int middle = 0;                                                      
	int gallop_count = 0;                                                
	bool flag;                                                           
	bool flag_gallop;                                                    
	int left_side;                                                       
	int right_side;                                                      

	while (i_first < lenl && i_second < lenr)
	{
		if (first_array[i_first] <= second_array[i_second])
		{

			arr[i_result] = first_array[i_first];
			gallop_count = 0;
			i_first++;
			i_result++;
			first_count++;
			second_count = 0;

			if ((first_count == time_to_gallop))
			{
				flag = false;
				flag_gallop = false;
				left_side = i_first;
				right_side = first_size;
				middle = (left_side + right_side) / 2;
				while ((flag != true) && (i_first < first_size) && (left_side <= right_side))
				{
					if (first_array[middle] == second_array[i_second])
					{

						while (first_array[middle - 1] == first_array[middle])
						{
							middle--;
						}

						for (int i = i_first; i <= middle; i++)
						{
							arr[i_result] = first_array[i];
							i_result++;
						}
						i_first = middle + 1;
						flag = true;
					}
					else if (first_array[middle] > second_array[i_second])
					{
						right_side = middle - 1;
						middle = (left_side + right_side) / 2;
					}
					while ((first_array[middle] < second_array[i_second]) && (left_side <= right_side))
					{
						left_side = middle + 1;
						gallop_count++;
						middle = (left_side + right_side) / 2;
						flag_gallop = true;
					}
					if (flag_gallop)
					{
						for (int i = i_first; i < gallop_count + i_first; i++)
						{
							arr[i_result] = first_array[i];
							i_result++;
						}
						i_first = i_first + gallop_count;
						flag = true;
					}
				}
			}
		}
		else
		{

			arr[i_result] = second_array[i_second];
			gallop_count = 0;
			i_second++;
			i_result++;
			second_count++;
			first_count = 0;

			if ((second_count == time_to_gallop))
			{
				flag = false;
				flag_gallop = false;
				right_side = i_second;
				left_side = second_size;
				middle = (left_side + right_side) / 2;
				while ((flag != true) && (i_second < second_size) && (right_side <= left_side))
				{
					if (second_array[middle] == first_array[i_first])
					{
						for (int i = i_second; i <= middle; i++)
						{
							arr[i_result] = second_array[i];
							i_result++;
						}
						i_second = middle + 1;
						flag = true;
					}
					else if (second_array[middle] > first_array[i_first])
					{
						left_side = middle - 1;
						middle = (left_side + right_side) / 2;
					}
					while ((second_array[middle] < first_array[i_first]) && (left_side >= right_side))
					{
						right_side = middle + 1;
						gallop_count++;
						middle = (left_side + right_side) / 2;
						flag_gallop = true;
					}
					if (flag_gallop)
					{
						for (int i = i_second; i < gallop_count + i_second; i++)
						{
							arr[i_result] = second_array[i];
							i_result++;
						}
						i_second = i_second + gallop_count;
						flag = true;
					}
				}
			}
		}
	}

	while (i_first < lenl)
	{
		arr[i_result] = first_array[i_first];
		i_first++;
		i_result++;
	}
	while (i_second < lenr)
	{
		arr[i_result] = second_array[i_second];
		i_second++;
		i_result++;
	}
}

int TimSort(int* arr, int size)
{
	if (size < 64)
		InsertionSort(arr, 0, size - 1);
	else
	{
		int minrun = getMinrun(size);
		Stack stack(3);
		Run run;
		run.start = 0;
		run.size = 1;

		for (int i = 1; i < size;)
		{
			if (arr[i] >= arr[i - 1])
			{
				while (arr[i] >= arr[i - 1] && i < size)
				{
					run.size++;
					i++;
				}
				if (run.size < minrun && i < size)
				{
					while (run.size < minrun && i < size)
					{
						run.size++;
						i++;
					}
					InsertionSort(arr, run.start, run.start + run.size - 1);
				}
				stack.push(run);
				run.start = i;
				run.size = 1;

				if (i == size - 1)
				{
					stack.push(run);
				}
				i++;
			}
			else if (arr[i] < arr[i - 1])
			{
				while (arr[i] < arr[i - 1] && i < size)
				{
					run.size++;
					i++;
				}
				Reverse(&arr[run.start], run.size);
				if (run.size < minrun && i < size)
				{
					while (run.size < minrun && i < size)
					{
						run.size++;
						i++;
					}
					InsertionSort(arr, run.start, run.start + run.size - 1);
				}
				stack.push(run);
				run.start = i;
				run.size = 1;

				if (i == size - 1)
				{
					stack.push(run);
				}
				i++;
			}
		}
		
			Run X, Y, Z;

			if (stack.getSize() >= 1)
			{
				X = stack.peak();
				stack.pop();
				Y = stack.peak();
				stack.pop();
			}

			if (stack.isEmpty())
			{
				Merge(arr, Y.start, Y.start + Y.size - 1, X.start + X.size - 1);
				stack.push(Y);
				return 0;
			}

			while (stack.getSize() >= 1 && (stack.peak().size <= (X.size + Y.size) || Y.size <= X.size))
			{
				if (X.size >= Y.size)
				{
					Merge(arr, Y.start, Y.start + Y.size - 1, X.start + X.size - 1);
					Y.size += X.size;
					stack.push(Y);
				}
				else if (stack.getSize() >= 2 && stack.peak().size <= (X.size + Y.size))
				{
					if (X.size <= stack.peak().size)
					{
						Merge(arr, Y.start, Y.start + Y.size - 1, X.start + X.size - 1);
						Y.size += X.size;
						stack.push(Y);
					}
					else
					{
						Z = stack.peak();
						stack.pop();
						Merge(arr, Y.start, Y.start + Y.size - 1, Z.start + Z.size - 1);
						Y.size += Z.size;
						stack.push(Y);
					}
				}
			}
		while (stack.getSize() > 0)
		{
			Run X, Y;
			X = stack.peak();
			stack.pop();
			Y = stack.peak();
			stack.pop();

			Merge(arr, Y.start, Y.start + Y.size - 1, X.start + X.size - 1);
			run.size = Y.size + X.size;
			run.start = X.start;
			stack.push(run);
		}
	}
}