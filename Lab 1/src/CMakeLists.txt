cmake_minimum_required(VERSION 3.20)

SET (CMAKE_C_COMPILER_WORKS 1)

project(algorithms_lab1)

set(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_CXX_STANDARD 14)

add_executable(algorithms_lab1 main.cpp LinkedList.h ArrayList.h Stack.h ShuntingYard.cpp ShuntingYard.h project_tests.cpp project_tests.h)
