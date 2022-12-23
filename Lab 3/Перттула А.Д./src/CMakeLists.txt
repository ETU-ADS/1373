cmake_minimum_required(VERSION 3.23)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_executable(src main.cpp BinaryTree.cpp BinaryTree.h ArrayList.h Stack.h AvlTree.cpp AvlTree.h Queue.h LinkedList.h ui.cpp ui.h)
