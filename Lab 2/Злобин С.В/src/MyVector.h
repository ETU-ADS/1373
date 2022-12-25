#pragma once

class MyVector{
public:
    int* data;
    int size;
    int capacity;
    MyVector();
    MyVector(int newsize);
    MyVector(const MyVector& other);
    ~MyVector();
    void push_back(int val);
    void add(int num, int val);
    void delete_a(int num);
    int* get_reference(int num);
    int get_size();
    void print_data();
    int find(int val);
    int& operator[](int num);
    void swap(int a, int b);
    void operator=(const MyVector& other);
};