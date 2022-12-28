#include <iostream>
#include <algorithm>

using namespace std;
const int RUN = 32;


void insertionSort(int arr[], int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		int temp = arr[i];
		int j = i - 1;
		while (arr[j] > temp && j >= left)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}
}

// Слияние малых массивов
void merge(int arr[], int l, int m, int r)
{
	// Разбиваем массив на левый и правый
	int len1 = m - l + 1, len2 = r - m;

	int * left = new int[len1];
	int * right = new int[len2];

	for (int i = 0; i < len1; i++)
		left[i] = arr[l + i];
	for (int i = 0; i < len2; i++)
		right[i] = arr[m + 1 + i];

	int i = 0;
	int j = 0;
	int k = l;


	while (i < len1 && j < len2)
	{
		if (left[i] <= right[j])
		{
			arr[k] = left[i];
			i++;
		}
		else
		{
			arr[k] = right[j];
			j++;
		}
		k++;
	}


	while (i < len1)
	{
		arr[k] = left[i];
		k++;
		i++;
	}

	
	while (j < len2)
	{
		arr[k] = right[j];
		k++;
		j++;
	}
}

//Реализация слияния подмассивов
void timSort(int arr[], int n)
{
	// сортируем подмассивы размера RUN
	for (int i = 0; i < n; i += RUN)
		insertionSort(arr, i, min((i + 31), (n - 1)));

	// начинаем слияние размера RUN (or 32). он возрастет до 64, затем 128, 256 и т. д. ....
	for (int size = RUN; size < n; size = 2 * size)
	{
		//Ставим начальную точку левого массива.Мы будем сливать воедино arr[left..left+size-1] и arr[left+size, left+2*size-1]
		for (int left = 0; left < n; left += 2 * size)
		{
			// находим последнюю точку левого подмассива
			// mid+1 стартовая точка правого
			int mid = left + size - 1;
			int right = min((left + 2 * size - 1), (n - 1));

			// сливаем массивы
			merge(arr, left, mid, right);
		}
	}
}

// печатаем массив
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d  ", arr[i]);
	printf("\n");
}


int main()
{
	//int  arr[] = {5, 21, 7, 23, 19, 78, 9, 15, 44, 32, 98, 56, 19};
	int n;

	cout << "Input num of elements: " << endl;
	cin >> n;
	cout << "\n\nInput elements of array: " << endl << endl;
	int *arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	//int n = sizeof(arr) / sizeof(arr[0]);
	printf("Given Array is\n");
	printArray(arr, n);

	timSort(arr, n);

	printf("After Sorting Array is\n");
	printArray(arr, n);

	delete[] arr;
	return 0;
}