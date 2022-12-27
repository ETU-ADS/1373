#include "definition.h"

int main()
{
    BinaryTree test;
    std::cout << "The introduced binary tree : " << std::endl;
    test.parsingTree(test);
    int *data = new int[10];
    int index = 0;
    test.DFS(data, index);
    AVL example;
    for (int i = 0; i < 10; ++i) // 7!
    {
        example.insertAVL(example.returnroot(), data[i]);
    }
    std::cout << std::endl;

    std::cout << "DirectDFS(avl tree)" << std::endl;
    directDFS(example.returnroot());
    std::cout << std::endl;

    std::cout << "CentralizedDFS(avl tree)" << std::endl;
    centralizedDFS(example.returnroot());
    std::cout << std::endl;

    std::cout << "ReverseDFS(avl tree)" << std::endl;
    reverseDFS(example.returnroot());
    std::cout << std::endl;

    std::cout << "BFS(avl tree)" << std::endl;
    BFS(example.returnroot());
    std::cout << std::endl;

    //for (int i = 16; i < 25; i++)
    //{
    //    example.insertAVL(example.returnroot(), i);
    //}

    //std::cout << std::endl;
    //BFS(example.returnroot());
    //std::cout << std::endl;

    //example.deleteElement(example.returnroot(), 8);
    //example.deleteElement(example.returnroot(), 15);
    //example.deleteElement(example.returnroot(), 2);
    //example.deleteElement(example.returnroot(), 3);

    //std::cout << std::endl;
    //BFS(example.returnroot());
    //std::cout << std::endl;


    delete[] data;
    return 0;
}
