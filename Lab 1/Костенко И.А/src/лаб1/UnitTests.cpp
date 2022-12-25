#include<cassert>
#include"List.h"
void tests()
{
	//LinkedList
	LinkedList<int> linkedList = LinkedList<int>(5);
	linkedList.add(5, 2);
	assert(linkedList[2].field == 5);
	linkedList.deleteItem(0);
	assert(linkedList.size() == 5);
	assert(linkedList.find(5) == 1);
	
	//Stack
	Stack<int> stack = Stack<int>();
	stack.push(3);
	assert(stack.isEmpty() == false);
	assert(stack.peak() == 3);
	assert(stack.pop() == 3);
	assert(stack.isEmpty() == true);

	//ArrayList
	ArrayList<int> list = ArrayList<int>(5);
	list.add(5);
	assert(list[0] == 5);
	list.add(7);
	assert(list.find(7) == 1);
	assert(list.getLast() == 7);
	list.deleteItem(0);
	assert(list[0] == 7);
	

}