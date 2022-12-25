#include <iostream>
#include "Stack.h"
#include <string>
using namespace std;

//Implementation of a singly linked list

struct Node {
    int data;
    Node* next;
};

class linkedList
{
    Node* head;

public:
    linkedList()
    {
        head = NULL;
    }
    void insert(int val)
    {
        Node* newNode = new Node; //Make a new node
        newNode->data = val;
        newNode->next = NULL;

        //If list is empty, make the new node
        if (head == NULL)
            head = newNode;
        else
        {
            newNode->next = head;
            head = newNode;
        }
    }
    //Element search
    bool search(int val)
    {
        Node* temp = head;
        while (temp != NULL)
        {
            if (temp->data == val)
                return true;
            temp = temp->next;
        }
        return false;
    }
    void remove(int val)
    {
        if (head->data == val)
        {
            delete head;
            head = head->next;
            return;
        }
        // If there is only one element in the list
        if (head->next == NULL)
        {
            if (head->data == val)
            {
                delete head;
                head = NULL;
                return;
            }
            cout << "Oops! Value not found!" << endl;
            return;
        }

        Node* temp = head;
        while (temp->next != NULL)
        {
            //When node is found, delete the node and modify the pointers
            if (temp->next->data == val)
            {
                Node* tempPtr = temp->next->next;
                delete temp->next;
                temp->next = tempPtr;
                return;
            }
            temp = temp->next;
        }
        cout << "Oops! Value not found!" << endl;
    }
    void printL()
    {
        Node* temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};
//Stack implementation

Stack::Stack(int stackSize)
{
    size = stackSize;
    op = new string[size];
    top = 0;
}
Stack::~Stack()
{
    delete[] op;
}
void Stack::push(string data)
{
    if (top == size - 1)
    {
        string* opBuff = new string[size];
        for (int i = 0; i < size; ++i)
            opBuff[i] = op[i];
        delete[] op;
        int sizeBuff = size;
        size *= 2;
        op = new string[size];
        for (int i = 0; i < sizeBuff; ++i)
            op[i] = opBuff[i];
        delete[] opBuff;
    }
    op[++top] = data;
}
string Stack::pop() //Removing an element from the stack
{
    return op[top--];
}
string Stack::see()
{
    return op[top];
}
bool Stack::empty() //Stack empty check
{
    return top == 0;
}
//Priority of operations and sorting

bool inArray(const string& temp, string* arr, int operSize) {
    for (int i = 0; i < operSize; i++)
        if (arr[i] == temp)
            return true;
    return false;
}

int priorityOperation(string op)
{
    if (op == "+" || op == "-")
        return 1;
    else if (op == "*" || op == "/")
        return 2;
    else if (op == "^")
        return 3;
    else if (op == "sin" || op == "cos")
        return 4;
    else return 0;
}

bool isNumber(string num)
{
    if (num.size() == 0)
        return false;
    if (num[0] == '0')
        return false;
    for (const auto& to : num)
        if (to < '0' || to > '9')
            return false;
    return true;
}

string sort(string str)
{
    const int op = 9;
    string operators[op] = { "+", "-", "*", "/", "^", "sin", "cos", "(", ")" };
    Stack stack(10);
    Stack bracketstack(20);
    str += " ";
    string tokens = "", strOut = "";
    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] != ' ')
            tokens += str[i];
        else if (isNumber(tokens))
        {
            strOut += (tokens + " ");
            tokens = "";
        }
        else if (inArray(tokens, operators, op))
        {
            if (tokens == "(")
                stack.push(tokens);
            else if (tokens == ")")
            {
                if (!bracketstack.empty() && bracketstack.see() == ")") //check stack of brackets )( ()
                {
                    cout << "\nOh...you forgot to put the bracket on the right!\n" << endl;
                    return "";
                }
                while (!stack.empty() && stack.see() != "(") //popping elements from the stack up to the bracket
                    strOut += (stack.pop() + " ");
                if (stack.empty())
                {
                    cout << "Oh...you forgot to put the bracket on the left!" << endl;
                    return "";
                }
                bracketstack.push(stack.pop()); //send ( bracket to stack of brackets ( already there ) )
            }
            else if (stack.empty() || priorityOperation(tokens) <= priorityOperation(stack.see()))
            {
                while (!stack.empty() && priorityOperation(tokens) <= priorityOperation(stack.see()))
                    strOut += stack.pop() + " ";
                stack.push(tokens);
            }
            else
                stack.push(tokens);
            tokens = "";
        }
        else
        {
            cout << "Error! " << tokens << " isn't token. Please, try again." << endl;
            return "";
        }
    }

    while (!stack.empty())
    {
        if (stack.see() == "(")
        {
            if (bracketstack.empty() || bracketstack.see() == "(")
            {
                cout << "Oh...you forgot to put the bracket on the right! " << endl;
                return "";
            }
            else
                bracketstack.push(stack.pop());
        }
        else
            strOut += (stack.pop() + " ");
    }
    return strOut;

}
//Dynamic array implementation

template <typename T>
class dynamicArray {

private:
    int size, capacity;
    T* array;

public:

    dynamicArray(int arrCapacity) {
        size = 0;
        capacity = arrCapacity;
        if (arrCapacity != 0) {
            array = new T[arrCapacity];
        }
        else {
            array = 0;
        }
    }
    ~dynamicArray() {
        if (array)
            delete[] array;
    }
    const T& checkElement(int ind)
    {
        if ((size - 1) < ind) {

            cout << "Error! This index doesn't exist." << endl;
            return -1;
        }
        return array[ind];
    }
    int findValue(const T& val) {
        for (int i = 0; i < size; i++) {
            if (array[i] == val) {
                return i;
            }
        }
    }
    void add(int ind, const T val) {
        if (size == capacity) {
            changeSize();
        }
        if (ind >= size) {
            array[size] = val;
        }
        else if (ind < size) {
            for (int i = size - 1; i >= ind; i--) {
                array[i + 1] = array[i];
            }
            array[ind] = val;
            size++;
        }
    }
    void changeSize() {
        T* tempArr = new T[capacity];
        for (int i = 0; i < size; i++) {
            tempArr[i] = array[i];
        }
        delete[]array;
        capacity *= 2;
        array = new T[capacity];
        for (int i = 0; i < size; i++) {
            array[i] = tempArr[i];
        }
        delete[] tempArr;
    }
    void deleteArr(const int ind) {
        if (ind == (size - 1)) {
            size--;
        }
        else if (ind < (size - 1)) {
            for (int i = ind; i < (size - 1); i++) {
                array[i] = array[i + 1];
            }
        }
        size--;
    }
    int sizeArr() const {
        return size;
    }
};

int main()
{
    cout << "Hello!\nThis program shows how the Reverse Polish sort works. \nPlease enter your values:" << endl;
    system("color B5");
    string str;
    getline(cin, str);
    cout << sort(str) << endl;
    system("pause");
}