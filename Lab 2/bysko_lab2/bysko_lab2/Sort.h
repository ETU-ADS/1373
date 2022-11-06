#pragma once

#include "Array.h"
#include "Stack.h"
//insertion sort
void InsertionSort(int* arr, int size) {
	for (int i = 1; i < size; i++) {
		int key = arr[i];
		int j = i - 1;
		while (j > -1 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}
//function to merge subarrays
void Merge(Array<int>& arr, int start_1, int len_1, int len_2) {

	int start_2 = start_1 + len_1;	//calculating the size of the second temporary array

	Array<int> arr_1(len_1);
	Array<int> arr_2(len_2);

	for (int i = 0; i < len_1; i++) {	//copying data to temporary arrays
		arr_1[i] = arr[start_1 + i];
	}
	for (int i = 0; i < len_2; i++) {
		arr_2[i] = arr[start_2 + i];
	}

	int x = 0, y = 0, i = start_1;	//array indexes

	int count_1 = 0, count_2 = 0, max = 7,	//for gallop mode
		plusIndex_1 = 1, plusIndex_2 = 1;

	while (x + y < len_1 + len_2) {
		if (arr_1[x] <= arr_2[y] && (x < len_1)) {
			arr[i] = arr_1[x];
			i++;
			x++;

			count_2 = 0;
			plusIndex_2 = 1;
			count_1++;

			if (count_1 > max) {	//gallop mode
				while (arr_1[x + plusIndex_1] <= arr_2[y] && x + plusIndex_1 < len_1 && y < len_2) {
					for (int j = x; j < x + plusIndex_1; j++) {
						arr[i] = arr_1[j];
						i++;
					}
					x += plusIndex_1;
					plusIndex_1 += 1;

					//
					if (x + plusIndex_1 > len_1) {
						plusIndex_1 = len_1 - x;
					}
					//
				}
				count_1 = 0;
				plusIndex_1 = 1;
			}
		}
		else if (y < len_2)
		{
			arr[i] = arr_2[y];
			i++;
			y++;

			count_1 = 0;
			plusIndex_1 = 1;
			count_2++;

			if (count_2 > max) {	//gallop mode
				int iterat_2 = y + plusIndex_2;
				while (arr_1[x] > arr_2[y + plusIndex_2] && y + plusIndex_2 < len_2 && x < len_1) {
					for (int j = y; j < y + plusIndex_2; j++) {
						arr[i] = arr_2[j];
						i++;
					}
					y += plusIndex_2;
					plusIndex_2 += 1;
				}
				count_2 = 0;
				plusIndex_2 = 1;

				//
				if (y + plusIndex_2 > len_2) {
					plusIndex_2 = len_2 - y;
				}
				//
			}
		}
		if (x >= len_1) {
			while (y < len_2) {
				arr[i] = arr_2[y];
				i++;
				y++;
			}
		}
		if (y >= len_2) {
			while (x < len_1) {
				arr[i] = arr_1[x];
				i++;
				x++;
			}
		}
	}
}
//getting minrun
int getMinrun(int N) {
	int r = 0;
	while (N >= 64) {
		r |= N & 1;
		N >>= 1;
	}
	return N + r;
}
//function to get the smallest of two numbers
template <class T>
T min(T x, T y) {
	if (x < y) {
		return x;
	}
	else {
		return y;
	}
}
//storage structure RUNs
struct RUN {
	int size = 0;
	int start = 0;
};

void TimSort(Array<int>& userArr, int N) {

	Stack<RUN> runStack;	//for storing ordered subarrays
	RUN run = {};
	run.size = 1;

	RUN X = {}, Y = {}, Z = {};
	int sizeOfStack = 0;

	int minrun = getMinrun(N);	//getting minrun

	int i = 1;
	while (i < N) {	//splitting into RUNs and ordering
		if (userArr[i - 1] <= userArr[i]) {
			while (true) {
				if (userArr[i - 1] <= userArr[i] && i < N) {
					run.size++;
					i++;
				}
				else {
					if (run.size < minrun) {
						while (run.size < minrun && i < N) {
							run.size++;
							i++;
						}
						InsertionSort(&userArr[run.start], run.size);
					}

					runStack.push(run);
					run.start = i;
					run.size = 1;
					i++;
					break;
				}
			}
		}
		if (userArr[i - 1] > userArr[i]) {
			while (true) {
				if (userArr[i - 1] > userArr[i] && i < N) {
					run.size++;
					i++;
				}
				else {
					for (int i = 0; i < (run.size) / 2; i++) {	//rearrange elements in ascending order
						userArr[i] = userArr[i] + userArr[(run.size - 1) - i];
						userArr[(run.size - 1) - i] = userArr[i] - userArr[(run.size - 1) - i];
						userArr[i] = userArr[i] - userArr[(run.size - 1) - i];
					}
					if (run.size < minrun) {
						while (run.size < minrun && i < N) {
							run.size++;
							i++;
						}
						InsertionSort(&userArr[run.start], run.size);
					}

					runStack.push(run);
					run.start = i;
					run.size = 1;
					i++;
					break;
				}
			}
		}
	}

	X = runStack.peak();
	runStack.pop();
	sizeOfStack++;

	while (!runStack.isEmpty()) {	//merge RUNs
		if (!runStack.isEmpty() && Y.size == 0) {
			Y = runStack.peak();
			runStack.pop();
			sizeOfStack++;
		}
		if (!runStack.isEmpty() && Z.size == 0) {
			Z = runStack.peak();
			runStack.pop();
			sizeOfStack++;
		}
		while ((Z.size <= X.size + Y.size || X.size >= Y.size) && sizeOfStack > 1) {
			if (sizeOfStack >= 2 && X.size >= Y.size) {
				Merge(userArr, Y.start, Y.size, X.size);
				X.start = min(X.start, Y.start);
				X.size = X.size + Y.size;

				if (Z.size != 0) {
					Y = Z;
				}
				else
				{
					break;
				}

				sizeOfStack--;

				if (!runStack.isEmpty()) {
					Z = runStack.peak();
					runStack.pop();
					sizeOfStack++;
				}
			}
			if (sizeOfStack >= 3 && Z.size <= X.size + Y.size) {
				if (X.size <= Z.size) {
					Merge(userArr, Y.start, Y.size, X.size);
					X.start = min(X.start, Y.start);
					X.size = X.size + Y.size;

					Y = Z;
					Z.size = 0;

					sizeOfStack--;

					if (!runStack.isEmpty()) {
						Z = runStack.peak();
						runStack.pop();

						sizeOfStack++;
					}
				}
				else
				{
					Merge(userArr, Z.start, Z.size, Y.size);
					Y.start = min(Y.start, Z.start);
					Y.size = Y.size + Z.size;
					Z.size = 0;

					sizeOfStack--;

					if (!runStack.isEmpty()) {
						Z = runStack.peak();
						runStack.pop();
						sizeOfStack++;
					}
				}
			}
		}
	}
}
