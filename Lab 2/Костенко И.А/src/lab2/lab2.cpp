#include <iostream>
#include "../lab2/List.h"

int main()
{
	ArrayList<int> arr = ArrayList<int>();
	for (int i = 0; i < 200; i++)
	{
		int index = rand() % 100;
		arr.add(index);
	}
	arr.print();
	cout << "\n\n\n";
	arr.timsort();
	system("pause");
	return 0;
}

