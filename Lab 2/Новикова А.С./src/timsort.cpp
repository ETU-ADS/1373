#include <ctime>
#include "timsort.h"

void randomInput(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		arr[i] = rand() % 150;
}

void manualInput(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << "Enter element #" << i + 1 << ": ";
		std::cin >> arr[i];
	}
}

int getMinrun(int size)
{
	int flag = 0;
	while (size >= 64)
	{
		flag |= size & 1;
		size >>= 1;
	}
	return size + flag;
}

void reverse(int* arr, int size)
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

void merge(int* arr, int left, int mid, int right)
{
	int leftLen = mid - left + 1;
	int* leftArr = new int[leftLen];

	for (int i = 0; i < leftLen; i++)
		leftArr[i] = arr[left + i];

	int rightLen = right - mid;
	int* rightArr = new int[rightLen];

	for (int i = 0; i < rightLen; i++)
		rightArr[i] = arr[mid + 1 + i];

	int i = 0;
	int j = 0;
	int k = left;

	int leftGallopCounter = 0;
	int rightGallopCounter = 0;

	int step = 1;

	while (i < leftLen && j < rightLen)
	{
		if (leftArr[i] <= rightArr[j])
		{
			arr[k] = leftArr[i];
			i++;
			leftGallopCounter++;
			if (rightGallopCounter > 0)
				rightGallopCounter = 0;
		}
		else
		{
			arr[k] = rightArr[j];
			j++;
			rightGallopCounter++;
			if (leftGallopCounter > 0)
				leftGallopCounter = 0;
		}
		k++;

		if (leftGallopCounter == 7)
		{
			while (leftArr[i + step] <= rightArr[j] && i + step < leftLen && j < rightLen)
			{
				if (i + step >= leftLen)
				{
					for (int x = i; x < leftLen; x++)
					{
						arr[k] = leftArr[x];
						k++;
					}
					break;
				}
				for (int x = i; x < i + step; x++)
				{
					arr[k] = leftArr[x];
					k++;
				}
				i += step;
				step++;
			}
			step = 1;
			leftGallopCounter = 0;
		}
		if (rightGallopCounter == 7)
		{
			while (rightArr[j + step] <= leftArr[i] && j + step < rightLen && i < leftLen)
			{
				if (j + step >= rightLen)
				{
					for (int x = j; x < rightLen; x++)
					{
						arr[k] = rightArr[x];
						k++;
					}
					break;
				}
				for (int x = j; x < j + step; x++)
				{
					arr[k] = rightArr[x];
					k++;
				}
				j += step;
				step++;
			}
			step = 1;
			rightGallopCounter = 0;
		}
	}
	
	while (i < leftLen)
	{
		arr[k] = leftArr[i];
		k++;
		i++;
	}
	while (j < rightLen)
	{
		arr[k] = rightArr[j];
		k++;
		j++;
	}

	delete[] leftArr;
	delete[] rightArr;
}

void insertionSort(int* arr, int left, int right)
{
	int j, key;
	for (int i = left + 1; i <= right; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= left && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

void timsort(int* arr, int size)
{
	if (size < 64)
		insertionSort(arr, 0, size - 1);
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
					insertionSort(arr, run.start, run.start + run.size - 1);
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
				reverse(&arr[run.start], run.size);
				if (run.size < minrun && i < size)
				{
					while (run.size < minrun && i < size)
					{
						run.size++;
						i++;
					}
					insertionSort(arr, run.start, run.start + run.size - 1);
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
				merge(arr, Y.start, Y.start + Y.size - 1, X.start + X.size - 1);
				stack.push(Y);
			}

			while (stack.getSize() >= 1 && (stack.peak().size <= (X.size + Y.size) || Y.size <= X.size))
			{
				if (X.size >= Y.size)
				{
					merge(arr, Y.start, Y.start + Y.size - 1, X.start + X.size - 1);
					Y.size += X.size;
					stack.push(Y);
				}
				else if (stack.getSize() >= 2 && stack.peak().size <= (X.size + Y.size))
				{
					if (X.size <= stack.peak().size)
					{
						merge(arr, Y.start, Y.start + Y.size - 1, X.start + X.size - 1);
						Y.size += X.size;
						stack.push(Y);
					}
					else
					{
						Z = stack.peak();
						stack.pop();
						merge(arr, Y.start, Y.start + Y.size - 1, Z.start + Z.size - 1);
						Y.size += Z.size;
						stack.push(Y);
					}
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

			merge(arr, Y.start, Y.start + Y.size - 1, X.start + X.size - 1);
			run.size = Y.size + X.size;
			run.start = X.start;
			stack.push(run);
		}
	}
}
