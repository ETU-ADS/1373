#include <iostream>
#include <string>
using namespace std;

class MyList {
public:
    class MyNode {
    public:
        int data = 0;
        MyNode* next = nullptr;
    };
    MyNode* head = nullptr;
    int size = 0;
    MyNode* end = nullptr;
    
    MyList() {
        create_list(1);
    }
    MyList(int new_size) {
        create_list(new_size);
    }
    ~MyList() {
        delete_list();
    }

    void create_list(int new_size) {
        head = new MyNode;
        MyNode* tmp = head;

        for (int i = 1; i < new_size; i++) {
            tmp->next = new MyNode;
            tmp = tmp->next;
        }
        size = new_size;
        end = tmp;
    }
    int get_size() {
        int c_size = 0;
        MyNode* tmp = head;
        while (tmp != nullptr) {
            c_size++;
            tmp = tmp->next;
        }
        return c_size;
    }
    void print_data() {
        MyNode* tmp = head;
        while (tmp != nullptr) {
            cout << tmp->data << "  ";
            tmp = tmp->next;
        }
        cout << endl;
    }
    void delete_list() {
        MyNode* tmp;
        while (head != nullptr) {
            tmp = head->next;
            delete head;
            head = tmp;
        }
    }
    void push_front(int val) {
        MyNode* tmp = head;
        head = new MyNode;
        head->next = tmp;
        head->data = val;
        size++;
    }
    void push_back(int val) {
        end->next = new MyNode;
        end = end->next;
        end->data = val;
        size++;
    }
    void add(int num, int val) {
        MyNode* tmp = head;
        if (num == 0) {
            push_front(val);
        }
        else if (num < size) {
            for (int i = 0; i < (num - 1); i++) {
                tmp = tmp->next;
            }
            MyNode* tmp2;
            tmp2 = tmp->next;
            tmp->next = new MyNode;
            tmp->next->data = val;
            tmp->next->next = tmp2;
            size++;
        }
        else if (num == size) {
            push_back(val);
        }
        else { cout << "Error! Out of the list" << endl; }
    }
    void delete_element(int num) {
        MyNode* tmp = head;
        for (int i = 0; i < num - 1; i++) {
            tmp = tmp->next;
        }
        if (num == 0) {
            head = tmp->next;
            delete tmp;
            size--;
        }
        else if (num < size - 1) {
            MyNode* tmp2 = tmp->next->next;
            delete tmp->next;
            tmp->next = tmp2;
            size--;
        }
        else if (num == size - 1) {
            delete tmp->next;
            tmp->next = nullptr;
            end = tmp;
            size--;
        }
        else { cout << "Error! Out of the list" << endl; }
    }
    int find(int val) {
        MyNode* tmp = head;
        int count = 0;
        while ((tmp != nullptr) && (val != tmp->data)) {
            tmp = tmp->next;
            count++;
        }
        if (tmp == nullptr) {
            cout << "Error! The element not found" << endl;
            count = -1;
        }
        return count;
    }
    MyNode* get_reference(int num) {
        if (num < size) {
            MyNode* tmp = head;
            for (int i = 0; i < num; i++) {
                tmp = tmp->next;
            }
            return tmp;
        }
        else { cout << "Error! Out of the List"; return nullptr; }
    }
    int& operator[](int num) {
        MyNode* tmp = head;
        if (num >= size) {
            cout << "Error! Out of the List" << endl;
            exit(0);
        }
        for (int i = 0; i < num; i++) {
            tmp = tmp->next;
        }
        return tmp->data;
    }
};

class MyVector {
public:
    int* data;
    int size;
    int capacity;
    MyVector() {
        data = nullptr;
        size = 0;
        capacity = 0;
    }
    MyVector(int newsize) {
        size = newsize;
        capacity = size * 2;
        data = new int[capacity];
    }
    ~MyVector() {
        delete[] data;
    }
    void push_back(int val) {
        if (size == 0) {
            size = 1;
            capacity = size * 2;
            data = new int[capacity];
            data[0] = val;
        }
        else {
            if (size < capacity) {
                data[size] = val;
                size++;
            }
            else {
                capacity = size * 2;
                int* tmp = data;
                data = new int[capacity];
                for (int i = 0; i < size; i++) {
                    data[i] = tmp[i];
                }
                data[size] = val;
                size++;
                delete[] tmp;
            }
        }
    }
    void add(int num, int val) {
        if (num < size) {
            if (size < capacity) {
                int* tmp = data;
                data = new int[capacity];
                for (int i = 0; i < num; i++) {
                    data[i] = tmp[i];
                }
                data[num] = val;
                size++;
                for (int i = num + 1; i < size; i++) {
                    data[i] = tmp[i - 1];
                }
                delete[] tmp;
            }
            else {
                capacity = size * 2;
                int* tmp = data;
                data = new int[capacity];
                for (int i = 0; i < num; i++) {
                    data[i] = tmp[i];
                }
                data[num] = val;
                size++;
                for (int i = num + 1; i < size; i++) {
                    data[i] = tmp[i - 1];
                }
                delete[] tmp;
            }
        }
        else if (num == size) {
            push_back(val);
        }
        else { cout << "Error! Out of the vector" << endl; }
    }
    void delete_a(int num) {
        if (num < size) {
            int* tmp = data;
            data = new int[capacity];
            for (int i = 0; i < num; i++) {
                data[i] = tmp[i];
            }
            for (int i = num + 1; i < size; i++) {
                data[i - 1] = tmp[i];
            }
            size--;
            delete[] tmp;
        }
        else { cout << "Error! Out of the vector" << endl; }
    }
    int* get_reference(int num) {
        if (num < size) {

            return (data + num);
        }
        else {
            cout << "Error! Out of the vector" << endl;
            return nullptr;
        }
    }
    int get_size() {
        return size;
    }
    void print_data() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << "  ";
        }
        cout << endl;
    }
    int find(int val) {
        int count = 0;
        while ((count < size) && (val != data[count])) {
            count++;
        }
        if (count == size) {
            cout << "Error! The element not found" << endl;
            count = -1;
        }
        return count;
    }
    int& operator[](int num) {
        if (num >= size) {
            cout << "Error! Out of the vector" << endl;
            exit(0);
        }
        return data[num];
    }
};

class MyStack {
public:
    class MyNode {
    public:
        string data;
        MyNode* next = nullptr;
        MyNode* prev = nullptr;
    };
    MyNode* head = nullptr;
    int size = 0;
    MyNode* end = nullptr;
    
    MyStack() {
    }
    ~MyStack() {
        MyNode* tmp = head;
        while (head != nullptr) {
            tmp = head->next;
            delete head;
            head = tmp;
        }
    }
    void push(string newData) {
        if (head == nullptr) {
            head = new MyNode;
            end = head;
            head->data = newData;
        }
        else {
            end->next = new MyNode;
            end->next->prev = end;
            end = end->next;
            end->data = newData;
        }
        size++;
    }
    void pop() {
        if (head != nullptr)
            if (head->next != nullptr) {
                end = end->prev;
                delete end->next;
                end->next = nullptr;
                size--;
            }
            else {
                delete head;
                head = nullptr;
                size--;
            }
        else cout << "Error! Stack is empty" << endl;
    }
    string peak() {
        if (size == 0) {
            return ("");
        }
        return end->data;
    }
    void print_data() {
        cout << "////////////////" << endl;
        MyNode* tmp = end;
        while (tmp != nullptr) {
            cout << tmp->data << endl;
            tmp = tmp->prev;
        }
        cout << "////////////////" << endl;
    }
};

class Sort_Station {
public:
    bool is_token(string token){
        int a = 0;
        if (token == "+") a++;
        if (token == "-") a++;
        if (token == "*") a++;
        if (token == "/") a++;
        if (token == "^") a++;
        if (token == "sin") a++;
        if (token == "cos") a++;
        if (token == "(") a++;
        if (token == ")") a++;
        if (token == "0") a++;
        if (token == "1") a++;
        if (token == "2") a++;
        if (token == "3") a++;
        if (token == "4") a++;
        if (token == "5") a++;
        if (token == "6") a++;
        if (token == "7") a++;
        if (token == "8") a++;
        if (token == "9") a++;
        if (a != 1) return false;
        return true;
    }
    int type(string token) {
        if ((token == "0") || (token == "1") || (token == "2") || (token == "3") || (token == "4") || (token == "5") || (token == "6") || (token == "7") || (token == "8") || (token == "9"))
            return 0; // Цифры
        if ((token == "sin") || (token == "cos"))
            return 1; // Функции
        if ((token == "+") || (token == "-"))
            return 2; // Оп. приоритет 1
        if ((token == "*") || (token == "/"))
            return 3; // Оп. приоритет 2
        if ((token == "^"))
            return 4; // Левосторонний оп.

    }
    MyStack Stack;
    
    void Sort(string newline) {
        bool is_error = 0;
        MyStack tmpStack;
        int a1=0;
        string newtoken;
        for (int i = 0; i < newline.size(); i++) {
            newtoken = "";
            if (newline[i] == ' ') {
                for (int k = a1; k < i; k++)
                    newtoken += newline[k];
                if (is_token(newtoken))
                    tmpStack.push(newtoken);
                else {
                    cout << "Error! Token '" << newtoken << "' is invalid" << endl;
                    break;
                }
                a1 = i+1;
            }
            if (i == newline.size() - 1) {
                for (int k = a1; k <= i; k++)
                    newtoken += newline[k];
                if (is_token(newtoken))
                    tmpStack.push(newtoken);
                else {
                    cout << "Error! Token '" << newtoken << "' is invalid" << endl;
                    break;
                }
                a1 = i + 1;
            }
        }
        int size = tmpStack.size;
        for (int i = 0; i < size; i++) {
            Stack.push(tmpStack.peak());
            tmpStack.pop();
        }
        
        MyStack SortStack;
        string token;
        string out;
        while (Stack.size != 0) {
            token = Stack.peak();
            Stack.pop();
            
            if (type(token) == 0)
                out += token;
            if (type(token)==1)
                SortStack.push(token);
           
            if ((type(token) == 2)|| (type(token) == 3)|| (type(token) == 4)) {
                if (type(token) == 2)
                while ((type(SortStack.peak()) == 2) ||(type(SortStack.peak()) == 3) || (type(SortStack.peak()) == 4)) {
                    out += SortStack.peak();
                    SortStack.pop();
                }
                if ((type(token)==3)||(type(token)==4))
                    while (type(SortStack.peak()) == 3) {
                        out += SortStack.peak();
                        SortStack.pop();
                    }
                SortStack.push(token);
            }
            if (token == "(")
                SortStack.push(token);
            if (token == ")") {
                while (SortStack.peak() != "(") {
                    if (SortStack.size == 0) { cout << "ERROR!" << endl; is_error = 1; break; }
                    out += SortStack.peak();
                    SortStack.pop();
                }
                SortStack.pop();
                if (type(SortStack.peak()) == 1) {
                    out += SortStack.peak();
                    SortStack.pop();
                }
            }

        }
        while (SortStack.size != 0) {
            if (SortStack.peak() == "(") { cout << "ERROR!" << endl; is_error = 1; break; }
            out += SortStack.peak();
            SortStack.pop();
        }
        if (is_error == 0)
        cout << out << endl;
    }
    
};

int main()
{
    Sort_Station Sort;
        
    string str;
    while (str != "x") {
        getline(cin, str);

        Sort.Sort(str);
    }
   
}