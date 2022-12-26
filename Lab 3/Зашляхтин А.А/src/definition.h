#include <iostream>
#include <fstream>
#include <cstring>

struct element
{
    int data;
    element* parent;
    element* leftChild;
    element* rightChild;
};
class BinaryTree
{
private:
    element* root;
    int* out;
    int index;
public:
    BinaryTree();
    ~BinaryTree();
    void DFS(int store[], int& index);
    void parsing(char* buffer, int& start, int size);
    void parsingTree(BinaryTree& test);
    void printroot()
    {
        std::cout << root->data;
    }
};

struct AVLtree
{
    int key;
    AVLtree* left = NULL;
    AVLtree* right = NULL;
    AVLtree* parent = NULL;
    int height;
};
class AVL
{
    AVLtree* root;
public:
    AVL();
    ~AVL();
    AVLtree* returnroot();
    int height(AVLtree* temp);
    int balance(AVLtree* var);
    void RotateRight(AVLtree* rotating);
    void RotateLeft(AVLtree* rotating);
    void RotateLeftThenRight(AVLtree* rotating);
    void RotateRightThenLeft(AVLtree* rotating);
    AVLtree* search(AVLtree* var, int value);
    void insert(AVLtree* var, int value); // ¡≈« ¡¿À¿Õ—¿, Õ≈ ¿¬À
    void restoreBalance(AVLtree* var);
    void insertAVL(AVLtree* var, int value);
    void restoreRoot(AVLtree* var);
    AVLtree* min(AVLtree* var);
    AVLtree* max(AVLtree* var);
    AVLtree* successor(AVLtree* var);
    void deleteElement(AVLtree*, int value);
};

struct Stack
{
    Stack* address;
    AVLtree* node = NULL;
};
class StackClass
{
private:
    Stack* current;
    int quantity;
public:
    StackClass();
    ~StackClass();
    bool isEmpty();
    AVLtree* pop();
    void push(AVLtree* var);
    AVLtree* peek();
};

struct Queue
{
    Queue* prev = NULL;
    Queue* next = NULL;
    AVLtree* node = NULL;
};
class QueueClass
{
private:
    Queue* head;
    Queue* tail;
    int quantity;
public:
    QueueClass();
    ~QueueClass();
    bool isEmpty();
    AVLtree* pop();
    void push(AVLtree* var);
};

void visit(AVLtree* var);
void directDFS(AVLtree* var);
void centralizedDFS(AVLtree* var);
void reverseDFS(AVLtree* var);
void BFS(AVLtree* var);
