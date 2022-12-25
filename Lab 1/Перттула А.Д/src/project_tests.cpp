//
// Created by theta-sigma on 9/29/2022.
//

#include "project_tests.h"
#include "LinkedList.h"

void arrayListTests() {
    ArrayList<int> ar;

    int n = 4;
    for (int i = 0; i < n; i++) {
        int value = i + 1;
        ar.append(value);
        assert(ar.get(i) == value);
    }
    assert(ar.size() == n);

    for (int i = n; i > 0; i--) {
        int value = (i + 1) * 10;
        ar.insert(i, value);
        assert(ar.get(i) == value);
    }

    // [1, 20, 2, 30, 3, 40, 4, 50, x]

    int index = ar.find(0);
    assert(index == -1);

    index = ar.find(1);
    assert(index == 0);

    index = ar.find(3);
    assert(index == 4);

    index = ar.find(50);
    assert(index == 7);

    int oldSize = ar.size();
    ar.insert(8, 20);
    ar.find(20);
    assert(ar.size() == oldSize + 1);

    // [1, 20, 2, 30, 3, 40, 4, 50, 20]
    oldSize = ar.size();
    ar.remove(4);
    assert(ar.size() == oldSize - 1);

    // [1, 20, 2, 30, 40, 4, 50, 20]

    assert(ar.get(0) == 1);
    assert(ar.get(1) == 20);
    assert(ar.get(2) == 2);
    assert(ar.get(3) == 30);
    assert(ar.get(4) == 40);
    assert(ar.get(5) == 4);
    assert(ar.get(6) == 50);
    assert(ar.get(7) == 20);

    oldSize = ar.size();
    ar.remove(0);
    assert(ar.size() == oldSize - 1);

    assert(ar.get(0) == 20);
    assert(ar.get(1) == 2);
    assert(ar.get(2) == 30);
    assert(ar.get(3) == 40);
    assert(ar.get(4) == 4);
    assert(ar.get(5) == 50);
    assert(ar.get(6) == 20);

    try {
        ar.get(7);
    } catch (const std::out_of_range &e) {
        assert(true);
    } catch (...) {
        std::cout << "caught some unknown exception" << std::endl;
    }
}

void linkedListTests() {
    LinkedList<int> ll;

    int n = 4;
    for (int i = 0; i < n; i++) {
        int value = i + 1;
        ll.pushBack(value);
        assert(ll.get(i) == value);
    }
    assert(ll.size() == n);

    for (int i = n; i > 0; i--) {
        int value = (i + 1) * 10;
        ll.insert(i, value);
        assert(ll.get(i) == value);
    }

    // [1, 20, 2, 30, 3, 40, 4, 50, x]

    int index = ll.find(0);
    assert(index == -1);

    index = ll.find(1);
    assert(index == 0);

    index = ll.find(3);
    assert(index == 4);

    index = ll.find(50);
    assert(index == 7);

    int oldSize = ll.size();
    ll.insert(8, 20);
    ll.find(20);
    assert(ll.size() == oldSize + 1);

    // [1, 20, 2, 30, 3, 40, 4, 50, 20]
    oldSize = ll.size();
    ll.remove(4);
    assert(ll.size() == oldSize - 1);

    // [1, 20, 2, 30, 40, 4, 50, 20]

    assert(ll.get(0) == 1);
    assert(ll.get(1) == 20);
    assert(ll.get(2) == 2);
    assert(ll.get(3) == 30);
    assert(ll.get(4) == 40);
    assert(ll.get(5) == 4);
    assert(ll.get(6) == 50);
    assert(ll.get(7) == 20);

    oldSize = ll.size();
    ll.remove(0);
    assert(ll.size() == oldSize - 1);

    assert(ll.get(0) == 20);
    assert(ll.get(1) == 2);
    assert(ll.get(2) == 30);
    assert(ll.get(3) == 40);
    assert(ll.get(4) == 4);
    assert(ll.get(5) == 50);
    assert(ll.get(6) == 20);

    try {
        ll.get(7);
    } catch (const std::out_of_range &e) {
        assert(true);
    } catch (...) {
        std::cout << "caught some unknown exception" << std::endl;
    }
}
