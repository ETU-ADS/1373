#include <iostream>
#include <cstdlib>
#include<ctime>

using namespace std;
#define SIZE 100

void algorythm();

// ARRAY
class Arr {
private:
    int* arr;
    int capacity;
public:
    Arr(int arrSize)
    {
        arr = new int[arrSize];
        capacity = arrSize;
    };
    ~Arr(){delete[] arr;}

    void fillArray(){
        string n;
        for(int j=0; j<capacity; j++){
            cout<<"Insert int"<<"("<<capacity-j<<" remain): ";
            cin>>n;
            bool wrongType=false;
            for (int i=0; i<n.length(); i++){
                if (isdigit(n[i]) == false){
                    cout<< "number must be integer!"<<endl;
                    j--;
                    wrongType = true;
                    break;
                }
            }
            if(wrongType==false)
                arr[j] = stoi(n);
        }
    }

    void fillRandArray(){
        for(int j=0; j<capacity; j++)
            arr[j] = rand()%20+1;
    }

    void printArray(){
        cout<<"Array: ";
        for(int j=0; j<capacity; j++)
            cout<<arr[j]<<" ";
        cout<<endl;
        cout<<"Array size: "<<capacity<<endl;
    }

    void deleteElement(int i)
    {
        if (i<0 || i>=capacity)
            cout<<"Number is out of range!"<<endl;
        else{
            int *tempArr = new int[capacity-1];
            int k = 0;
            for(int j=0; j<capacity; j++){
                if(j==i)
                    j++;
                tempArr[k]=arr[j];
                k++;
            }
        capacity--;

        arr = new int[capacity];
        for(int j=0; j<capacity; j++)
              arr[j] = tempArr[j];
        delete [] tempArr;
        }
    }

    void addElement(int i, int val)
    {
        if (i<0 || i>=capacity)
            cout<<"Number is out of range!"<<endl;
        else{
            int *tempArr = new int[capacity+1];
            int k = 0;
            for(int j=0; j<capacity; j++){
                if(j==i){
                    tempArr[k]=val;
                    k++;
                }
                tempArr[k]=arr[j];
                k++;
            }
        capacity++;

        arr = new int[capacity];
        for(int j=0; j<capacity; j++)
              arr[j] = tempArr[j];
        delete [] tempArr;
        }
    }
};

// LIST
struct Node
{
    int data;
    Node *nextNode;
};
class List
{
private:
    Node *startNode = NULL;
public:
    void addNode(int d)
    {
        Node *node = new Node;
        node->data = d;
        node->nextNode = NULL;
        if(startNode == NULL)
            startNode = node;
        else
        {
            Node *thisNode = startNode;
            while(thisNode->nextNode != NULL)
                thisNode = thisNode->nextNode;
            thisNode->nextNode = node;
        }
    }
    void printList()
    {
        Node *thisNode = startNode;
        cout<<"Current list: ";
        while(thisNode->nextNode != NULL)
        {
            cout<<thisNode->data<<" ";
            thisNode = thisNode->nextNode;
        }
        cout<<thisNode->data<<endl;
    }

    int getListSize()
    {
        Node *thisNode = startNode;
        int listSize = 0;
        while(thisNode != NULL){
            listSize+=1;
            thisNode = thisNode->nextNode;
        }
        return listSize;
    }

    void deleteNode(int i)
    {
        if(i>getListSize())
        {
            cout<<"Index is out of range!"<<endl;
        }
        else if(i==0){
            startNode = startNode->nextNode;
        }
        else{
            Node *thisNode = startNode;
            Node *newNode = startNode;
            int j = 0;
            while(j!=i-1)
            {
                j++;
                thisNode = thisNode->nextNode;
            }
            newNode = thisNode->nextNode;
            newNode = newNode->nextNode;

            thisNode->nextNode = newNode;
        }
    }
};

// STACK + Algorythm
class Stack
{

public:
    string* arr_string;
    int top;
    int capacity;


    Stack(int stackSize = SIZE)
    {
        arr_string = new string[stackSize];
        capacity = stackSize;
        top = -1;
    };
    ~Stack(){delete[] arr_string;}

    void push(string);
    string pop();
    string topElement();

    int stackSize();
    bool isEmpty();
    bool isFull();
    void printStack();
};


void Stack::push(string x)
{
    if (!isFull())
        arr_string[++top] = x;

}

string Stack::pop()
{
    if (!isEmpty())
        return arr_string[top--];
}

string Stack::topElement()
{
    if (!isEmpty()) {
        return arr_string[top];
    }
}

int Stack::stackSize() {
    return top + 1;
}

bool Stack::isEmpty() {
    return stackSize() == 0;
}

bool Stack::isFull() {
    return stackSize() == capacity;
}

void Stack::printStack(){
    cout<<"Stack: "<< endl;
    for(int i=0; i<=top; i++)
    {
        cout<<arr_string[i]<<" "<<endl;
    }
}

bool check_number(string word) {
    for (int i = 0; i < word.length(); i++)
        if (isdigit(word[i]) == false)
            return false;
    return true;
}

int operatorRank(string str)
{
    if(str=="^")
        return 3;
    if(str=="*" || str=="/")
        return 2;
    if(str=="+" || str=="-")
        return 1;
    return 0;
}

void sortString(Stack& stackOperators, string word)
{
    bool checkBranch = true;
    if(check_number(word))
            cout<<word<<" ";
        else if(word == "sin" || word == "cos")
            stackOperators.push(word);
        else if(word == "("){
            stackOperators.push(word);
        }
        else if(word == ")")
        {
            while(stackOperators.stackSize()>0 && stackOperators.topElement()!="(")
            {
                cout<<stackOperators.topElement()<<" ";
                stackOperators.pop();
            }
            if (stackOperators.stackSize()==0){
                cout<<"\nERROR! Check Your branches"<<endl;
                algorythm();
            }
            else
                stackOperators.pop();
                if(stackOperators.topElement()=="sin" || stackOperators.topElement()=="cos")
                {
                    cout<<stackOperators.topElement()<<" ";
                    stackOperators.pop();
                }
        }
        else
        {
            while(stackOperators.stackSize()>0  && operatorRank(stackOperators.topElement()) >= operatorRank(word))
            {
                cout<<stackOperators.topElement()<<" ";
                stackOperators.pop();
            }
            stackOperators.push(word);
        }
        if(checkBranch == false)
            cout<<"ERR"<<endl;
}

void algorythm()
{
    string input;
    string line;
    while(input != "q"){
        Stack stackOperators;

        cout<<"\n\nInput string with spaces (ex: 4 + 5 ^ 2 )"<<endl;
        cout<<"Or press 1 to use default example line"<<endl;
        cout<<"Press q to exit\n"<<endl;
        getline (cin>>ws, input);
        if (input == "q")
            break;
        if(input == "1")
            line = "54 + 6 / sin ( 5 ) * 5 ^ 4 - cos ( 33 + 1 )";
        else
            line = input;

        cout<<"String: "<<line<<endl;
        cout<<"Result: ";

        string word = "";
        for (auto x : line)
        {
            if (x == ' ')
                {
                  sortString(stackOperators, word);
                  word = "";
                }
            else {
              word = word + x;
            }
        }
        sortString(stackOperators, word);
        while(stackOperators.stackSize()>0)
        {
            if(stackOperators.topElement() == "("){
                cout<<"\nERROR! Check Your branches"<<endl;
                algorythm();
            }
            cout<<stackOperators.topElement()<<" ";
            stackOperators.pop();
        }
    }

}

void arrayInterface()
{
    system("cls");

    int arrSize;
    cout<<"Input size of Array"<<endl;
    cin>>arrSize;
    Arr arr(arrSize);
    int func;
    string n;
    while(func != 6){
        cout<<"\n1 - input elements manualy\n2 - input random elements\n3 - delete element\n4 - add element\n5 - print array\n6 - exit"<<endl;
        cin>>func;
        system("cls");
        switch(func)
        {
        case 1:
            arr.fillArray();
            arr.printArray();
            break;
        case 2:
            arr.fillRandArray();
            arr.printArray();
            break;
        case 3:
            arr.printArray();
            cout<<"Insert number of element to delete: ";
            cin>>n;
            if(check_number(n)== false)
            {
                cout<< "number must be integer!"<<endl;
                break;
            }
            arr.deleteElement(stoi(n)-1);
            arr.printArray();
            break;
        case 4:
            arr.printArray();
            int val;
            cout<<"Insert number of element to insert: ";
            cin>>n;
            cout<<"Insert value to insert: ";
            cin>>val;
            if(check_number(n)== false)
            {
                cout<< "number and value must be integer!"<<endl;
                break;
            }
            arr.addElement(stoi(n)-1,val);
            arr.printArray();
            break;
        case 5:
            arr.printArray();
            break;
        }
    }
}

void listInterface()
{
    system("cls");

    List testList;
    int func;
    string n;
    while(func != 6){
        cout<<"\n1 - generate random number of nodes\n2 - add node\n3 - delete node\n4 - print list\n5 - get list size\n6 - exit"<<endl;
        cin>>func;
        system("cls");
        switch(func)
        {
        case 1:
            for(int i=0; i<rand()%5+1; i++)
            {
                testList.addNode(rand()%100+1);
            }
            testList.printList();
            break;
        case 2:
            cout<<"Enter number"<<endl;
            cin>>n;
            if(check_number(n)== false)
            {
                cout<< "number must be integer!"<<endl;
                break;
            }
            testList.addNode(stoi(n));
            testList.printList();
            break;
        case 3:
            testList.printList();
            cout<<"Enter node number:"<<endl;
            cin>>n;
            if(check_number(n)== false)
            {
                cout<< "node number must be integer!"<<endl;
                break;
            }
            testList.deleteNode(stoi(n)-1);
            testList.printList();
            break;
        case 4:
            testList.printList();
            break;
        case 5:
            cout<<"Size of list: "<<testList.getListSize()<<endl;
            break;
        }
    }
}

int interface()
{
    int func;
    while(func != 4){
        system("cls");
        cout<<"1 - dynamic array example\n2 - list example\n3 - Shunting yard algorithm\n4 - exit"<<endl;
        cin>>func;
        switch(func)
        {
        case 1:
            arrayInterface();
            break;
        case 2:
            listInterface();
            break;
        case 3:
            algorythm();
            break;
        case 4:
            return 0;
        }
    }
}


int main()
{
    srand(time(NULL));
    interface();
    return 0;
}
