#include <iostream>
#include <string>

using namespace std;

struct ListEl    //Структура списка
{
	int data;
	ListEl* next;
	ListEl(int _data) : data(_data), next(nullptr) {};
};                        

struct list {
	ListEl * first;  //Указатель на первый элемент списка
	ListEl * last;  // на последний
	list() : first(nullptr), last(nullptr) {} //конструктор

	bool is_empty() {              // проверка на пустоту списка
		return first == nullptr;
	}

	void push_back(int _data) {           //Добавление элемента
		ListEl * p = new ListEl(_data);
		if (is_empty()) {
			first = p;
			last = p;
			return;
		}
		last->next = p;
		last = p;
	}

	void print() {  // Печать списка
		if (is_empty()) return;
		ListEl * p = first;
		while (p) {
			cout << p->data << "\t";
			p = p->next;
		}
		cout << endl;
		int sip = 1;
		p = first;
		while (p) {
			cout << sip << "\t";
			p = p->next;
			sip++;
		}
		cout << endl;
	}

	ListEl * operator[] (const int index) {    //Оператор перегрузки для индексации списка
		if (is_empty()) return nullptr;
		ListEl * p = first;
		for (int i = 0; i < index; i++) {
			p = p->next;
			if (!p) return nullptr;
		}
		return p;
	}

	void remove_last() {    //Удаление последнего элемента
		if (is_empty()) return;
		if (first == last) {
			ListEl * p = first;
			first = p->next;
			delete p;
		}
		ListEl * p = first;
		while (p->next != last) p = p->next;
		p->next = nullptr;
		delete last;
		last = p;
	}

	void remove(int num, list name) {   //Удаление любого элемента
		if (is_empty()) return;
		if (num == 0) {
			ListEl * p = first;
			first = p->next;
			delete p;
			return;
		}
		else if (last->next == nullptr && last->data == name[num]->data) {
			remove_last();
			return;
		}
		ListEl * back = first;
		ListEl * forward = first->next;
		while (forward && forward->data != name[num]->data) {
			forward = forward->next;
			back = back->next;
		}
		if (!forward) {
			cout << "Элемент не обнаружен" << endl;
			return;
		}
		back->next = forward->next;
		delete forward;
	}
};

struct steck    //структура стека
{
	int num;
	steck *next;
}; 

struct Stack {

	char ch; // Символ операции

	Stack *next;
};

void add(int num, steck *&box)    //Добавление элемента в стек
{
	steck *temp = new steck;
	temp->num = num;
	temp->next = box;
	box = temp;
}

void pop(steck*&box)
{
	box = box->next;
}

void show(steck *box)    //Отображаем стек

{
	steck *temp = box;
	while (temp != NULL)
	{
		cout << temp->num << "\t";
		temp = temp->next;
	}
}

void clearSteck(steck *box)   //Очищаем память
{
	while (box != NULL)
	{
		steck * temp = box->next;
		delete box;
		box = temp;
	}
}

	void push_back(int *& arr, int &size, int value) //
	{
		int * newArray = new int[size + 1];
		for (int i = 0; i < size; i++)
		{
			newArray[i] = arr[i];
		}
		newArray[size] = value;
		size++;

		delete[] arr;

		arr = newArray;
	}

	void pop_back(int *& arr, int &size)
	{
		size--;
		int * newArray = new int[size];
		for (int i = 0; i < size; i++)
		{
			newArray[i] = arr[i];
		}

		delete[] arr;

		arr = newArray;
	}

	void delete_num(int *& arr, int &size, int value)
	{
		size--;
		int * newArray = new int[size];
		for (int i = 0; i < value-1; i++)
		{
			newArray[i] = arr[i];
		}
		for (int i = value-1; i < size; i++)
		{
			newArray[i] = arr[i+1];
		}

		delete[] arr;

		arr = newArray;
	}

	
	void arr_print(int* arr, int size)
	{
		for (int i = 0; i < size; i++) {    // Заполнение массива и вывод значений его элементов

			cout << arr[i] << "\t";
		}
		cout << endl;
		for (int i = 0; i < size; i++) {   //нумерация массива

			cout << i+1 << "\t";
		}
		cout << endl;
	}
		

	Stack* InS(Stack *&box, char symb) {

		Stack *t1 = new Stack;

			t1->ch = symb;

			t1->next = box;

		return t1;
		
	}

	Stack* OutS(Stack *&box, char* symb) {

		Stack *t1 = box;

		*symb = box->ch;

		box = box->next;

		free(t1);

		return box;
	}

	int Prior(char a) {

		switch (a) {

		case '^': return 4;

		case '*': case '/': return 3;

		case '-': case '+': return 2;

		case '(': case ')': return 1;

		}

		return 0;
	}

void menu_start()
{
	cout << "1 - Односвязный список\n";
	cout << "2 - Динамический массив\n";
	cout << "3 - Стек\n";
	cout << "4 - сортировачная станция\n";
	cout << "0 - Выход\n\n";
};

void menu_list()
{
	cout << "\n1 - Создать элемент\n";
	cout << "2 - Удалить элемент\n";
	cout << "3 - Вывод списка\n";
	cout << "4 - сортировка\n";
	cout << "5 - добавить несколько элементов\n";
	cout << "6 - удалить с .. по ..\n";
	cout << "0 - Возврат\n\n";
};

void menu_dinam()
{
	cout << "\n1 - Добавить элемент\n";
	cout << "2 - Удалить элемент\n";
	cout << "3 - сортировка\n";
	cout << "4 - добавить несколько элементов\n";
	cout << "5 - удалить с .. по ..\n";
	cout << "0 - Возврат\n\n";
};

void menu_steck()
{
	cout << "\n\n1 - Добавить элемент\n";
	cout << "2 - Удалить элемент\n";
	cout << "3 - добавить несколько элементов\n";
	cout << "4 - удалить несколько элементов\n";
	cout << "0 - Возврат\n\n";
};


int main()
{
	setlocale(LC_ALL, "rus");

	list row;

	int count, check = 0, min, key, size = 0;
	const int max_row = 20;



	char sol, choice;
	menu_start();
	do 
	{
		cout << "Ответ пользователя: ";
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			menu_list();
			do
			{
				cout << "Ответ пользователя: ";
				cin >> sol;
				switch (sol)
				{

				case '1':
				{
					if (check == max_row) {
						cout << "Список полон, удалите элемент \n";
						break;
					}
					cout << "Введите значение нового элемента:  \n";
					cin >> count;
					row.push_back(count);
					check++;
					system("CLS");
					row.print();
					menu_list();
					break;
				}
				case '2':
				{
					if (check == 0) {
						system("CLS");
						cout << "Список пуст, добавьте элемент \n";

						menu_list();
						break;
					}
					cout << "Введите номер элемента для удаления:  \n";
					cin >> count;
					while (count <= 0 || count > check) {
						cout << "Некорректный ввод.\n";
						cout << "Введите номер элемента для удаления:  \n";
						cin >> count;
						cout << endl;
					}
					row.remove(count - 1, row);
					check--;
					system("CLS");
					row.print();
					menu_list();
					break;
				}
				case '3':
				{
					system("CLS");
					row.print();
					cout << "Длина списка составляет " << check << " элементов\n";
					menu_list();
					break;
				}
				case '4':
				{
					min = row[0]->data;
					for (int i = 0; i < check; i++) {
						for (int j = i + 1; j < check; j++) {
							if (row[j]->data < row[i]->data) {
								min = row[j]->data;
								row[j]->data = row[i]->data;
								row[i]->data = min;
							}
						}
					}
					system("CLS");
					row.print();
					menu_list();
					break;
				}
				case '5':
				{
					cout << "Введите количество новых элементов:  \n";
					cin >> count;
					if ((check + count) > max_row) {
						int f = check + count - max_row;
						cout << "Обнаружено " << f << " лишних элементов. Добавьте меньше или удалите.\n";
						break;
					}
					cout << "Введите значение нового элемента:  \n";
					for (int i = 0, j = 0; i < count; i++) {
						cin >> j;
						row.push_back(j);
						check++;
					};
					system("CLS");
					row.print();
					menu_list();
					break;
				}
				case '6':
				{
					int end;
					cout << "Введите номер первого элемента:  \n";
					cin >> count;
					while (count <= 0 || count > check) {
						cout << "Некорректный ввод.\n";
						cout << "Введите номер элемента для удаления:  \n";
						cin >> count;
					}
					cout << "Введите номер последнего:  \n";
					cin >> end;
					while (end > check || end <= 0 || end < count) {
						cout << "Некорректный ввод.\n";
						cout << "Введите номер элемента для удаления:  \n";
						cin >> end;
					}
					for (int i = 0; i <= (end - count); i++) {
						row.remove(count - 1, row);
						check--;
					};
					if (check == 0)
						cout << "Список пуст.\n";
					else {
						system("CLS");
						row.print();
						cout << "Длина списка составляет " << check << " элементов\n";
						menu_list();
					}

					break;
				}
				case '0':
				{
					system("CLS");
					menu_start();
					break;

				}
				default: cout << "Некорректный ввод. Используйте цифры 1-6 для управления и 0 для возврата\n" << endl;
				}
			} while (sol != '0');
			break;
		}
		case '2':
		{
			int *arr = new int[size];
			menu_dinam();
			
			do
			{
				cout << "Ответ пользователя: ";
				cin >> sol;
				switch (sol)
				{

				case '1':
				{
					cout << "Введите значение нового элемента:  \n";
					cin >> count;
					
					system("CLS");
					push_back(arr, size, count);
					arr_print(arr, size);
					menu_dinam();
					break;
				}
				case '2':
				{
					if (size == 0) {
						system("cls");
						cout << "Массив пуст, добавьте элемент \n";
						menu_dinam();
						break;
					}

					cout << "Введите номер элемента для удаления:  \n";
					cin >> count;
					while (count <= 0 || count > size) {
						cout << "Некорректный ввод.\n";
						cout << "Введите номер элемента для удаления:  \n";
						cin >> count;
						cout << endl;
					}
					if (count == size)
					{
						pop_back(arr, size);
					}
					else
					{
						delete_num(arr, size, count);
					}
					
					system("CLS");
					arr_print(arr, size);
					menu_dinam();
					break;
				}
				case '3':
				{
					min = arr[0];
					for (int i = 0; i < size; i++) {
						for (int j = i + 1; j < size; j++) {
							if (arr[j] < arr[i]) {
								min = arr[j];
								arr[j] = arr[i];
								arr[i] = min;
							}
						}
					}
					system("CLS");
					arr_print(arr, size);
					menu_dinam();
					break;
				}
				case '4':
				{
					cout << "Введите количество новых элементов:  \n";
					cin >> count;
					
					cout << "Введите значение нового элемента:  \n";
					for (int i = 0, j = 0; i < count; i++) {
						cin >> j;
						push_back(arr, size, j);
					};
					system("CLS");
					arr_print(arr, size);
					menu_dinam();
					break;
				}
				case '5':
				{
					int end;
					cout << "Введите номер первого элемента:  \n";
					cin >> count;
					while (count <= 0 || count > size) {
						cout << "Некорректный ввод.\n";
						cout << "Введите номер элемента для удаления:  \n";
						cin >> count;
					}
					cout << "Введите номер последнего:  \n";
					cin >> end;
					while (end > size || end <= 0 || end < count) {
						cout << "Некорректный ввод.\n";
						cout << "Введите номер элемента для удаления:  \n";
						cin >> end;
					}
					for (int i = 0; i <= (end - count); i++) {
						delete_num(arr, size, count);
					};
					if (size == 0)
						cout << "Список пуст.\n";
					else {
						system("CLS");
						arr_print(arr, size);
						menu_dinam();
					}

					break;
				}
				case '0':
				{
					delete[] arr;
					system("CLS");
					menu_start();
					break;

				}
				default: cout << "Некорректный ввод. Используйте цифры 1-5 для управления и 0 для возврата\n" << endl;
				}
			} while (sol != '0');
			break;
		}
		case '3':
		{
			steck *box = new steck;
			box = NULL;
			key = 0;
			menu_steck();

			do
			{
				cout << "Ответ пользователя: ";
				cin >> sol;
				switch (sol)
				{

				case '1':
				{
					cout << "Введите значение нового элемента:  \n";
					cin >> count;

					system("CLS");
					add(count, box);
					key++;
					show(box);
					menu_steck();
					break;
				}
				case '2':
				{
					if (box == nullptr) {
						system("cls");
						cout << "Стек пуст, добавьте элемент \n";
						menu_steck();
						break;
					}

					pop(box);
					key--;

					system("CLS");
					show(box);
					menu_steck();
					break;
				}
				case '3':
				{
					cout << "Введите количество новых элементов:  \n";
					cin >> count;

					cout << "Введите значение нового элемента:  \n";
					for (int i = 0, j = 0; i < count; i++) {
						cin >> j;
						add(j, box);
						key++;
					};
					system("CLS");
					show(box);
					menu_steck();
					break;
				}
				case '4':
				{
					cout << "Введите количество элементов:  \n";
					cin >> count;
					while (count > key)
					{
						cout << "В Стеке нет столько элементов" << endl; 
						cout << "Введите количество элементов:" << endl;
						cin >> count;
					}

					for (int i = 0; i < count; i++) {
						if (box == nullptr) {
							system("cls");
							cout << "Стек пуст, добавьте элемент \n";
							menu_steck();
							break;
						}
						pop(box);
					};
					system("CLS");
					show(box);
					menu_steck();
					break;
				}
				
				case '0':
				{
					clearSteck(box);

					delete box;
					system("CLS");
					menu_start();
					break;

				}
				default: cout << "Некорректный ввод. Используйте цифры 1-5 для управления и 0 для возврата\n" << endl;
				}
			} while (sol != '0');
			break;
		}
		case '4':
		{
			Stack *t,  *Op = NULL; // Стек операций Op – пуст
			char symb, in_str[30], out_str[30];
			int l = 0; // Текущие индексы для строк


			cout << "Введите выражение для алгоритма: \n";
			cin.ignore();
			cin.getline(in_str, 30, '\n');


			for (int i = 0; i < 30 && (in_str[i] != '\n'); i++)
			{
				if (in_str[i] == ')')
				{
					while (Op->ch != '(') // Если символ «)», выталкиваем из стека в выходную строку все операции
					{ 
						Op = OutS(Op, &symb); // Считываем элемент из стека
						if (!Op) symb = '\0';
						out_str[l++] = symb; // и записываем в строку Out.
					}
					t = Op; // Удаляем из стека открывающую скобку

					Op = Op->next;

					free(t);

						
				}

				//Если функция sin или cos - заносим в стек.

				if ((in_str[i] == 'c' && in_str[i + 1] == 'o' && in_str[i + 2] == 's') ||
					(in_str[i] == 's' && in_str[i + 1] == 'i' && in_str[i + 2] == 'n'))
				{
					Op = InS(Op, in_str[i+2]);
					Op = InS(Op, in_str[i + 1]);
					Op = InS(Op, in_str[i]);

					i += 2;
					continue;
				}

				// Если символ строки In – буква, заносим ее в строку Out

				if ((in_str[i] >= 'a' && in_str[i] <= 'z') || (in_str[i] >= 'A' && in_str[i] <= 'Z') ||
					(in_str[i] >= '0' && in_str[i] <= '9')) out_str[l++] = in_str[i];

		
				// Если символ – открывающая скобка, записываем ее в стек

				if (in_str[i] == '(') Op = InS(Op, in_str[i]);

				/* Если символ – знак операции, переписываем из стека в строку Out все операции с большим или равным приоритетом */

				if (in_str[i] == '+' || in_str[i] == '-' || in_str[i] == '*' || in_str[i] == '/' || in_str[i] == '^')
				{

					if ((Op != NULL) && ((Op->ch == 'c') || (Op->ch == 's')))
						for (int j = 0; j < 3; j++)
						{
							{
								Op = OutS(Op, &symb); // Считываем элемент из стека

								out_str[l++] = symb; // и записываем в строку Out.
							}
						}

					while (Op != NULL &&( Prior(Op->ch) >= Prior(in_str[i])))
					{
						
						Op = OutS(Op, &symb); // Извлекаем из стека символ Out[l++] = a; // и записываем в строку Out
						out_str[l++] = symb;

					}

					Op = InS(Op, in_str[i]); // Текущий символ – в стек

				}

			} // Конец цикла анализа входной строки

			// Если стек не пуст, переписываем все операции в выходную строку

			while (Op != NULL) {

				Op = OutS(Op, &symb);
				out_str[l++] = symb;

			}

			out_str[l] = '\0';
		



			system("CLS");

			cout << "Входная строка: ";
			cout << in_str << endl << endl;
			cout << "Выходная строка: ";
			cout << out_str << endl << endl;
			

			for (int i = 0; i < 30; i++)
			{
				out_str[i] = 0;
				in_str[i] = 0;
			}
		

			
			menu_start();
			break;
		}
		case'0':
		{
			exit(0);
		}
		default: cout << "Некорректный ввод. Используйте цифры 1-3 для управления и 0 для выхода\n" << endl;
		}

	} while (choice != 0);
		

}




