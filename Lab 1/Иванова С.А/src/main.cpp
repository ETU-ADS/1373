#include <iostream>
#include <string>
using namespace std;
//Список
struct Spisok
{
    int data;
    Spisok* adr;
};

Spisok* CreateSpisok(unsigned length)
{
    Spisok* cur = 0, * next = 0;
    for (unsigned i = 1; i <= length; i++)
    {
        cur = new Spisok;
        cur->adr = next;
        next = cur;
    }
    return cur;
}
Spisok* FindItem(Spisok* beg, unsigned index, bool err_msg = true)
{
    while (beg && (index--))
        beg = beg->adr;
    if (err_msg && !beg)
        std::cout << "There is no this item" << std::endl;
    return beg;
}
Spisok* AddItem(Spisok*& beg, unsigned index)
{
    Spisok* item = new Spisok;
    if (!index || !beg)
    {
        item->adr = beg;
        beg = item;
        return item;
    }
    Spisok* prev_item = beg;
    --index;
    while (prev_item->adr && (index--))
        prev_item = prev_item->adr;
    item->adr = prev_item->adr;
    prev_item->adr = item;
    return item;
}
void DeleteSpisok(Spisok*& beg)
{
    Spisok* next;
    while (beg)
    {
        next = beg->adr;
        delete beg;
        beg = next;
    }
}
void DellByIndex(Spisok*& beg, int index)
{
    Spisok* cur, * prev;
    if (!index)
    {
        cur = beg->adr;
        delete beg;
        beg = cur;
    }
    else
    {
        cur = beg;
        while (--index)
        {
            cur = cur->adr;
        }
        prev = cur;
        cur = cur->adr;
        prev->adr = cur->adr;
        delete cur;
    }
}

//Динамический массив
class DynArr
{
private:
    int mass_size;
    int mass_capacity;
    int* mass_data;
    int* arr;

public:
    DynArr()
    {
        mass_size = 0;
        mass_capacity = 0;
        mass_data = nullptr;
    }

    DynArr(int size)
    {
        mass_size = size;
        mass_capacity = size*2;
        mass_data = new int[mass_capacity];
    }

    ~DynArr()
    {
      delete[] mass_data;
    }

    void AddIndex(int data, int index)
    {
        if (mass_size == mass_capacity)
        {
            int* arrBuff = new int[mass_capacity];
            for (int i = 0; i < mass_size; ++i)
                arrBuff[i] = arr[i];
            delete[] arr;
            mass_capacity *= 2;
            arr = new int[mass_capacity];
            for (int i = 0; i < mass_size; ++i)
                arr[i] = arrBuff[i];
            delete[] arrBuff;
        }
        if (index >= mass_size)
            arr[mass_size] = data;
        else if (index < mass_size)
        {
            int right = 0;
            while ((mass_size - right) != index)
            {
                arr[mass_size - right] = arr[mass_size - right - 1];
                ++right;
            }
            arr[index] = data;
        }
        ++mass_size;
    }
    int FindElementByIndex(int element) {
        int index = 0;
        while ((index < mass_size) && (element != mass_data[index])) {
            index++;
        }
        if (index == mass_size) {
            cout << "Элемент по данному индексу не найден" << endl;
            return -1;
        }
        return index;
    }
    void DelIndex(int index)
    {
        if (index == (mass_size - 1))
            --mass_size;
        else if (index < (mass_size - 1))
        {
            for (int i = index; i < (mass_size - 1); ++i)
                arr[i] = arr[i + 1];
        }
        else if (index > mass_size)
        {
            cout << "Индекс находится за пределами границ массива" << endl;
            exit(0);
        }
        --mass_size;
    }
};  
//Стек.
class Stack {
    string* data;
    int stack_size, top;
public:
    Stack(int size) {
        stack_size = size;
        data = new string[stack_size];
        top = 0;
    }
    ~Stack() {
        delete[] data;
    }
    void push(string element) {
        if (top == stack_size - 1) {
            string* new_data = new string[stack_size];
            for (int i = 0; i < stack_size; i++)
                new_data[i] = data[i];
            delete[] data;
            int new_size = stack_size;
            stack_size *= 2;
            data = new string[stack_size];
            for (int i = 0; i < new_size; i++)
                data[i] = new_data[i];
            delete[] new_data;
        }
        data[++top] = element;
    }
    string pop() {
        return data[top--];
    }
    string peak() {
        return data[top];
    }
    bool is_empty() {
        return top == 0;
    }
};
//Алгоритм сортировочной станции
int Priority(string op) {
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/")
        return 2;
    if (op == "^")
        return 3;
    if (op == "sin" || op == "cos")
        return 4;
    else return 0;
}
bool Operand(std::string num) {
    if (num == "1" || num == "2" || num == "3" || num == "4" || num == "5" || num == "6" || num == "7" ||num == "8" || 
        num == "9") 
    {
        return true;
    }
    else {
        return false;
    }
}

bool Operator(std::string op) {
    if (op == "*" || op == "/" || op == "+" || op == "-" || op == "^" || op == "sin" || op == "cos") 
    {
        return true;
    }
    else {
        return false;
    }
}
string FromInfixToPostfix(string stroka) {
    Stack stack(100);
    string postfix = "", strbuff = "";
    int r= 0, l = 0;
    stroka += " ";
    for (int i = 0; i < stroka.length(); i++) {
        if (stroka[i] != ' ') {
            strbuff += stroka[i];
        }
        else if (Operand(strbuff)) {
            postfix += (strbuff + " ");
            strbuff = "";
        }
        else if (Operator(strbuff)) {
            if ((Priority(strbuff) > Priority(stack.peak())) && (!stack.is_empty())) {
                stack.push(strbuff);
                strbuff = "";
            }
            else {
                while ((Priority(strbuff) <= Priority(stack.peak())) && (!stack.is_empty())) {
                    postfix += (stack.pop() + " ");
                }
                stack.push(strbuff);
                strbuff = "";
            }
        }
        else if (strbuff == "(") {
            stack.push(strbuff);
            strbuff = "";
            l++;
        }
        else if (strbuff == ")") {
            r++;
            if (l < r){
                cout << "Количество скобок разное: левых скобок меньше, чем правых" << endl;
                exit(0);
            }
            while (stack.peak() != "(") {
                postfix += (stack.pop() + " ");
            }
            stack.pop();
            strbuff = "";

        }
        else {
            cout << strbuff << " Не является токеном" << endl;
            exit(0);
        }
    }
    if (l > r) {
        cout << "Количество скобок разное: левых скобок больше, чем правых" << endl;
        exit(0);
    }
    while (!stack.is_empty()) {
        postfix += (stack.pop() + " ");
    }
    return postfix;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    string str;
    cout << "        Алгоритм сортировочной станции" << endl;
    cout << "Разрешённые символы в исходном выражении: +, -, *, /, ^, sin, cos, (, ), 0, 1, 2, 3, 4, 5, 6, 7, 8, 9" << endl;
    cout << "Введите ваше инфиксное выражение: ";
    getline(cin, str);
    cout<<"Префиксное выражение: "<< FromInfixToPostfix(str) << endl;
}