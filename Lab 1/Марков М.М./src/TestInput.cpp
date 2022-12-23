#include <iostream>

#include "LinkedList.h"
#include "DynamicArray.h"
#include "Stack.h"

void tests() {
    // TESTING THE LINKEDLIST
    std::cout << "LinkedList:" << std::endl << std::endl;
    LinkedList<double> list;
    LinkedList<double> list2;

    list.add(5.0);
    list.add(2.3);
    list.add(8.6);
    list.add(7.6);
    list.add(0.9);

    list2.add(1.0);
    list2.add(2.0);
    list2.add(3.0);
    list2.add(4.0);
    list2.add(66.9);

    std::cout << "Index of finded element: " << list.find(0.6) << std::endl;
    std::cout << "Is element added by index: " << list.addByIndex(2, 43) << std::endl;
    std::cout << "Is element deleted by index: " << list.deleteElem(3) << std::endl;
    std::cout << "Size of list: " << list.length() << std::endl;
    std::cout << "Merging..." << std::endl;

    list.merge(&list2);

    std::cout << "Size of list: " << list.length() << std::endl;
    std::cout << "Element number 6: " << list[6] << std::endl;
    // out of bounds
    try {
        std::cout << "Element number 11: " << list[11] << std::endl;
    }
    catch (const char* msg) {
        std::cout << "ERROR!!! -> " << msg << std::endl;
    }

    std::cout << "Index of finded element: " << list.find(4.0) << std::endl;
    std::cout << "Is cleared: " << list.clear() << std::endl;

    std::cout << std::endl;

    // TESTING THE ARRAY
    std::cout << "DinamicArray:" << std::endl << std::endl;

    DynamicArray<double> dinArray;
    DynamicArray<double> dinArray2;

    dinArray.add(1);
    dinArray.add(2);
    dinArray.add(3);
    dinArray.add(1, 8);

    dinArray2.add(6);
    dinArray2.add(5);
    dinArray2.add(4);
    dinArray2.add(0);
    dinArray2.add(2.3);
    dinArray2.add(4.7);

    std::cout << "Is raised: " << dinArray.add(2, 9) << std::endl;
    std::cout << "Created array: ";
    for (int i = 0; i < dinArray.length(); ++i) {
        std::cout << dinArray[i] << ' ';
    }
    std::cout << std::endl;

    dinArray.deleteElem(2);

    std::cout << "Modifyied array 1: ";
    for (int i = 0; i < dinArray.length(); ++i) {
        std::cout << dinArray[i] << ' ';
    }
    std::cout << std::endl;

    std::cout << "Index of finded element: " << dinArray.find(0) << std::endl;
    std::cout << "Capacity of array: " << dinArray.getCapacity() << std::endl;
    dinArray.clear();
    std::cout << "Length of array after clearing: " << dinArray.length() << std::endl;
    dinArray.add(1);
    dinArray.add(2);
    dinArray.add(3);
    dinArray.add(1, 8);
    dinArray.merge(&dinArray2);
    std::cout << "Modifyied array 2: ";
    for (int i = 0; i < dinArray.length(); ++i) {
        std::cout << dinArray[i] << ' ';
    }
    dinArray.shrink();
    std::cout << std::endl;

    std::cout << "New capacity of array: " << dinArray.getCapacity() << std::endl;
    std::cout << "Is not data loss after resizing: " << dinArray.resize(6) << std::endl;
    std::cout << "New capacity of array after resizing: " << dinArray.getCapacity() << std::endl;
    std::cout << "Modifyied array 3: ";
    for (int i = 0; i < dinArray.length(); ++i) {
        std::cout << dinArray[i] << ' ';
    }
    std::cout << std::endl;

    dinArray.swap(1, 4);
    dinArray.swap(3, 2);
    dinArray.swap(0, 5);

    std::cout << "Modifyied array 4: ";
    for (int i = 0; i < dinArray.length(); ++i) {
        std::cout << dinArray[i] << ' ';
    }
    std::cout << std::endl;

    Stack<int> a;
    a.push(2);
    a.push(3);
    a.push(4);
    std::cout << a.peak() << std::endl;
    std::cout << a.size() << std::endl;
    a.pop();
    a.pop();
    std::cout << a.peak() << std::endl;
    std::cout << a.size() << std::endl;
    a.pop();
    a.pop();
    std::cout << a.size() << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
}