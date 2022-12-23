#include "Lists.h"
#include <iostream>
#include <cassert>

using namespace std;
template<typename T>
LinkedList<T>::LinkedList()
{
	head->next = nullptr;
}
template<typename T>
LinkedList<T>::LinkedList(const int count)
{

	if (count <= 0) {
		cout << "Ошибка создания списка: count <= 0" << endl;
		return;
	}
	head->next = nullptr;
	if (count == 1)
	{
		head->next = nullptr;
		return;
	}
	if (count == 2)
	{
		Item<T>* cur = new Item<T>();
		head->next = cur;
		return;
	}
	Item<T>* cur = new Item<T>();
	cur->next = nullptr;
	head->next = cur;
	for (int i = 0; i < count - 2; i++)//count-2 т.к мы уже создали head и cur
	{
		Item<T>* next = new Item<T>();
		cur->next = next;
		cur = next;
		cur->next = nullptr;
	}
}
template<typename T>
Item<T>& LinkedList<T>::operator[](int index)
{
	if (index >= size() || index < 0)
	{
		cout << "Ошибка выхода за массив" << endl;
	}
	else
	{
		unsigned counter = 0;
		Item<T>* current = head;
		while (current->next != nullptr)
		{
			if (index == counter)
			{
				return *current;
			}
			current = current->next;
			counter++;
		}
	}
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	Item<T>* current = head;
	Item<T>* next = current->next;
	while (next != nullptr)
	{
		delete current;
		current = next;
		next = next->next;
	}
	delete current;
	head = nullptr;
}

template<typename T>
bool LinkedList<T>::deleteItem(unsigned pos)
{
	if (pos >= size())
	{
		cout << "Ошибка: index больше размера" << endl;
		return false;
	}
	if (pos < 0)
	{
		cout << "Ошибка: index < 0" << endl;
		return false;
	}
	unsigned counter = 0;
	Item<T>* current = head;
	Item<T>* past = new Item<T>();
	if (pos == 0)
	{
		head = head->next;
		delete current;
		return true;
	}
	while (current->next != nullptr) {
		if (counter == pos - 1)
		{
			past = current;
		}
		if (counter == pos)
		{
			past->next = current->next;
			delete current;
			current->next = nullptr;
			current->field = 0;
			break;
		}
		current = current->next;
		counter++;
	}
	return true;
}

template<typename T>
unsigned LinkedList<T>::find(T item)
{
	unsigned counter = 0;
	Item<T>* current = head;
	if (current->field == item)
		return counter;
	while (current->next != nullptr)
	{
		if (current->field == item)
			break;
		current = current->next;
		counter++;
	}
	return counter;
}
template<typename T>
bool LinkedList<T>::add(T field, unsigned index)
{
	if (index >= size())
	{
		cout << "Ошибка: index больше размера" << endl;
		return false;
	}
	if (index < 0)
	{
		cout << "Ошибка: index < 0" << endl;
		return false;
	}
	unsigned counter = 0;
	Item<T>* current = head;
	Item<T>* newItem = new Item<T>();
	if (index == 0)
	{
		head->field = field;
		return true;
	}
	Item<T>* prev = head;
	while (current->next != nullptr)
	{
		if (counter == index - 1)
		{
			prev = current;
			newItem->next = current->next;
			prev->next = newItem;
			newItem->field = field;
			break;
		}
		current = current->next;
		counter++;
	}
	return true;
}


template<typename T>
unsigned LinkedList<T>::size()
{
	unsigned counter = 1;
	Item<T>* item = head;
	while (item->next != nullptr)
	{
		item = item->next;
		counter++;
	}
	return counter;
}
template<typename T>
void LinkedList<T>::print()
{
	Item* item = head;
	if (head == nullptr)
	{
		cout << "Список пуст!" << endl;
		return;
	}
	while (item->next != nullptr)
	{
		cout << item->field << endl;
		item = item->next;
	}
	cout << item->field;
}
template<typename T>
Stack<T>::Stack(const int count)
{
	if (count <= 0) {
		cout << "Ошибка создания списка: count <= 0" << endl;
		return;
	}
	head = new Item<T>();
	head->next = nullptr;
	if (count == 1)
	{
		head->next = nullptr;
		return;
	}
	if (count == 2)
	{
		Item<T>* cur = new Item<T>();
		head->next = cur;
		return;
	}
	Item<T>* cur = new Item<T>();
	cur->next = nullptr;
	head->next = cur;
	for (int i = 0; i < count - 2; i++)//count-2 т.к мы уже создали head и cur
	{
		Item<T>* next = new Item<T>();
		cur->next = next;
		cur = next;
		cur->next = nullptr;
	}
}
template<typename T>
Stack<T>::Stack()
{
}
template<typename T>
Stack<T>::~Stack()
{
	if (head == nullptr)
	{
		return;
	}
	Item<T>* current = head;
	Item<T>* next = current->next;
	while (next != nullptr)
	{
		delete current;
		current = next;
		next = next->next;
	}
	delete current;
	head = nullptr;
}


template<typename T>
void Stack<T>::push(T item)
{
	Item<T>* newItem = new Item<T>();
	//newItem->field = ;
	newItem->next = nullptr;
	newItem->field = item;
	newItem->next = head;
	head = newItem;
}
template<typename T>
T Stack<T>::pop()
{
	if (isEmpty())
	{
		head = nullptr;
		//return T;
	}
	Item<T>* result;
	result = head;
	if (head->next == nullptr)
	{
		head = nullptr;
		return result->field;
	}
	head = head->next;
	result->next = nullptr;
	return result->field;
}

template<typename T>
void Stack<T>::print()
{
	if (head == nullptr)
	{
		cout << "Стек пуст!" << endl;
		return;
	}
	Item<T>* item = head;
	while (item->next != nullptr)
	{
		cout << item->field;
		item = item->next;
	}
	cout << item->field;
}
template<typename T>
T Stack<T>::peak()
{
	if (isEmpty()) {
		return NULL;
	}
	return head->field;
}

template<typename T>
bool Stack<T>::isEmpty()
{
	if (head == nullptr)
		return true;
	return false;
}



template<typename T>
void ArrayList<T>::add(T field, int index)
{
	expansionArr();
	if (lastItemIndex == (maxSize - 1))
	{
		add(field);
		return;
	}
	for (int i = lastItemIndex; i > index; i--)
	{
		arr[i] = arr[i - 1];
	}
	arr[index] = field;
}

template<typename T>
void ArrayList<T>::add(T field)
{
	expansionArr();
	arr[lastItemIndex] = field;
	lastItemIndex++;
}
template<typename T>
void ArrayList<T>::deleteItem(int index)
{
	for (int i = index; i < lastItemIndex; i++)
	{
		arr[i] = arr[i + 1];
	}
	arr[lastItemIndex - 1] = 0;
}

template<typename T>
unsigned ArrayList<T>::find(T index)
{
	for (int i = 0; i < lastItemIndex; i++)
	{
		if (arr[i] == index)
		{
			return i;
		}
	}
}

template<typename T>
void ArrayList<T>::insertionSort(int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		int current = arr[i];
		int prevItem = i - 1;
		while (prevItem >= left && arr[prevItem] > current)
		{
			arr[prevItem + 1] = arr[prevItem];
			prevItem--;
		}
		arr[prevItem + 1] = current;
	}
}




template<typename T>
void ArrayList<T>::insertArray(T* buffer, int length)
{
	for (int i = 0; i < length; i++)
	{
		expansionArr();
		add(buffer[i]);
	}
}

template<typename T>
void ArrayList<T>::merge(int leftBarrier, int rightBarrier, int secondEndIndex)
{
	ArrayList<T> buffer = ArrayList<T>(secondEndIndex-leftBarrier);
	int gallopingModeFirst = 0;
	int gallopingModeSecond = 0;
	int gallopingCheckIndex = 0;
	int bufferSize = 0;
	int fIndex = leftBarrier, sIndex = rightBarrier, rIndex = 0;
	while (fIndex < rightBarrier || sIndex < secondEndIndex)
	{
		if (gallopingModeFirst == 7)
		{
			int i = 0;
			int j = 0;
			while (fIndex + (int)pow(2,i) <= rightBarrier && arr[fIndex + (int)pow(2, i)] <= arr[sIndex])
			{
				i++;
			}
			for (j = fIndex + (int)pow(2, i-1); j < rightBarrier; j++)
			{
				i = rightBarrier - 1;
				if (arr[j] > arr[sIndex])
				{
					i = j;
					break;
				}
			}
			for (int k = fIndex; k < i; k++)
			{
				buffer[rIndex] = arr[k];
				rIndex++;
				fIndex++;
			}
		}
		else
		{
			if (gallopingModeSecond == 7)
			{
				int i = 0;
				int j = 0;
				while (sIndex + (int)pow(2, i) <= secondEndIndex - 1 && arr[sIndex + (int)pow(2, i)] <= arr[fIndex])
				{
					i++;
				}
				for (j = sIndex + (int)pow(2, i - 1); j < secondEndIndex; j++)
				{
					i = secondEndIndex - 1;
					if (arr[j] > arr[fIndex])
					{
						i = j;
						break;
					}
				}
				for (int k = sIndex; k < i; k++)
				{
					buffer[rIndex] = arr[k];
					sIndex++;
					rIndex++;
				}
			}
		}
		if (fIndex == rightBarrier)
		{
			while (sIndex != secondEndIndex)
			{
				buffer[rIndex] = arr[sIndex];
				sIndex++;
				rIndex++;
			}
			break;
		}
		else
		{
			if (sIndex == secondEndIndex) {
				while (fIndex != rightBarrier)
				{

					buffer[rIndex] = arr[fIndex];
					fIndex++;
					rIndex++;
				}
				break;
			}
		}
		if (arr[fIndex] <= arr[sIndex]) {
			gallopingModeSecond = 0;
			gallopingModeFirst++;
			gallopingCheckIndex = fIndex;
			buffer[rIndex] = arr[fIndex];
			fIndex++;
		}
		else
		{
			gallopingModeFirst = 0;
			gallopingModeSecond++;
			gallopingCheckIndex = sIndex;
			buffer[rIndex] = arr[sIndex];
			sIndex++;
		}
		rIndex++;
	}
	for (int i = 0; i < secondEndIndex - leftBarrier; i++)
	{
		arr[i + leftBarrier] = buffer[i];
	}
}

template<typename T>
void ArrayList<T>::timsort()
{
	Stack<Interval> stack = Stack<Interval>();
	
	int elementsInStack = 0;
	int minRan = calculateMinRun(size());
	int length = 0;
	bool isSorted = false;
	bool isReverse = false;
	int startReverse;
	int endReverse;
	for (int i = 0; i <= size()-1; i++)
	{
		if ((length < minRan || (arr[i] < arr[i+1] || isReverse == false) || (arr[i] >= arr[i + 1] || isReverse == true)) && i + 1 != size() - 1)
		{
			if (arr[i] > arr[i + 1] && isReverse == false) {
				startReverse = i + 1;
				isReverse = true;
			}
			if (arr[i] < arr[i+1]  && isReverse == true) {
				isReverse = false;
				endReverse = i;
				for (int i = 0; i < endReverse-startReverse; i++)
				{
					T helper = arr[startReverse + i];
					arr[startReverse + i] = arr[endReverse - i];
					arr[endReverse - i] = helper;
				}
			}
			length++;
		}
		else
		{

			isSorted = true;
			Interval sf = {i-length,i+1};
			insertionSort(sf.start, sf.finish);
			stack.push(sf);
			elementsInStack++;
			if (elementsInStack >= 3)
			{
				Interval x = stack.pop(), y = stack.pop(), z = stack.pop();
				if (((z.finish-z.start) > (y.finish-y.start) + (x.finish - x.start)) && (y.finish - y.start) > (x.finish - x.start))
				{
					stack.push(z);
					stack.push(y);
					stack.push(x);
				}
				else
				{
					if ((z.finish - z.start) > (x.finish - x.start))
					{
						merge(z.start, z.finish, y.finish + 1);
						stack.push({ z.start, y.finish + 1 });
						elementsInStack--;
					}
					else
					{
						merge(y.start, y.finish, x.finish + 1);
						stack.push({ y.start, x.finish + 1 });
						elementsInStack--;
					}
				}
			}
			length = 0;
		}
	}
	Interval prev;
	if (stack.isEmpty() == false)
	{
		prev = stack.pop();
	}
	while (!stack.isEmpty())
	{
		Interval cur = stack.pop();
		merge(cur.start, cur.finish, prev.finish + 1);
		prev = {cur.start, prev.finish + 1};
	}
	print();
}

template<typename T>
int ArrayList<T>::size()
{
	return lastItemIndex;
}

template<typename T>
void ArrayList<T>::print()
{
	for (int i = 0; i < lastItemIndex; i++)
	{
		cout << arr[i] << ' ';
	}
}
template<typename T>
T ArrayList<T>::getLast()
{
	return arr[lastItemIndex - 1];
}
template<typename T>
T& ArrayList<T>::operator[](int index)
{
	assert((index >= maxSize) == false);//?
	return arr[index];
}
template<typename T>
ArrayList<T>::ArrayList()
{
	arr = new T[10];
	maxSize = 10;
}
template<typename T>
ArrayList<T>::ArrayList(int count)
{
	arr = new T[count];
	maxSize = count;
	for (int i = 0; i < maxSize; i++)
	{
		arr[i] = 0;
	}
}
template<typename T>
ArrayList<T>::~ArrayList()
{
	delete[] arr;
}
template<typename T>
void ArrayList<T>::expansionArr()
{
	if (lastItemIndex == maxSize)
	{
		int prevMaxSize = maxSize;
		maxSize = static_cast<int>(maxSize * 2);
		T* arrHelper = new T[maxSize];
		for (int i = 0; i < prevMaxSize; i++)
		{
			arrHelper[i] = arr[i];
		}
		for (int i = prevMaxSize; i < maxSize; i++)
		{
			arrHelper[i] = 0;
		}
		delete[] arr;
		arr = arrHelper;
	}
}
template<typename T>
int ArrayList<T>::calculateMinRun(int arraySize)
{
	int r = 0;
	while (arraySize >= 64) {
		r |= arraySize & 1;
		arraySize >>= 1;
	}
	return arraySize + r;
}