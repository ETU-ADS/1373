#include <iostream>
#include <ctime>
#include "Vector.h"
#include "Stack.h"

struct Run 
{
	int size = 0;
	int index_start = 0;
};

int MinIndex(Run x, Run y)
{
	if (x.index_start > y.index_start)
	{
		return y.index_start;
	}
	else
	{
		return x.index_start;
	}
}

void Reverse(Vector& arr, int start, int end)
{
	int temp;
	for (int i = start; i < end / 2; i++)
	{
		temp = arr[i];
		arr[i] = arr[end - 1 - i];
		arr[end - 1 - i] = temp;
	}
}


void printArray(int size_of_array, Vector arr)
{
	for (int i = 0; i < size_of_array; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}



void Merge(Vector& arr, int first_index, int first_size, int second_size) 
{
	int second_index = first_index + first_size;

	Vector first_array(first_size);
	Vector second_array(second_size);

	for (int i = 0; i < first_size; i++)
	{
		first_array[i] = arr[i + first_index];
		/*std::cout << arr[i + first_index] << " ";*/
	}
	/*std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;*/

	for (int j = 0; j < second_size; j++)
	{
		second_array[j] = arr[j + second_index];
		/*std::cout << arr[j + second_index] << " ";*/
	}
	/*std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;*/

	int i_first = 0;                                                     //Iterator of first array
	int i_second = 0;                                                    //Iterator of second array
	int i_result = first_index;                                          //Iterator of result array

	int first_count = 0;                                                 //Counter of first array
	int second_count = 0;                                                //Counter of first array
	int time_to_gallop = 7;                                              //7

	//for galloping
	int middle = 0;                                                      //middle of array
	int gallop_count = 0;                                                //how many elements need to add to array after galloping
	bool flag;                                                           //check main while in gallopintg
	bool flag_gallop;                                                    //check elements in galloping
	int left_side;                                                       //left border of array
	int right_side;                                                      //right border of array

	while (i_first < first_size && i_second < second_size)
	{
		/*std::cout << first_array[i_first] << "                         " << second_array[i_second] << std::endl;*/
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
		/*std::cout << arr[i_result] << std::endl;*/
	}

	while (i_first < first_size)
	{
		arr[i_result] = first_array[i_first];
		/*std::cout << std::endl << std::endl << first_array[i_first] << std::endl << std::endl;*/
		i_first++;
		i_result++;
	}
	while (i_second < second_size)
	{
		arr[i_result] = second_array[i_second];
		i_second++;
		i_result++;
	}
	/*printArray(arr.get_size(), arr);*/
}


void InsertionSort(Vector& arr, int start, int end)
{
	for (int i = start + 1; i < end; i++)
	{
		int j = i - 1;
		int temp = arr[i];
		while ((j >= start) && (temp < arr[j]))
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}

}


int GetMinrun(int number_of_elements)
{
	int odd = 0;          
	while (number_of_elements >= 64) 
	{
		odd |= number_of_elements & 1;
		number_of_elements >>= 1;
	}
	return number_of_elements + odd;
}


void Timsort(Vector& arr, int size_of_array)
{

	Run run;

	Run x;
	Run y;
	Run z;

	Stack <Run> run_stack;

	int size_of_stack = 0;

	run.index_start = 0;
	run.size = 1;

	bool flag_while = false;
	int insertion_check = 1;
	int minrun = GetMinrun(size_of_array);
	int i = 0;
	while (i < size_of_array - 1)
	{
		flag_while = true;
		if (arr[i] <= arr[i + 1])
		{
			while (true)
			{
				if (arr[i] <= arr[i + 1])
				{
					insertion_check++;
					i++;
					run.size++;
				}
				else
				{
					while ((run.size < minrun) && (i < size_of_array - 1))
					{
						i++;
						run.size++;
					}
					if (insertion_check != size_of_array)
					{
						InsertionSort(arr, run.index_start, run.size + run.index_start);
						/*printArray(arr.get_size(), arr);
						std::cout << std::endl;
						std::cout << std::endl;*/

					}
					run_stack.push(run);
					size_of_stack++;
					run.index_start = i + 1;
					run.size = 1;
					break;
				}
			}
			i++;
		}
		else
		{
			insertion_check = 1;
			run.index_start = i;
			while (true)
			{
				if (arr[i] > arr[i + 1])
				{
					insertion_check++;
					i++;
					run.size++;
				}
				else
				{

					Reverse(arr, run.index_start, run.size + run.index_start);
					/*printArray(arr.get_size(), arr);*/
					/*std::cout << std::endl;
					std::cout << std::endl;*/


					while ((run.size < minrun) && (i < size_of_array - 1))
					{
						i++;
						run.size++;
					}

					if (insertion_check != size_of_array)
					{
						InsertionSort(arr, run.index_start, run.size + run.index_start);
						/*printArray(arr.get_size(), arr);
						std::cout << std::endl;
						std::cout << std::endl;*/
					}
					run_stack.push(run);
					size_of_stack++;
					run.index_start = i + 1;
					run.size = 1;
					break;
				}
			}
			i++;
		}

		if (run_stack.GetSize() >= 2)
		{
			x = run_stack.peak();
			run_stack.pop();
			y = run_stack.peak();
			run_stack.push(x);

		}

		while ((run_stack.GetSize() >= 2) && ((x.size >= y.size) || (run_stack.GetSize() >= 3) && (z.size <= y.size + x.size)))
		{
			while ((run_stack.GetSize() >= 2) && ((x.size >= y.size)))
			{

				Merge(arr, y.index_start, y.size, x.size);

				y.size += x.size;
				y.index_start = MinIndex(y, x);

				run_stack.pop();
				run_stack.pop();
				run_stack.push(y);

				size_of_stack--;

				if (run_stack.GetSize() >= 2)
				{
					x = run_stack.peak();
					run_stack.pop();
					y = run_stack.peak();
					run_stack.push(x);
				}

			}

			if (run_stack.GetSize() >= 3)
			{
				x = run_stack.peak();
				run_stack.pop();
				y = run_stack.peak();
				run_stack.pop();
				z = run_stack.peak();
				run_stack.push(y);
				run_stack.push(x);
			}

			while ((run_stack.GetSize() >= 3) && (z.size <= y.size + x.size))
			{
				
				if (x.size <= z.size)
				{
					Merge(arr, y.index_start, y.size, x.size);
					y.size += x.size;
					y.index_start = MinIndex(y, x);
					x.size = 0;
					run_stack.pop();
					run_stack.pop();
					run_stack.push(y);
					size_of_stack--;
				}
				else
				{
					Merge(arr, z.index_start, z.size, y.size);
					y.size += z.size;
					y.index_start = MinIndex(y, z);
					z.size = 0;
					run_stack.pop();
					run_stack.pop();
					run_stack.push(y);
					size_of_stack--;
				}

				if (run_stack.GetSize() >= 3)
				{
					x = run_stack.peak();
					run_stack.pop();
					y = run_stack.peak();
					run_stack.pop();
					z = run_stack.peak();
					run_stack.push(y);
					run_stack.push(x);
				}

			}

			if (run_stack.GetSize() >= 2) 
			{
				x = run_stack.peak();
				run_stack.pop();
				y = run_stack.peak();
				run_stack.push(x);
			}
			if (run_stack.GetSize() >= 3)
			{
				x = run_stack.peak();
				run_stack.pop();
				y = run_stack.peak();
				run_stack.pop();
				z = run_stack.peak();
				run_stack.push(y);
				run_stack.push(x);
			}

		}


	}
	while (size_of_stack > 1)
	{
		if (!run_stack.Empty()) 
		{
			x = run_stack.peak();
			run_stack.pop();
		}
		if (!run_stack.Empty()) 
		{
			y = run_stack.peak();
			run_stack.pop();
		}
		Merge(arr, y.index_start, y.size, x.size);
		y.size += x.size;
		y.index_start = MinIndex(x, y);
		run_stack.push(y);
		size_of_stack--;
	}
}




int main() 
{

	Vector arr;

	srand(time(NULL));

	for (int i = 0; i < 5000; i++)
	{
		arr.push_back(rand() % 1000);
	}

	printArray(arr.get_size(), arr);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	Timsort(arr, arr.get_size());
	printArray(arr.get_size(), arr);
	

	return 0;
}




