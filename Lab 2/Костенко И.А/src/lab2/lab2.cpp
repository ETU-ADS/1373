#include <iostream>
#include "../lab2/List.h"

int main()
{
	int buffer[18] = { 11, 10, 12, 13, 14,15,16,17,18,1,2,3,5,101,202,55,44, 37};
	ArrayList<int> arr = ArrayList<int>();
	arr.insertArray(buffer, 18);
	arr.add(1);
	arr.add(0);
	arr.print();
	cout << "\n\n\n";
	arr.timsort();
	system("pause");
	return 0;
}

